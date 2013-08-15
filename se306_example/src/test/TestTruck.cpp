#include "../Truck.h"
#include <gtest/gtest.h>
#include <thread>


TEST(TestTruck, teststationarymovement){
  Truck truck = Truck("Truck",argc,argv,0.00,0.00,3);
  truck.run();
  //run truck in a seperate thread
  //check that pose remains constant
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
