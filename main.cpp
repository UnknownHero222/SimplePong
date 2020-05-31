#include "ball.h"
#include "bat.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;

int main() {
  sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Pong");

  Bat bat(kWindowWidth / 2, kWindowHeight - 30);
  Ball ball(kWindowWidth / 2, 1);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
      bat.move_left();
    } else if (Keyboard::isKeyPressed(Keyboard::D)) {
      bat.move_right();
    } else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    if (ball.get_position().top > kWindowHeight) {
      ball.hit_bottom();
    }
    if (ball.get_position().top < 0) {
      ball.rebound_bat_or_top();
    }

    auto var = ball.get_position().left;

    if (ball.get_position().left < 0 || kWindowWidth < ball.get_position().left + 10) {
      ball.rebound_sides();
    }
    if (ball.get_position().intersects(bat.get_position())) {
      ball.rebound_bat_or_top();
    }

    ball.update();
    bat.update();

    window.clear(Color(26, 128, 182, 255));
    window.draw(bat.get_shape());
    window.draw(ball.get_shape());

    window.display();
  }

  return 0;
}
