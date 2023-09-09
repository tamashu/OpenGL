#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "BasicFunction.h"
#include "RollerWalkerModel.h"
#include "BaseShape.h"
#define OFF 0
#define ON  1
#define TO_M 0.1 //[10^(-1)m]→[m]への単位変換

#define PI 3.14159265359


//角度の制限
#define MAX_PHI 89      //仰角の最大角
#define MIN_PHI -10     //最小の最小角
#define MAX_R 400
#define MIN_R 1

//注視点からの角度
int e_r = 50;           //視点点の距離[0.1m]
int e_theta = -60;      //視点の方位角は-180度[deg]
int e_phi = 45;         //視点の仰角[deg]
int x_old = 0;          //前回motion()が呼び出されたときのマウスのx座標
int y_old = 0;          //前回motion()が呼び出されたときのマウスのy座標
int left_button = 0;  //マウスの左ボタンが押されているかどうか　0:OFF, 1:ON



RollerWalkerModel rollerwalker_model = RollerWalkerModel();
BaseShape baseshape = BaseShape();

/*
 * 画面表示
 */
static void display(void){

    GLfloat lightpos[] = { 0.0, 0.0, 10.0, 1.0 }; /* 光源の位置 */
    double e_x = 0.0, e_y = 0.0, e_z = 0.0;    //視点
    double f_x = 0.0, f_y = 0.0, f_z = 0.0;     //注視点(固定)

    /* 画面クリア */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* モデルビュー変換行列の初期化 */
    glLoadIdentity();

    //視点の移動
    e_x = f_x + (double)e_r * TO_M * cos(degreeToRad(e_theta)) * cos(degreeToRad(e_phi));
    e_y = f_y + (double)e_r * TO_M * sin(degreeToRad(e_theta)) * cos(degreeToRad(e_phi));
    e_z = f_z + (double)e_r * TO_M * sin(degreeToRad(e_phi));

    lightpos[0] = e_x;
    lightpos[1] = e_y;
    lightpos[2] = e_z;
    

    std::cout<< "e_r: "<< e_r << "  e_theta: " << e_theta << "e_phi: " << e_phi << std::endl;


    /* 視点の移動（シーンの方を奥に移す）*/
    gluLookAt(e_x,e_y,e_z,f_x,f_y,f_z,0.0,0.0,1.0); 
    /* 光源の位置を設定 */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    

    baseshape.myGround(0.0);
    baseshape.myCordinateSystem(8.0);

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



static void init(void)
{
    /* 初期設定 */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

//void specialKey(int key, int x, int y) {
//
//    float dt = 0.1;
//    int num_of_trails = 1.0 / dt;
//
//
//    switch (key) {
//    case GLUT_KEY_UP:
//        i++;
//        break;
//    case GLUT_KEY_DOWN:
//        if (i - 1 > 0) {
//            i--;
//        }
//        else {
//            i = 0;
//        }
//
//        break;
//    case GLUT_KEY_RIGHT:
//        is_start = true;
//        glutTimerFunc(40, timer, 0);
//        break;
//    case GLUT_KEY_LEFT:
//        if (is_start) {
//            is_start = false;
//        }
//        else {
//            is_start = true;
//        }
//
//    default:
//        break;
//    }
//    glutPostRedisplay();
//
//}

void mouse(int button, int state, int x, int y) {//マウスが押されるたびに呼び出される
    //最後にマウスが押された（離された）時のボタン
    x_old = x;
    y_old = y;

    switch (button) {
    case GLUT_LEFT_BUTTON:
        
        if (state == GLUT_UP)left_button = OFF;
        else {
            left_button = ON;
        }
        break;
    default:
        break;
    }

    //マウスホイールによる視点の遠近の変更(ホイールの奥への回転:button = 3, 手前への回転: button = 4)
    if (button == 3) {//ホイールを奥に回転 = 視点を近づける
        //if (state == GLUT_UP) return;    //glut_UPの方を無視(1回の回転でUPとDOWNの二回呼ばれるため)
        e_r--;
        if (e_r < MIN_R)e_r = MIN_R;
        glutPostRedisplay(); //視点が変更されたため再描画
    }
    else if (button == 4) {//ホイールを手前に回転 = 視点を遠ざける
        //if (state == GLUT_UP)return;    //glut_UPの方を無視(1回の回転でUPとDOWNの二回呼ばれるため)
        e_r++;
        if (e_r > MAX_R)e_r = MAX_R;
        glutPostRedisplay(); //視点が変更されたため再描画
    }

}

void motion(int x, int y) {
    if (left_button == 1) {//左ボタンが押されている時、方位角(θ),仰角(φ)を変更
        e_theta = e_theta - (x - x_old);    //前回のマウスの位置からの移動を基に変更
        e_phi = e_phi + (y - y_old);        //前回のマウスの位置からの移動を基に変更
    }

    
    

    //仰角の制限
    if (e_phi > MAX_PHI) {
        e_phi = MAX_PHI;
    }
    else if(e_phi < MIN_PHI){
        e_phi = MIN_PHI;
    }

    x_old = x;  //次にmotion()が呼び出された時のために値を保存
    y_old = y;  //次にmotion()が呼び出された時のために値を保存

    glutPostRedisplay();//マウスが動いた時だけアニメーションさせる
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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    /*glutSpecialFunc(specialKey);*/
    init();
    

    glutMainLoop();
    return 0;
}