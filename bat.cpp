#include "bat.h"

/******************************************************************/

Bat::Bat(float start_x, float start_y) {
  position_.x = start_x;
  position_.y = start_y;

  bat_shape_.setSize(sf::Vector2f(50, 5));
  bat_shape_.setPosition(start_x, start_y);
}

/******************************************************************/

FloatRect Bat::get_position() {
  return bat_shape_.getGlobalBounds();
}

/******************************************************************/

RectangleShape Bat::get_shape() {
  return bat_shape_;
}

/******************************************************************/

void Bat::move_right() {
  position_.x += bat_speed_;
}

/******************************************************************/

void Bat::move_left() {
  position_.x -= bat_speed_;
}

/******************************************************************/

void Bat::update() {
  bat_shape_.setPosition(position_);
}

