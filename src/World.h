	/*
 * World.h
 *
 *  Created on: Feb 19, 2009
 *      Author: njoubert
 * (edited by jima)
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "global.h"
#include "UCB/SceneInfo.h"
#include "UCB/ParametricValue.h"
#include "UCB/Scene.h"
#include "Primitives.h"
#include "Viewport.h"
#include "BoundingVolume.h"

/**
 * The World forms a container for lights and primitives
 * in our scene.
 */
class World {
public:
    World(string filename);
    ~World();

	void loadScene(string filename);

	// tests a ray for intersection with the world, and fills in t, n, and m with info from the surface it hit
    bool intersect(Ray & r, double & t, vec3 &n, MaterialInfo &m);
	
	inline void setAmbientLight(vec3 ambient) { _ambientLight = ambient; }
	inline const vec3& getAmbientLight() { return _ambientLight; }

	inline vector<Light>::iterator getLightsBeginIterator(int type) { return _lights[type].begin(); }
    inline vector<Light>::iterator getLightsEndIterator(int type) { return _lights[type].end(); }
	inline Sphere * getSphere(int s) { return &(_spheres[s]); }
	inline Viewport& getViewport() { return _view; }
	inline void RenderGroup(SceneGroup *i, mat4 t);
	inline void RenderInstance(SceneInstance *n, mat4 t);
	void test();
	void toggleAABB() {aabbOn = !aabbOn;}
private:

    vector<Sphere> _spheres; // for now, all the geometry is spheres
	vector<Light> _lights[3]; // keep a separate array for each sort of light except ambient
	vec3 _ambientLight; // ambient lights just sum to a world-wide value
	
	Viewport _view;
	BoundingVolume _aabb;
	bool aabbOn;
};

#endif /* WORLD_H_ */

