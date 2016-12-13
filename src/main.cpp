
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

const int LENGTH_GROUND {50};
const int NUMBER_OBJECTS {20};

using std::vector;

vector < vector < GLfloat >> matriz_ground;
GLdouble eyex=5.0, eyey=5.0, eyez=5.0;
GLfloat rotate_angle =1;
GLfloat CAMERASPEED = 0.05f;
GLfloat view_x, view_z, view_y;

GLfloat object_posx[NUMBER_OBJECTS], object_posz[NUMBER_OBJECTS], object_posy[NUMBER_OBJECTS];

GLfloat color1 = 0.3, color2 = 1.0, color3 = 0.5;

int dentro=0;
int type_object = 0;
int encostou = 0, virou = 0, andou = 0;

//////////////////////////////////////
//The tVector3 Struct
//////////////////////////////////////
struct tVector3	// Extended 3D Vector Struct
{			
	tVector3() {} // Struct Constructor
	tVector3 (float new_x, float new_y, float new_z) // Init Constructor	 
	{ x = new_x; y = new_y; z = new_z; }
	// overload + operator
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}
	
	float x, y, z;						// 3D vector coordinates
};

tVector3 mPos, mView;



void setEyePoint(void)
{
	mPos.x = LENGTH_GROUND/2.0; mPos.z = LENGTH_GROUND/2.0;
	mPos.y = matriz_ground[(int)mPos.x][(int)mPos.z] + 2.0;
	//view_x = LENGTH_GROUND/2.0 + 2.0; view_z = LENGTH_GROUND/2.0 + 2.0;
	//view_y = 2.5;
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

void setPositionObjects(void)
{
	int tempx, tempz;

	for (int jjj = 0; jjj < NUMBER_OBJECTS; ++jjj)
	{
		object_posx[jjj] = jjj;
		object_posz[jjj] = jjj;
		//tempx = static_cast<int>()
		object_posy[jjj] = matriz_ground[object_posx[jjj]][object_posz[jjj]] + 1;
	}
}

void Move_Camera(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector
	
	// forward positive cameraspeed and backward negative -cameraspeed.
	if ((mPos.x  + vVector.x * speed) > LENGTH_GROUND-1)
	{
		mPos.x = LENGTH_GROUND - 2;
	}
	else if ((mPos.x  + vVector.x * speed) < 1)
	{
		mPos.x = 2;
	}
	else
	{	
		mPos.x  = mPos.x  + vVector.x * speed;
		mView.x = mView.x + vVector.x * speed;
	}

	if ((mPos.z  + vVector.z * speed) > LENGTH_GROUND -1)
	{
		mPos.z = LENGTH_GROUND - 2;
	}
	else if ((mPos.z  + vVector.z * speed) < 1)
	{
		mPos.z = 2;
	}
	else
	{	
		mPos.z  = mPos.z  + vVector.z * speed;

		mView.z = mView.z + vVector.z * speed;
	}

	//mPos.y   = matriz_ground.at(eyex).at(eyez) + 2.0;
	//mView.y = matriz_ground.at(eyex).at(eyez) + 1.8;

}

void Rotate_View(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector

	mView.z = (float)(mPos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	mView.x = (float)(mPos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}

void init (void)
{	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable( GL_DEPTH_TEST );

	setMatrixRandom(LENGTH_GROUND, matriz_ground);
	setPositionObjects();
	setEyePoint();
}

void object(void)
{
	switch (type_object)
	{
		case 0:
			gluSphere(gluNewQuadric(), 1, 100, 100);
			break;

		case 1:
			glutSolidTeapot(0.5);
			break;
	}
} 

void Render_map(int x_matriz,int z_matriz)
{
	glPushMatrix();

		for(x_matriz=0;x_matriz<LENGTH_GROUND-1;x_matriz++)
		{
			for(z_matriz= 0; z_matriz<LENGTH_GROUND-1; z_matriz++)
			{
			
				glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz], z_matriz);
					glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);

					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz], z_matriz);
					glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);

					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);
					glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);

					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz], z_matriz);
					glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz+1], z_matriz+1);

					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex3f(x_matriz, matriz_ground[x_matriz][z_matriz+1], z_matriz+1);
					glVertex3f(x_matriz+1, matriz_ground[x_matriz+1][z_matriz+1], z_matriz+1);
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

	glPopMatrix();
}

static void Timer(int value)
{
	int tempx, tempz;

	for (int count = 0; count < NUMBER_OBJECTS; ++count)
	{
		object_posx[count] += 0.1;
    	object_posz[count] += 0.1;
    	tempx = static_cast<int>(object_posx[count]);
    	tempz = static_cast<int>(object_posz[count]);
    	object_posy[count] = matriz_ground.at(tempx).at(tempz) + 1.0;

    	if(object_posx[count]>LENGTH_GROUND-2)
    	{
    		object_posx[count] = LENGTH_GROUND-3;
    	}	

    	if(object_posz[count]>LENGTH_GROUND-2)
    	{
    		object_posz[count] = LENGTH_GROUND-3;
    	}


    	if(pow((object_posx[count] - mPos.x), 2)+(pow((object_posz[count] - mPos.z), 2)) < 16)
    	{
    		int tempor;

    		if(dentro == 0)
    		{
    			encostou++;
	    		tempor = color1;
    			color1 = color2;
    			color2 = color3;
    			color3 = tempor;
	    		color1 += 0.2;
    			color2 -= 0.3;
    		}
    		dentro = 1;
    	}
    	else if(dentro == 1)
    	{
    		dentro = 0;
    	}
	}

    
    glutPostRedisplay();
    // 100 milliseconds
    glutTimerFunc(100, Timer, 0);
}

void display(void)
{	
	int x_matriz, z_matriz;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport(0, 0, 800, 800); // 1a. viewport a esquerda da janela
	
	glLoadIdentity();

	glPushMatrix();
		gluLookAt(mPos.x, mPos.y, mPos.z, mView.x, mView.y, mView.z, 0.0, 1.0, 0.0);

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

		Render_map(x_matriz, z_matriz);

		glPushMatrix();

			glTranslatef(10,1,10);

			glColor4f (0.0, 0.0, 1.0, 0.0);
			glutSolidTeapot(0.5);

		glPopMatrix();

		for (int iii = 0; iii < NUMBER_OBJECTS; ++iii)
		{
			glPushMatrix();

				glColor4f (color1, color2, color3, 0.0);

				glTranslatef(object_posx[iii], object_posy[iii], object_posz[iii]);
			
				object();

			glPopMatrix();
		}
		

	glPopMatrix();

	glPushMatrix();
		glViewport(600, 600, 200, 200); 
		gluLookAt(mPos.x, 20, mPos.z, mPos.x, 0, mPos.z, 0.0, 0.0, -1.0);
		glDisable(GL_LIGHTING);
		Render_map(x_matriz, z_matriz);



		for (int iii = 0; iii < NUMBER_OBJECTS; ++iii)
		{
			glPushMatrix();

				glColor4f (color1, color2, color3, 0.0);

				glTranslatef(object_posx[iii], object_posy[iii], object_posz[iii]);
			
				object();

			glPopMatrix();
		}


		glPushMatrix();

			glTranslatef(10,1,10);
			glColor4f (0.0, 0.0, 1.0, 0.0);
			glutSolidTeapot(0.5);

		glPopMatrix();
		glPushMatrix();
			glTranslatef(mPos.x, 18, mPos.z);
			glColor4f (0.0, 1.0, 0.0, 0.0);
			gluSphere(gluNewQuadric(), 0.05, 100, 100);

		glPopMatrix();

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
	case GLUT_KEY_LEFT:	 
	{
		virou++;
		Rotate_View(-CAMERASPEED*5); 
		break;
	}
    case GLUT_KEY_RIGHT:
    {
		virou++;
		Rotate_View(CAMERASPEED*5); 
		break;
	}
    case GLUT_KEY_DOWN: 
    {
    	andou++;
    	Move_Camera(-CAMERASPEED); 
    	break;
    }
    case GLUT_KEY_UP:  
    {
    	andou++;
    	Move_Camera(CAMERASPEED); 
    	break;
    }
    default: break;
    }
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{	
	switch(key) {
	case 'q': 
	{
		printf("Encostou em objetos %d vezes\n", encostou);
		printf("Trocou de direcao %d vezes\n", virou);
		printf("Caminhou %d vezes\n", andou);
		exit(0); 
		break;

	}
	case 'a': 
    {
		virou++;
		Rotate_View(-CAMERASPEED*5); 
		break;
	}
    case 'd':
    {
		virou++;
		Rotate_View(CAMERASPEED*5); 
		break;
	}
    case 's': 
    {
    	andou++;
    	Move_Camera(-CAMERASPEED); 
    	break;
    }
    case 'w':
    {
    	andou++;
    	Move_Camera(CAMERASPEED); 
    	break;
    }
    case 'r': CAMERASPEED+=0.01; break;
    case 'e': CAMERASPEED-=0.01; break;
    case 27 : 
    {
		printf("Encostou em objetos %d vezes\n", encostou);
		printf("Trocou de direcao %d vezes\n", virou);
		printf("Caminhou %d vezes\n", andou);
		exit(0); 
		break;

	}
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
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Trabalho Trabalho Trabalho");

 	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(specialkeys);
	glutReshapeFunc(reshape);

	Timer(0);

	glutMainLoop();
    return (0);
}

