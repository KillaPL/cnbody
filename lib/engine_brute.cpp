#include "star.cpp"
#include <iostream>

class EngineBrute{
  public:

  Vector **force_matrix;
  int stars_count;

  EngineBrute(Star **&stars, const int &stars_count_, const float &gravity_constant){
    stars_count = stars_count_;

    init_matrices();
    update_matrices(stars, gravity_constant);
  }

  ~EngineBrute(){
    #pragma omp parallel for num_threads(50)
    for(int i = 0; i < stars_count; ++i){
      delete[] force_matrix[i];
    }

    delete[] force_matrix;
  }

  void init_matrices(){
    force_matrix = new Vector*[stars_count*stars_count];

    #pragma omp parallel for num_threads(50)
    for(int i = 0; i < stars_count; ++i){
      force_matrix[i] = new Vector[stars_count];
    }
  }

  void update_matrices(Star **&stars, const float &gravity_constant){
    #pragma omp parallel for num_threads(50) //shared(a_x_matrix, a_y_matrix)
    for(int i = 0; i < stars_count; ++i){
      #pragma omp parallel for num_threads(50)
      for(int j = 0; j < i; ++j){
        Star &star_1 = *stars[i];
        Star &star_2 = *stars[j];

        float distance = star_1.squared_distance_to(star_2);

        if(distance > sqr(star_1.size + star_2.size)){
          force_matrix[i][j] = force_between(star_1, star_2, distance, gravity_constant);
        }
        else{
          force_matrix[i][j] = Vector(0, 0);
        }
      }
    }
  }

  Vector force_between(Star &star_1, Star &star_2, const float distance, const float gravity_constant){
    Vector result = star_1.position - star_2.position;
    result *= (-1 * gravity_constant * star_1.mass * star_2.mass / distance);
    return result;
  }
};