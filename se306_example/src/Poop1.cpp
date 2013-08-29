#include "Poop.h"
#include "Robot.h"

int main(int argc, char **argv)
{
	Poop robot = Poop("Poop",argc,argv,5,1,"One");
	robot.run();
	return 0;
}
