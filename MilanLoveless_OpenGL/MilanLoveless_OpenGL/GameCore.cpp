// GameCore.cpp
/////////////////////////////////////////////////////////////

#include "GameCore.h"

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f };

	
	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();

}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBatch.Draw();

	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	GLfloat stepSize= 0.25f;

	GLfloat blockX = vVerts[0];
	GLfloat blockY = vVerts[7];

	if(key == GLUT_KEY_UP) blockY += stepSize;
	if(key == GLUT_KEY_DOWN) blockY -= stepSize;
	if(key == GLUT_KEY_LEFT) blockX -= stepSize;
	if(key == GLUT_KEY_RIGHT) blockX += stepSize;

	if(blockX < -1.0f) blockX = -1.0f;
	if(blockX > (1.0f - blockSize * 2)) blockX = 1.0f - blockSize * 2;
	if(blockY > 1.0f) blockY = 1.0f;
	if(blockY < (-1.0f - blockSize * 2)) blockY = -1.0f - blockSize * 2;

	vVerts[0] = blockX;
	vVerts[1] = blockY - blockSize*2;
	
	vVerts[3] = blockX + blockSize*2;
	vVerts[4] = blockY - blockSize*2;

	vVerts[6] = blockX + blockSize*2;
	vVerts[7] = blockY;

	vVerts[9] = blockX;
	vVerts[10] = blockY;

	squareBatch.copyVertexData3f(vVerts);

	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Milan Loveless OpenGL");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();

	glutMainLoop();
	return 0;
}
