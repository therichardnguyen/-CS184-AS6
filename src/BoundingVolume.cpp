#include "BoundingVolume.h"

BoundingVolume::BoundingVolume() {
	_xmax = _ymax = _zmax = 5;
	_xmin = _ymin = _zmin = -5;
}

// build a bounding box to fit the spheres
BoundingVolume::BoundingVolume(vector<Sphere> s,unsigned int depth) {
	// find the bounds of this bounding volume
		_xmax = _ymax = _zmax = -1*numeric_limits<double>::max();
		_xmin = _ymin = _zmin = numeric_limits<double>::max();
	for(vector<Sphere>::iterator it = s.begin(); it!= s.end(); it++) {
		cout << "x " << it->xmax() << " y " << it->ymax() << " z " << it->zmax() << endl;
		_xmax = max(_xmax,it->xmax()); _xmin = min(_xmin,it->xmin());
		_ymax = max(_ymax,it->ymax()); _ymin = min(_ymin,it->ymin());
		_zmax = max(_zmax,it->zmax()); _zmin = min(_zmin,it->zmin());
	}
	
	if (depth > 0 && s.size()>1) {
		double dx, dy, dz;
		vector<Sphere> s1;
		vector<Sphere> s2;
	
		split(s, s1, s2, XAXIS);
		/*
		dx = abs(_xmax - _xmin); dy = abs(_ymax - _ymin); dz = abs(_zmax - _zmin);
	
		
		if (dx >= dz && dx >= dy) {	// if x is the longest axis
			split(s, s1, s2, XAXIS);
		} else if (dy >= dz) {		// if y is the longest axis
			split(s, s1, s2, YAXIS);
		} else {					// if z is the longest axis
			split(s, s1, s2, ZAXIS);
		}
		*/
		if (s1.size() > 0)
			_children.push_back(BoundingVolume(s1,depth-1));
		if (s2.size() > 0)
			_children.push_back(BoundingVolume(s2,depth-1));
	} else {
		
		_spheres = s;
	}
}	

// return true if this bounding box is a leaf node
bool BoundingVolume::isLeaf() {
	return _children.empty();
}			

// return true if the r intersects this bounding box
bool BoundingVolume::intersect(Ray &r) {
	// 3d coordinates for two opposite corners of the bounding volume
	vec3 maxCorner(_xmax,_ymax,_zmax);
	vec3 minCorner(_xmin,_ymin,_zmin);
	
	// positive normals for each plane
	vec3 xnorm(1,0,0);
	vec3 ynorm(0,1,0);
	vec3 znorm(0,0,1);
	
	// parametric intersections for each side of the bounding volume
	double t,x,y,z;
	double denom;
	denom = xnorm*(vec3(r.direction().normalize(),VW));
	if (denom != 0) {
		t = (xnorm*(maxCorner-vec3(r.start(),VW))) / denom;
		x = r.getPos(t)[0];
		y = r.getPos(t)[1];
		z = r.getPos(t)[2];		
		if (t>=0) {
			if (x == _xmax && y<=_ymax && y>=_ymin && z<=_zmax && z>=_zmin) { 
				return true;			
			}
		}
	} 
	denom = (xnorm)*(vec3(r.direction().normalize(),VW));
	
	if (denom != 0) {
		t = ((xnorm)*(minCorner-vec3(r.start(),VW))) / denom;
		x = r.getPos(t)[0];
		y = r.getPos(t)[1];
		z = r.getPos(t)[2];	
		if (t>=0) {
			if (x == _xmin && y<=_ymax && y>=_ymin && z<=_zmax && z>=_zmin) {
				return true;
			}
		} 
	} 
	denom = ynorm*(vec3(r.direction().normalize(),VW));
	if (denom != 0) {
		t = (ynorm*(maxCorner-vec3(r.start(),VW))) / denom;	
		x = r.getPos(t)[0];
		y = r.getPos(t)[1];
		z = r.getPos(t)[2];		
		if (t>=0) {	
			if (y == _ymax && x<=_xmax && x>=_xmin && z<=_zmax && z>=_zmin) { 
				return true; 
			}
		}
	} 
	denom = (ynorm)*(vec3(r.direction().normalize(),VW));	
	if ( denom != 0) {
		t = ((ynorm)*(minCorner-vec3(r.start(),VW))) / denom;		
		x = r.getPos(t)[0];
		y = r.getPos(t)[1];
		z = r.getPos(t)[2];		
		if (t>=0) {
			if (y == _ymin && x<=_xmax && x>=_xmin && z<=_zmax && z>=_zmin){
				return true; 
			}
		}
	} 
	denom = znorm*(vec3(r.direction().normalize(),VW));	
	if ( denom != 0) {
		t = (znorm*(maxCorner-vec3(r.start(),VW))) / denom;		
		x = r.getPos(t)[0];
		y = r.getPos(t)[1];
		z = r.getPos(t)[2];		
		if (t>=0) {
			if (z == _zmax && y<=_ymax && y>=_ymin && x<=_xmax && x>=_xmin) { 
				return true; 
			}
		}
	} 
	denom = (znorm)*(vec3(r.direction().normalize(),VW));	
	if (denom != 0) {
		t = ((znorm)*(minCorner-vec3(r.start(),VW))) / denom;		
		x = r.getPos(t)[0];
		y = r.getPos(t)[1];
		z = r.getPos(t)[2];		
		if (t>=0) {
			if (z == _zmin && y<=_ymax && y>=_ymin && x<=_xmax && x>=_xmin) {
				return true; 
			}
		}
	} 
	return false;
	
}	

// checks intersections with primatives
bool BoundingVolume::intersect(Ray & r, double & bestT, vec3 &outn, MaterialInfo &outm) {
	if (intersect(r)) {
		if (isLeaf()) {
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
		} else {
			bool rtn = false, result;
			bestT =numeric_limits<double>::infinity();
			for(vector<BoundingVolume>::iterator it=_children.begin();it!=_children.end();it++) {
				double tempT; vec3 tempn; MaterialInfo tempm;
				result = it->intersect(r,tempT,tempn,tempm);				
				if(result && tempT < bestT) {
					rtn = rtn || result;
					outn = tempn;
					outm = tempm;
					bestT = tempT;
				}
			}
			return rtn;
		}
	}
	return false;
}	

/*
void BoundingVolume::split(vector<Sphere> o, vector<Sphere> &s1, vector<Sphere> &s2, int axis) {
	vec3 centroid(0,0,0);
	if (o.size() >0) {
		for (vector<Sphere>::iterator it = o.begin(); it!= o.end(); it++) {
			centroid += it->center();
		}
		centroid *= (((double) 1)/((double) o.size()));
		for (vector<Sphere>::iterator it = o.begin(); it!= o.end(); it++) {
			if (it->center()[axis] < centroid[axis]) {
				s1.push_back(*it);
			} else {
				s2.push_back(*it);
			}
		}
	}
}
*/

void BoundingVolume::split(vector<Sphere> o, vector<Sphere> &s1, vector<Sphere> &s2, int axis) {
	vec3 centroid(0,0,0);
	if (o.size() >0) {
		for (vector<Sphere>::iterator it = o.begin(); it!= o.end(); it++) {
			centroid += it->center();
		}
		centroid *= (((double) 1)/((double) o.size()));
		int diff = numeric_limits<int>::max();
		vector<Sphere> ltemp,rtemp;
		for (axis = XAXIS;axis<=ZAXIS;axis++) {	
			ltemp.clear(); rtemp.clear();
			for (vector<Sphere>::iterator it = o.begin(); it!= o.end(); it++) {
				if (it->center()[axis] < centroid[axis]) {
					ltemp.push_back(*it);
				} else {
					rtemp.push_back(*it);
				}
			}
			if (abs(((int)ltemp.size())-((int)rtemp.size())) < diff) {
				diff = abs(((int)ltemp.size())-((int)rtemp.size()));
				s1 = ltemp; s2 = rtemp;
			}
		}
	}
}

void tabs(int level) {
    while (level-- > 0)
    {
        cout << "\t";
    }
}

void BoundingVolume::print(int level) {
	tabs(level); 
	if (!isLeaf()) {
		cout << "Box " << level << ": Has " << _children.size() << " children " << endl;
		tabs(level+1); cout << "x:[" << _xmin << ","<< _xmax << "] y:[" << _ymin << ","<< _ymax << "] z:[" << _zmin << ","<< _zmax << "]" <<  endl;
		for(vector<BoundingVolume>::iterator it = _children.begin(); it!=_children.end(); it++)
			it->print(level+1);
	}
	else {
		cout << "leaf with " << _spheres.size() << " spheres ";//" with centers ";
		//for (vector<Sphere>::iterator it = _spheres.begin(); it!=_spheres.end();it++)
		//	cout << it->center() << " , ";
	 cout << endl;
	tabs(level+1); cout << "x:[" << _xmin << ","<< _xmax << "] y:[" << _ymin << ","<< _ymax << "] z:[" << _zmin << ","<< _zmax << "]" <<  endl;
	}
}