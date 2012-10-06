#include <Gosu/Gosu.hpp>
#include <cmath>
#include "star.cpp"

#ifndef VECTOR_CPP
#define VECTOR_CPP
#endif

#include <iostream>
#include <time.h>

class Galaxy{
  public:

  int stars_count;
  float gravity_constant;
  Star **stars;
  Vector **force_matrix;

  Galaxy(int _stars_count){
    stars_count = _stars_count;
    gravity_constant = 0.0001;
    
    int size = 1000;

    srand(time(NULL));
    // srand(0);

    stars = new Star*[stars_count];

    for(int i = 0; i < stars_count; i++){
      float random_x = 1.0 * size * rand() / RAND_MAX;
      float random_y = 1.0 * size * rand() / RAND_MAX;
      float random_mass = 10000 * sqrt(-2 * log(1.0 * rand() / RAND_MAX)) * sin(3.1415926 * rand() / RAND_MAX);

      if(random_mass < 0){
        random_mass *= -1;
      }

      stars[i] = new Star(random_x, random_y, random_mass);
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

  void init_matrices(){
    force_matrix = new Vector*[stars_count*stars_count];

    #pragma omp parallel for num_threads(50)
    for(int i = 0; i < stars_count; ++i){
      force_matrix[i] = new Vector[stars_count];
    }
  }

  void update_matrices(){
    #pragma omp parallel for num_threads(50) //shared(a_x_matrix, a_y_matrix)
    for(int i = 0; i < stars_count; ++i){
      #pragma omp parallel for num_threads(50)
      for(int j = 0; j < i; ++j){
        Star &star_1 = *stars[i];
        Star &star_2 = *stars[j];

        float distance = star_1.squared_distance_to(star_2);

        if(distance > sqr(star_1.size + star_2.size)){
          force_matrix[i][j] = force_between(star_1, star_2, distance);
        }
        else{
          force_matrix[i][j] = Vector(0, 0);
        }
      }
    }
  }

  void update_forces(){
    #pragma omp parallel for num_threads(50)
    for(int i = 0; i < stars_count; ++i){
      Vector force = Vector(0, 0);

      for(int j = 0; j < i; ++j){
        force += force_matrix[i][j];
      }

      for(int j = i+1; j < stars_count; j++){
        force -= force_matrix[j][i];
      }

      stars[i]->update_acceleration(force);
    }
  }

  void remove_matrices(){
    #pragma omp parallel for num_threads(50)
    for(int i = 0; i < stars_count; ++i){
      delete[] force_matrix[i];
    }

    delete[] force_matrix;
  }

  void calculate_forces(){
    init_matrices();
    update_matrices();
    update_forces();
    remove_matrices();
  }


  Vector force_between(Star &star_1, Star &star_2, const float distance){
    Vector result = star_1.position - star_2.position;
    result *= (-1 * gravity_constant * star_1.mass * star_2.mass / distance);
    return result;
  }

  void move(){
    for(int i = 0; i < stars_count; i++){
      stars[i]->move();
    }
  }
};