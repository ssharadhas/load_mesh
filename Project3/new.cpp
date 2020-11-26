#include<windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include <GL/glut.h>
#include<cstdio>
#include <vector>
#include <exception>
#include <cstring>
//#include <bits/stdc++.h>

using namespace std;
class vertex {
public:
	double x, y, z;

	//set<int> flist;
	vertex(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}


};

class Face {
public:
	int v1, v2, v3;

	Face(int _x, int _y, int _z) {
		v1 = _x;
		v2 = _y;
		v3 = _z;
	}


};
vector<vertex> V;
//vector<vector<int> > F;
vector<Face> F;
double rotate_x = 0.5;

int vnum = 0,fnum=0;
int normal_count = 0;
int moving, startx, starty;
GLfloat angle, angle2;
int usesnormals = 0;
float minx = -1, maxx = 1, miny = -1, maxy = 1, minz = -1, maxz = 1;
static int slices = 16;
static int stacks = 16;

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		moving = 1;
		startx = x;
		starty = y;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		moving = 0;
	}
	if (btn == 3)
		rotate_x -= 0.5;
	else if (btn == 4)
		rotate_x += 0.5;

}
void motion(int x, int y)
{
	if (moving)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}
void Load(char* filename) {
	//char line[100];


	//char* pch;
	vector<int> faceIndex;
	//int index;
	//char const* p = filename;

	freopen(filename, "r", stdin);
	//V.push_back(vertex(0, 0, 0));


	//int fnum = 0;
	char c;
	int num = 0, count = 0;
	while ((c = getchar()) && (c != EOF)) {
		if (c == '#') {
			while ((c = getchar()) && (c != EOF) && (c != '\n'));
			continue;
		}
		if (c == 'v') {
			double x, y, z;
			c = getchar();

			if (c == ' ') {
				scanf_s("%lf %lf %lf", &x, &y, &z);
				V.push_back(vertex(x, y, z));
				vnum++;
			}

		}


		else if (c == 'f') {
			int u, v, w;
			c = getchar();

			scanf_s("%d", &u);
			c = getchar();
			while (c != ' ') {
				c = getchar();
			}
			scanf_s("%d", &v);
			c = getchar();
			while (c != ' ') {
				c = getchar();
			}
			scanf_s("%d", &w);

			u--; v--; w--;
			F.push_back(Face(u, v, w));
			
			fnum++;

		}
	}
	//fclose(stdin);
}

void Draw() {
	
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < fnum; i++)
	{
		int a = F[i].v1;
		int b = F[i].v2;
		int c = F[i].v3;

		glVertex3f(V[a].x, V[a].y, V[a].z);
		glVertex3f(V[b].x, V[b].y, V[b].z);
		glVertex3f(V[c].x, V[c].y, V[c].z);
	
	
	}
		glEnd();
	

	
}



void display(void) {
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double a = t * 90.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLoadIdentity();
	glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glScalef(rotate_x, rotate_x, 1.0);
	glRotatef(angle, 0, 1, 0);
	glRotatef(angle2, 0, 0, 1);
	glPointSize(3.0);
	Draw();
	
	
	glFlush();
	glutSwapBuffers();


}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)h / (double)w, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -200);
	glRotated(45, 1, 1, 1);

}

static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GLUT Shapes");

	char p[] = "bun_zipper.obj";
	char* z = p;
	Load(z);
	//glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//glutKeyboardFunc(key);
	//   glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	//glutSpecialFunc(keyPressed);
	
	glutMainLoop();

	return EXIT_SUCCESS;
}