#include <gl/glut.h>
#include <vector>
#include <iostream>
#include "DrawBezier.h"
#include < GL/freeglut.h>
#include <string>
#include <sstream>
#include <iomanip>

void drawTrail(std::vector<float> p0, std::vector<float> p1);
inline void glutBitmapString(void* font, const char* string);
void drawString(std::vector < float >p, std::string string);
void drawString(std::vector < float >p, std::string string, int i);

void drawXAxis(float increments);
void drawYAxis(float increments);

float calDist(std::vector<float> p, float clicked_x, float clicked_y);
float convertGlobalCordinate_x(int x);
float convertGlobalCordinate_y(int y);



int window_h;
int window_w;

float l = -5.0;
float r = 5.0;
float t = 5.0;
float b = -5.0;

//エラー退避用の処置
float t_position_x = l * 0.9;
float t_position_y = t * 0.8;


float clicked_x;
float clicked_y;
int clicked_point = -1;



std::vector<std::vector<float>> trail = {};//軌跡
std::vector<float> s_0;//求める点
std::vector<float> t_position = { t_position_x, t_position_y };//時刻の表示位置

//制御点
std::vector<float>p_0 = { -4.0,-4.0 };
std::vector<float>p_1 = { -3.0,-1.0 };
std::vector<float>p_2 = { -2.0,2.0 };
std::vector<float>p_3 = { 0.0,4.5 };
std::vector<float>p_4 = { 2.0,3.5 };
std::vector<float>p_5 = { 3.0,2.5 };
std::vector<float>p_6 = { 3.0,1.0 };
std::vector<float>p_7 = { 0.0,-1.0 };
std::vector<float>p_8 = { 3,0,-5.0};
std::vector<float>p_9 = { -3,0,-5.0 };
std::vector<float>p_10 = { 4,0,-5.0 };


//制御点のコンテナ
std::vector<std::vector<float>> control_points = { p_0,p_1,p_2,p_3 ,p_4,p_5 ,p_6 ,p_7 ,p_8 ,p_9,p_10};

DrawBezier bezier = DrawBezier(control_points);






void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	std::string t_now = "t: " + std::to_string(bezier.get_t());
	
	
	s_0 = bezier.drawNDimensionBezier();
	drawString(t_position, t_now);
	drawXAxis(1.0);
	drawYAxis(0.5);
	
	

	//個々の処理もっと良いのないか
	if (trail.size() > 1) {
		for (int i = 0; i < trail.size() - 1; i++) {
			drawTrail(trail[i], trail[i + 1]);
		}
	}

	if (bezier.get_t() == 0) { //tが0なら初期化
		trail.clear();
		std::cout << "trail is cleared " << std::endl;
	}

	glFlush();

	std::cout << "call Display " << std::endl;

}

void resize(int w, int h)
{
	window_h = h;
	window_w = w;

	glViewport(0, 0, w, h);/* ウィンドウ全体をビューポートにする */
	glLoadIdentity();/* 変換行列の初期化(単位行列にする） */
	std::cout << "w: " << w << " h: " << h << std::endl;
	/* スクリーン上の座標系をマウスの座標系に一致させる */
	glOrtho(l, (GLdouble)r, b, t, -1.0, 1.0);

}




void specialKey(int key, int x, int y) {

	float dt = 0.01; 
	int num_of_trails = 1.0 / dt;
	

	switch (key) {
	case GLUT_KEY_UP:
		bezier.set_t(bezier.get_t() + dt);
		trail.push_back(s_0);
		break;
	case GLUT_KEY_DOWN:
		bezier.set_t(bezier.get_t() - dt);
		if(trail.size()>1)
			trail.pop_back();
		break;
	
	case GLUT_KEY_RIGHT://右キーでt=1.0までの軌跡表示
		trail.clear();
		bezier.set_t(0.0);
		for (int i = 0; i < num_of_trails; i ++) {
			std::cout << "t: " << bezier.get_t() << std::endl;
			bezier.set_t(bezier.get_t() + dt);
			trail.push_back(bezier.drawNDimensionBezier());
		}
		break;
	case GLUT_KEY_LEFT:
		trail.clear();
		bezier.set_t(0.0);
		break;

	default:
		break;
	}

	if (bezier.get_t() <= 0 ||bezier.get_t()>1 ) {
		bezier.set_t(0.0);
	}

	glutPostRedisplay();
	std::cout << "t: " << bezier.get_t() << " size_of_trail: " << trail.size() << std::endl;

}

void mouse(int button, int state, int x, int y) {
	clicked_x = convertGlobalCordinate_x(x);
	clicked_y = convertGlobalCordinate_y(y);

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			for (int i = 0; i < control_points.size(); i++) {
				float dist = calDist(bezier.get_ith_control_point(i), clicked_x, clicked_y);
				if (dist < 0.5) {
					clicked_point = i;
				}
			}
			break;
		}
		else {
			clicked_point = -1;
			trail.clear();
			bezier.set_t(0.0);
		}
	default:
		break;
	}


	printf(" at (%f, %f)\n", clicked_x, clicked_y);

}

void motion(int x, int y) {
	float mouse_x = convertGlobalCordinate_x(x);
	float mouse_y = convertGlobalCordinate_y(y);
	if (clicked_point >= 0) {
		bezier.set_ith_control_points(clicked_point, mouse_x, mouse_y);
		glutPostRedisplay();
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

int main(int argc, char* argv[]) {
	glutInitWindowSize(800, 600);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("Bezier Curve");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);		//画面変更時の処理
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(specialKey);
	init();
	glutMainLoop();
	return 0;
}

void drawTrail(std::vector<float> p0, std::vector<float> p1) {
	glLineWidth(3);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	{
		glVertex2f(p0[0], p0[1]);
		glVertex2f(p1[0], p1[1]);
	}
	glEnd();
}

inline void glutBitmapString(void* font, const char* string) //文字表示をしやすくするためのオーバーロード
{
	glutBitmapString(font, reinterpret_cast<const unsigned char*>(string));
}

void drawString(std::vector < float >p, std::string string) {
	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(p[0] + r * 0.05, p[1] + t * 0.04);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, string.c_str());
}

void drawString(std::vector < float >p, std::string string,int i) {
	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(p[0] + r * 0.05, p[1] + t * 0.04);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, string.c_str());
}

void drawXAxis(float increments) {
	float tick_y_positon = 0.1*b;
	float tick_x_corecction = -r/15;
	float line_width = 0.25;
	char* cstr;
	std::stringstream ss;

	//x軸の描画
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	{
		glVertex2f(l, 0); 
		glVertex2f(r, 0);
	}
	glEnd();

	//右側
	for (float i = increments; i < r; i += increments) {
		std::vector<float> tick_position = {i+tick_x_corecction,tick_y_positon};
		ss << std::fixed << std::setprecision(1) << i;
		std::string str = ss.str();
		drawString(tick_position,str,1);
		ss.str("");//stringStreamの初期化

		//軸
		glLineWidth(line_width);
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_LINES);
		{
			glVertex2f(i, t);
			glVertex2f(i, b);
		}
		glEnd();
	}

	//左側
	for (float i = -increments; i > l; i -= increments) {
		std::vector<float> tick_position = { i+tick_x_corecction,tick_y_positon };
		ss << std::fixed << std::setprecision(1) << i;
		std::string str = ss.str();
		drawString(tick_position, str,1);
		ss.str("");//stringStreamの初期化

		//軸
		glLineWidth(line_width);
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_LINES);
		{
			glVertex2f(i, t);
			glVertex2f(i, b);
		}
		glEnd();
	}
}

void drawYAxis(float increments) {
	float tick_x_positon = 0.11*l;
	float tick_y_corecction = -t / 15;
	float line_width = 0.5;
	char* cstr;
	std::stringstream ss;

	//x軸の描画
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	{
		glVertex2f(0, t);
		glVertex2f(0, b);
	}
	glEnd();

	//上側
	for (float i = increments; i < t; i += increments) {
		std::vector<float> tick_position = { tick_x_positon,i+tick_y_corecction };
		ss << std::fixed << std::setprecision(1) << i;
		std::string str = ss.str();
		drawString(tick_position, str,1);
		ss.str("");//stringStreamの初期化

		//軸
		glLineWidth(line_width);
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_LINES);
		{
			glVertex2f(l, i);
			glVertex2f(r, i);
		}
		glEnd();
	}

	//左側
	for (float i = increments; i > l; i -= increments) {
		std::vector<float> tick_position = { tick_x_positon,i + tick_y_corecction };
		ss << std::fixed << std::setprecision(1) << i;
		std::string str = ss.str();
		drawString(tick_position, str,1);
		ss.str("");//stringStreamの初期化

		//軸
		glLineWidth(line_width);
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_LINES);
		{
			glVertex2f(l, i);
			glVertex2f(r, i);
		}
		glEnd();
	}
}

float calDist(std::vector<float> p, float clicked_x, float clicked_y) {
	return  sqrt((p[0] - clicked_x) * (p[0] - clicked_x) + (p[1] - clicked_y) * (p[1] - clicked_y));
	
}

float convertGlobalCordinate_x(int x) {
	return r * (x - window_w / 2.0) / (window_w / 2.0);
}

float convertGlobalCordinate_y(int y) {
	return -t * (y - window_h / 2.0) / (window_h / 2.0);
}
