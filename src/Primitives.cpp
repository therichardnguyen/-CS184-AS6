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

    return numeric_limits<double>::infinity(); //no hit!
}

//Calculates the normal for the given position on this sphere.
vec4 Sphere::calculateNormal(vec4 & position) {
    IMPLEMENT_ME(__LINE__, __FILE__);

	return vec4(0);
}
