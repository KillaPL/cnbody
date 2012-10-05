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

  int size;
  int stars_count;
  float gravity_constant;
  Star **stars;
  Vector **force_matrix;

  Galaxy(int _stars_count){
    stars_count = _stars_count;
    size = 1000;
    gravity_constant = 0.0001;

    srand(time(NULL));

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
    force_matrix = new Vector*[stars_count];

    #pragma omp parallel for num_threads(200)
    for(int i = 0; i < stars_count; ++i){
      force_matrix[i] = new Vector[stars_count];

      for(int j = 0; j < stars_count; ++j){
        force_matrix[i][j] = Vector(0, 0);
      }
    }
  }

  void update_matrices(){
    #pragma omp parallel for num_threads(200) //shared(a_x_matrix, a_y_matrix)
    for(int i = 0; i < stars_count; ++i){
      #pragma omp parallel for num_threads(200)
      for(int j = i+1; j < stars_count; ++j){
        update_forces_with_matrices(i, j);
      }
    }
  }

  void update_forces(){
    #pragma omp parallel for num_threads(200)
    for(int i = 0; i < stars_count; ++i){
      Vector force = Vector(0.0, 0.0);

      for(int j = 0; j < stars_count; ++j){
        force += force_matrix[i][j];
      }

      stars[i]->update_acceleration(force);
    }
  }

  void remove_matrices(){
    #pragma omp parallel for num_threads(200)
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

  void add_to_matrix(int i, int j, Vector v){
    force_matrix[i][j] -= v;
    force_matrix[j][i] += v;
  }

  void update_forces_with_matrices(int i, int j){
    Star *star_1 = stars[i];
    Star *star_2 = stars[j];

    float distance = star_1->distance_to(star_2);

    if(distance > star_1->size + star_2->size){
      Vector force = force_between(star_1, star_2, distance);
      add_to_matrix(i, j, force);
    }
  }

  Vector force_between(Star *star_1, Star *star_2, float distance){
    Vector result = star_1->position - star_2->position;
    result *= gravity_constant * star_1->mass * star_2->mass / (distance * distance);
    return result;
  }

  void move(){
    #pragma omp parallel for
    for(int i = 0; i < stars_count; i++){
      stars[i]->move();
    }
  }
};

