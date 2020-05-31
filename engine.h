#ifndef SIMPLEPONG__ENGINE_H_
#define SIMPLEPONG__ENGINE_H_

#include "ball.h"
#include "bat.h"
#include <memory>
#include <SFML/Graphics.hpp>

class Engine {
 public:
  Engine();
  ~Engine() = default;

  void start();

 private:
  void check_gameplay();
  void draw();
  void update();

 private:
  sf::RenderWindow window_;

  std::unique_ptr<Bat> game_bat_;
  std::unique_ptr<Ball> game_ball_;
};

#endif//SIMPLEPONG__ENGINE_H_
