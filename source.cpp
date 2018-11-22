#include "mainClass.h"

int main(int argc, char *argv[])
{
	mainClass *mainclass = new mainClass();
	mainclass->gameLoop();
	delete mainclass;
	return 0;
}