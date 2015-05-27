#include "CommonHelpers.h"
#include "System.h"

void main(int argc, char **argv)
{
	//Initialize all systems
	System::Initialize(argc, argv);

	//start game loop

	LOG__INFO("Engine Exit");
	getchar();
}