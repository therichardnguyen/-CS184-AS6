/*
 * World.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 * (edited by jima)
 */

#include "World.h"

#include <limits>



World::World(string filename) {
	loadScene(filename);
}

World::~World() {}

bool World::intersect(Ray & r, double & bestT, vec3 &outn, MaterialInfo &outm) {
	double thisT;
	Ray w2mRay;
	bestT = numeric_limits<double>::infinity();
	for (vector<Sphere>::iterator it = _spheres.begin();it != _spheres.end();it++) {
		w2mRay = Ray(r);
		w2mRay.transform(it->w2m());
		thisT = it->intersect(w2mRay);
		if (thisT<bestT && thisT>=0){
			vec4 p = w2mRay.getPos(thisT);
			outn = vec3(it->w2m().transpose() * it->calculateNormal(p),VW);
			outn.normalize();
			outm = it->getMaterial();
			bestT = thisT;
		}
	}
				
	return bestT < numeric_limits<double>::infinity();
}

void World::RenderGroup(SceneGroup *i, mat4 t) 
{
	int ii, time = 0;
	// sphere vars
	double r;
	MaterialInfo m;
	
	// light vars
	LightInfo l;
	
	// camera vars
	CameraInfo f;
	   
	// if this is a terminal node
	if (i->getChildCount() == 0) {
		
		// if this node is a sphere
		if (i->computeSphere(r,m,time)) {
			_spheres.push_back(Sphere(vec4(0,0,0,1), r, m, t));
		} else if (i->computeLight(l)) {
			
			if (l.type == LIGHT_POINT) {
				_lights[l.type].push_back(Light(vec3(t*vec4(0,0,0,1),VW),0, l));
			}else if (l.type == LIGHT_DIRECTIONAL){
				_lights[l.type].push_back(Light(0,vec3(t*vec4(0,0,-1,0),VW), l));
			}else if (l.type == LIGHT_AMBIENT)
				_ambientLight = l.color;
				
		} else if (i->computeCamera(f)) {
			vec4 eye(0.0, 0.0, 0.0, 1.0);
		    vec4 LL(f.sides[FRUS_LEFT], f.sides[FRUS_BOTTOM], -1*f.sides[FRUS_NEAR], 1.0);
		    vec4 UL(f.sides[FRUS_LEFT], f.sides[FRUS_TOP], -1*f.sides[FRUS_NEAR], 1.0);
		    vec4 LR(f.sides[FRUS_RIGHT], f.sides[FRUS_BOTTOM], -1*f.sides[FRUS_NEAR], 1.0);
		    vec4 UR(f.sides[FRUS_RIGHT], f.sides[FRUS_TOP], -1*f.sides[FRUS_NEAR], 1.0);

		    _view = Viewport(eye, LL, UL, LR, UR, IMAGE_WIDTH, IMAGE_HEIGHT);
		}
		
	} else {
		
		// expand and traverse this node
		for(ii=0; ii<i->getChildCount();ii++) 
			RenderInstance(i->getChild(ii), t);
		
	}
	
}

void World::RenderInstance(SceneInstance *n, mat4 t)
{
	// vars for computing the transform
	mat4 nmatrix(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1));
	
	// get this instance's transform matrix
	n->computeTransform(nmatrix,0);
	
	
	// render the group that this instance is
	RenderGroup(n->getChild(),t*nmatrix); 
}

void World::loadScene(string filename) {
	// for as4, you can optionally hard-code the scene.  For as5 and as6 it must be loaded from a file.
	Scene *scene = new Scene(filename);
	RenderInstance(scene->getRoot(),mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)));
}



