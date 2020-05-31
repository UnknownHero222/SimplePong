#ifndef SIMPLEPONG__ENGINE_H_
#define SIMPLEPONG__ENGINE_H_

#include "ball.h"
#include "bat.h"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

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

  Text score_text_;

  uint8_t user_lives_;
  uint64_t user_scores_;
};

#endif//SIMPLEPONG__ENGINE_H_
