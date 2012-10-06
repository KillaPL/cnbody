#include <Gosu/Gosu.hpp>
#include <cmath>
#include "engine_brute.cpp"
#include <iostream>
#include <time.h>

class Galaxy{
  public:

  int stars_count;
  float gravity_constant;
  Star **stars;

  Galaxy(){
    stars_count = 5000;
    gravity_constant = 0.0003;
    
    int size = 1000;

    srand(time(NULL));
    // srand(0);

    stars = new Star*[stars_count];

    float var = 0.2;
    float mass_param = 10000;

    for(int i = 0; i < stars_count/2; i++){
      float random_x = var * size * rand() / RAND_MAX;
      float random_y = var * size * rand() / RAND_MAX;
      float random_z = var * size * rand() / RAND_MAX;
      // float random_z = 0;
      float random_mass = mass_param * sqrt(-2 * log(1.0 * rand() / RAND_MAX)) * sin(3.1415926 * rand() / RAND_MAX);

      if(random_mass < 0){
        random_mass *= -1;
      }

      stars[i] = new Star(random_x, random_y, random_z, 20, 0, 0, random_mass);
    }

    for(int i = stars_count/2; i < stars_count; i++){
      float random_x = (1 - var) * size + var * size * rand() / RAND_MAX;
      float random_y = (1 - var) * size + var * size * rand() / RAND_MAX;
      float random_z = (1 - var) * size + var * size * rand() / RAND_MAX;
      // float random_z = 0;
      float random_mass = mass_param * sqrt(-2 * log(1.0 * rand() / RAND_MAX)) * sin(3.1415926 * rand() / RAND_MAX);

      if(random_mass < 0){
        random_mass *= -1;
      }

      stars[i] = new Star(random_x, random_y, random_z, -20, 0, 0, random_mass);
    }

    std::cout << "Initialised galaxy with " << stars_count << " stars\n";
  }

  ~Galaxy(){
  }

  void draw(Gosu::Graphics &graphics){
    for(int i = 0; i < stars_count; i++){
      stars[i]->draw(graphics);
    }
  }

  void update_forces(const EngineBrute &calculations){
    #pragma omp parallel for num_threads(50)
    for(int i = 0; i < stars_count; ++i){
      Vector force = Vector(0, 0, 0);

      for(int j = 0; j < i; ++j){
        force += calculations.force_matrix[i][j];
      }

      for(int j = i+1; j < stars_count; j++){
        force -= calculations.force_matrix[j][i];
      }

      stars[i]->update_acceleration(force);
    }
  }

  void calculate_forces(){
    EngineBrute calculations = EngineBrute(stars, stars_count, gravity_constant);
    update_forces(calculations);
  }

  void move(){
    for(int i = 0; i < stars_count; i++){
      stars[i]->move();
    }
  }
};