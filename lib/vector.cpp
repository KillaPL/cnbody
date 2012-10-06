#include <cmath>
#include "helpers.cpp"

class Vector{
  public:

  float a;
  float b;

  Vector(const float _a, const float _b){
    this->a = _a;
    this->b = _b;
  }

  Vector(){
  }

  ~Vector(){
  }

  Vector operator=(const Vector &other){
    this->a = other.a;
    this->b = other.b;
  }

  void operator+=(const Vector &other){
    this->a += other.a;
    this->b += other.b;
  }

  void operator-=(const Vector &other){
    this->a -= other.a;
    this->b -= other.b;
  }

  void operator*=(const float number){
    this->a *= number;
    this->b *= number;
  }

  void operator/=(const float number){
    this->a /= number;
    this->b /= number;
  }

  Vector operator-(const Vector &other){
    return Vector(this->a - other.a, this->b - other.b);
  }

  void reset(){
    this->a = 0.0;
    this->b = 0.0;
  }

  float square_sum(){
    return sqr(this->a) + sqr(this->b);
  }
};