#include <GL/glut.h>
#include <iostream>

#define MAXPOINTS 100      /* 記憶する点の数　　 */
GLint point[MAXPOINTS][2]; /* 座標を記憶する配列 */
int pointnum = 0;          /* 記憶した座標の数　 */
int rubberband = 0;        /* ラバーバンドの消去 */

int window_h;
int window_w;

int mode = 1;

//プロトタイプ宣言
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
        /* 記録したデータで線を描く */
        

        if (mode == 6) {
            //glLogicOp説明用
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

    glViewport(0, 0, w, h);/* ウィンドウ全体をビューポートにする */
    glLoadIdentity();/* 変換行列の初期化(単位行列にする） */
    std::cout << "w: " << w << " h: " << h << std::endl;
    /* スクリーン上の座標系をマウスの座標系に一致させる */
    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);

}



void mouse(int button, int state, int x, int y)
{
    switch (mode)
    {
        case 1:
            mouse_test1(button, state, x, y);//最初のマウスの位置、状態を表示するプログラム
            break;
        case 2:
            mouse_test2(button, state, x, y);//glOrthoの説明用
            break;
        case 3:
            mouse_test3(button, state, x, y);//マウスを用いた図の描画
            break;
        case 4:
            mouse_test4(button, state, x, y);//図の保持
            break;
        case 5:
            mouse_test5(button, state, x, y);//ラバーバンドの表示
            break;
        case 6:
            mouse_test5(button, state, x, y);//ラバーバンドの表示
            break;
        default:
            break;
    }
    
}

void motion(int x, int y){
    if (mode >= 5) {
        glLineWidth(7.0);

        static GLint savepoint[2]; /* 以前のラバーバンドの端点 */

        /* 論理演算機能 ON */
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_INVERT);

        glBegin(GL_LINES);
        if (rubberband) {
            /* 以前のラバーバンドを消す */
            glVertex2iv(point[pointnum - 1]);
            glVertex2iv(savepoint);
        }
        /* 新しいラバーバンドを描く */
        glVertex2iv(point[pointnum - 1]);
        glVertex2i(x, y);
        glEnd();

        glFlush();

        /* 論理演算機能 OFF */
        glLogicOp(GL_COPY);
        glDisable(GL_COLOR_LOGIC_OP);

        /* 今描いたラバーバンドの端点を保存 */
        savepoint[0] = x;
        savepoint[1] = y;

        /* 今描いたラバーバンドは次のタイミングで消す */
        rubberband = 1;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
    case 'q':
    case 'Q':
    case '\033':  /* '\033' は ESC の ASCII コード */
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
    glutInit(&argc, argv);			//GLUT,OPENGLの初期化（引数はmainの引数と同じ）
    glutInitDisplayMode(GLUT_RGBA);	//ディスプレイの表示モードの設定　引数のGLUT_RGBAは色の指定を光の三原色＋透明度で行う
    glutCreateWindow("テスト");		//ウィンドウの作成を行う（引数はウィンドウの名前）
    glutDisplayFunc(display);		//引数はウィンドウ内に描画する関数へのポインタ
    glutReshapeFunc(resize);		//画面変更時の処理
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();					//プログラムがイベントの待ち状態となる（無限ループ）
    return 0;
}

void write_grid() { //glOrtho説明用プログラム
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 0.0);
    //縦線の描画
    for (int i = 0; i <= window_w; i += 50) {

        glVertex2i(i, 0);
        glVertex2i(i, window_h);
    }

    //横線の描画
    for (int i = 0; i <= window_h; i += 50) {
        //縦線
        glVertex2i(0, i);
        glVertex2i(window_w, i);
    }
    glEnd();

}

void write_square(int* left_top, int* left_buttom, int* right_buttom, int* right_top) { //正方形描画


    glBegin(GL_POLYGON);

    glVertex2d(left_top[0], left_top[1]);          //左上
    glVertex2d(left_buttom[0], left_buttom[1]);    //左下
    glVertex2d(right_buttom[0], right_buttom[1]);  //右下
    glVertex2d(right_top[0], right_top[1]);        //右上

    glEnd();


}

void write_colorful_square(int* left_top, int* left_buttom, int* right_buttom, int* right_top) { //正方形描画)

    int harf_top[2] = { window_w / 2, right_top[1] };
    int harf_buttom[2] = { window_w / 2, right_buttom[1] };

    glColor3d(1.0, 0.0, 0.0);
    write_square(left_top, left_buttom, harf_buttom, harf_top);

    glColor3d(0.0, 1.0, 0.0);
    write_square(harf_top, harf_buttom, right_buttom, right_top);

}


void mouse_test1(int button, int state, int x, int y) {
    //最初のプログラム
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
    //glOrthoの説明用
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

void mouse_test3(int button, int state, int x, int y) {//7.1二つ目（マウスを用いた図形の表示

    static int x0, y0;

    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_UP) {
            /* ボタンを押した位置から離した位置まで線を引く */
            glColor3d(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2i(x0, y0);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
        else {
            /* ボタンを押した位置を覚える */
            x0 = x;
            y0 = y;
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        /* 削除 */
        break;
    case GLUT_RIGHT_BUTTON:
        /* 削除 */
        break;
    default:
        break;
    }
}

void mouse_test4(int button, int state, int x, int y) {//描いた絵を保持（display()も要変更
    switch (button) {
    case GLUT_LEFT_BUTTON:
        /* ボタンを操作した位置を記録する */
        point[pointnum][0] = x;
        point[pointnum][1] = y;
        if (state == GLUT_UP) {
            /* ボタンを押した位置から離した位置まで線を引く */
            glColor3d(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2iv(point[pointnum - 1]); /* 一つ前は押した位置　 */
            glVertex2iv(point[pointnum]);     /* 今の位置は離した位置 */
            glEnd();
            glFlush();
        }
        else {
            /* 削除 */
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

void mouse_test5(int button, int state, int x, int y) {//ラバーバンド
    switch (button) {
    case GLUT_LEFT_BUTTON:
        /* ボタンを操作した位置を記録する */
        point[pointnum][0] = x;
        point[pointnum][1] = y;
        if (state == GLUT_UP) {
            /* ボタンを押した位置から離した位置まで線を引く */
            glColor3d(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2iv(point[pointnum - 1]); /* 一つ前は押した位置　 */
            glVertex2iv(point[pointnum]);     /* 今の位置は離した位置 */
            glEnd();
            glFlush();

            /* 始点ではラバーバンドを描いていないので消さない */
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