#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "BasicFunction.h"
#include "RollerWalkerModel.h"
#include "BaseShape.h"
#define OFF 0
#define ON  1
#define TO_M 0.1 //[10^(-1)m]��[m]�ւ̒P�ʕϊ�

#define PI 3.14159265359


//�p�x�̐���
#define MAX_PHI 89      //�p�̍ő�p
#define MIN_PHI -10     //�ŏ��̍ŏ��p
#define MAX_R 400
#define MIN_R 1

//�����_����̊p�x
int e_r = 50;           //���_�_�̋���[0.1m]
int e_theta = -60;      //���_�̕��ʊp��-180�x[deg]
int e_phi = 45;         //���_�̋p[deg]
int x_old = 0;          //�O��motion()���Ăяo���ꂽ�Ƃ��̃}�E�X��x���W
int y_old = 0;          //�O��motion()���Ăяo���ꂽ�Ƃ��̃}�E�X��y���W
int left_button = 0;  //�}�E�X�̍��{�^����������Ă��邩�ǂ����@0:OFF, 1:ON



RollerWalkerModel rollerwalker_model = RollerWalkerModel();
BaseShape baseshape = BaseShape();

/*
 * ��ʕ\��
 */
static void display(void){

    GLfloat lightpos[] = { 0.0, 0.0, 10.0, 1.0 }; /* �����̈ʒu */
    double e_x = 0.0, e_y = 0.0, e_z = 0.0;    //���_
    double f_x = 0.0, f_y = 0.0, f_z = 0.0;     //�����_(�Œ�)

    /* ��ʃN���A */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* ���f���r���[�ϊ��s��̏����� */
    glLoadIdentity();

    //���_�̈ړ�
    e_x = f_x + (double)e_r * TO_M * cos(degreeToRad(e_theta)) * cos(degreeToRad(e_phi));
    e_y = f_y + (double)e_r * TO_M * sin(degreeToRad(e_theta)) * cos(degreeToRad(e_phi));
    e_z = f_z + (double)e_r * TO_M * sin(degreeToRad(e_phi));

    lightpos[0] = e_x;
    lightpos[1] = e_y;
    lightpos[2] = e_z;
    

    std::cout<< "e_r: "<< e_r << "  e_theta: " << e_theta << "e_phi: " << e_phi << std::endl;


    /* ���_�̈ړ��i�V�[���̕������Ɉڂ��j*/
    gluLookAt(e_x,e_y,e_z,f_x,f_y,f_z,0.0,0.0,1.0); 
    /* �����̈ʒu��ݒ� */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    

    baseshape.myGround(0.0);
    baseshape.myCordinateSystem(8.0);

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



static void init(void)
{
    /* �����ݒ� */
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

void mouse(int button, int state, int x, int y) {//�}�E�X��������邽�тɌĂяo�����
    //�Ō�Ƀ}�E�X�������ꂽ�i�����ꂽ�j���̃{�^��
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

    //�}�E�X�z�C�[���ɂ�鎋�_�̉��߂̕ύX(�z�C�[���̉��ւ̉�]:button = 3, ��O�ւ̉�]: button = 4)
    if (button == 3) {//�z�C�[�������ɉ�] = ���_���߂Â���
        //if (state == GLUT_UP) return;    //glut_UP�̕��𖳎�(1��̉�]��UP��DOWN�̓��Ă΂�邽��)
        e_r--;
        if (e_r < MIN_R)e_r = MIN_R;
        glutPostRedisplay(); //���_���ύX���ꂽ���ߍĕ`��
    }
    else if (button == 4) {//�z�C�[������O�ɉ�] = ���_����������
        //if (state == GLUT_UP)return;    //glut_UP�̕��𖳎�(1��̉�]��UP��DOWN�̓��Ă΂�邽��)
        e_r++;
        if (e_r > MAX_R)e_r = MAX_R;
        glutPostRedisplay(); //���_���ύX���ꂽ���ߍĕ`��
    }

}

void motion(int x, int y) {
    if (left_button == 1) {//���{�^����������Ă��鎞�A���ʊp(��),�p(��)��ύX
        e_theta = e_theta - (x - x_old);    //�O��̃}�E�X�̈ʒu����̈ړ�����ɕύX
        e_phi = e_phi + (y - y_old);        //�O��̃}�E�X�̈ʒu����̈ړ�����ɕύX
    }

    
    

    //�p�̐���
    if (e_phi > MAX_PHI) {
        e_phi = MAX_PHI;
    }
    else if(e_phi < MIN_PHI){
        e_phi = MIN_PHI;
    }

    x_old = x;  //����motion()���Ăяo���ꂽ���̂��߂ɒl��ۑ�
    y_old = y;  //����motion()���Ăяo���ꂽ���̂��߂ɒl��ۑ�

    glutPostRedisplay();//�}�E�X���������������A�j���[�V����������
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