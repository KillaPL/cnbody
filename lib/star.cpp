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
  
  Star(const float _x, const float _y, const float _z, const int _mass){
    position = Vector(_x, _y, _z);
    velocity = Vector(0.0, 0.0, 0.0);
    acceleration = Vector(0.0, 0.0, 0.0);
    mass = _mass;
    size = log(_mass + 2.2);
  }

  Star(const float _x, const float _y, const float _z, const float _vx, const float _vy, const float _vz, const int _mass){
    position = Vector(_x, _y, _z);
    velocity = Vector(_vx, _vy, _vz);
    acceleration = Vector(0.0, 0.0, 0.0);
    mass = _mass;
    size = log(_mass + 2.2);
  }

  Star(){
  }

  ~Star(){
  }

  float squared_distance_to(const Star &star){
    return (this->position - star.position).square_sum();
  }

  void update_acceleration(Vector &force){
    force /= mass;
    acceleration += force;
  }

  void move(){
    velocity += acceleration;
    position += velocity;
    acceleration.reset();
  }

  void draw(Gosu::Graphics &graphics){
    Gosu::Color color = Gosu::interpolate(0xffffffff, 0x00000000, color_depth());
    graphics.drawQuad(
      position.a,        position.b,        color, 
      position.a + size, position.b,        color, 
      position.a + size, position.b + size, color, 
      position.a,        position.b + size, color, 
      0
    );
  }

  float color_depth(){
    return 0.5 + 0.5 * tanh(0.5 - 0.5 * position.c/1000.0);
    // return 0.5 + 0.5 * tanh(0.5 - 0.5 * mass/4000.0);
  }
};

