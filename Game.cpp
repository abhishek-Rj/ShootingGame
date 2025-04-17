#include"Game.h"

void Game::initVariable() {
    this->window = nullptr;
    this->bulletSpawnTimer = 0;
}


void Game::initWindow() {
    this->video_mode.height = 800;
    this->video_mode.width = 1200;
    this->window = new sf::RenderWindow(this->video_mode, "Shooting Game");
    this->window->setFramerateLimit(60);
}

void Game::initTexture() {
    //FUCK DSA IDK HOW DO IT EFFECTIVELY
    std::vector<std::string> images = {"alien.png", "alien2.png", "alien3.png"};
    std::mt19937 gen(this->rd());
    std::uniform_int_distribution<> dist(0, 2);
    int randomNumber = dist(gen);
    if(!this->texture.loadFromFile(images[randomNumber])) {
        std::cerr << "Error: Could not load texture!" << std::endl;
    }
}

void Game::initText() {
    if (!(this->font.loadFromFile("operius-mono.ttf"))) {
        std::cout << "Font not loaded" << std::endl;
    }
    this->score.setFont(this->font);
    this->score.setCharacterSize(24); // Set font size
    this->score.setFillColor(sf::Color::White); // Set text color
    this->score.setPosition(10.f, 10.f); // Position on the top-left corner
    this->score.setString("Score: 0"); // Initial score text

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(48);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setPosition(400.f, 300.f);
    this->gameOverText.setString("Game Over!");
}

void Game::initSprite() {
    for (int i = 0; i < 5; ++i) { 
        sf::Sprite alien;
        alien.setTexture(this->texture);
        alien.setScale(0.2f, 0.2f);
        alien.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - alien.getGlobalBounds().width)), 0.f);
        this->aliens.push_back(alien);
    }
}

void Game::initShip() {
    if (!this->shipTexture.loadFromFile("ship.png")) {
        std::cerr << "Error: Could not load ship texture!" << std::endl;
    }

    this->ship.setTexture(this->shipTexture);
    this->ship.setScale(0.3f, 0.3f); // Scale the ship
    this->ship.setPosition(
        this->window->getSize().x / 2.f - this->ship.getGlobalBounds().width / 2.f, // Center horizontally
        this->window->getSize().y - this->ship.getGlobalBounds().height - 10.f     // Position near the bottom
    );
}

void Game::initBullet() {
    if (!this->bulletTexture.loadFromFile("bullet.png")) {
        std::cerr << "Error: Could not load bullet texture!" << std::endl;
    }
    this->bulletSpawnTimer = 0;
}


Game::Game() {
    this->initVariable();
    this->initWindow();
    this->initTexture();
    this->initSprite();
    this->initShip();
    this->initBullet();
    this->initText();
}


Game::~Game() {
    delete this->window;
}

bool Game::is_window_running() {
    return this->window->isOpen();
}

void Game::event_polling() {
    while(this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::updateBullets() {
    if (this->bulletSpawnTimer >= 15) {
        sf::Sprite bullet;
        bullet.setTexture(this->bulletTexture);
        bullet.setScale(0.05f, 0.05f);
        bullet.setPosition(
            this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2.f - bullet.getGlobalBounds().width / 2.f,
            this->ship.getPosition().y
        );
        this->bullets.push_back(bullet);
        this->bulletSpawnTimer = 0;
    } else {
        ++this->bulletSpawnTimer;
    }

    for (size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].move(0.f, -10.f);

        if (bullets[i].getPosition().y + bullets[i].getGlobalBounds().height < 0) {
            bullets.erase(bullets.begin() + i);
            --i;
            continue;
        }

        for (size_t j = 0; j < aliens.size(); ++j) {
            if (bullets[i].getGlobalBounds().intersects(aliens[j].getGlobalBounds())) {
                bullets.erase(bullets.begin() + i);
                aliens.erase(aliens.begin() + j);
                this->playerScore += 1; // Increment score by 10
                this->score.setString("Score: " + std::to_string(this->playerScore)); // Update score text
                --i;
                break;
            }
        }
    }
}

void Game::sprite_update() {
    for (size_t i = 0; i < this->aliens.size(); ++i) {
        this->aliens[i].move(0.f, 2.f);

        if (this->aliens[i].getGlobalBounds().intersects(this->ship.getGlobalBounds())) {
            std::cout << "Game Over! Alien collided with the ship." << std::endl;
            this->isGameOver = true; // Set the game over flag
            return;
        }

        if (this->aliens[i].getPosition().y > this->window->getSize().y) {
            this->aliens.erase(this->aliens.begin() + i);
            --i;
        }
    }

    if (rand() % 100 < 2) {
        sf::Sprite alien;
        alien.setTexture(this->texture);
        alien.setScale(0.2f, 0.2f);
        alien.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - alien.getGlobalBounds().width)), 0.f);
        this->aliens.push_back(alien);
    }
}

void Game::updateShip() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (this->ship.getPosition().x > 0) { // Prevent moving out of bounds
            this->ship.move(-5.f, 0.f); // Move left
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (this->ship.getPosition().x + this->ship.getGlobalBounds().width < this->window->getSize().x) {
            this->ship.move(5.f, 0.f); // Move right
        }
    }
}


void Game::game_update() {
    this->event_polling();
    this->sprite_update();
    this->updateShip();
    this->updateBullets();
}

void Game::game_render() {
    this->window->clear();

    if (this->isGameOver) {
        this->window->draw(this->gameOverText); // Draw the "Game Over" message
    } else {
        for (const auto& alien : this->aliens)
            this->window->draw(alien);

        for (const auto& bullet : this->bullets)
            this->window->draw(bullet);

        this->window->draw(this->ship);
        this->window->draw(this->score);
    }

    this->window->display();
}