////Jeff Chastine
//#include <Windows.h>
//#include <GL\glew.h>
//#include <GL\freeglut.h>
//#include <iostream>
//#define WindowWidth  400
//#define WindowHeight 400
//#define WindowTitle  "OpenGL Texture Test"
//
//static GLint imagewidth;
//static GLint imageheight;
//static GLint pixellength;
//static GLubyte* pixeldata;
//
//
////定义两个纹理对象编号
//GLuint texGround;
//
//static GLfloat angle = 0.0f;
//
//
//
//
//
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
//	// 绘制立面
//	/*glBindTexture(GL_TEXTURE_2D, texWall);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 5.0f);
//	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
//	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
//	glEnd();
//*/
////绘制另外一个立面
///*glBegin(GL_QUADS);
//glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
//glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, 9.0f, 0.0f);
//glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 9.0f, 5.0f);
//glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
//glEnd();
//*/
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
//
//	//// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
//	//// 若图像宽高超过了OpenGL规定的最大值，也缩放
//	//{
//	//	GLint max;
//	//	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
//	//	if (!power_of_two(width)
//	//		|| !power_of_two(height)
//	//		|| width > max
//	//		|| height > max)
//	//	{
//	//		const GLint new_width = 256;
//	//		const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
//	//		GLint new_line_bytes, new_total_bytes;
//	//		GLubyte* new_pixels = 0;
//
//	//		// 计算每行需要的字节数和总字节数
//	//		new_line_bytes = new_width * 3;
//	//		while (new_line_bytes % 4 != 0)
//	//			++new_line_bytes;
//	//		new_total_bytes = new_line_bytes * new_height;
//
//	//		// 分配内存
//	//		new_pixels = (GLubyte*)malloc(new_total_bytes);
//	//		if (new_pixels == 0)
//	//		{
//	//			free(pixels);
//	//			fclose(pFile);
//	//			return 0;
//	//		}
//
//	//		// 进行像素缩放
//	//		gluScaleImage(GL_RGB,
//	//			width, height, GL_UNSIGNED_BYTE, pixels,
//	//			new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
//
//	//		// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
//	//		free(pixels);
//	//		pixels = new_pixels;
//	//		width = new_width;
//	//		height = new_height;
//	//	}
//	//}
//
//	//// 分配一个新的纹理编号
//	//glGenTextures(1, &texture_ID);
//	//if (texture_ID == 0)
//	//{
//	//	free(pixels);
//	//	fclose(pFile);
//	//	return 0;
//	//}
//
//	// 绑定新的纹理，载入纹理并设置纹理参数
//	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
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
////void myIdle(void)
////{
////	angle += 1.8f;
////	if (angle >= 360.0f)
////		angle = 0.0f;
////	display();
////}
//
//
////int main(int argc, char* argv[]) {
////
////	// Initialize GLUT
////	glutInit(&argc, argv);
////	// Set up some memory buffers for our display
////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
////	// Set the window size
////	glutInitWindowSize(800, 600);
////	// Create the window with the title "Hello,GL"
////	glutCreateWindow("Hello, GL");
////	// Bind the two functions (above) to respond when necessary
////	glutReshapeFunc(changeViewPort);
////	glutDisplayFunc(render);
////
////	// Very important!  This initializes the entry points in the OpenGL driver so we can 
////	// call all the functions in the API.
////	GLenum err = glewInit();
////	if (GLEW_OK != err) {
////		fprintf(stderr, "GLEW error");
////		return 1;
////	}
////
////
////	glutMainLoop();
////	return 0;
////}
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
//	/*texWall = load_texture("wall2.bmp");*/
//	glutDisplayFunc(&display);   //注册函数 
//	/*glutIdleFunc(&myIdle);*/
//	glutMainLoop(); //循环调用
//	return 0;
//}


