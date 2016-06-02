#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <GL/GL.h>
#define PI 3.141592
void createCylinder(GLfloat, GLfloat);
void createHemiSphere(GLfloat);
float x, y, z;
float radius;
float theta;
float phi;
float zoom = 60.0;

int beforeX, beforeY;

GLfloat vertices[][3] = {
    { -1.0, -1.0, 1.0 },
    { -1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0 },
    { 1.0, -1.0, 1.0 },
    { -1.0, -1.0, -1.0 },
    { -1.0, 1.0, -1.0 },
    { 1.0, 1.0, -1.0 },
    { 1.0, -1.0, -1.0 }};

GLfloat colors[][3] = {
    { 1.0, 0.0, 0.0 },  // red
    { 1.0, 1.0, 0.0 },  // yellow
    { 0.0, 1.0, 0.0 },  // green
    { 0.0, 0.0, 1.0 },  // blue
    { 1.0, 1.0, 1.0 },  // white
    { 1.0, 0.0, 1.0 }}; // magenta

GLfloat JinmaeColors[][3] =
{
    { 243.0, 152.0, 0.0 },
    { 143.0, 195.0, 3.0 },
    { 0.0, 158.0, 150.0 },
    { 0.0, 104.0, 183.0 },
    { 146.0, 7.0, 131.0 },
    { 229.0, 0.0, 79.0 }
};
GLfloat JinmaeColorsAdjusted[6][3];

void InitLight()
{
    GLfloat MyLightPosition[] = {5.0, 5.0, 5.0, 0.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, MyLightPosition);
}

void InitLight_positional()
{
    GLfloat MyLightPosio[] = {1.0, 2.0, 3.0, 1.0};
    GLfloat MyLightDirection[] = {3.0, 4.0, 3.0};
    GLfloat MySpotAngle[] = {50.0};
    glEnable(GL_LIGHTING);
}
void polygon(int a, int b, int c, int d)
{
    glColor3fv(colors[a]);
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// 6개의 면을 만든다.
void createCube(void)
{
    polygon(0, 3, 2, 1);    // front
    polygon(2, 3, 7, 6);    // right
    polygon(3, 0, 4, 7);    // bottom
    polygon(4, 5, 6, 7);    // back
    polygon(1, 2, 6, 5);    // top
    polygon(5, 4, 0, 1);    // right
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST); // depth activation
}

void reshape (int w, int h)
{
    printf("reshape\n");
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
//    glOrtho (-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // 멀고 가까움을 표현.

    radius = 10.0;
    theta = 10.0;
    phi = -10.0;
}
void display (void)
{
//    printf("display\n");

    // for zoom
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // 멀고 가까움을 표현.

    x = radius * cos(phi) * cos(theta);
    y = radius * cos(phi) * sin(theta);
    z = radius * sin(phi);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    // (앞의 세 인자는 카메라의 위치, 중간의 세 인자는 카메라의 초점,
    //  뒤의 세 인자는 법선벡터 방향 (0, 1, 0))으로 해줘야 세워져 보인다.

    glBegin(GL_LINES);  // X, Y, Z 선 표시
    glColor3f(1.0, 0.0, 0.0); // X축, red
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // Y축, green
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // Z축, blue
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();

    //createCube();// 큐브 생성
    /*
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.5);
    glBegin(GL_POLYGON);
    glColor3ub(153, 224, 0);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 1.8, 1.8, 3, 30, 30);
    glEnd();
	*/
    //glutSolidCube(3);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.5);
	createCylinder(2, 3);   // body

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 3.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    createCylinder(0.1, 1.0); // left antenna

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 0.0, 3.0);
    glRotatef(30, 0.0, -1.0, 0.0);
    createCylinder(0.1, 1.0); // right antenna

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.5, 0.0, -1.0);
    createCylinder(0.4, 2.5); // left arm

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.5, 0.0, -1.0);
    createCylinder(0.4, 2.5); // right arm

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, 0.0, -2.8);
    createCylinder(0.4, 2.5); // ieft leg

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, 0.0, -2.8);
    createCylinder(0.4, 2.5); // right leg

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 1.8);
    glRotatef(90, 1.0, 0.0, 0.0);
    createHemiSphere(2);    // head

    glFlush ();
    glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y ) // why are there xx and yy?
{
    switch(key)
    {
        case 'a':
            zoom--;
            break;
        case 'z':
            zoom++;
            break;
    }

}

void processMouse(int button, int state, int x, int y)
{

    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            beforeX = x;
            beforeY = y;
            //printf("down- x:%d , y:%d\n ",x,y);
        }
        else{
            //printf("up- x:%d , y:%d\n ",x,y);
        }
    }
}

void processMouseMotion(int x, int y)
{
    //printf("process- x:%d , y:%d\n ",x,y);

    if(abs(beforeX-x) > abs(beforeY-y)){
        if(beforeX < x)
        {
            theta -= 0.1;
//            zoom--;
        }else if(beforeX > x){
            theta += 0.1;
//            zoom++;
        }
    }else {
        if(beforeY > y){
            phi -= 0.1;
        }else if(beforeY < y){
            phi -= 0.1;
        }
    }

    beforeX = x;
    beforeY = y;

    glutPostRedisplay();

    if ( theta > 2.0 * PI ) // 360도 넘어가면
        theta -= (2.0 * PI);
    else if ( theta < 0.0 )
        theta += (2.0 * PI);
}

void createHemiSphere(GLfloat radius)
{
    GLfloat x = y = z = 0;
    /* function createHalfSphere()
    구의 중심 x, y, z 좌표를 받아 반구를 만드는 함수
    x : 반구의 중심 x 좌표
    y : 반구의 중심 y 좌표
    z : 반구의 중심 z 좌표
    raidus : 반구의 반지름
    */
    GLfloat angley;  //y축 값을 구하기 위한 각도
    GLfloat nexty;  //다음 y축 값을 구하기 위한 각도
    GLfloat anglex;  //x, y축 값을 구하기 위한 각도

    glColor3ub(153, 224, 0);  //반구의 색 지정
    glBegin(GL_QUAD_STRIP);
    for(angley = 0.0f; angley <= (0.5f*PI); angley += ((0.5f*PI)/8.0f))  //반구만 그려야 하므로 0.5곱함
    {
        y = radius*sin(angley);     //y축 값 계산
        nexty = angley+((0.5f*PI)/8.0f);  //다음 angley값 저장
        for(anglex = 0.0f; anglex < (2.0f*PI); anglex += (PI/8.0f))
        {
            x = radius*cos(angley)*sin(anglex);
            z = radius*cos(angley)*cos(anglex);
            glNormal3f(-cos(angley)*sin(anglex), -sin(angley), -cos(angley)*cos(anglex)); //반구의 안쪽으로 normal 벡터 생성
            glVertex3f(x, y, z);

            x = radius*cos(nexty)*sin(anglex);
            z = radius*cos(nexty)*cos(anglex);
            glNormal3f(-cos(nexty)*sin(anglex), -sin(nexty), -cos(nexty)*cos(anglex));
            glVertex3f(x, radius*sin(nexty), z);
        }
    }
    glEnd();

}

void createCylinder(GLfloat radius, GLfloat h)
{
    GLfloat centerx = 0, centery = 0, centerz = 0;
    /* function createCyliner()
    원기둥의 중심 x,y,z좌표, 반지름, 높이를 받아 원기둥을 생성하는 함수(+z방향으로 원에서 늘어남)
    centerx : 원기둥 원의 중심 x좌표
    centery : 원기둥 원의 중심 y좌표
    centerz : 원기둥 원의 중심 z좌표
    radius : 원기둥의 반지름
    h : 원기둥의 높이
    */
    GLfloat x, y, angle;

    glBegin(GL_TRIANGLE_FAN);           //원기둥의 윗면
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor3ub(153, 224, 0);
    glVertex3f(centerx, centery, centerz);

    for(angle = 0.0f; angle < (2.0f*PI); angle += (PI/8.0f))
    {
        x = centerx + radius*sin(angle);
        y = centery + radius*cos(angle);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, centerz);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);            //원기둥의 옆면
    for(angle = 0.0f; angle < (2.0f*PI); angle += (PI/8.0f))
    {
        x = centerx + radius*sin(angle);
        y = centery + radius*cos(angle);
        glNormal3f(sin(angle), cos(angle), 0.0f);
        glVertex3f(x, y, centerz);
        glVertex3f(x, y, centerz + h);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);           //원기둥의 밑면
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(centerx, centery, centerz + h);
    for(angle = (2.0f*PI); angle > 0.0f; angle -= (PI/8.0f))
    {
        x = centerx + radius*sin(angle);
        y = centery + radius*cos(angle);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, centerz + h);
    }
    glEnd();
}

void main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("Cube");
    init();
//    InitLight();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    glutMainLoop();
}