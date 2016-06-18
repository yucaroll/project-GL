#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <GL/GL.h>
#define TEX_SKIN 3
#define TEX_BLACK 1
#define TEX_SHOE 5
#define TEX_EYE 6
#define TEX_FACE 7
#define PI 3.141592
void createCircle(GLfloat, GLfloat, GLfloat);
void createCylinder(GLfloat, GLfloat);
void createCylinder2(GLfloat,GLfloat,GLfloat);
void createCylinder3(GLfloat,GLfloat,GLfloat, int, int);
void createHemiSphere2(GLfloat);
void createHemiSphere(GLfloat);
int LoadGLTextures(char*,int);
void createSphere(GLfloat);
AUX_RGBImageRec *LoadBMPFile(char *Filename);
float x, y, z;
float radius;
float theta;
float phi;
float zoom = 60.0;

int beforeX, beforeY;

GLuint texture[10];                          // �ؽ�ó �ϳ��� ������� ( ���ڵ� )

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
	GLfloat ambientLight[4];
    GLfloat diffuseLight[4];
    GLfloat lightPosition[4];
    GLfloat specular[4];
    GLfloat yrot;

	ambientLight[0] = 0.3f; 
    ambientLight[1] = 0.3f;
    ambientLight[2] = 0.3f;
    ambientLight[3] = 1.0f;

    diffuseLight[0] = 0.7f;
    diffuseLight[1] = 0.7f;
    diffuseLight[2] = 0.7f;
    diffuseLight[3] = 1.0f;

    lightPosition[0] = 0.0f;
    lightPosition[1] = 0.0f;
    lightPosition[2] = 5.0f;
    lightPosition[3] = 1.0f;

    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;

    yrot = 0.0f;

    //GLfloat MyLightPosition[] = {5.0, 5.0, 5.0, 0.0};
   // glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glLightfv(GL_LIGHT0, GL_POSITION, MyLightPosition);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //���� ȸ���� �������� ���� 
    glFrontFace(GL_CCW); //�ݽð�������� ���� �������� �ո�

    glEnable(GL_LIGHTING); //���� �ѱ�
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //����
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //����
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular); //����
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //����
    glEnable(GL_LIGHT0); // 0�� ���� ���


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
	if (!LoadGLTextures("Data/texture.bmp",0))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
	   printf("fail1");
       return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

	if (!LoadGLTextures("Data/black.bmp",TEX_BLACK))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail2");
	   return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

	if (!LoadGLTextures("Data/body.bmp",2))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail3");
	   return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

	if (!LoadGLTextures("Data/skin.bmp",TEX_SKIN))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail4");
	   return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

	if (!LoadGLTextures("Data/arm2.bmp",4))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail5");
	   return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

   if (!LoadGLTextures("Data/shoe.bmp",TEX_SHOE))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail5");
	   return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

   if (!LoadGLTextures("Data/eye.bmp",TEX_EYE))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail6");
	   return FALSE;                            // �ؽ�ó�� �ε����� �ʾҴٸ� FALSE�� ��ȯ ( ���ڵ� )
   }

    if (!LoadGLTextures("Data/face.bmp",TEX_FACE))                            // �ؽ�ó �ε� ��ƾ���� ������( ���ڵ� )
   {
       printf("fail7");
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
	
    glBindTexture(GL_TEXTURE_2D, texture[4]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.5, 0.0, -0.5);
	glRotatef(30, 0.0, -1.0, 0.0);
    createCylinder3(0.4, 0.4, 2.0,TEX_SKIN,TEX_BLACK); // right arm
	
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, -2.0, 1.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
    createCylinder3(0.4, 0.4, 2.0,TEX_SKIN,TEX_BLACK); // left arm
	
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, 0.0, -3.2);
    createCylinder2(0.4, 1.0, 3.0); // ieft leg

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, 0.0, -3.2);
    createCylinder2(0.4, 1.0, 3.0); // right leg

    glBindTexture(GL_TEXTURE_2D, texture[2]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.5);
	createCylinder3(2.3,1.3,3.0,TEX_BLACK,TEX_BLACK);   // body

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, -2.0, 1.0);
    createSphere(0.4f); // left hand

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.4, -2.2, 1.2);
    createCylinder2(0.1, 0.1, 0.4); // left finger

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.4, -2.2, 1.6);
    createSphere(0.1f); // left finger point

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.9, -2.2, 1.0);
	glRotatef(90.0, 0.0, -1.0, 0.0);
    createCylinder2(0.1, 0.1, 0.4); // left finger2
	
	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.9, -2.2, 1.0);
    createSphere(0.1f); // left finger2 point

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.5, 0.0, -0.5);
    createSphere(0.4f); // right hand
	
	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, 0.0, 1.0);
    createSphere(0.4f); // left sholder

	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.5, 0.0, 1.2);
    createSphere(0.4f); // right sholder

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SHOE]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, 0.0, -3.2);
    createSphere(0.4f); // right shoe

	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, 0.0, -3.2);
    createSphere(0.4f); // left shoe
	
	/*
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 1.8);
	createCircle(2,1.0f,0.0f);// head bottom
*/

	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);			// �޸Ӹ�
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.5, -0.1, 3.6);
	glRotatef(50, 0.0, -1.0, 0.0);
	glScalef(1.0, 1.0, 0.8);
    createSphere(1.8f);

	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);			// �޸Ӹ�
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.5, -0.1, 3.6);
	glRotatef(-50, 0.0, -1.0, 0.0);
	glScalef(1.0, 1.0, 0.8);
    createSphere(1.8f);

	glBindTexture(GL_TEXTURE_2D, texture[TEX_FACE]);			// �ĵο�
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 3.0);
    createSphere(2.0f);

	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);			// �޸Ӹ�
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.3, 3.2);
    createSphere(2.0f);

	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.0, 0.6, 2.2);
	glRotatef(-60, 0.0, -1.0, 0.0);
	glScalef(4.0, 1.0, 1.3);
    createSphere(0.4f);

	glBindTexture(GL_TEXTURE_2D, texture[TEX_BLACK]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.0, 0.6, 2.2);
	glRotatef(60, 0.0, -1.0, 0.0);
	glScalef(4.0, 1.0, 1.3);
    createSphere(0.4f);
	/*
	glBindTexture(GL_TEXTURE_2D, texture[TEX_EYE]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.0, -1.1, 3.1);
	glRotatef(30, 0.0, 0.0, 1.0);
    createSphere(0.7f); // right eye
	*/
/*
	glBindTexture(GL_TEXTURE_2D, texture[0]);			// ���ο�
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.0, 2.5);
    createSphere(2.0f);
	*/

	/*
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 1.8);
    glRotatef(90, 1.0, 0.0, 0.0);
    createHemiSphere(2);    // head
	*/

	/* ��Ÿ�� ������
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    createSphere(3);
	*/

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
            theta -= 0.2;
//            zoom--;
        }else if(beforeX > x){
            theta += 0.2;
//            zoom++;
        }
    }else {
        if(beforeY > y){
            phi -= 0.2;
        }else if(beforeY < y){
            phi -= 0.2;
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

void createSphere(GLfloat r)
{
GLUquadricObj *sphere = gluNewQuadric();
  
  gluQuadricTexture(sphere, GL_TRUE); 
  gluQuadricDrawStyle(sphere, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(sphere, GLU_SMOOTH);
  gluSphere(sphere,r,36 ,18);
}

void createCylinder3(GLfloat top, GLfloat bottom, GLfloat height, int texture1, int texture2)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE); 
  gluQuadricDrawStyle(cylinder, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, top, bottom, height, 20, 100);
  
  glBindTexture(GL_TEXTURE_2D, texture[texture1]);
  createCircle(top, 1.0f, 0.0f); // ����� ����
  glBindTexture(GL_TEXTURE_2D, texture[texture2]);
  createCircle(bottom, -1.0f, height); // ����� �ظ�
}

void createCylinder2(GLfloat top, GLfloat bottom, GLfloat height)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE); 
  gluQuadricDrawStyle(cylinder, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, top, bottom, height, 20, 100);
  
  createCircle(top, 1.0f, 0.0f); // ����� ����
  createCircle(bottom, -1.0f, height); // ����� �ظ�
}

void createCircle(GLfloat r, GLfloat pos, GLfloat move){
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

int LoadGLTextures(char* filename, int num)
{
	int Status=FALSE;                            // ���� ǥ�ñ�
	AUX_RGBImageRec *TextureImage[1];                    // �ؽ�ó�� ��������� ����
	memset(TextureImage,0,sizeof(void *)*1);                // �����͸� NULL�� ����

	printf("%s\n",filename);
	if (TextureImage[0]=LoadBMPFile(filename))
	{
       Status=TRUE;                            // Status�� TRUE�� ����
	   glGenTextures(1, &texture[num]);                    // �ؽ�ó�� ����

       // ��Ʈ�����κ��� ������ �����͸� ����� �Ϲ����� �ؽ�ó ����
       glBindTexture(GL_TEXTURE_2D, texture[num]);
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
    glutCreateWindow ("IU YOU&I ver");
    init();
    InitLight();
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    glutMainLoop();
}