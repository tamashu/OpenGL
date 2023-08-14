#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "CooperativeTruck.h"
#include "BasicFunction.h"
#include "DrawLine.h"

#define MARGIN 0

std::vector<std::vector<double>>car_tranjectory = readFile("test.csv");//車の軌跡のセット
std::vector<std::vector<double>>bezier_curve = readFile("bezier.csv");//ベジェ曲線のセット
std::vector<std::vector<double>>status = readFile("d_theta_p.csv");
std::vector<std::vector<double>>front_tranjectory;//軌跡
std::vector<std::vector<double>>carrier_tranjectory;//軌跡
std::vector<std::vector<double>>rear_tranjectory;//軌跡

//プリウス参照(ホイルベース2.75m,全長4.6, 幅1.78m,高さ1.42m,タイヤ半径0.317m) 
CooperativeTruck truck(L1, L2, L3);
DrawLine line = DrawLine();

bool is_start = false;

int i = 0;

/*
 * 画面表示
 */
static void display(void)
{
    double blue[]   = { 0.2, 0.2, 0.8, 1.0 };  
    double red[]    = { 0.8, 0.2, 0.2, 1.0 };
    double green[]  = { 0.2, 0.8, 0.2, 1.0 };
    double yellow[] = { 0.8, 0.8, 0.0 ,1.0 };

    const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* 光源の位置 */
    //const static GLfloat lightpos[] = { 0.0, 0.0, 10.0, 1.0 }; /* 光源の位置 */


    /* 画面クリア */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* モデルビュー変換行列の初期化 */
    glLoadIdentity();

    /* 光源の位置を設定 */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* 視点の移動（シーンの方を奥に移す）*/
    //gluLookAt(car_tranjectory[i][1] + MARGIN, car_tranjectory[i][2], 20.0, car_tranjectory[i][1] + MARGIN, car_tranjectory[i][2]+1, 1.0, 0.0, 0.0, 1.0); //真上
    gluLookAt(status[i][1] + MARGIN, status[i][2], 30.0, status[i][1] + MARGIN, status[i][2] +1, 1.0, 0.0, 0.0, 1.0); //荷台から
    //gluLookAt(car_tranjectory[i][1]+MARGIN, -8.0, 1.0, car_tranjectory[i][1], -3.0, 0.0, 0.0, 0.0, 1.0); //真横(車追従)
    //gluLookAt(car_tranjectory[i][1] + 15, car_tranjectory[i][2], 1.0, car_tranjectory[i][1], car_tranjectory[i][2], 0.0, 0.0, 0.0, 1.0); //真正面(車追従)


    /*---------------------------------------------------------------------------------------------
    *                           車の描画
    *---------------------------------------------------------------------------------------------*/
    double t  = status[i][0]; 
    double v1 = status[i][5]; 

    //前の車
    double x1 = car_tranjectory[i][1]; double y1 = car_tranjectory[i][2]; 
    double theta1_rad = car_tranjectory[i][4]; double phi1_rad = car_tranjectory[i][3];

    //荷台
    double x2 = status[i][1]; double y2 = status[i][2]; double theta2_rad = car_tranjectory[i][6];

    //後ろの車
    double x3 = status[i][3]; double y3 = status[i][4];
    double theta3_rad = car_tranjectory[i][7]; double phi2_rad = car_tranjectory[i][5];

    //std::cout << "x1: " << x1 << " y1:  " << y1 << std::endl;
    //std::cout << "carrier_tranjectory: " << carrier_tranjectory.size() << "rear_tranjectory: " << rear_tranjectory.size() << std::endl;

    //描画
    line.drawCarTranjectory(front_tranjectory, 0.12, blue); //車の軌跡  
    line.drawCarTranjectory1(carrier_tranjectory, 0.12, green); //車の軌跡  
    line.drawCarTranjectory2(rear_tranjectory, 0.12, yellow); //車の軌跡  
    line.drawCurve(bezier_curve, 0.11, red);
    

    truck.DrawTruck( t,  v1,  x1,  y1,  theta1_rad,  phi1_rad,  //前の車
                     x2,  y2,  theta2_rad,					//荷台
                     x3,  y3,  theta3_rad,  phi2_rad);
    
    glutSwapBuffers();

    glFlush();
}

static void resize(int w, int h)
{
    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, w, h);

    /* 透視変換行列の指定 */
    glMatrixMode(GL_PROJECTION);

    /* 透視変換行列の初期化 */
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    /* モデルビュー変換行列の指定 */
    glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
    /* ESC か q をタイプしたら終了 */
    switch (key)
    {
    default:
        break;
    case '\033':
    case 'q':
        exit(0);
   
    }
}



void timer(int value) {
    if (is_start) {
        i++;
    }
    
    if (i >= car_tranjectory.size()-1) {
        i = 0;
        front_tranjectory.clear();
        carrier_tranjectory.clear();
        rear_tranjectory.clear();
    }

    if (i % 10 == 0) {
        std::vector<double> front_position = { car_tranjectory[i][1], car_tranjectory[i][2] };
        std::vector<double> carrier_position = { status[i][1], status[i][2] };
        std::vector<double> rear_position = { status[i][3], status[i][4] };

        front_tranjectory.push_back(front_position);
        carrier_tranjectory.push_back(carrier_position);
        rear_tranjectory.push_back(rear_position);
    }

    glutPostRedisplay();
    glutTimerFunc(40, timer, 0);
}

static void init(void)
{
    /* 初期設定 */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void specialKey(int key, int x, int y) {

    float dt = 0.1;
    int num_of_trails = 1.0 / dt;


    switch (key) {
    case GLUT_KEY_UP:
        i++;
        break;
    case GLUT_KEY_DOWN:
        if (i - 1 > 0) {
            i--;
        }
        else {
            i = 0;
        }

        break;
    case GLUT_KEY_RIGHT:
        is_start = true;
        glutTimerFunc(40, timer, 0);
        break;
    case GLUT_KEY_LEFT:
        if (is_start) {
            is_start = false;
        }
        else {
            is_start = true;
        }

    default:
        break;
    }
    glutPostRedisplay();

}

int main(int argc, char* argv[])
{
    glutInitWindowSize(800, 800);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    init();
    

    glutMainLoop();
    return 0;
}