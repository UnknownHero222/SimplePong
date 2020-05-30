#include "ball.h"

/******************************************************************/

Ball::Ball(float start_x, float start_y) {
  position_.x = start_x;
  position_.y = start_y;

  ball_shape_.setSize(Vector2f(10, 10));
  ball_shape_.setPosition(position_);
}

/******************************************************************/

FloatRect Ball::get_position() {
  return ball_shape_.getGlobalBounds();
}

/******************************************************************/

RectangleShape Ball::get_shape() {
  return ball_shape_;
}

/******************************************************************/

float Ball::get_x_velocity() {
  return x_velocity;
}

/******************************************************************/

void Ball::rebound_sides() {
  x_velocity = -x_velocity;
}

/******************************************************************/

void Ball::rebound_bat_or_top() {
  position_.y -= (y_velocity * 30);
  y_velocity = -y_velocity;
}

/******************************************************************/

void Ball::hit_bottom() {
  position_.y = 1;
  position_.x = 500;
}

/******************************************************************/

void Ball::update() {
  position_.x += x_velocity;
  position_.y += y_velocity;

  ball_shape_.setPosition(position_);
}