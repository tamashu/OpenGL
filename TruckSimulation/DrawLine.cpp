#include "DrawLine.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h>



void DrawLine::drawCurve(std::vector<std::vector<double>>points,double z,double *color) {
	int vector_size = points.size();
	
	const static GLfloat colors[] = { color[0], color[1] , color[2], 0.9 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, colors);
	glNormal3d(0.0, 0.0, 1.0);

	if (vector_size > 1) {
		for (int i = 0; i < vector_size - 1; i++) {
			drawLine(points[i], points[i + 1],z);
		}
	}
}

void DrawLine::drawCarTranjectory(std::vector<std::vector<double>>points, double z, double* color){
	int vector_size = points.size();

	const static GLfloat colors[] = { color[0], color[1] , color[2], 0.9 };
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colors);
	glNormal3d(0.0, 0.0, 1.0);

	glPointSize(8);
	if (vector_size > 1) {
		for (int i = 0; i < vector_size - 1; i++) {
			glBegin(GL_POINTS);
			glVertex3d(points[i][0], points[i][1], z);
			glEnd();
		}
	}
}

void DrawLine::drawCarTranjectory1(std::vector<std::vector<double>>points, double z, double* color) {
	int vector_size = points.size();

	const static GLfloat colors[] = { color[0], color[1] , color[2], 0.9 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, colors);
	glNormal3d(0.0, 0.0, 1.0);

	glPointSize(8);
	if (vector_size > 1) {
		for (int i = 0; i < vector_size - 1; i++) {
			glBegin(GL_POINTS);
			glVertex3d(points[i][0], points[i][1], z);
			glEnd();
		}
	}
}

void DrawLine::drawCarTranjectory2(std::vector<std::vector<double>>points, double z, double* color) {
	int vector_size = points.size();

	const static GLfloat colors[] = { color[0], color[1] , color[2], 0.9 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, colors);
	glNormal3d(0.0, 0.0, 1.0);

	glPointSize(8);
	if (vector_size > 1) {
		for (int i = 0; i < vector_size - 1; i++) {
			glBegin(GL_POINTS);
			glVertex3d(points[i][0], points[i][1], z);
			glEnd();
		}
	}
}



void DrawLine::drawLine(std::vector<double> p0, std::vector<double> p1,double z) {
	glLineWidth(10);
	glBegin(GL_LINES);
	{
		glVertex3d(p0[0], p0[1],z);
		glVertex3d(p1[0], p1[1],z);
	}
	glEnd();
}