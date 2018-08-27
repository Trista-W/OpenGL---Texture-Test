
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

	// ���ļ������ʧ�ܣ�����
	pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, sizeof(width), 1, pFile);
    fseek(pFile, 0x0012, SEEK_SET);
	fread(&height, sizeof(height), 1, pFile);
	

	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// �����������ֽ��������ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	fseek(pFile, 54, SEEK_SET);

	// ��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_TEXTURE_2D);  //��ʱ��һ�� ������
	//glGenTextures(1, &texGround);
	///*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
	//glBindTexture(GL_TEXTURE_2D, texGround);  //�ָ�֮ǰ�������
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
	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear to black
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	// �����ӽ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);

	glRotatef(angle, 0.0f, 0.0f, 1.0f); //��ת
	glColor3f(1.0f, 1.0f, 1.0f);

	// ���Ƶ����Լ�����
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
	if (!load_texture("Texture.bmp"))		// ������������������
	{
		std::cout << "Loading fail";		// ���δ�����룬����FALSE
	}
	// GLUT��ʼ��
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	glEnable(GL_DEPTH_TEST);
	texGround = load_texture("Texture.bmp");//��������
	glEnable(GL_TEXTURE_2D);// �������� 
	glBindTexture(GL_TEXTURE_2D, texGround);
	glutDisplayFunc(&display);   //ע�ắ�� 
	/*glutIdleFunc(&myIdle);*/
	glutMainLoop(); //ѭ������
	return 0;
}




//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//
//	//��������
//	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
//	//glPixelZoom(-0.5f, 0.5f);
//
//	//---------------------------------
//	// �����ӽ�
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(100, 1, 1, 21);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);
//
//	glRotatef(angle, 0.0f, 0.0f, 1.0f); //��ת
//	glColor3f(1.0f, 1.0f, 1.0f);
//
//	// ���Ƶ����Լ�����
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
//	//���ļ�
//	FILE* pfile = fopen(FileName, "rb");
//	if (pfile == 0) exit(0);
//
//	//��ȡͼ���С
//	fseek(pfile, 0x0012, SEEK_SET);
//	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
//	fseek(pfile, 0x0012, SEEK_SET);
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
//	//glGenTextures(1, &texture_ID);
//	//glBindTexture(GL_TEXTURE_2D, texture_ID);
//	/*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
//
//
//	//�ر��ļ�
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
//	if (!LoadTexture("Texture.bmp"))		// ������������������
//	{
//		std::cout<<"Loading fail";		// ���δ�����룬����FALSE
//	}
//	glEnable(GL_TEXTURE_2D);	// ��������ӳ��
//	glShadeModel(GL_SMOOTH);	// ������Ӱƽ��
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// ��ɫ����
//	glClearDepth(1.0f);		// ������Ȼ���
//	glEnable(GL_DEPTH_TEST);	// ������Ȳ���
//	glDepthFunc(GL_LEQUAL);	// ������Ȳ��Ե�����
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����ϵͳ��͸�ӽ�������
//	//return TRUE;	// ��ʼ�� OK
//	//��ʼ��glut����
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
