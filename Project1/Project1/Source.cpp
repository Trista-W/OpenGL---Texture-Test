
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
//#define FileName "Texture.bmp"
//#define _CRT_SECURE_NO_DEPRECATE
#define WindowWidth  400
#define WindowHeight 400
#define WindowTitle  "OpenGL Texture Test"

static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;
static GLubyte* pixels = 0;

GLuint texGround;

static GLfloat angle = 0.0f;
GLuint texture_ID;





GLuint load_texture(const char* file_name)
{

	static GLint total_bytes;
    static GLint height;
    static GLint width;
	FILE *pFile;

	// 打开文件，如果失败，返回
	pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, sizeof(width), 1, pFile);
    fseek(pFile, 0x0012, SEEK_SET);
	fread(&height, sizeof(height), 1, pFile);
	

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	fseek(pFile, 54, SEEK_SET);

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_TEXTURE_2D);  //临时放一下 做测试
	//glGenTextures(1, &texGround);
	///*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
	//glBindTexture(GL_TEXTURE_2D, texGround);  //恢复之前的纹理绑定
	////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	////glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0,
	//	GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);




	/*free(pixels);*/
	return 0;
}

void display(void)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear to black
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	// 设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);

	glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转
	glColor3f(1.0f, 1.0f, 1.0f);

	// 绘制底面以及纹理
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -6.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 6.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(6.0f, 6.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6.0f, -6.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
}



int main(int argc, char* argv[])
{
	if (!load_texture("Texture.bmp"))		// 调用纹理载入子例程
	{
		std::cout << "Loading fail";		// 如果未能载入，返回FALSE
	}
	// GLUT初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	glEnable(GL_DEPTH_TEST);
	texGround = load_texture("Texture.bmp");//加载纹理
	glEnable(GL_TEXTURE_2D);// 启用纹理 
	glBindTexture(GL_TEXTURE_2D, texGround);
	glutDisplayFunc(&display);   //注册函数 
	/*glutIdleFunc(&myIdle);*/
	glutMainLoop(); //循环调用
	return 0;
}




//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//
//	//绘制像素
//	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
//	//glPixelZoom(-0.5f, 0.5f);
//
//	//---------------------------------
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
//	glEnable(GL_TEXTURE_2D);
//	glGenTextures(1,&texture_ID);
//	
//	glBindTexture(GL_TEXTURE_2D, texture_ID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, imagewidth, imageheight, 0,
//				GL_LUMINANCE, GL_UNSIGNED_BYTE, pixeldata);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -6.0f, 0.0f);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 6.0f, 0.0f);
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(6.0f, 6.0f, 0.0f);
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(6.0f, -6.0f, 0.0f);
//	glEnd();
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//
//int LoadTexture(const char* FileName)
//{
//	GLuint texture_ID = 0;
//	//打开文件
//	FILE* pfile = fopen(FileName, "rb");
//	if (pfile == 0) exit(0);
//
//	//读取图像大小
//	fseek(pfile, 0x0012, SEEK_SET);
//	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
//	fseek(pfile, 0x0012, SEEK_SET);
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
//	//glGenTextures(1, &texture_ID);
//	//glBindTexture(GL_TEXTURE_2D, texture_ID);
//	/*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
//
//
//	//关闭文件
//	fclose(pfile);
//
//}
//
//
//int main(int argc, char* argv[])
//{	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 0);
//	glutInitWindowSize(1024, 1024);
//
//
//	if (!LoadTexture("Texture.bmp"))		// 调用纹理载入子例程
//	{
//		std::cout<<"Loading fail";		// 如果未能载入，返回FALSE
//	}
//	glEnable(GL_TEXTURE_2D);	// 启用纹理映射
//	glShadeModel(GL_SMOOTH);	// 启用阴影平滑
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// 黑色背景
//	glClearDepth(1.0f);		// 设置深度缓存
//	glEnable(GL_DEPTH_TEST);	// 启用深度测试
//	glDepthFunc(GL_LEQUAL);	// 所作深度测试的类型
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 告诉系统对透视进行修正
//	//return TRUE;	// 初始化 OK
//	//初始化glut运行
//
//	//glEnable(GL_TEXTURE_2D);  
//	//glEnable(GL_DEPTH_TEST);
//	texGround = LoadTexture("Texture.bmp");
//	glutCreateWindow("Test");
//	glutDisplayFunc(&display);
//	glutMainLoop();
//	//-------------------------------------
//	free(pixeldata);
//
//	return 0;
//}
