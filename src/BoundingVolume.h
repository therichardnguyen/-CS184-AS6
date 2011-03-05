#ifndef BOUNDINGVOLUME_H_
#define BOUNDINGVOLUME_H_
#include "global.h"
#include "Primitives.h"

enum {XAXIS, YAXIS, ZAXIS};
class BoundingVolume {
public:
	BoundingVolume();
	BoundingVolume(vector<Sphere> s,unsigned int depth);	// build a bounding box to fit the spheres
	
	bool isLeaf();			// return true if this bounding box is a leaf node
	
	bool intersect(Ray &r);	// return true if the ray intersects this bounding box
	bool intersect(Ray & r, double & bestT, vec3 &outn, MaterialInfo &outm);	// checks intersections with primatives
	void split(vector<Sphere> o, vector<Sphere> &s1, vector<Sphere> &s2, int axis); 	// splits the spheres into the two buckets
	void print(int level);
private:
	double _xmin,_xmax,_ymin,_ymax,_zmin,_zmax;
	vector<BoundingVolume> _children;
	vector<Sphere> _spheres;
	bool leaf;
};

#endif /* BOUNDINGVOLUME_H_ */