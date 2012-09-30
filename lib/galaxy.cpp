#include <Gosu/Gosu.hpp>
#include <cmath>
#include "star.cpp"
#include <iostream>

class Galaxy{
  public:

  int size;
  int stars_count;
  float gravity_constant;
  Star* stars;

  Galaxy(int _size, int _stars_count, float _gravity_constant){
    size = _size;
    stars_count = _stars_count;
    gravity_constant = _gravity_constant;

    stars = new Star[stars_count];

    for(int i = 0; i < stars_count; i++){
      stars[i] = Star(1.0 * size * rand() / RAND_MAX, 1.0 * size * rand() / RAND_MAX, exp(10.0 * rand() / RAND_MAX));
    }
  }

  Galaxy(){
  }

  ~Galaxy(){
  }

  void draw(Gosu::Graphics &graphics){
    for(int i = 0; i < stars_count; i++){
      stars[i].draw(graphics);
    }
  }
};

