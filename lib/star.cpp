#include <cmath>
#include <Gosu/Gosu.hpp>


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
    size = log(_mass*0.01 + 2.2);
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
    ax += force_x / mass;
    ay += force_y / mass;
  }

  void move(){
    vx += ax;
    vy += ay;
    x  += vx;
    y  += vy;
    ax = 0;
    ay = 0;
  }

  void draw(Gosu::Graphics graphics){
    graphics.drawQuad(
      x,        y,        0xffffffff, 
      x + size, y,        0xffffffff, 
      x + size, y + size, 0xffffffff, 
      x,        y + size, 0xffffffff, 
      0
    );
  }
};

