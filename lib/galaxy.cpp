#include <Gosu/Gosu.hpp>
#include <cmath>
#include "star.cpp"
#include <iostream>
#include <omp.h>

class Galaxy{
  public:

  int size;
  int stars_count;
  float gravity_constant;
  Star **stars;

  Galaxy(int _size, int _stars_count, float _gravity_constant){
    size = _size;
    stars_count = _stars_count;
    gravity_constant = _gravity_constant;

    stars = new Star*[stars_count];

    for(int i = 0; i < stars_count; i++){
      stars[i] = new Star(1.0 * size * rand() / RAND_MAX, 1.0 * size * rand() / RAND_MAX, exp(10.0 * rand() / RAND_MAX));
    }

    std::cout << "Initialised galaxy with " << stars_count << " stars\n";
  }

  Galaxy(){
  }

  ~Galaxy(){
  }

  void draw(Gosu::Graphics &graphics){
    for(int i = 0; i < stars_count; i++){
      stars[i]->draw(graphics);
    }
  }

  void calculate_forces(){
    #pragma omp parallel for
    for(int i = 0; i < stars_count; ++i){
      #pragma omp parallel for
      for(int j = i+1; j < stars_count; ++j){
        update_forces_between(stars[i], stars[j]);
      }
    }
  }

  void update_forces_between(Star *star_1, Star *star_2){
    float distance = distance_between(star_1, star_2);

    if(distance > star_1->size + star_2->size){
      float force = force_between(star_1, star_2, distance);
      float force_x = force * (star_1->x - star_2->x) / distance;
      float force_y = force * (star_1->y - star_2->y) / distance;
      star_1->update_acceleration(-force_x, -force_y);
      star_2->update_acceleration(force_x, force_y);
    }
  }

  float distance_between(Star *star_1, Star *star_2){
    return sqrt((star_1->x - star_2->x)*(star_1->x - star_2->x) + (star_1->y - star_2->y)*(star_1->y - star_2->y));
  }

  float force_between(Star *star_1, Star *star_2, float distance){
    return gravity_constant * star_1->mass * star_2->mass / distance;
  }

  void move(){
    #pragma omp parallel for
    for(int i = 0; i < stars_count; i++){
      stars[i]->move();
    }
  }
};

