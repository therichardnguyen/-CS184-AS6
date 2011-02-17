#include "main.h"

using namespace std;

//****************************************************
// Global Variables
//****************************************************
World * world;
Film * film;
int frameCount = 0;


// use this to multiply colors:
inline vec3 pairwiseMult(const vec3 &a, const vec3 &b) {
	return vec3(a[0]*b[0], a[1]*b[1], a[2]*b[2]);
}

//-------------------------------------------------------------------------------
// Here you raycast a single ray, calculating the color of this ray.
vec3 raycast(Ray & ray) {
	vec3 retColor(0,0,0);
	vec3 d = vec3(ray.direction().normalize(),VW);

    
	double t; vec3 n; MaterialInfo m;
	if (world->intersect(ray, t, n, m)) {
		retColor += pairwiseMult(m.color, world->getAmbientLight()) * m.k[MAT_KA];
	
		// etc
		IMPLEMENT_ME(__LINE__, __FILE__);
	}

    return retColor;
}

//-------------------------------------------------------------------------------
/// The display function
void display() {

	//Clear Buffers
    glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);					// indicate we are specifying camera transformations
	glLoadIdentity();							// make sure transformation is "zero'd"

	// Calls the raycast method on each pixel
	// sampled using the Viewport and Ray classes.
	// and stores the result using the Film class
	film->clear();
	Viewport &view = world->getViewport();
    view.resetSampler();
	vec2 point; Ray ray;
    while(view.getSample(point, ray)) {
		ray.transform(view.getViewToWorld());
        vec3 c = raycast(ray);
        film->expose(c, point);
    }
	film->show();

	//Now that we've drawn on the buffer, swap the drawing buffer and the displaying buffer.
	glutSwapBuffers();
}


//-------------------------------------------------------------------------------
/// \brief	Called when the screen gets resized.
/// This gives you the opportunity to set up all the relevant transforms.
///
void reshape(int w, int h) {
	//Set up the viewport to ignore any size change.
	Viewport &view = world->getViewport();
	glViewport(0,0,view.getW(),view.getH());

	//Set up the PROJECTION transformationstack to be a simple orthographic [-1, +1] projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, view.getW(), 0, view.getH(), 1, -1);

	//Set the MODELVIEW transformation stack to the identity.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//-------------------------------------------------------------------------------
/// Called to handle keyboard events.
void myKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
        case 's':
            film->saveFrame(); // image saving has been moved to the film class
            break;
		case 27:			// Escape key
			exit(0);
			break;
	}
}

void myMouseFunc(int button, int state, int x, int y) {
    //Your code here
}

void myMotionFunc(int x, int y) {
    //Your code here
}




//-------------------------------------------------------------------------------
/// Initialize the environment
int main(int argc,char** argv) {

	//Initialize OpenGL
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

	// Load the world
	world = new World(/*argv[1]*/);
	// Allocate film for rendering
	film = new Film(IMAGE_WIDTH, IMAGE_HEIGHT);

	//Create OpenGL Window
	glutInitWindowSize(IMAGE_WIDTH,IMAGE_HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CS184 Raycaster");

	//Register event handlers with OpenGL.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMotionFunc);
	glutPassiveMotionFunc(myMotionFunc);

	//And Go!
	glutMainLoop();
}
