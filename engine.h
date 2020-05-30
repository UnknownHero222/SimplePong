#ifndef SIMPLEPONG__ENGINE_H_
#define SIMPLEPONG__ENGINE_H_

#include "ball.h"
#include "bat.h"
#include <SFML/Graphics.hpp>

class Engine {
 public:
  Engine();
  ~Engine() = default;

  void start();

 private:
  void update();
  void draw();

 private:
  Bat game_bat_;
  Ball game_ball_;
};

#endif//SIMPLEPONG__ENGINE_H_
