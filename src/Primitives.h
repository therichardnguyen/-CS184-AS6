/*
 * Primitive.h
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 * (edited by jima)
 */

#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "global.h"
#include "UCB/SceneInfo.h"

struct Light {
	Light() {}
	Light(vec3 pos, vec3 dir, LightInfo l) : _l(l), _pos(pos), _dir(dir) {}
	
	inline const LightInfo& getLightInfo() { return _l; }
	inline const vec3& getPosition() { return _pos; }
	inline const vec3& getDirection() { return _dir; }

private:
	LightInfo _l;
	vec3 _pos, _dir;
};

class Sphere {
public:
    Sphere(vec4 center, double radius, MaterialInfo m);
	Sphere(vec4 center, double radius, MaterialInfo m, mat4 m2w);
    
    double intersect(Ray & ray);
    vec4 calculateNormal(vec4 & position);
	inline MaterialInfo& getMaterial() { return _m; }
	void setK(int type, double val) { _m.k[type] = val; }
	mat4 m2w() { return _modelToWorld; }
	mat4 w2m() { return _worldToModel; }
	vec3 center() { return vec3(_center,VW); }
	double radius() {return _r;}
	double xmax() {return max(x1,x2);}
	double xmin(){return min(x1,x2);}
	double ymax(){return max(y1,y2);}
	double ymin(){return min(y1,y2);}
	double zmax(){return max(z1,z2);}
	double zmin(){return min(z1,z2);}

private:
    vec4 _p,_center;
    double _r;
	MaterialInfo _m;

	// these won't be needed until you want to stretch the spheres:
    mat4 _modelToWorld;
    mat4 _worldToModel;

	// to calculate bounding volumes
	double x1,x2,y1,y2,z1,z2;
	//mat4 r;
};

#endif /* PRIMITIVE_H_ */
