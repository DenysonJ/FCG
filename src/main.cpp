
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


GLfloat matriz_ground[4][4] = {{1,2,1,1},{2,2,3,5},{3,3,5,-1},{4,2,3,1}};
GLdouble eyex=5.0, eyey=5.0, eyez=5.0;
GLfloat rotate_angle =1;
GLfloat CAMERASPEED = 0.03f;
GLfloat view_x, view_z;


void setEyePoint(void)
{
		eyex=5.0; eyey=5.0; eyez = 5.0; return;
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
	eyex  = eyex  + (view_x-eyex) * speed;
	eyez  = eyez  + (view_z-eyez) * speed;
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
}
void display(void)
{	
	int x_matriz, z_matriz;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	gluLookAt(eyex, 1, eyez, view_x, 1, view_z, 0.0, 1.0, 0.0);


	glPushMatrix();

	glRotatef(rotate_angle, 0, 1, 0);

	glPopMatrix();


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

	glTranslatef(10,1,10);

	glColor4f (0.0, 0.0, 1.0, 0.0);
	glutSolidTeapot(.75);



	for(x_matriz=0;x_matriz<3;x_matriz++)
	{
		for(z_matriz= 0; z_matriz<3; z_matriz++)
		{
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
	case 'x': eyex=5.0; eyey=0.0; eyez=0.0; break;
	case 'y': eyex=0.05; eyey=5.0; eyez=0.0; break;
	case 'z': eyex=0.0; eyey=0.0; eyez=5.0; break;
	case 'e': glEnable( GL_DEPTH_TEST); break;
	case 'd': glDisable(GL_DEPTH_TEST); break;
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
	glutCreateWindow("Exemplo de Depth Test");

 	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc( specialkeys );
	glutReshapeFunc(reshape);
	glutMainLoop();
    return (0);
}

