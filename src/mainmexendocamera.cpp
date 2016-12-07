
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
GLfloat matriz_ground[4][4] = {{1,2,1,1},{2,2,3,5},{3,3,5,-1},{4,2,3,1}};
GLdouble eyex=5.0, eyey=5.0, eyez=5.0;
void setEyePoint(void)
{
		eyex=5.0; eyey=5.0; eyez = 5.0; return;
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
	gluLookAt(eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    	glScalef(1,1,1);


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
	case GLUT_KEY_LEFT:	 eyex--; break;
    case GLUT_KEY_RIGHT: eyex++; break;
    case GLUT_KEY_DOWN:  eyey--; break;
    case GLUT_KEY_UP:    eyey++; break;
    case GLUT_KEY_PAGE_UP: eyez++; break;
    case GLUT_KEY_PAGE_DOWN:eyez--;	break;
    case GLUT_KEY_HOME:	 setEyePoint(); break;
    case GLUT_KEY_END: 	exit(0);	break;
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

