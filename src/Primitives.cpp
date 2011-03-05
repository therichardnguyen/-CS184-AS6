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
	
	// transformation matrices
	_modelToWorld = m2w;
	_worldToModel = m2w.inverse();
	
	// bounding box matrix
	mat4 st(vec4(_r,0,0,0),vec4(0,_r,0,0),vec4(0,0,_r,0),vec4(0,0,0,-1));
	//r = _modelToWorld*st.inverse()*_modelToWorld.transpose();
	
	// maxes and mins of the bounding box for this sphere in world space
		
	/*
	x1 = (r[0][3] + sqrt(pow(r[0][3],2) - r[3][3] * r[0][0])) / (r[3][3]);
	x2 = (r[0][3] - sqrt(pow(r[0][3],2) - r[3][3] * r[0][0])) / (r[3][3]);
	y1 = (r[1][3] + sqrt(pow(r[1][3],2) - r[3][3] * r[1][1])) / (r[3][3]);
	y2 = (r[1][3] - sqrt(pow(r[1][3],2) - r[3][3] * r[1][1])) / (r[3][3]);
 	z1 = (r[2][3] + sqrt(pow(r[2][3],2) - r[3][3] * r[2][2])) / (r[3][3]);
	z2 = (r[2][3] - sqrt(pow(r[2][3],2) - r[3][3] * r[2][2])) / (r[3][3]);
	*/
	// altered center
	
	//bounding box
	vec4 c1(_r,_r,-_r,1), c2(-_r,_r,-_r,1), c3(-_r,_r,_r,1), c4(_r,_r,_r,1),
		c5(_r,-_r,-_r,1), c6(-_r,-_r,-_r,1), c7(-_r,-_r,_r,1), c8(_r,-_r,_r,1);
		
	vec4 tc1 = _modelToWorld*c1;
	vec4 tc2 = _modelToWorld*c2;
	vec4 tc3 = _modelToWorld*c3;
	vec4 tc4 = _modelToWorld*c4;
	vec4 tc5 = _modelToWorld*c5;
	vec4 tc6 = _modelToWorld*c6;
	vec4 tc7 = _modelToWorld*c7;
	vec4 tc8 = _modelToWorld*c8;
	
	x1 = max(max(max(max(max(max(max(tc1[0],tc2[0]),tc3[0]),tc4[0]),tc5[0]),tc6[0]),tc7[0]),tc8[0]);
	y1 = max(max(max(max(max(max(max(tc1[1],tc2[1]),tc3[1]),tc4[1]),tc5[1]),tc6[1]),tc7[1]),tc8[1]);
	z1 = max(max(max(max(max(max(max(tc1[2],tc2[2]),tc3[2]),tc4[2]),tc5[2]),tc6[2]),tc7[2]),tc8[2]);
	
	x2 = min(min(min(min(min(min(min(tc1[0],tc2[0]),tc3[0]),tc4[0]),tc5[0]),tc6[0]),tc7[0]),tc8[0]);
	y2 = min(min(min(min(min(min(min(tc1[1],tc2[1]),tc3[1]),tc4[1]),tc5[1]),tc6[1]),tc7[1]),tc8[1]);
	z2 = min(min(min(min(min(min(min(tc1[2],tc2[2]),tc3[2]),tc4[2]),tc5[2]),tc6[2]),tc7[2]),tc8[2]);
	
	_center = _modelToWorld * _p;
	
}
//Checks for intersection with the given ray
double Sphere::intersect(Ray & ray) {
	
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
	/*
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
	*/
}

//Calculates the normal for the given position on this sphere.
vec4 Sphere::calculateNormal(vec4 & position) {
	vec4 normal = ((position - _p) +vec4(0,0,0,1))/_r;
	normal[VW] = 0.0;
	return normal;
}


