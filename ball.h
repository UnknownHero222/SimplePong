#ifndef SIMPLEPONG__BALL_H_
#define SIMPLEPONG__BALL_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
 public:
  Ball(float start_x, float start_y);
  ~Ball() = default;

  FloatRect get_position();
  RectangleShape get_shape();

  float get_x_velocity();

  void rebound_sides();
  void rebound_bat_or_top();
  void hit_bottom();

  void update();

 private:
  Vector2f position_;

  RectangleShape ball_shape_;

  float x_velocity = .6f;
  float y_velocity = .6f;
};

#endif//SIMPLEPONG__BALL_H_
