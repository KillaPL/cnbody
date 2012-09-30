#include <Gosu/Gosu.hpp>
#include <cmath>
#include <iostream>

class Star{
  public:

  int x;
  int y;
  int mass;
  int size;
  float vx;
  float vy;
  float ax;
  float ay;
  
  Star(int _x, int _y, int _mass){
    x = _x;
    y = _y;
    mass = _mass;
    size = 10 + log(_mass + 2.2);
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
  }

  Star(){
  }

  ~Star(){
  }

  void update_acceleration(float force_x, float force_y){
    ax += 1.0 * force_x / mass;
    ay += 1.0 * force_y / mass;

    // std::cout << ax << "  " << ay << "\n";
  }

  void move(){
    vx += ax;
    vy += ay;
    x  += vx;
    y  += vy;
    ax = 0;
    ay = 0;
  }

  void draw(Gosu::Graphics &graphics){
    graphics.drawQuad(
      x,        y,        0xffffffff, 
      x + size, y,        0xffffffff, 
      x + size, y + size, 0xffffffff, 
      x,        y + size, 0xffffffff, 
      0
    );
  }
};

