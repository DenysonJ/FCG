
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include "dSFMT.h"

const int LENGTH_GROUND {500};

using std::vector;

vector< vector < GLfloat >> matriz_ground;
GLdouble eyex=5.0, eyey=5.0, eyez=5.0;
GLfloat rotate_angle =1;
GLfloat CAMERASPEED = 0.03f;
GLfloat view_x, view_z;


void setEyePoint(void)
{
	eyex = LENGTH_GROUND/2.0; eyez = LENGTH_GROUND/2.0;
	eyey = matriz_ground[eyex][eyez] + 2.0;
	return;
}	

void setMatrixRandom(int lenght_matrix, vector <vector <GLfloat> > & matrix)
{
	dsfmt_t dsfmt;

	dsfmt_init_gen_rand(&dsfmt, time(NULL));//initialize the random generator with time(NULL) like seed

	for (int count = 0; count < lenght_matrix; ++count)
	{
		vector <GLfloat> temp;

		for (int count2 = 0; count2 < lenght_matrix; ++count2)
		{
			//std::cout << count << "\t" << count2 << std::endl;
			temp.push_back(dsfmt_genrand_close_open(&dsfmt)); //generates a pseudorandom number between [0,1)
			//std::cout << temp.at(count2) << " "; 
		}
		//std::cout << std::endl;

		matrix.push_back(temp);
	}
}


/*
void CCamera::Move_Camera(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector
	
	// forward positive cameraspeed and backward negative -cameraspeed.
	mPos.x  = mPos.x  + vVector.x * speed;
	mPos.z  = mPos.z  + vVector.z * speed;
	mView.x = mView.x + vVector.x * speed;
	mView.z = mView.z + vVector.z * speed;
}

*/

void Move_Camera(float speed)
{
	// forward positive cameraspeed and backward negative -cameraspeed.
	if ((eyex  + (view_x-eyex) * speed) > LENGTH_GROUND)
		eyex = LENGTH_GROUND - 1;
	else if ((eyex  + (view_x-eyex) * speed) < 0)
		eyex = 0;
	else
		eyex  = eyex  + (view_x-eyex) * speed;

	if ((eyez  + (view_z-eyez) * speed) > LENGTH_GROUND)
		eyez = LENGTH_GROUND - 1;
	else if ((eyez  + (view_z-eyez) * speed) < 0)
		eyez = 0;
	else
		eyez  = eyez  + (view_z-eyez) * speed;

	//std::cout << eyex << " " << eyez;

	eyey  = matriz_ground.at(eyex).at(eyez) + 2;

	view_x = view_x + (view_x-eyex) * speed;
	view_z = view_z + (view_z-eyez) * speed;
}


void Rotate_View(GLfloat speed)
{
	view_z = (float)(eyez + sin(speed)*(view_x - eyex) + cos(speed)*(view_z-eyez));
	view_x = (float)(eyex + cos(speed)*(view_x - eyex) - sin(speed)*(view_z-eyez));
}


void init (void)
{	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable( GL_DEPTH_TEST );

	setMatrixRandom(LENGTH_GROUND, matriz_ground);
	setEyePoint();
}
void display(void)
{	
	int x_matriz, z_matriz;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	gluLookAt(eyex, 3, eyez, view_x, 2.5, view_z, 0.0, 1.0, 0.0);

	/*
	for(float i = -500; i <= 500; i += 5)
	{
		glBegin(GL_LINES);
			glColor3ub(150, 190, 150);						
			glVertex3f(-500, 0, i);					
			glVertex3f(500, 0, i);
			glVertex3f(i, 0,-500);							
			glVertex3f(i, 0, 500);
		glEnd();
	}
	*/

	glPushMatrix();

	glTranslatef(10,1,10);

	glColor4f (0.0, 0.0, 1.0, 0.0);
	glutSolidTeapot(0.5);

	glPopMatrix();

	glPushMatrix();

	for(x_matriz=0;x_matriz<LENGTH_GROUND-1;x_matriz++)
	{
		for(z_matriz= 0; z_matriz<LENGTH_GROUND-1; z_matriz++)
		{
			/*
			glBegin(GL_LINES);
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex3i(x_matriz, matriz_ground[x_matriz][z_matriz], z_matriz);
				glVertex3i(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);

				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex3i(x_matriz, matriz_ground[x_matriz][z_matriz], z_matriz);
				glVertex3i(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);

				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex3i(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);
				glVertex3i(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);

				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex3i(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);
				glVertex3i(x_matriz+1, matriz_ground[x_matriz+1][z_matriz+1], z_matriz+1);

				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex3i(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);
				glVertex3i(x_matriz+1, matriz_ground[x_matriz+1][z_matriz+1], z_matriz+1);
			glEnd();
			*/

			glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz], z_matriz);
				glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);
				glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);

				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz+1], z_matriz+1);
				glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);
				glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);
			glEnd();
		}	
	}

	glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective( 45.0, w/h, 1.0, 40.0 );
	glMatrixMode(GL_MODELVIEW);
}

void specialkeys( int key, int x, int y )
{
	switch (key) {
	case GLUT_KEY_LEFT:	 Rotate_View(-CAMERASPEED); break;
    case GLUT_KEY_RIGHT: Rotate_View(CAMERASPEED); break;
    case GLUT_KEY_DOWN:  Move_Camera(-CAMERASPEED); break;
    case GLUT_KEY_UP:    Move_Camera(CAMERASPEED); break;
    default: break;
    }
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{	
	switch(key) {
	case 'q': exit(0); break;
	case 'a': Rotate_View(-CAMERASPEED); break;
    case 'd': Rotate_View(CAMERASPEED); break;
    case 's': Move_Camera(-CAMERASPEED); break;
    case 'w': Move_Camera(CAMERASPEED); break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// Inicializa a glut com parametros recebidos pelo programa principal
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(500, 500);
	glutInitWindowPosition( 100, 100);
	glutCreateWindow("Trabalho Trabalho Trabalho");

 	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc( specialkeys );
	glutReshapeFunc(reshape);
	glutMainLoop();
    return (0);
}

