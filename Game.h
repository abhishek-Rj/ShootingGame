#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<ctime>
#include<iostream>
#include<vector>
#include<string>
#include<random>

class Game {
private:
    sf::RenderWindow* window;
    sf::VideoMode video_mode;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Event event;
    sf::Text score;
    sf::Font font;
    sf::CircleShape circle;
    int playerScore = 0;
    sf::Text gameOverText;

    sf::Texture shipTexture;
    sf::Sprite ship;
    bool isGameOver = false;
    sf::Texture bulletTexture;
    std::vector<sf::Sprite> bullets;
    unsigned bulletSpawnTimer;

    std::vector<sf::Sprite> aliens;
    std::random_device rd;

    void initVariable();
    void initWindow();
    void initShip();
    void initTexture();
    void initSprite();
    void initBullet();
    void initText();

public:
    Game();
    ~Game();
    bool is_window_running();
    void event_polling();
    void sprite_update();
    void updateShip();
    void updateBullets();
    void game_update();
    void game_render();
};
