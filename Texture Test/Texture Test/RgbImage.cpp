#include<gl/freeglut.h>
#define FileName "Texture.bmp"
#define _CRT_SECURE_NO_DEPRECATE
static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;
static GLfloat angle = 0.0f;
static GLuint texGround;

#include<stdio.h>
#include<stdlib.h>
#include <GL\freeglut.h>



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//��������
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

	//---------------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);

	glRotatef(angle, 0.0f, 0.0f, 1.0f); //��ת
	glColor3f(1.0f, 1.0f, 1.0f);

	//// ���Ƶ����Լ�����
	//glBindTexture(GL_TEXTURE_2D, texGround);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0.0f);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 0.0f);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 5.0f, 0.0f);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -5.0f, 0.0f);
	//glEnd();
	glFlush();
	glutSwapBuffers();
}

//GLuint LoadTexture(const char* FileName)
//{
//	GLuint texture_ID = 0;
//	//���ļ�
//	FILE* pfile = fopen(FileName, "rb");
//	if (pfile == 0) exit(0);
//
//	//��ȡͼ���С
//	fseek(pfile, 0x0012, SEEK_SET);
//	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
//	fread(&imageheight, sizeof(imageheight), 1, pfile);
//
//	//�����������ݳ���
//	pixellength = imagewidth * 3;
//	while (pixellength % 4 != 0)pixellength++;
//	pixellength *= imageheight;
//
//	//��ȡ��������
//	pixeldata = (GLubyte*)malloc(pixellength);
//	if (pixeldata == 0) exit(0);
//
//	fseek(pfile, 54, SEEK_SET);
//	fread(pixeldata, pixellength, 1, pfile);
//
//	glGenTextures(1, &texture_ID);
//	glBindTexture(GL_TEXTURE_2D, texture_ID);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//
//	//�ر��ļ�
//	fclose(pfile);
//
//}
int main(int argc, char* argv[])
{
	GLuint texture_ID = 0;
	//���ļ�
	FILE* pfile = fopen(FileName, "rb");
	if (pfile == 0) exit(0);

	//��ȡͼ���С
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);

	//�����������ݳ���
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;

	//��ȡ��������
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);	
	
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//�ر��ļ�
	fclose(pfile);

	//��ʼ��glut����
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(imagewidth, imageheight);
	glutCreateWindow(FileName);
	glutDisplayFunc(&display);
	glutMainLoop();
	//-------------------------------------
	free(pixeldata);

	return 0;
}