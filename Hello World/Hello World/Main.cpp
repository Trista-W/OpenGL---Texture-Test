#define WindowWidth  400
#define WindowHeight 400
#define WindowTitle  "OpenGL Texture Test"
#define BMP_Header_Length 54

#include <GL\freeglut.h>
#include <stdio.h>
#include <stdlib.h>




GLuint texGround;

GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	//GLuint texture_ID = 0;
	GLubyte* pixels = 0;
	FILE *pFile;

	// Open the file;
	pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// Read height and width of the image
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, sizeof(width), 1, pFile);
	fread(&height, sizeof(height), 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// Calculate the bytes of the image
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// Distribute the buffer to the image
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// Read the pixel data
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGenTextures(1, &texGround);
	glBindTexture(GL_TEXTURE_2D, texGround);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	
	free(pixels);
	return texGround;
}


void display(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// clear to black
	//glDrawPixels(width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	// Set the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 7, 7, 0, 0, 0, 0, 0, 1);

	glRotatef(0.0f, 0.0f, 0.0f, 1.0f); //rotate
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw the texture and ground
	//glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, 5.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -5.0f, 0.0f);
	glEnd();


	glutSwapBuffers();
}



int main(int argc, char* argv[])
{
	// GLUT initialize  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);    // Enable texture
	glGenTextures(1, &texGround);
	glBindTexture(GL_TEXTURE_2D, texGround);
	texGround = load_texture("Texture.bmp");  //Load texture
	glutDisplayFunc(&display);   //Display
	glutMainLoop(); //Loop
	return 0;
}
