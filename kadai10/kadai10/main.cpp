#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "BasicCar.h"
#include "BasicFunction.h"
#include "DrawLine.h"

#define MARGIN 5

std::vector<std::vector<double>>car_tranjectory = readFile("test.csv");//�Ԃ̋O�Ղ̃Z�b�g
std::vector<std::vector<double>>bezier_curve = readFile("bezier.csv");//�x�W�F�Ȑ��̃Z�b�g
std::vector<std::vector<double>>tranjectory;//�O��

//�v���E�X�Q��(�z�C���x�[�X2.75m,�S��4.6, ��1.78m,����1.42m,�^�C�����a0.317m) 
BasicCar car = BasicCar(2.75, 1.78, 0.925, 1.420, 0.317);
DrawLine line = DrawLine();

bool is_start = false;

int i = 0;

/*
 * ��ʕ\��
 */
static void display(void)
{
    double blue[] = { 0.2, 0.2, 0.8, 1.0 };  
    double red[] = { 0.8, 0.2, 0.2, 1.0 };

    const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* �����̈ʒu */



    /* ��ʃN���A */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* ���f���r���[�ϊ��s��̏����� */
    glLoadIdentity();

    /* �����̈ʒu��ݒ� */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* ���_�̈ړ��i�V�[���̕������Ɉڂ��j*/
    //gluLookAt(car_tranjectory[i][1] + MARGIN, car_tranjectory[i][2], 40.0, car_tranjectory[i][1] + MARGIN, car_tranjectory[i][2]+1, 1.0, 0.0, 0.0, 1.0); //�^��
    //gluLookAt(car_tranjectory[i][1]+MARGIN, -20.0, 1.0, car_tranjectory[i][1], -3.0, 0.0, 0.0, 0.0, 1.0); //�^��(�ԒǏ])
    gluLookAt(car_tranjectory[i][1] + 15, car_tranjectory[i][2], 1.0, car_tranjectory[i][1], car_tranjectory[i][2], 0.0, 0.0, 0.0, 1.0); //�^����(�ԒǏ])



    line.drawCurve(bezier_curve,0.1,red);//�x�W�F�Ȑ��̕`��
    line.drawCarTranjectory(tranjectory, 0.12, blue); //�Ԃ̋O��    

    std::cout << "x[" << i << "]: "<< car_tranjectory[i][1] << "  y[" << i << "]: " << car_tranjectory[i][2]
                  <<"  theta[" << i << "]: " << car_tranjectory[i][3] << "  phi" << i << "]: " << car_tranjectory[i][4]<<std::endl;

    car.DrawCar(car_tranjectory[i][0],car_tranjectory[i][1], car_tranjectory[i][2], car_tranjectory[i][3], car_tranjectory[i][4]);


    glutSwapBuffers();

    glFlush();
}

static void resize(int w, int h)
{
    /* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
    glViewport(0, 0, w, h);

    /* �����ϊ��s��̎w�� */
    glMatrixMode(GL_PROJECTION);

    /* �����ϊ��s��̏����� */
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    /* ���f���r���[�ϊ��s��̎w�� */
    glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
    /* ESC �� q ���^�C�v������I�� */
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
        tranjectory.clear();
    }

    if (i % 10 == 0) {
        std::vector<double> car_position = { car_tranjectory[i][1], car_tranjectory[i][2] };
        tranjectory.push_back(car_position);
    }

    glutPostRedisplay();
    glutTimerFunc(40, timer, 0);
}

static void init(void)
{
    /* �����ݒ� */
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