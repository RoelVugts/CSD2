#include <iostream>
#include <math.h>

class Woofer
{
public:
  float magnet;
  float coil;


  void move(float position)
  {
    coil = position;
    
  }

  void userInput() {
    std::string keyInput;
    std::cin >> keyInput;
    coil = stof(keyInput);
  }

  void printCoilPosition() {
    std::cout << "Coil position: " << coil << std::endl;
  }

};


int main()
{
  Woofer myWoofer;
  for(int i = 0; i < 15; i++) {
    myWoofer.move(pow(2,i));
    myWoofer.printCoilPosition();
  }
  myWoofer.userInput();
  return 0;
}

