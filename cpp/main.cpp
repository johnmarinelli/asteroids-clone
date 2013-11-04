#include "JUtilities.h"

void initGlut(int argc, char **args);
void runMainLoop(int val);

int startTime = 0;
int timeElapsed = 0;

int main(int argc, char *args[])
{
	initGlut(argc, args);
	return 0;
}

void initGlut(int argc, char **args)
{
	glutInit(&argc, args);
	startTime = glutGet(GLUT_ELAPSED_TIME);

	glutInitContextVersion(2, 1);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Asteroids");

	if (!initGL())
	{
		printf("Unable to initialize GL\n");
		return;
	}

	glutDisplayFunc(renderScene);
	glutTimerFunc(1000 / FRAMES_PER_SECOND, runMainLoop, 0);
	glutKeyboardFunc(handleKeys);
	glutMainLoop();
}

void runMainLoop(int val)
{
	//printf("glutgettime: %d\n", glutGet(GLUT_ELAPSED_TIME)); 

	timeElapsed = glutGet(GLUT_ELAPSED_TIME) - startTime;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	//printf("dTime: %d\n", timeElapsed);

	update(timeElapsed);
	renderScene();

	glutTimerFunc(1000 / FRAMES_PER_SECOND, runMainLoop, val);
}