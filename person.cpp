#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <GL/GL.h>
#define TEX_BLACK 1
#define TEX_BODY 2
#define TEX_SKIN 3
#define TEX_ARM 4
#define TEX_SHOE 5
#define TEX_EYE 6
#define TEX_FACE 7
#define TEX_HAIR 8
#define PI 3.141592
void createCircle(GLfloat, GLfloat, GLfloat);
void createCylinder(GLfloat,GLfloat,GLfloat);
void createCylinder_tex(GLfloat,GLfloat,GLfloat, int, int);
int LoadGLTextures(char*,int);
void createSphere(GLfloat);
AUX_RGBImageRec *LoadBMPFile(char *Filename);
float x, y, z;
float radius;
float theta;
float phi;
float zoom = 60.0;

int beforeX, beforeY;

GLuint texture[10];                          // �ؽ�ó �������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);                // WndProc ����

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

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //���� ȸ���� �������� ���� 
    glFrontFace(GL_CCW); //�ݽð�������� ���� �������� �ո�

    glEnable(GL_LIGHTING); //���� �ѱ�
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //����
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //����
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular); //����
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //����
    glEnable(GL_LIGHT0); // 0�� ���� ���
}

int init (void)
{
	// texture loading
	LoadGLTextures("Data/black.bmp",TEX_BLACK);
	LoadGLTextures("Data/body.bmp",TEX_BODY);
	LoadGLTextures("Data/skin.bmp",TEX_SKIN);
	LoadGLTextures("Data/arm.bmp",TEX_ARM);
	LoadGLTextures("Data/shoe.bmp",TEX_SHOE);
	LoadGLTextures("Data/eye.bmp",TEX_EYE);
	LoadGLTextures("Data/face.bmp",TEX_FACE);
	LoadGLTextures("Data/hair.bmp",TEX_HAIR);

	glEnable(GL_TEXTURE_2D);                        // �ؽ�ó ������ Ȱ��ȭ��Ŵ ( ���ڵ� )
	glShadeModel(GL_SMOOTH);                        // �ε巯�� ���̵��� Ȱ��ȭ��Ŵ
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                    // ������ ���
    glClearDepth(1.0f);                            // ���̹��� ����
    glEnable(GL_DEPTH_TEST);                        // �����׽�Ʈ�� ��
    glDepthFunc(GL_LEQUAL);                            // �����׽�Ʈ ����
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);            // ���� ���
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
	
	// modeling & texure mapping
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.5, 0.0, -0.5);
	glRotatef(30, 0.0, -1.0, 0.0);
    createCylinder_tex(0.4, 0.4, 2.0,TEX_SKIN,TEX_BLACK); // right arm
	
    glBindTexture(GL_TEXTURE_2D, texture[TEX_ARM]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, -2.0, 1.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
    createCylinder_tex(0.4, 0.4, 2.0,TEX_SKIN,TEX_BLACK); // left arm
	
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, 0.0, -3.2);
    createCylinder(0.4, 1.0, 3.0); // ieft leg
	
    glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, 0.0, -3.2);
    createCylinder(0.4, 1.0, 3.0); // right leg

    glBindTexture(GL_TEXTURE_2D, texture[TEX_BODY]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -1.5);
	createCylinder_tex(2.3,1.3,3.0,TEX_BLACK,TEX_BLACK);   // body

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, -2.0, 1.0);
    createSphere(0.4f); // left hand

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.4, -2.2, 1.2);
    createCylinder(0.1, 0.1, 0.4); // left finger

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.4, -2.2, 1.6);
    createSphere(0.1f); // left finger point

	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.05, -2.2, 1.0);
	glRotatef(90.0, 0.0, -1.0, 0.0);
    createCylinder(0.1, 0.1, 0.4); // left finger2
	
	glBindTexture(GL_TEXTURE_2D, texture[TEX_SKIN]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.05, -2.2, 1.0);
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
	
	glBindTexture(GL_TEXTURE_2D, texture[TEX_SHOE]);
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, 0.0, -3.2);
    createSphere(0.4f); // left shoe

	glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);			
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.5, -0.1, 3.6);
	glRotatef(50, 0.0, -1.0, 0.0);
	glScalef(1.0, 1.0, 0.8);
    createSphere(1.8f); // left hair
	
	glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);			
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.5, -0.1, 3.6);
	glRotatef(-50, 0.0, -1.0, 0.0);
	glScalef(1.0, 1.0, 0.8);
    createSphere(1.8f); // right hair
	
	glBindTexture(GL_TEXTURE_2D, texture[TEX_FACE]);			
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 3.0);
	glScalef(0.9, 1.0, 1.0);
    createSphere(2.0f); // head

	glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);			
	glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.3, 3.2);
	glRotatef(-180, 0.0, 0.0, 1.0);
    createSphere(2.0f); // back hair

	glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.0, 0.6, 2.2);
	glRotatef(-60, 0.0, -1.0, 0.0);
	glScalef(4.0, 1.2, 1.3);
    createSphere(0.4f); // right pony

	glBindTexture(GL_TEXTURE_2D, texture[TEX_HAIR]);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.0, 0.6, 2.2);
	glRotatef(60, 0.0, -1.0, 0.0);
	glScalef(4.0, 1.2, 1.3);
    createSphere(0.4f); // left pony
	
    glFlush ();
    glutSwapBuffers();
}

// ZOOM
void keyboard( unsigned char key, int x, int y )
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

// VIEWPOINT 1
void processMouse(int button, int state, int x, int y)
{

    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            beforeX = x;
            beforeY = y;
        }
    }
}

// VIEWPOINT 2
void processMouseMotion(int x, int y)
{
    if(abs(beforeX-x) > abs(beforeY-y)){
        if(beforeX < x)
        {
            theta -= 0.2;
        }else if(beforeX > x){
            theta += 0.2;
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

void createSphere(GLfloat r)
{
GLUquadricObj *sphere = gluNewQuadric();
  
  gluQuadricTexture(sphere, GL_TRUE); 
  gluQuadricDrawStyle(sphere, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(sphere, GLU_SMOOTH);
  gluSphere(sphere,r,36 ,18);
}

void createCylinder_tex(GLfloat bottom, GLfloat top, GLfloat height, int texture1, int texture2)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE); 
  gluQuadricDrawStyle(cylinder, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, bottom, top, height, 20, 100);
  
  glBindTexture(GL_TEXTURE_2D, texture[texture1]);
  createCircle(bottom, 1.0f, 0.0f); // ����� �ظ�
  glBindTexture(GL_TEXTURE_2D, texture[texture2]);
  createCircle(top, -1.0f, height); // ����� ����
}

void createCylinder(GLfloat bottom, GLfloat top, GLfloat height)
{
  GLUquadricObj *cylinder = gluNewQuadric();
  
  gluQuadricTexture(cylinder, GL_TRUE); 
  gluQuadricDrawStyle(cylinder, GLU_FILL); 
  glPolygonMode(GL_FRONT, GL_FILL); 
  gluQuadricNormals(cylinder, GLU_SMOOTH);
  gluCylinder(cylinder, bottom, top, height, 20, 100);
  
  createCircle(bottom, 1.0f, 0.0f); // ����� �ظ�
  createCircle(top, -1.0f, height); // ����� ����
}

// for cylinder top & bottom
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

// texure load 1
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

// texure load 2
int LoadGLTextures(char* filename, int num)
{
	int Status=FALSE;                            // ���� ǥ�ñ�
	AUX_RGBImageRec *TextureImage[1];                    // �ؽ�ó�� ��������� ����
	memset(TextureImage,0,sizeof(void *)*1);                // �����͸� NULL�� ����

	//printf("%s\n",filename);
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