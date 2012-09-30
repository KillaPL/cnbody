#include <Gosu/Gosu.hpp>
#include "lib/galaxy.cpp"
// #include <iostream>

int SIZE = 1000;
int GALAXY_SIZE = 10000;
int GALAXY_STARS_COUNT = 10000;
float GALAXY_GRAVITY_CONSTANT = 0.0001;

class GameWindow : public Gosu::Window
{
  Galaxy* galaxy; 

  public:
  
  GameWindow() : Window(SIZE, SIZE, false)
  {
    galaxy = new Galaxy(GALAXY_SIZE, GALAXY_STARS_COUNT, GALAXY_GRAVITY_CONSTANT);
    setCaption(L"Gosu Tutorial Game"); 
  }

  void update()
  {
    galaxy->calculate_forces();
    galaxy->move(); 
  }

  void draw()
  {
    graphics().pushTransform(Gosu::scale(1.0 * SIZE / GALAXY_SIZE));
    galaxy->draw(graphics());
    graphics().popTransform();
  }
};

int main() 
{
  GameWindow window;
  window.show(); 
}