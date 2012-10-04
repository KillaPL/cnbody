#include <Gosu/Gosu.hpp>
#include <cmath>
#include <iostream>
#include "vector.cpp"

class Star{
  public:

  Vector position;
  Vector velocity;
  Vector acceleration;
  int mass;
  int size;
  
  Star(int _x, int _y, int _mass){
    position = Vector(_x, _y);
    velocity = Vector(0.0, 0.0);
    acceleration = Vector(0.0, 0.0);
    mass = _mass;
    size = log(_mass + 2.2);
  }

  Star(){
  }

  ~Star(){
  }

  float distance_to(Star *star){
    return (this->position - star->position).normal_sum();
  }

  void update_acceleration(Vector force){
    force /= mass;
    acceleration += force;
  }

  void move(){
    velocity += acceleration;
    position += velocity;
    acceleration.reset();
  }

  void draw(Gosu::Graphics &graphics){
    graphics.drawQuad(
      position.a,        position.b,        0xffffffff, 
      position.a + size, position.b,        0xffffffff, 
      position.a + size, position.b + size, 0xffffffff, 
      position.a,        position.b + size, 0xffffffff, 
      0
    );
  }
};

