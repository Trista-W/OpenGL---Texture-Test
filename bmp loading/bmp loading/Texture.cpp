#define WindowTitle  "OpenGL Texture Test"

#define _CRT_SECURE_NO_DEPRECATE

#include <GL\freeglut.h>
#include <stdio.h>
#include <stdlib.h>
//#include <GL/glew.h>
#include <iostream>



GLuint LoadTexture(const char * filename)
{
	unsigned char header[54];
    unsigned char * data;
    int width, height;
	unsigned int imageSize;
	unsigned int dataPos;
	GLuint texture;
	

	FILE * file;

	file = fopen(filename, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	//if (file == NULL) return 0;
	//width = 1024;
	//height = 1024;
	//data = (unsigned char *)malloc(width * height * 3);
	////int size = fseek(file,);
	//fread(data, width * height * 3, 1, file);
	//fclose(file);

	//for (int i = 0; i < width * height; ++i)
	//{
	//	int index = i * 3;
	//	unsigned char B, R;
	//	B = data[index];
	//	R = data[index + 2];

	//	data[index] = R;
	//	data[index + 2] = B;

	//}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}


int main(int argc, char* argv[])
{   
	
	glutInit(&argc, argv);
	GLuint texture;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear to black
	//glDrawPixels(width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 1024);
	glutCreateWindow(WindowTitle);
	glEnable(GL_DEPTH_TEST);
	texture = LoadTexture("./Texture.bmp");
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, texture);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(100, 1, 1, 21);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);
    //glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0.0f);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 0.0f);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 5.0f, 0.0f);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -5.0f, 0.0f);
	//glEnd();


	glutMainLoop();
	return 0;
}