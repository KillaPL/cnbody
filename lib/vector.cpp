#include <cmath>

class Vector{
  public:

  float a;
  float b;

  Vector(float _a, float _b){
    this->a = _a;
    this->b = _b;
  }

  Vector(){
  }

  ~Vector(){
  }

  void operator+=(Vector other){
    this->a += other.a;
    this->b += other.b;
  }

  void operator-=(Vector other){
    this->a -= other.a;
    this->b -= other.b;
  }

  void operator*=(float number){
    this->a *= number;
    this->b *= number;
  }

  void operator/=(float number){
    this->a /= number;
    this->b /= number;
  }

  Vector operator-(Vector other){
    return Vector(this->a - other.a, this->b - other.b);
  }

  void reset(){
    this->a = 0.0;
    this->b = 0.0;
  }

  float normal_sum(){
    return sqrt(this->a*this->a + this->b*this->b);
  }
};