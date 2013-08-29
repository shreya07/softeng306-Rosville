#include "Poop.h"
#include "Robot.h"

int main(int argc, char **argv)
{
	Poop robot = Poop("Poop",argc,argv,10,5,"One");
	robot.run();
	return 0;
}
