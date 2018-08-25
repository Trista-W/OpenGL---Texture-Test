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

	//绘制像素
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

	//---------------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);

	glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转
	glColor3f(1.0f, 1.0f, 1.0f);

	//// 绘制底面以及纹理
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
//	//打开文件
//	FILE* pfile = fopen(FileName, "rb");
//	if (pfile == 0) exit(0);
//
//	//读取图像大小
//	fseek(pfile, 0x0012, SEEK_SET);
//	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
//	fread(&imageheight, sizeof(imageheight), 1, pfile);
//
//	//计算像素数据长度
//	pixellength = imagewidth * 3;
//	while (pixellength % 4 != 0)pixellength++;
//	pixellength *= imageheight;
//
//	//读取像素数据
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
//	//关闭文件
//	fclose(pfile);
//
//}
int main(int argc, char* argv[])
{
	GLuint texture_ID = 0;
	//打开文件
	FILE* pfile = fopen(FileName, "rb");
	if (pfile == 0) exit(0);

	//读取图像大小
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);

	//计算像素数据长度
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;

	//读取像素数据
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);

	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);	
	
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//关闭文件
	fclose(pfile);

	//初始化glut运行
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