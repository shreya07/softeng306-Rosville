#include "../Sheep1.h"
#include <gtest/gtest.h>
#include <thread>


TEST(TestSheep, testforwardmovement){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves forward
}

TEST(TestSheep, testbackwardmovement){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves backward
}

TEST(TestSheep, testrightmovement){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves right
}

TEST(TestSheep, testleftmovement){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves left
}

TEST(TestSheep, testsheepwithsheepcollision){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheeps in a seperate threads
  //set them on the same path so that they can collide
  //test to see that the sheep dont collide
}

TEST(TestSheep, testsheepwithfarmercollision){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  Farmer farmer = Farmer("Farmer",argc,argv,0.00,0.00,3);
  sheep.run();
  farmer.run();
  //run sheep and farmer on seperate threads
  //set them on the same path
  //test to see that the sheep and farmer dont collide
}

TEST(TestSheep, testsheepwithgrasscollision){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  Grass grass = Grass("Grass",argc,argv,0.00,0.00,3);
  grass.run();
  sheep.run();
}

TEST(TestSheep, testsheepwithtruckcollision){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves forward
}

TEST(TestSheep, testsheepgrasseating){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves forward
}

TEST(TestSheep, testsheepgrowth){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves forward
}

TEST(TestSheep, testsellingofsheep){
  Sheep1 sheep = Sheep("Sheep",argc,argv,0.00,0.00,3);
  sheep.run();
  //run sheep in a seperate thread
  //check that sheep moves forward
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
