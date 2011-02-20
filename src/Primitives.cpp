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

//Checks for intersection with the given ray
double Sphere::intersect(Ray & ray) {
	vec4 e = ray.start();
	vec4 d = ray.direction();
	if ( pow(d*(e-_p),2) - (d*d)*((e-_p)*(e-_p)-pow(_r,2)) >= 0) {
		return min(
			(-1*d*(e-_p)+sqrt(pow(d*(e-_p),2) - (d*d)*((e-_p)*(e-_p)-pow(_r,2))))/(d*d),
			(-1*d*(e-_p)-sqrt(pow(d*(e-_p),2) - (d*d)*((e-_p)*(e-_p)-pow(_r,2))))/(d*d));
	}
    return numeric_limits<double>::infinity(); //no hit!
}

//Calculates the normal for the given position on this sphere.
vec4 Sphere::calculateNormal(vec4 & position) {
	vec4 normal = ((position - _p) +vec4(0,0,0,1))/_r;
	normal[VW] = 1.0;
	return normal;
}
