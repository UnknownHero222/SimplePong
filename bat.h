#ifndef SIMPLEPONG__BAT_H_
#define SIMPLEPONG__BAT_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Bat {
 public:
  Bat(float start_x, float start_y);
  ~Bat() = default;

  RectangleShape get_shape();
  FloatRect get_position();

  void move_right();
  void move_left();
  void stop_move_right(int x_max);
  void stop_move_left();

  void update();

 private:
  Vector2f position_;

  RectangleShape bat_shape_;

  float bat_speed_ = .5f;
};

#endif//SIMPLEPONG__BAT_H_
