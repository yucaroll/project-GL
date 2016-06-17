#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <GL/GL.h>
#define PI 3.141592
void createCircle(GLfloat, GLfloat, GLfloat, GLfloat);
void createCylinder(GLfloat, GLfloat);
void createCylinder2(GLfloat,GLfloat,GLfloat);
void createHemiSphere2(GLfloat);
void createHemiSphere(GLfloat);
int LoadGLTextures();
AUX_RGBImageRec *LoadBMPFile(char *Filename);
float x, y, z;
float radius;
float theta;
float phi;
float zoom = 60.0;

int beforeX, beforeY;

GLuint texture[1];                          // �ؽ�ó �ϳ��� ������� ( ���ڵ� )

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);                // WndProc ����

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
    //glColor3fv(colors[a]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[a]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[b]);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[c]);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[d]);
    glEnd();
}

// 6���� ���� �����.
void createCube(void)
{
    polygon(0, 3, 2, 1);    // front
    polygon(2, 3, 7, 6);    // right
    polygon(3, 0, 4, 7);    // bottom
    polygon(4, 5, 6, 7);    // back
    polygon(1, 2, 6, 5);    // top
    polygon(5, 4, 0, 1);    // right
	
	/*
	glBegin(GL_QUADS);
       // �ո�
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);    // �ؽ�ó�� ������ ���ʾƷ�
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);    // �ؽ�ó�� ������ �����ʾƷ�
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);    // �ؽ�ó�� ������ ��������
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);    // �ؽ�ó�� ������ ������
       // �޸�
       glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // �ؽ�ó�� ������ �����ʾƷ�
       glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);    // �ؽ�ó�� ������ ��������
       glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);    // �ؽ�ó�� ������ ������
       glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);    // �ؽ�ó�� ������ ���ʾƷ�
       // ����
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);    // �ؽ�ó�� ������ ������
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);    // �ؽ�ó�� ������ ���ʾƷ�
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);    // �ؽ�ó�� ������ �����ʾƷ�
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);    // �ؽ�ó�� ������ ��������
       // �Ʒ���
       glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // �ؽ�ó�� ������ ��������
       glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);    // �ؽ�ó�� ������ ������
       glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);    // �ؽ�ó�� ������ ���ʾƷ�
       glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);    // �ؽ�ó�� ������ �����ʾƷ�
       // ������
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);    // �ؽ�ó�� ������ �����ʾƷ�
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);    // �ؽ�ó�� ������ ��������
       glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);    // �ؽ�ó�� ������ ������
       glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);    // �ؽ�ó�� ������ ���ʾƷ�
       // �޸�
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);    // �ؽ�ó�� ������ ���ʾƷ�
       glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);    // �ؽ�ó�� ������ �����ʾƷ�
       glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);    // �ؽ�ó�� ������ ��������
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);    // �ؽ�ó�� ������ ������
   glEnd();
   */
}

int init (void)
{
	 if (!LoadGLTextures())                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

   glEnable(GL_TEXTURE_2D);                        // �ؽ�ó ������ Ȱ��ȭ��Ŵ ( ���ڵ� )
   glShadeModel(GL_SMOOTH);                        // �ε巯�� ���̵��� Ȱ��ȭ��Ŵ
   glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                    // ������ ���
   glClearDepth(1.0f);                            // ���̹��� ����
   glEnable(GL_DEPTH_TEST);                        // �����׽�Ʈ�� ��
   glDepthFunc(GL_LEQUAL);                            // �����׽�Ʈ ����
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);            // ������ ���� ���� ���
   return TRUE;                                // �ʱ�ȭ ����
}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
//    glOrtho (-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // �ְ� ������� ǥ��.

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
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // �ְ� ������� ǥ��.

    x = radius * cos(phi) * cos(theta);
    y = radius * cos(phi) * sin(theta);
    z = radius * sin(phi);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	
    // (���� �� ���ڴ� ī�޶��� ��ġ, �߰��� �� ���ڴ� ī�޶��� ����,
    //  ���� �� ���ڴ� �������� ���� (0, 1, 0))���� ����� ������ ���δ�.
	/*
    glBegin(GL_LINES);  // X, Y, Z �� ǥ��
    glColor3f(1.0, 0.0, 0.0); // X��, red
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // Y��, green
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // Z��, blue
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
	*/
    //createCube();// ť�� ����
	
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.5);
	createCylinder2(2.0,2.0,3.0);   // body

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 1.8);
    glRotatef(90, 1.0, 0.0, 0.0);
    createHemiSphere2(2);    // head
	
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
	/*
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
	*/
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

    if ( theta > 2.0 * PI ) // 360�� �Ѿ��
        theta -= (2.0 * PI);
    else if ( theta < 0.0 )
        theta += (2.0 * PI);
}

void createHemiSphere2(GLfloat radius)
{
    GLfloat x = y = z = 0;
    /* function createHalfSphere()
    ���� �߽� x, y, z ��ǥ�� �޾� �ݱ��� ����� �Լ�
    x : �ݱ��� �߽� x ��ǥ
    y : �ݱ��� �߽� y ��ǥ
    z : �ݱ��� �߽� z ��ǥ
    raidus : �ݱ��� ������
    */
    GLfloat angley;  //y�� ���� ���ϱ� ���� ����
    GLfloat nexty;  //���� y�� ���� ���ϱ� ���� ����
    GLfloat anglex;  //x, y�� ���� ���ϱ� ���� ����

   // glColor3ub(153, 224, 0);  //�ݱ��� �� ����
    glBegin(GL_QUAD_STRIP);
    for(angley = 0.0f; angley <= (0.5f*PI); angley += ((0.5f*PI)/8.0f))  //�ݱ��� �׷��� �ϹǷ� 0.5����
    {
        y = radius*sin(angley);     //y�� �� ���
        nexty = angley+((0.5f*PI)/8.0f);  //���� angley�� ����
        for(anglex = 0.0f; anglex < (2.0f*PI); anglex += (PI/8.0f))
        {
            x = radius*cos(angley)*sin(anglex);
            z = radius*cos(angley)*cos(anglex);
			glTexCoord2d(x, nexty); 
            glNormal3f(-cos(angley)*sin(anglex), -sin(angley), -cos(angley)*cos(anglex)); //�ݱ��� �������� normal ���� ����
            glVertex3f(x, y, z);

            x = radius*cos(nexty)*sin(anglex);
            z = radius*cos(nexty)*cos(anglex);
			glTexCoord2d(x, nexty); 
            glNormal3f(-cos(nexty)*sin(anglex), -sin(nexty), -cos(nexty)*cos(anglex));
			glVertex3f(x, radius*sin(nexty), z);
        }
    }
    glEnd();

}


void createHemiSphere(GLfloat radius)
{
    GLfloat x = y = z = 0;
    /* function createHalfSphere()
    ���� �߽� x, y, z ��ǥ�� �޾� �ݱ��� ����� �Լ�
    x : �ݱ��� �߽� x ��ǥ
    y : �ݱ��� �߽� y ��ǥ
    z : �ݱ��� �߽� z ��ǥ
    raidus : �ݱ��� ������
    */
    GLfloat angley;  //y�� ���� ���ϱ� ���� ����
    GLfloat nexty;  //���� y�� ���� ���ϱ� ���� ����
    GLfloat anglex;  //x, y�� ���� ���ϱ� ���� ����

    glColor3ub(153, 224, 0);  //�ݱ��� �� ����
    glBegin(GL_QUAD_STRIP);
    for(angley = 0.0f; angley <= (0.5f*PI); angley += ((0.5f*PI)/8.0f))  //�ݱ��� �׷��� �ϹǷ� 0.5����
    {
        y = radius*sin(angley);     //y�� �� ���
        nexty = angley+((0.5f*PI)/8.0f);  //���� angley�� ����
        for(anglex = 0.0f; anglex < (2.0f*PI); anglex += (PI/8.0f))
        {
            x = radius*cos(angley)*sin(anglex);
            z = radius*cos(angley)*cos(anglex);
            glNormal3f(-cos(angley)*sin(anglex), -sin(angley), -cos(angley)*cos(anglex)); //�ݱ��� �������� normal ���� ����
            glVertex3f(x, y, z);

            x = radius*cos(nexty)*sin(anglex);
            z = radius*cos(nexty)*cos(anglex);
            glNormal3f(-cos(nexty)*sin(anglex), -sin(nexty), -cos(nexty)*cos(anglex));
            glVertex3f(x, radius*sin(nexty), z);
        }
    }
    glEnd();

}

void createCylinder2(GLfloat top, GLfloat bottom, GLfloat height)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  gluQuadricTexture(cylinder, GL_TRUE); 
  gluQuadricDrawStyle(cylinder, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, top, bottom, height, 20, 100);
  
  createCircle(top, height, 1.0f, 0.0f); // ����� ����
  createCircle(bottom, height, -1.0f, height); // ����� �ظ�
}

void createCircle(GLfloat r, GLfloat h, GLfloat pos, GLfloat move){
  GLfloat centerx = 0, centery = 0, centerz = 0;
  GLfloat x, y, angle;

  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0.0f, 0.0f);
  glNormal3f(0.0f, 0.0f, pos);
  glVertex3f(centerx, centery, centerz + move);
  for(angle = (2.0f*PI); angle > 0.0f; angle -= (PI/8.0f))
  {
      x = centerx + r*sin(angle);
      y = centery + r*cos(angle);
	  glTexCoord2f(x, y);
      glNormal3f(0.0f, 0.0f, pos);
      glVertex3f(x, y, centerz + move);
  }
  glEnd();
}

void createCylinder(GLfloat radius, GLfloat h)
{
    GLfloat centerx = 0, centery = 0, centerz = 0;
    /* function createCyliner()
    ������� �߽� x,y,z��ǥ, ������, ���̸� �޾� ������� �����ϴ� �Լ�(+z�������� ������ �þ)
    centerx : ����� ���� �߽� x��ǥ
    centery : ����� ���� �߽� y��ǥ
    centerz : ����� ���� �߽� z��ǥ
    radius : ������� ������
    h : ������� ����
    */
    GLfloat x, y, angle;

    glBegin(GL_TRIANGLE_FAN);           //������� ����
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

    glBegin(GL_QUAD_STRIP);            //������� ����
    for(angle = 0.0f; angle < (2.0f*PI); angle += (PI/8.0f))
    {
        x = centerx + radius*sin(angle);
        y = centery + radius*cos(angle);
        glNormal3f(sin(angle), cos(angle), 0.0f);
        glVertex3f(x, y, centerz);
        glVertex3f(x, y, centerz + h);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);           //������� �ظ�
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

AUX_RGBImageRec *LoadBMPFile(char *Filename)
{
	FILE *File=NULL;                            // ���� �ڵ�
	if (!Filename)                                // �����̸��� ���޵Ǿ����� Ȯ��
   {
       return NULL;                            // �׷��� �ʴٸ� NULL�� ��ȯ
   }

	File=fopen(Filename,"r");                        // ������ �����ϴ��� Ȯ��
	if (File)                                // ������ �����ϴ°�?
   {
       fclose(File);                            // �ڵ��� ����
       return auxDIBImageLoad(Filename);                // ��Ʈ���� �о���̰� �����͸� ��ȯ
   }

	return NULL;
}

int LoadGLTextures()
{
	int Status=FALSE;                            // ���� ǥ�ñ�
	AUX_RGBImageRec *TextureImage[1];                    // �ؽ�ó�� ��������� ����
	memset(TextureImage,0,sizeof(void *)*1);                // �����͸� NULL�� ����
	char* filename = "Data/texture.bmp";
	printf("%s\n",filename);
	if (TextureImage[0]=LoadBMPFile(filename))
	{
       Status=TRUE;                            // Status�� TRUE�� ����
	   glGenTextures(1, &texture[0]);                    // �ؽ�ó�� ����

       // ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
       glBindTexture(GL_TEXTURE_2D, texture[0]);
	   // �ؽ�ó�� �����
       glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);    // ���� ���͸�
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);    // ���� ���͸�
	}

	 if (TextureImage[0])                            // �ؽ�ó�� �����ϴ��� Ȯ��
   {
       if (TextureImage[0]->data)                    // �ؽ�ó �̹����� �����ϴ��� Ȯ��
       {
           free(TextureImage[0]->data);                // �ؽ�ó �̹��� �޸𸮸� ����
       }

       free(TextureImage[0]);                        // �̹��� ����ü�� ����
   }

	return Status;                                // Status�� ��ȯ
}

void main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("Cube");
    init();
    //InitLight();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    glutMainLoop();
}