#include <Gosu/Gosu.hpp>
#include "lib/star.cpp"
// #include <iostream>

int WINDOW_X = 1000;
int WINDOW_Y = 1000;
int GALAXY_SIZE = 1000;
int GALAXY_STARS_COUNT = 200;
float GALAXY_GRAVITY_CONSTANT = 0.00001;
float GALAXY_JOINING_DISTANCE = 2;
float GALAXY_FORCE_CHANGE_DISTANCE = 4;

class GameWindow : public Gosu::Window
{
  Star first;

  public:
  
  GameWindow() : Window(WINDOW_X, WINDOW_Y, false)
  {
    first = Star(100, 100, 1000);
    setCaption(L"Gosu Tutorial Game");
  }

  void update()
  {
  }

  void draw()
  {
    first.draw(graphics());
  }
};

int main()
{
  GameWindow window;
  window.show();
}