#include <Gosu/Gosu.hpp>
#include "lib/galaxy.cpp"
// #include <iostream>

int WINDOW_X = 1000;
int WINDOW_Y = 1000;
int GALAXY_SIZE = 1000;
int GALAXY_STARS_COUNT = 200;
float GALAXY_GRAVITY_CONSTANT = 0.00001;

class GameWindow : public Gosu::Window
{
  Galaxy* galaxy;

  public:
  
  GameWindow() : Window(WINDOW_X, WINDOW_Y, false)
  {
    galaxy = new Galaxy(GALAXY_SIZE, GALAXY_STARS_COUNT, GALAXY_GRAVITY_CONSTANT);
    setCaption(L"Gosu Tutorial Game");
  }

  void update()
  {
  }

  void draw()
  {
    galaxy->draw(graphics());
  }
};

int main()
{
  GameWindow window;
  window.show();
}