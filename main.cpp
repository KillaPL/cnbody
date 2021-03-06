#include <Gosu/Gosu.hpp>
#include "lib/galaxy.cpp"
// #include <iostream>

class GameWindow : public Gosu::Window
{
  Galaxy* galaxy;
  // int counter;
  // int mili;

  public:
  
  GameWindow() : Window(1000, 1000, false)
  {
    // counter = 0;
    // mili = Gosu::milliseconds();
    galaxy = new Galaxy();
    setCaption(L"Gosu Tutorial Game"); 
  }

  void update()
  {
    galaxy->calculate_forces();
    galaxy->move();
    // counter++;
    // if(counter == 30){
    //   std::cout << Gosu::milliseconds() - mili << "\n";
    //   exit(1);
    // }
  }

  void draw()
  {
    graphics().pushTransform(Gosu::translate(400, 400));
    graphics().pushTransform(Gosu::scale(0.2));
    galaxy->draw(graphics());
    graphics().popTransform();
  }
};

int main() 
{
  GameWindow window;
  window.show();
}