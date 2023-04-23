#include <GL/glut.h>
#include <iostream>

#define MAXPOINTS 100      /* �L������_�̐��@�@ */
GLint point[MAXPOINTS][2]; /* ���W���L������z�� */
int pointnum = 0;          /* �L���������W�̐��@ */
int rubberband = 0;        /* ���o�[�o���h�̏��� */

int window_h;
int window_w;

int mode = 1;

//�v���g�^�C�v�錾
void write_grid();
void write_square(int* left_top, int* left_buttom, int* right_buttom, int* right_top);
void write_colorful_square(int* left_top, int* left_buttom, int* right_buttom, int* right_top);
void mouse_test1(int button, int state, int x, int y);
void mouse_test2(int button, int state, int x, int y);
void mouse_test3(int button, int state, int x, int y);
void mouse_test4(int button, int state, int x, int y);
void mouse_test5(int button, int state, int x, int y);





void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (mode == 2) {
        write_grid();
    }
    else if (mode >= 4) {
        /* �L�^�����f�[�^�Ő���`�� */
        

        if (mode == 6) {
            //glLogicOp�����p
            int margin = 80;
            int l_top[] = { margin,margin };
            int l_buttom[] = { margin,window_h - margin };
            int r_buttom[] = { window_w - margin,window_h - margin };
            int r_top[] = { window_w - margin,margin };

            write_colorful_square(l_top, l_buttom, r_buttom, r_top);


        }
        if (pointnum > 1) {
            if (mode == 6) {
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_INVERT);
            }
            else {
                glColor3d(0.0, 0.0, 0.0);
            }
            glBegin(GL_LINES);
            for (int i = 0; i < pointnum; ++i) {
                glVertex2iv(point[i]);
            }
            glEnd();
            glDisable(GL_COLOR_LOGIC_OP);
        }

    }
    
    

    
    

}

void resize(int w, int h)
{
    window_h = h;
    window_w = w;

    glViewport(0, 0, w, h);/* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
    glLoadIdentity();/* �ϊ��s��̏�����(�P�ʍs��ɂ���j */
    std::cout << "w: " << w << " h: " << h << std::endl;
    /* �X�N���[����̍��W�n���}�E�X�̍��W�n�Ɉ�v������ */
    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);

}



void mouse(int button, int state, int x, int y)
{
    switch (mode)
    {
        case 1:
            mouse_test1(button, state, x, y);//�ŏ��̃}�E�X�̈ʒu�A��Ԃ�\������v���O����
            break;
        case 2:
            mouse_test2(button, state, x, y);//glOrtho�̐����p
            break;
        case 3:
            mouse_test3(button, state, x, y);//�}�E�X��p�����}�̕`��
            break;
        case 4:
            mouse_test4(button, state, x, y);//�}�̕ێ�
            break;
        case 5:
            mouse_test5(button, state, x, y);//���o�[�o���h�̕\��
            break;
        case 6:
            mouse_test5(button, state, x, y);//���o�[�o���h�̕\��
            break;
        default:
            break;
    }
    
}

void motion(int x, int y){
    if (mode >= 5) {
        glLineWidth(7.0);

        static GLint savepoint[2]; /* �ȑO�̃��o�[�o���h�̒[�_ */

        /* �_�����Z�@�\ ON */
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_INVERT);

        glBegin(GL_LINES);
        if (rubberband) {
            /* �ȑO�̃��o�[�o���h������ */
            glVertex2iv(point[pointnum - 1]);
            glVertex2iv(savepoint);
        }
        /* �V�������o�[�o���h��`�� */
        glVertex2iv(point[pointnum - 1]);
        glVertex2i(x, y);
        glEnd();

        glFlush();

        /* �_�����Z�@�\ OFF */
        glLogicOp(GL_COPY);
        glDisable(GL_COLOR_LOGIC_OP);

        /* ���`�������o�[�o���h�̒[�_��ۑ� */
        savepoint[0] = x;
        savepoint[1] = y;

        /* ���`�������o�[�o���h�͎��̃^�C�~���O�ŏ��� */
        rubberband = 1;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
    case 'q':
    case 'Q':
    case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
        exit(0);
    case '1':
        mode = 16;
        break;
    case '2':
        mode = 2;
        break;
    case '3':
        mode = 3;
        break;
    case '4':
        mode = 4;
        break;
    case '5':
        mode = 5;
        break;
    case '6':
        mode = 6;
        break;
    default:
        break;
    }
    std::cout << "mode: " << mode << std::endl;
    pointnum = 0;
    glutPostRedisplay();
    
}


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    std::cout << "initialized " << std::endl;
}



int main(int argc, char* argv[])
{
    glutInitWindowSize(650, 500);
    glutInit(&argc, argv);			//GLUT,OPENGL�̏������i������main�̈����Ɠ����j
    glutInitDisplayMode(GLUT_RGBA);	//�f�B�X�v���C�̕\�����[�h�̐ݒ�@������GLUT_RGBA�͐F�̎w������̎O���F�{�����x�ōs��
    glutCreateWindow("�e�X�g");		//�E�B���h�E�̍쐬���s���i�����̓E�B���h�E�̖��O�j
    glutDisplayFunc(display);		//�����̓E�B���h�E���ɕ`�悷��֐��ւ̃|�C���^
    glutReshapeFunc(resize);		//��ʕύX���̏���
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();					//�v���O�������C�x���g�̑҂���ԂƂȂ�i�������[�v�j
    return 0;
}

void write_grid() { //glOrtho�����p�v���O����
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 0.0);
    //�c���̕`��
    for (int i = 0; i <= window_w; i += 50) {

        glVertex2i(i, 0);
        glVertex2i(i, window_h);
    }

    //�����̕`��
    for (int i = 0; i <= window_h; i += 50) {
        //�c��
        glVertex2i(0, i);
        glVertex2i(window_w, i);
    }
    glEnd();

}

void write_square(int* left_top, int* left_buttom, int* right_buttom, int* right_top) { //�����`�`��


    glBegin(GL_POLYGON);

    glVertex2d(left_top[0], left_top[1]);          //����
    glVertex2d(left_buttom[0], left_buttom[1]);    //����
    glVertex2d(right_buttom[0], right_buttom[1]);  //�E��
    glVertex2d(right_top[0], right_top[1]);        //�E��

    glEnd();


}

void write_colorful_square(int* left_top, int* left_buttom, int* right_buttom, int* right_top) { //�����`�`��)

    int harf_top[2] = { window_w / 2, right_top[1] };
    int harf_buttom[2] = { window_w / 2, right_buttom[1] };

    glColor3d(1.0, 0.0, 0.0);
    write_square(left_top, left_buttom, harf_buttom, harf_top);

    glColor3d(0.0, 1.0, 0.0);
    write_square(harf_top, harf_buttom, right_buttom, right_top);

}


void mouse_test1(int button, int state, int x, int y) {
    //�ŏ��̃v���O����
    switch (button) {
    case GLUT_LEFT_BUTTON:
        printf("left");
        break;
    case GLUT_MIDDLE_BUTTON:
        printf("middle");
        break;
    case GLUT_RIGHT_BUTTON:
        printf("right");
        break;
    default:
        break;
    }

    printf(" button is ");

    switch (state) {
    case GLUT_UP:
        printf("up");
        break;
    case GLUT_DOWN:
        printf("down");
        break;
    default:
        break;
    }

    printf(" at (%d, %d)\n", x, y);

}

void mouse_test2(int button, int state, int x, int y) {
    //glOrtho�̐����p
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_UP) {
            std::cout << "left(x.y) = (" << x / 50 << " , " << y / 50 << ")" << std::endl;
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }
}

void mouse_test3(int button, int state, int x, int y) {//7.1��ځi�}�E�X��p�����}�`�̕\��

    static int x0, y0;

    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_UP) {
            /* �{�^�����������ʒu���痣�����ʒu�܂Ő������� */
            glColor3d(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2i(x0, y0);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
        else {
            /* �{�^�����������ʒu���o���� */
            x0 = x;
            y0 = y;
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        /* �폜 */
        break;
    case GLUT_RIGHT_BUTTON:
        /* �폜 */
        break;
    default:
        break;
    }
}

void mouse_test4(int button, int state, int x, int y) {//�`�����G��ێ��idisplay()���v�ύX
    switch (button) {
    case GLUT_LEFT_BUTTON:
        /* �{�^���𑀍삵���ʒu���L�^���� */
        point[pointnum][0] = x;
        point[pointnum][1] = y;
        if (state == GLUT_UP) {
            /* �{�^�����������ʒu���痣�����ʒu�܂Ő������� */
            glColor3d(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2iv(point[pointnum - 1]); /* ��O�͉������ʒu�@ */
            glVertex2iv(point[pointnum]);     /* ���̈ʒu�͗������ʒu */
            glEnd();
            glFlush();
        }
        else {
            /* �폜 */
        }
        if (pointnum < MAXPOINTS - 1) ++pointnum;
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }
}

void mouse_test5(int button, int state, int x, int y) {//���o�[�o���h
    switch (button) {
    case GLUT_LEFT_BUTTON:
        /* �{�^���𑀍삵���ʒu���L�^���� */
        point[pointnum][0] = x;
        point[pointnum][1] = y;
        if (state == GLUT_UP) {
            /* �{�^�����������ʒu���痣�����ʒu�܂Ő������� */
            glColor3d(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2iv(point[pointnum - 1]); /* ��O�͉������ʒu�@ */
            glVertex2iv(point[pointnum]);     /* ���̈ʒu�͗������ʒu */
            glEnd();
            glFlush();

            /* �n�_�ł̓��o�[�o���h��`���Ă��Ȃ��̂ŏ����Ȃ� */
            rubberband = 0;
        }
        else {
        }
        if (pointnum < MAXPOINTS) ++pointnum;
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    default:
        break;
    }
}