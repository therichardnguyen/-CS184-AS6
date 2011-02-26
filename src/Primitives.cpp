/*
 * Primitive.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 */

#include "Primitives.h"

#include <limits>


Sphere::Sphere(vec4 center, double radius, MaterialInfo m) {
    _p = center;
    _r = radius;
	_m = m;
}

Sphere::Sphere(vec4 center, double radius, MaterialInfo m, mat4 m2w) {
    _p = center;
    _r = radius;
	_m = m;
	_modelToWorld = m2w;
	_worldToModel = m2w.inverse();
	
	
}
//Checks for intersection with the given ray
double Sphere::intersect(Ray & ray) {
	/*
	vec4 e =ray.start();
	vec4 d =ray.direction();
	
	e[VW] = 1;
	d[VW] = 0;
	
	
	if ( pow(d*(e-_p),2) - (d*d)*((e-_p)*(e-_p)-pow(_r,2)) >= 0) {
		return min(
			(-1*d*(e-_p)+sqrt(pow(d*(e-_p),2) - (d*d)*((e-_p)*(e-_p)-pow(_r,2))))/(d*d),
			(-1*d*(e-_p)-sqrt(pow(d*(e-_p),2) - (d*d)*((e-_p)*(e-_p)-pow(_r,2))))/(d*d));
	}
    return numeric_limits<double>::infinity(); //no hit!
	*/
	vec3 d(ray.direction(), VW);
	vec3 e(ray.start(), VW);
	vec3 ec = vec3(vec4(e,1)-_p, VW);
	double dec = (d * ec);
	double desc = dec*dec - (d*d)*(ec*ec - _r*_r);
	if (desc < 0) {
	    return numeric_limits<double>::infinity(); //no hit!
	}
	desc = sqrt(desc);
	double t1 = (-1*dec - desc) / (d*d);
	double t2 = (-1*dec + desc) / (d*d);
	return min(t1,t2);
}

//Calculates the normal for the given position on this sphere.
vec4 Sphere::calculateNormal(vec4 & position) {
	vec4 normal = ((position - _p) +vec4(0,0,0,1))/_r;
	normal[VW] = 0.0;
	return normal;
}
