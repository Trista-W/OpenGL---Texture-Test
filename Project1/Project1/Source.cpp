//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#define FileName "Texture.bmp"
#define _CRT_SECURE_NO_DEPRECATE
//#define WindowWidth  400
//#define WindowHeight 400
//#define WindowTitle  "OpenGL Texture Test"

static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;


//定义两个纹理对象编号
GLuint texGround;

static GLfloat angle = 0.0f;





//void display(void)
//{
//	// 清除屏幕
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear to black
//	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
//
//	// 设置视角
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(100, 1, 1, 21);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);
//
//	glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转
//	glColor3f(1.0f, 1.0f, 1.0f);
//
//	// 绘制底面以及纹理
//	glBindTexture(GL_TEXTURE_2D, texGround);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0.0f);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 0.0f);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 5.0f, 0.0f);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -5.0f, 0.0f);
//	glEnd();
//
//	glutSwapBuffers();
//}
//
//GLuint load_texture(const char* file_name)
//{
//	GLint width, height, total_bytes;
//	GLuint texture_ID = 0;
//	GLubyte* pixels = 0;
//	FILE *pFile;
//
//	// 打开文件，如果失败，返回
//	pFile = fopen(file_name, "rb");
//	if (pFile == 0)
//		return 0;
//
//	// 读取文件中图象的宽度和高度
//	fseek(pFile, 0x0012, SEEK_SET);
//	fread(&width, sizeof(imagewidth), 1, pFile);
//	fread(&height, sizeof(imageheight), 1, pFile);
//	//fseek(pFile, BMP_Header_Length, SEEK_SET);
//
//	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
//	{
//		GLint line_bytes = width * 3;
//		while (line_bytes % 4 != 0)
//			++line_bytes;
//		total_bytes = line_bytes * height;
//	}
//
//	// 根据总像素字节数分配内存
//	pixels = (GLubyte*)malloc(total_bytes);
//	if (pixels == 0)
//	{
//		fclose(pFile);
//		return 0;
//	}
//
//	// 读取像素数据
//	if (fread(pixels, total_bytes, 1, pFile) <= 0)
//	{
//		/*free(pixels);*/
//		fclose(pFile);
//		return 0;
//	}
//
//	glGenTextures(1, &texture_ID);
//	glBindTexture(GL_TEXTURE_2D, texture_ID);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//
//
//	GLint last_texture_ID = texture_ID;
//	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
//	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
//	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0,
//		GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
//	//glBindTexture(GL_TEXTURE_2D, texture_ID);  //恢复之前的纹理绑定
//
//
//
//	/*free(pixels);*/
//	return 0;
//}
//
//
//
//
//int main(int argc, char* argv[])
//{
//	// GLUT初始化
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(WindowWidth, WindowHeight);
//	glutCreateWindow(WindowTitle);
//	glEnable(GL_DEPTH_TEST);
//	texGround = load_texture("Texture.bmp");//加载纹理
//	glEnable(GL_TEXTURE_2D);// 启用纹理    
//	glutDisplayFunc(&display);   //注册函数 
//	/*glutIdleFunc(&myIdle);*/
//	glutMainLoop(); //循环调用
//	return 0;
//}




void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//绘制像素
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

	//---------------------------------
	glFlush();
	glutSwapBuffers();
}

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