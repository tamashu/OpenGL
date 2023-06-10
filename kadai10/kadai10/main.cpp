#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "BasicCar.h"
#include "BasicFunction.h"

//�v���E�X�Q��(�z�C���x�[�X2.75m,�S��4.6, ��1.78m,����1.42m,�^�C�����a0.317m) 
BasicCar car = BasicCar(2.75, 1.78, 0.925, 1.420, 0.317);
int i = 0;

/*
 * ��ʕ\��
 */
static void display(void)
{
    const static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };     /* ���̐F */
    const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* �����̈ʒu */

  

    /* ��ʃN���A */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* ���f���r���[�ϊ��s��̏����� */
    glLoadIdentity();

    /* �����̈ʒu��ݒ� */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* ���_�̈ړ��i�V�[���̕������Ɉڂ��j*/
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
    /* �����ݒ� */
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