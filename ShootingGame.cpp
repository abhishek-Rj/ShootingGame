#include"Game.h"

int main() {
    srand(time(NULL));
    Game shootingGame;
    while(shootingGame.is_window_running()) {
        shootingGame.game_update();
        shootingGame.game_render();
    }

    return 0;
}