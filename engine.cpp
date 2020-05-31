#include "engine.h"

constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr int kBallStarPos = 1;
constexpr int kBatHeightLevel = 50;

/******************************************************************/

Engine::Engine() {
  window_.create(sf::VideoMode(kWindowWidth, kWindowHeight), "Pong");

  game_bat_ =
      std::make_unique<Bat>(kWindowWidth / 2, kWindowHeight - kBatHeightLevel);
  game_ball_ = std::make_unique<Ball>(kWindowWidth / 2, kBallStarPos);
}

/******************************************************************/

void Engine::start() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
      game_bat_->move_left();
    } else if (Keyboard::isKeyPressed(Keyboard::D)) {
      game_bat_->move_right();
    } else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window_.close();
    }

    check_gameplay();

    update();

    draw();
  }
}

/******************************************************************/

void Engine::check_gameplay() {
  if (game_ball_->get_position().top > kWindowHeight) {
    game_ball_->hit_bottom();
  }
  if (game_ball_->get_position().top < 0) { game_ball_->rebound_bat_or_top(); }

  auto game_ball_width = game_ball_->get_position().width;
  if (game_ball_->get_position().left < 0
      || kWindowWidth < game_ball_->get_position().left + game_ball_width) {
    game_ball_->rebound_sides();
  }
  if (game_ball_->get_position().intersects(game_bat_->get_position())) {
    game_ball_->rebound_bat_or_top();
  }

  auto game_bat_width = game_bat_->get_position().width;
  if (game_bat_->get_position().left < 0) {
    game_bat_->stop_move_left();
  }

  if (kWindowWidth < game_bat_->get_position().left + game_bat_width) {
    game_bat_->stop_move_right(kWindowWidth);
  }
}

/******************************************************************/

void Engine::update() {
  game_ball_->update();
  game_bat_->update();
}

/******************************************************************/

void Engine::draw() {
  window_.clear(Color(26, 128, 182, 255));
  window_.draw(game_bat_->get_shape());
  window_.draw(game_ball_->get_shape());

  window_.display();
}

/******************************************************************/
