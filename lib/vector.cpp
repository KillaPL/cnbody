#include <cmath>

class Vector{
  public:

  float a;
  float b;

  Vector(float _a, float _b){
    a = _a;
    b = _b;
  }

  Vector(){
  }

  ~Vector(){
  }

  Vector operator-(){
    return Vector(-this->a, -this->b);
  }

  Vector operator+(Vector other){
    return Vector(this->a + other.a, this->b + other.b);
  }

  void operator+=(Vector other){
    this->a += other.a;
    this->b += other.b;
  }

  Vector operator-(Vector other){
    return Vector(this->a - other.a, this->b - other.b);
  }

  Vector operator*(float number){
    return Vector(this->a * number, this->b * number);
  }

  Vector operator/(float number){
    return Vector(this->a / number, this->b / number);
  }

  void reset(){
    this->a = 0.0;
    this->b = 0.0;
  }

  float normal_sum(){
    return sqrt(this->a*this->a + this->b*this->b);
  }
};