#include <cmath>
#include "helpers.cpp"

class Vector{
  public:

  float a;
  float b;
  float c;

  Vector(const float _a, const float _b, const float _c){
    this->a = _a;
    this->b = _b;
    this->c = _c;
  }

  Vector(){
  }

  ~Vector(){
  }

  Vector operator=(const Vector &other){
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
  }

  void operator+=(const Vector &other){
    this->a += other.a;
    this->b += other.b;
    this->c += other.c;
  }

  void operator-=(const Vector &other){
    this->a -= other.a;
    this->b -= other.b;
    this->c -= other.c;
  }

  void operator*=(const float number){
    this->a *= number;
    this->b *= number;
    this->c *= number;
  }

  void operator/=(const float number){
    this->a /= number;
    this->b /= number;
    this->c /= number;
  }

  Vector operator-(const Vector &other){
    return Vector(this->a - other.a, this->b - other.b, this->c - other.c);
  }

  void reset(){
    this->a = 0.0;
    this->b = 0.0;
    this->c = 0.0;
  }

  float square_sum(){
    return sqr(this->a) + sqr(this->b) + sqr(this->c);
  }
};