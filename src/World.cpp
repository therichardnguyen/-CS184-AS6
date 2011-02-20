/*
 * World.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 * (edited by jima)
 */

#include "World.h"

#include <limits>

World::World() {
	loadScene("scene.scd");
}

World::~World() {}

bool World::intersect(Ray & r, double & bestT, vec3 &outn, MaterialInfo &outm) {
	double thisT;
	bestT = numeric_limits<double>::infinity();
	for (vector<Sphere>::iterator it = _spheres.begin();it != _spheres.end();it++) {
		thisT = it->intersect(r);
		if (thisT<bestT && thisT>=0){
			vec4 p = r.getPos(thisT);
			outn = it->calculateNormal(p);
			outm = it->getMaterial();
			bestT = thisT;
		}
	}
				
	return bestT < numeric_limits<double>::infinity();
}

void World::loadScene(string filename) {
	// for as4, you can optionally hard-code the scene.  For as5 and as6 it must be loaded from a file.
	
	vec4 eye(0.0, 0.0, 0, 1.0);
    vec4 LL(-1.0, -1.0, -3.0, 1.0);
    vec4 UL(-1.0, 1.0, -3.0, 1.0);
    vec4 LR(1.0, -1.0, -3.0, 1.0);
    vec4 UR(1.0, 1.0, -3.0, 1.0);

    _view = Viewport(eye, LL, UL, LR, UR, IMAGE_WIDTH, IMAGE_HEIGHT);

	/* LIGHTS */
	
	_lights[LIGHT_DIRECTIONAL].push_back(
							Light(0, vec3(.5,.5,-.5), 
							LightInfo(LIGHT_DIRECTIONAL, vec3(.4, .8, 1.2))));
	
	_lights[LIGHT_POINT].push_back(
							Light(vec3(0,0,-14),0,
							LightInfo(LIGHT_POINT,vec3(1.39,.2,.2))));
							
	
	_ambientLight = vec3(.5,.2,.2);
	
	/* SPHERES */
	// metal (blueish)
	
	_spheres.push_back(Sphere(vec4(-2.5,-1.5,-17.0,1.0), 2.0,
						MaterialInfo(vec3(.4, .5, .9), 
						.1, .5, .5, 150, 1)));
	
	// shiny plastic (redish)
	_spheres.push_back(Sphere(vec4(0.0,4.0,-25.0,1.0), 2.5,
						MaterialInfo(vec3(.9, .4, .5), 
						.4, .2, .5, 20.0, 0.0)));

	// chalky (greenish)
	_spheres.push_back(Sphere(vec4(1.5,-1.5,-10.0,1.0), 1.0,
						MaterialInfo(vec3(.5, .9, .4), 
						.5, .5, .3, 4, .5)));				


	// etc ...
	//IMPLEMENT_ME(__LINE__, __FILE__);
}



