#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;


#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
int WIDTH = 1280;
int HEIGHT = 720;
double carpositioninX = -4.0;
double carpositioninZ = 0.0;
double xc = 0.6;
double yc = 0.1;
double zc = 0.4;
double firstballposition = 0;
double secondballposition = 0.2;
double flyp = 0.0;
double thirdballposition = 0.2;
double forthballposition = 0.2;

double fifthballposition = 0.2;
double firstpowerupposition = 0.2;
double secondpowerupposition = 0.0;
double thirdpowerupposition = 0.0;
double p2 = 0.2;
bool o1 = 0;
bool o2 = 0;
bool o3 = 0;
bool o4 = 0;
bool b1 = false;
bool b2 = false;
bool b3 = false;
bool b4 = false;
bool b5 = false;
bool fl = false;
double p3 = 0;
bool gameover = false;
bool pyramid1 = false;
bool pyramid2 = false;
bool pyramid3 = false;
bool pyramid4 = false;
bool pyramid5 = false;
bool pyramid6 = false;
bool pyramid7 = false;
bool pyramid8 = false;
bool pyramid9 = false;
double pyramidpositioninY1 = 0.2;
double pyramidpositioninY2 = 0.2;
double pyramidpositioninY3 = 0.2;
double pyramidpositioninY4 = 0.2;
double pyramidpositioninY5 = 0.2;
double pyramidpositioninY6 = 0.2;
double pyramidpositioninY7 = 0.2;
double pyramidpositioninY8 = 0.2;
double pyramidpositioninY9 = 0.2;
double power1 = 0.2;
double power2 = 0.2;
double power3 = 0.2;
double box1 = 0;
double box2 = 0;
double box3 = 0;
double box4 = 0;
//double p3 = 0;
double suny = 3;
double moony = 3;
double sunx = 0.75;
double moonx = 0.75;
bool over = false;
int countball = 0;
int countobs = 0;
double carpositioninY = 0.30;
GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 1000;



class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = -7.0f, float eyeY = 1.0f, float eyeZ = 0.0f, float centerX = 100, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
	center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);


		/*gluLookAt(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z
		);*/
	}
	void looktop() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}

};

Camera camera;

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.1;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;




	case 'o':
		camera.looktop();
		break;


	case 'r':
		carpositioninX = carpositioninX + 0.2;
		//camera.rotateY(-5);
		camera.eye.x = carpositioninX;
		camera.center.x += 0.02;



	case 'f':
		fl = true;
		break;

	case 'k':
		/*cout << "ball is equal to " << countball << " ";
		cout << "   ";*/
		carpositioninX = carpositioninX + 0.2;
		camera.eye.x = carpositioninX - 5;
		camera.center.x += 0.02;
		moonx = moonx + 0.2;
		sunx = sunx + 0.2;
		//	cout << "x is equal to " << carpositioninX;
			//cout << "reem";
			//camera.moveZ(carpositioninX-0.2);
		break;

	case 'l':
		/*cout << "z is equal to " << carpositioninZ;
		cout << "       ";
		cout << "x is equal to " << carpositioninX;*/

		if (carpositioninZ <= 1.4) {

			carpositioninZ = carpositioninZ + 0.2;
			camera.moveX(-d);
		}

		if (carpositioninX >= 2 && carpositioninZ >= 0.9)                          //CHECKING FIRST BALL
		{
			firstballposition = 6;
			b1 = true;
			cout << " First ball is equal to " << b1;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

			/*if (secondballposition == 6)
			{
				countball = countball + 1;
				cout << " second ball is equal to " << countball;
			}*/


		}

		//if (carpositioninX <= 27 && carpositioninZ >= 0.2)
		//{
		//
		//	//cout << "z is equal to " << carpositioninZ;
		//	fifthballposition = 6;
		//	b5 = true;
		//	cout << " Fifth ball is equal to " << b1;
		//	/*if (fifthballposition==6)
		//	{
		//		countball = countball + 1;
		//		cout << "ball is equal to " << countball;
		//	}*/
		//
		//	
		//}
		if (carpositioninX >= 0.4 && carpositioninZ >= 0.6) {
			/*cout << "z is equal to " << carpositioninZ << " ";
			cout << "x is equal to " << carpositioninX << " ";*/
			firstpowerupposition = 6;
			carpositioninX = carpositioninX + 0.3;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}
		if (carpositioninX >= 29 && carpositioninZ >= 1.6)
		{
			//cout << "x is equal to " << carpositioninX << " ";
			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}
		if (carpositioninX >= 20 && carpositioninX <= 22 && carpositioninZ >= 0 && carpositioninZ <= 0.4)
		{
			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}
		if (carpositioninX >= 50 && carpositioninX <= 52 && carpositioninZ >= 1 && carpositioninZ <= 1.2)
		{
			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}

		if (carpositioninX >= 60 && carpositioninX <= 64 && carpositioninZ >= 1.2 && carpositioninZ <= 1.5)
		{
			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}

		if (carpositioninX >= 80 && carpositioninX <= 84 && carpositioninZ >= 0 && carpositioninZ <=0.3)
		{
			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}
		/*	if (carpositioninX >= 10.5 && carpositioninZ == 1.0)
			{
				cout << "x is equal to " << carpositioninX << " ";
				gameover = true;
			}*/
		if (carpositioninX >= 25 && carpositioninX <= 29 && carpositioninZ >= 0.6 && carpositioninZ <= 0.9) {
			/*cout << "z is equal to " << carpositioninZ << " ";
			cout << "x is equal to " << carpositioninX << " ";*/
			power1 = 15;
			carpositioninX = carpositioninX + 0.3;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}
		if (carpositioninX >= 35 && carpositioninX <= 39 && carpositioninZ <= 0.4 && carpositioninZ >= 0.0)
		{

			power3 = 15;

			carpositioninX = carpositioninX + 0.3;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

		}

		if (carpositioninX >= 25 && carpositioninX <= 29 && carpositioninZ >= 1.3 && carpositioninZ <= 1.5)
		{

			pyramidpositioninY2 = 15;

			pyramid2 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

		}

		if (carpositioninX >= 20 && carpositioninX <=24 && carpositioninZ >= 1.3 && carpositioninZ <= 1.5)
		{

			pyramidpositioninY1 = 15;

			pyramid1 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}

		if (carpositioninX >= 30 && carpositioninX <= 34 && carpositioninZ >= -0.4 && carpositioninZ <= -0.1)
		{

			pyramidpositioninY3 = 15;

			pyramid3= true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}
		if (carpositioninX >= 55 && carpositioninX <= 60 && carpositioninZ >= 0.0 && carpositioninZ <= 0.3)
		{

			pyramidpositioninY5 = 15;

			pyramid5= true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}
		if (carpositioninX >= 70 && carpositioninX <= 74 && carpositioninZ >= 1.4 && carpositioninZ <= 1.8)
		{

			pyramidpositioninY7 = 15;

			pyramid7 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}
		if (carpositioninX >=75 && carpositioninX <= 79 && carpositioninZ >= 1.4 && carpositioninZ <= 1.8)
		{

			pyramidpositioninY8 = 15;

			pyramid8 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);


		}

		if (carpositioninX >=80 && carpositioninX <= 84 && carpositioninZ >= 1.4 && carpositioninZ <= 1.8)
		{

			pyramidpositioninY9 = 15;

			pyramid9 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

		}

		
		break;
	case 'j':
		// cout << "z is equal to " << carpositioninZ; 
			if (carpositioninZ >= -1.4) {
				camera.moveX(d);
				carpositioninZ = carpositioninZ - 0.2;
			}

		if (carpositioninX >= 10 && carpositioninZ <= -1.4)
		{

			secondballposition = 6;
			b2 = true;
			cout << " second ball is equal to " << b1;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

			/*if (firstballposition == 6)
			{
				countball = countball + 1;
				cout << " first ball is equal to " << countball;
			}*/

		}

		if (carpositioninX >= 7 && carpositioninZ <= -0.1)
		{
			thirdballposition = 6;
			b3 = true;
			cout << " Third ball is equal to " << b1;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

			/*if (thirdballposition == 6)
			{
				countball = countball + 1;
				cout << " third ball is equal to " << countball;

			}*/


		}


		if (carpositioninX >= 17 && carpositioninZ <= -0.8)
		{



			forthballposition = 6;
			b4 = true;
			cout << " fourth ball is equal to " << b1;
			//if (forthballposition == 6)
			//{
			//	countball = countball + 1;
			//	cout << "ball is equal to " << countball;
			//}

		}
		if (carpositioninX >= 8.0 && carpositioninZ >= -1.2)
		{

			secondpowerupposition = 6;

			carpositioninX = carpositioninX + 0.3;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

		}

		/*	if (carpositioninZ <= -1 && carpositioninX >= 0)
			{
				gameOver();

			}*/
		
		if (carpositioninX >= 40 && carpositioninZ >= -1.5)
		{
			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}
		if (carpositioninX >= 40 && carpositioninX <= 42 && carpositioninZ <= -1.1 && carpositioninZ >=-1.3 ) {

			gameover = true;
			bool player = PlaySound("yt1s.com - Car Crash Sound Effect", NULL, SND_SYNC);

		}
	


		if (carpositioninX >= 50 && carpositioninX <= 55 && carpositioninZ >= -1.6 && carpositioninZ <= -1.4)
		{

			pyramidpositioninY4 = 15;

			pyramid4 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);
			

		}	
		if (carpositioninX >= 65 && carpositioninX <= 69 && carpositioninZ >= -1.4 && carpositioninZ <= -1.0)
		{

			pyramidpositioninY6 = 15;

			pyramid6 = true;
			bool player = PlaySound("Coin collectng green screen no copyright!", NULL, SND_SYNC);

		}
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}

void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}


class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_street;
Model_3DS model_ball;
Model_3DS model_car;
Model_3DS model_cone;
Model_3DS model_sand;
Model_3DS model_pokeball;



//level 2
Model_3DS model_pyramid;
Model_3DS model_box;
Model_3DS model_Sun;
// Textures
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void InitLightSource1()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = {1.5f, 1.5f, 0.5f, 1.5f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 4.0f, 4.0f,4.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}



void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}
//=======================================================================
// Material Configuration Function
//======================================================================

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************//

	InitLightSource();
	if (fl) {
		InitLightSource1();
	}
	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

void SpotLight(int pos) {
	/* Spot light */
	glEnable(GL_LIGHT1);
	glPushMatrix();
	GLfloat lightColor0[] = { 1.0f, 1.0f, 1.0f,0.0f }; //brigtness and color
	GLfloat lightPos0[] = { 0.75, 3.0f,-2.0f, 1.0f }; //makan el light
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 3.0);  //how much light comes out
	GLfloat spot_direction[] = { -1.0, 0.0, 0.0 }; //light bases feen
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glPopMatrix();
}
//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 
	glDisable(GL_LIGHT1);
	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -2);
	glTexCoord2f(200, 0);
	glVertex3f(700, 0, -2);
	glTexCoord2f(200, 2);
	glVertex3f(700, 0, 2);
	glTexCoord2f(0, 2);
	glVertex3f(-20, 0, 2);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glEnable(GL_LIGHT1);

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void obs() {
	glPushMatrix();
	glTranslated(0.9, 0.0, 0.55);
	glScaled(4.0, 4.2, 4.0);
	glRotated(270, 1, 0, 0);
	//glColor3f(0.4, 0.1, 0.5);
	glutSolidCone(0.06, 0.1, 15, 15);
	glPopMatrix();
}
//void gameOver() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glColor3d(1.0, 0.0, 0.0);
//	//glColor3f(1, 0, 0);
//	char* p0s[20];
//	sprintf((char*)p0s, "Game Over!", 50);
//	print(500, 300, (char*)p0s);
//
//}
void powerups() {



}
//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{


	//if (gameover == true)
	//{
	//	glutPostRedisplay();
	//	glColor3d(0.0, 1.0, 0.0);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	char* p0s[20];
	//	sprintf((char*)p0s, "Game Over!", 50);
	//	print(500, 300, (char*)p0s);
	//	glFlush();


	//}
	//else
	{


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();	//Clear Model_View Matrix
		camera.look();
		SpotLight(3);
		if (fl) {
			InitLightSource1();
		}

		GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
		GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);




		GLfloat light1Intensity[] = { 0.7, 0.7, 0.7, 1.0f };
		GLfloat light1Position[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1Intensity);


		// Draw Ground
		RenderGround();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(7, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(7, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(14, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(14, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(-3, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(-3, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(17, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();


		// Draw Tree Model
		glPushMatrix();
		glTranslatef(17, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();




		// Draw Tree Model
		glPushMatrix();
		glTranslatef(19, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(19, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(22, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(25, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();


		// Draw Tree Model
		glPushMatrix();
		glTranslatef(30, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();


		// Draw Tree Model
		glPushMatrix();
		glTranslatef(30, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(35, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();


		// Draw Tree Model
		glPushMatrix();
		glTranslatef(35, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(40, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(45, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(45, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();





		// Draw Tree Model
		glPushMatrix();
		glTranslatef(50, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(55, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();




		// Draw Tree Model
		glPushMatrix();
		glTranslatef(55, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(50, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(40, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(30, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();


		// Draw Tree Model
		glPushMatrix();
		glTranslatef(25, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();



		// Draw Tree Model
		glPushMatrix();
		glTranslatef(22, 0, -2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();


		// Draw Tree Model
		glPushMatrix();
		glTranslatef(10, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(7, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(5, 0, 2);
		glScalef(0.1, 0.1, 0.1);
		model_tree.Draw();
		glPopMatrix();

		// Draw Car Model
		glPushMatrix();

		glTranslatef(carpositioninX, carpositioninY, carpositioninZ);

		glScalef(0.03, 0.03, 0.03);
		glRotatef(90.f, 0, 1, 0);
		// glScalef(0.1, 0.1, 0.1); //
		model_car.Draw();
		glPopMatrix();

		// Draw house Model
		glPushMatrix();
		glTranslatef(2, 0, -2.3);
		glScalef(0.2, 0.2, 0.2);
		glRotatef(90.f, 1, 0, 0);
		model_house.Draw();
		glPopMatrix();

		// Draw house Model
		glPushMatrix();
		glTranslatef(2, 0, 2.3);
		glScalef(0.2, 0.2, 0.2);
		glRotatef(90.f, 1, 0, 0);
		model_house.Draw();
		glPopMatrix();






		glPushMatrix();
		//glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glTranslated(0.4, firstpowerupposition, 0.6);
		glScaled(3.2, 3.5, 3.2);
		glRotated(0, 0, 0, 1);

		glRotated(0, 0, 0, 1);

		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.01, 0.06, 30, 30);
		glPopMatrix();


		glPushMatrix();
		glTranslated(8.0, secondpowerupposition, -1.2);
		glScaled(3.2, 3.5, 3.2);
		glRotated(0, 0, 0, 1);

		glRotated(0, 0, 0, 1);

		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.01, 0.06, 30, 30);
		glPopMatrix();

		/*glPushMatrix();
		glTranslated(25.0, thirdpowerupposition, 0.0);
		powerups();
		glPopMatrix();*/

		

		// Draw ball Model
		glPushMatrix();
		glTranslatef(10, secondballposition, -1.4);
		glScalef(0.1, 0.1, 0.1);
		model_ball.Draw();
		glPopMatrix();



		//// Draw ball Model
		//glPushMatrix();
		//glTranslatef(27, fifthballposition, 0.2);
		//glScalef(0.1, 0.1, 0.1);
		//model_ball.Draw();
		//glPopMatrix();




		// Draw ball Model
		glPushMatrix();
		glTranslatef(17, forthballposition, -0.8);
		glScalef(0.1, 0.1, 0.1);
		model_ball.Draw();
		glPopMatrix();

		// Draw ball Model
		glPushMatrix();
		glTranslatef(7, thirdballposition, -0.1);
		glScalef(0.1, 0.1, 0.1);
		model_ball.Draw();
		glPopMatrix();

		// Draw ball Model
		glPushMatrix();
		glTranslatef(2, firstballposition, 1.3);
		glScalef(0.1, 0.1, 0.1);
		model_ball.Draw();
		glPopMatrix();

		//sky box
		glPushMatrix();

		// draw streetlight
		glPushMatrix();
		

		//glColor3f(0, 1, 0);

		glTranslated(0.8, 0.0,  -2.0);
		glScaled(0.5, 0.5, 0.1);

		drawTableLeg(0.1, 1.0);
		glPopMatrix();

		glPushMatrix();
		

		//glColor3f(0, 0, 1);

		glTranslated(0.8, 0.4, -2.0);
		glScaled(0.2, 1.8, 0.3);

		drawTableLeg(0.5, 0.08);
		glPopMatrix();

		glPushMatrix();
		//glColor3f(1.0f, 0.0f, 0.0f);
		
		glTranslated(0.75, 0.4, -2.0);
		glutSolidSphere(0.02, 15, 15);
		
		glPopMatrix();


		glPushMatrix();
		//glColor3f(0.0f, 1.0f, 0.0f);
		
		glTranslated(0.75, 0.5, -2.0);
		glutSolidSphere(0.02, 15, 15);
		
		glPopMatrix();

		// draw streetlight
		glPushMatrix();


		//glColor3f(0, 1, 0);

		glTranslated(0.8, 0.0,2.0);
		glScaled(0.5, 0.5, 0.1);

		drawTableLeg(0.1, 1.0);
		glPopMatrix();

		glPushMatrix();


		//glColor3f(0, 0, 1);

		glTranslated(0.8, 0.4, 2.0);
		glScaled(0.2, 1.8, 0.3);

		drawTableLeg(0.5, 0.08);
		glPopMatrix();

		glPushMatrix();
		//glColor3f(1.0f, 0.0f, 0.0f);

		glTranslated(0.75, 0.4,2.0);
		glutSolidSphere(0.02, 15, 15);

		glPopMatrix();


		glPushMatrix();
		//glColor3f(0.0f, 1.0f, 0.0f);

		glTranslated(0.75, 0.5, 2.0);
		glutSolidSphere(0.02, 15, 15);

		glPopMatrix();


		// Draw obs Model
		glPushMatrix();
		glTranslated(40.0, flyp, -1.5);
		glScaled(0.01, 0.05, 0.05);
		model_pyramid.Draw();
		glPopMatrix();

		// Draw obs Model
		glPushMatrix();
		glTranslated(30.0, flyp, 1.6);
		glScaled(0.01, 0.05, 0.05);
		model_pyramid.Draw();
		glPopMatrix();


		// Draw obs Model
		glPushMatrix();
		glTranslated(20.0, flyp, 0.0);
		glScaled(0.01, 0.05, 0.05);
		model_pyramid.Draw();
		glPopMatrix();

		// Draw obs Model
		glPushMatrix();
		glTranslated(10.0, flyp, 1.0);
		glScaled(0.01, 0.05, 0.05);
		model_pyramid.Draw();
		glPopMatrix();

		//Draw moon
		glPushMatrix();

		glTranslated(moonx, moony, -2.0);
		glutSolidSphere(0.3, 20, 20);

		glPopMatrix();


		//glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", 50);
		print(500, 300, (char*)p0s);


		GLUquadricObj* qobj;
		qobj = gluNewQuadric();
		glTranslated(50, 0, 0);
		glRotated(90, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, tex);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 100, 100, 100);
		gluDeleteQuadric(qobj);


		glPopMatrix();

		if (b1 && b2 && b3 && b4) {

		//	glClear(GL_COLOR_BUFFER_BIT);
			tex_ground.Load("Textures/street.bmp");

			loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
			flyp = 15;
			moony = 15;
			// Draw Tree Model
			glPushMatrix();
			glTranslatef(7, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(7, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();


			// Draw Tree Model
			glPushMatrix();
			glTranslatef(35, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(35, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();


			// Draw Tree Model
			glPushMatrix();
			glTranslatef(45, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(45, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();
			// Draw Tree Model
			glPushMatrix();
			glTranslatef(55, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(60, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();



			// Draw Tree Model
			glPushMatrix();
			glTranslatef(60, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();


			// Draw Tree Model
			glPushMatrix();
			glTranslatef(65, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(65, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(55, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();



			// Draw Tree Model
			glPushMatrix();
			glTranslatef(14, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(14, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(-3, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(-3, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(17, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();


			// Draw Tree Model
			glPushMatrix();
			glTranslatef(17, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();




			// Draw Tree Model
			glPushMatrix();
			glTranslatef(19, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();



			// Draw Tree Model
			glPushMatrix();
			glTranslatef(19, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();



			// Draw Tree Model
			glPushMatrix();
			glTranslatef(22, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();



			// Draw Tree Model
			glPushMatrix();
			glTranslatef(25, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();


			// Draw Tree Model
			glPushMatrix();
			glTranslatef(25, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();



			// Draw Tree Model
			glPushMatrix();
			glTranslatef(22, 0, -2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();


			// Draw Tree Model
			glPushMatrix();
			glTranslatef(10, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(7, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			// Draw Tree Model
			glPushMatrix();
			glTranslatef(5, 0, 2);
			glScalef(0.1, 0.1, 0.1);
			model_tree.Draw();
			glPopMatrix();

			//// Draw Car Model
			//glPushMatrix();

			//glTranslatef(carpositioninX, 0.3, carpositioninZ);

			//glScalef(0.03, 0.03, 0.03);
			//glRotatef(90.f, 0, 1, 0);
			//// glScalef(0.1, 0.1, 0.1); //
			//model_car.Draw();
			//glPopMatrix();

			// Draw house Model
			glPushMatrix();
			glTranslatef(70, 0, -2.3);
			glScalef(0.2, 0.2, 0.2);
			glRotatef(90.f, 1, 0, 0);
			model_house.Draw();
			glPopMatrix();

			//// Draw house Model
			glPushMatrix();
			glTranslatef(70, 0, 2.3);
			glScalef(0.2, 0.2, 0.2);
			glRotatef(90.f, 1, 0, 0);
			model_house.Draw();
			glPopMatrix();




			////first powerup
			glPushMatrix();
			//glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
			glTranslated(25.0, power1, 0.6);
			glScaled(2.2, 2.0, 2.2);
			glRotated(0, 0, 0, 1);

			glRotated(0, 0, 0, 1);

			glRotatef(0, 1, 0, 0);
			glutSolidTeapot(0.08);
			glPopMatrix();





			////third powerup
			glPushMatrix();
			glTranslated(35.0, power3, 0.0);
			//glTranslated(0.4, 0.2, 0.6);
			glScaled(2.2, 2.0, 2.2);
			glRotated(0, 0, 0, 1);

			glRotated(0, 0, 0, 1);

			glRotatef(0, 1, 0, 0);
			glutSolidTeapot(0.08);
			glPopMatrix();
			glPopMatrix();





			//// Draw ball Model


			////// Draw ball Model
			glPushMatrix();
			glTranslatef(20, pyramidpositioninY1, 1.3);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();


			////// Draw ball Model
			glPushMatrix();
			glTranslatef(25, pyramidpositioninY2, 1.3);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();

			//////glPushMatrix();
			//glTranslatef(30, pyramidpositioninY3, -0.1);
			//glScalef(0.025, 0.025, 0.025);
			//model_pyramid.Draw();
			//glPopMatrix();

			////// Draw ball Model
			glPushMatrix();
			glTranslatef(50, pyramidpositioninY4, -1.4);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();

			////// Draw ball Model
			glPushMatrix();
			glTranslatef(55, pyramidpositioninY5, 0.0);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();


			////// Draw ball Model
			glPushMatrix();
			glTranslatef(65, pyramidpositioninY6, -1.0);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();


			////// Draw ball Model
			glPushMatrix();
			glTranslatef(70, pyramidpositioninY7, 1.4);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();

			////// Draw ball Model
			glPushMatrix();
			glTranslatef(75, pyramidpositioninY8, 1.4);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();

			////// Draw ball Model
			glPushMatrix();
			glTranslatef(80, pyramidpositioninY9, 1.4);
			glScalef(0.025, 0.025, 0.025);
			model_pyramid.Draw();
			glPopMatrix();


			////sky box
			//glPushMatrix();


			//// Draw obs Model
			glPushMatrix();
			glTranslated(40.0, box1, -1.0);
			glScaled(0.02, 0.02, 0.02);
			model_box.Draw();
			glPopMatrix();



			//// Draw Sun Model
			//glPushMatrix();
			//glTranslatef(0.0, 0, -1.0);
			//glScaled(0.02, 0.02, 0.02);
			//model_Sun.Draw();
			//glPopMatrix();


			// Draw obs Model
			glPushMatrix();
			glTranslated(50.0, box2, 1);
			glScaled(0.02, 0.02, 0.02);
			model_box.Draw();
			glPopMatrix();

			glPushMatrix();

			glTranslated(sunx, suny, -2.0);
			glutSolidSphere(0.3, 20, 20);

			glPopMatrix();

			////// Draw obs Model
			glPushMatrix();
			glTranslated(40.0, box3, 1.2);
			glScaled(0.02, 0.02, 0.02);
			model_box.Draw();
			glPopMatrix();

			//// Draw obs Model
			glPushMatrix();
			glTranslated(80.0, box4, 0.0);
			glScaled(0.02, 0.02, 0.02);
			model_box.Draw();
			glPopMatrix();



			/*tex_ground.Load("Textures/sand.bmp");
			loadBMP(&tex, "Textures/nightsky.bmp", true);*/
			//glClearColor(0.0, 1.0, 0.0, 0.0);
			glColor3f(1, 0.0, 0);
			char* p0s[20];
			sprintf((char*)p0s, "Game over", 50);
			print(90, 285, (char*)p0s);
			glFlush();
		}

		if (gameover == true)
		{
			glClearColor(1.0, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			glFlush();
		}

		glFlush();



		glutSwapBuffers();
	}


}


//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light1_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
		carpositioninY = 0.5;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_car.Load("Models/car/car.3ds");
	model_ball.Load("Models/ball/ball.3ds");
	model_cone.Load("Models/cone/cone.3ds");
	model_pokeball.Load("Models/pokeball/pokeball.3ds");
	model_pyramid.Load("Models/pyramid/pyramid.3ds");
	
	model_box.Load("Models/box/box.3ds");
	model_Sun.Load("Models/Sun/Sun.3ds");
	tex_ground.Load("Textures/sand.bmp");
	loadBMP(&tex, "Textures/nightsky.bmp", true);
	// Loading texture files
	if (b1 && b2 && b3 && b4)
	{
		tex_ground.Load("Textures/street.bmp");

		loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	 }
	
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();
	SpotLight(3);
	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}