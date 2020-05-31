#include "engine.h"
#include <SFML/Audio.hpp>
#include <sstream>

constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr int kBallStarPos = 1;
constexpr int kBatHeightLevel = 200;
constexpr int kUserLives = 3;

/******************************************************************/

Engine::Engine() : user_lives_{kUserLives}, user_scores_{0} {
  window_.create(sf::VideoMode(kWindowWidth, kWindowHeight), "Pong");

  sf::Image game_icon;
  game_icon.loadFromFile("icons/ping-pong-bat.png");
  window_.setIcon(game_icon.getSize().x, game_icon.getSize().y,
                  game_icon.getPixelsPtr());

  game_bat_ =
      std::make_unique<Bat>(kWindowWidth / 2, kWindowHeight - kBatHeightLevel);
  game_ball_ = std::make_unique<Ball>(kWindowWidth / 2, kBallStarPos);

  sf::Listener::setPosition(10.f, 0.f, 5.f);
  sf::Listener::setDirection(1.f, 0.f, 0.f);
  sf::Listener::setUpVector(1.f, 1.f, 0.f);
  sf::Listener::setGlobalVolume(50.f);
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

    score_text_.setPosition(50, 710);
    Font font;
    font.loadFromFile("resources/game_text.ttf");
    score_text_.setFont(font);
    score_text_.setCharacterSize(20);
    score_text_.setFillColor(sf::Color::White);

    update();

    std::stringstream ss;
    ss << "SCORE: " << std::to_string(user_scores_)
       << "\tLIVES: " << std::to_string(user_lives_) << std::endl;
    score_text_.setString(ss.str());

    draw();
  }
}

/******************************************************************/

void Engine::check_gameplay() {
  if (game_ball_->get_position().top > kWindowHeight) {
    user_lives_--;
    if (user_lives_ == 0) {
      user_lives_ = kUserLives;
      user_scores_ = 0;
    }
    play_sound("sounds/lose.wav");
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
    user_scores_++;
  }

  auto game_bat_width = game_bat_->get_position().width;
  if (game_bat_->get_position().left < 0) { game_bat_->stop_move_left(); }

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
  window_.draw(score_text_);

  window_.display();
}

/******************************************************************/

void Engine::play_sound(const std::string &sound_path) {
  sf::Sound game_sound;
  game_sound.setPosition(0.f, 0.f, 0.f);
  game_sound.setRelativeToListener(true);
  sf::SoundBuffer buffer;

  if (buffer.loadFromFile(sound_path)) {
    game_sound.setBuffer(buffer);
    game_sound.play();
  }
}

/******************************************************************/
