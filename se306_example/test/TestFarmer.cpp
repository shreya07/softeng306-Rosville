#include "source/Farmer.h"
#include "R3.h"
#include <gtest/gtest.h>
#include <thread>


TEST(TestFarmer, testforwardmovement){
  Farmer robot = Farmer("Farmer",argc,argv,0.00,0.00,3);
  robot.run();

}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
