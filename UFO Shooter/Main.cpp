#include"Game.h"
#include "iostream"
using namespace std;

//calls GameRunning from Game class
Game GameRunning;

//main function
int main(int argc, char *argv[])
{
	//runs main loop
	GameRunning.MainGameLoop();

	return 0;
}