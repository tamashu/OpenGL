#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "BasicCar.h"
#include "BasicFunction.h"

//プリウス参照(ホイルベース2.75m,全長4.6, 幅1.78m,高さ1.42m,タイヤ半径0.317m) 
BasicCar car = BasicCar(2.75, 1.78, 0.925, 1.420, 0.317);
int i = 0;

/*
 * 画面表示
 */
static void display(void)
{
    const static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };     /* 球の色 */
    const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* 光源の位置 */

  

    /* 画面クリア */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* モデルビュー変換行列の初期化 */
    glLoadIdentity();

    /* 光源の位置を設定 */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* 視点の移動（シーンの方を奥に移す）*/
    //gluLookAt(10.0, 10.0, 6.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
    gluLookAt(0.0, 0.0, 40.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    std::vector<std::vector<double>>result = readFile("test.csv");
    
    std::cout << "x[" << i << "]: "<< result[i][1] << "  y[" << i << "]: " << result[i][2] << std::endl;
    car.DrawCar(result[i][1], result[i][2]);

    i++;

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

void specialKey(int key, int x, int y) {

    float dt = 0.1;
    int num_of_trails = 1.0 / dt;


    switch (key) {
    case GLUT_KEY_UP:
        i++;
        break;
    case GLUT_KEY_DOWN:
        if(i-1 >0){
            i--;
        }
        else {
            i = 0;
        }
        
        break;
    default:
        break;
    }
    glutPostRedisplay();

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