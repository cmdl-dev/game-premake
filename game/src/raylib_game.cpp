#include "raylib.h"
#include "Game.h"

#include <iostream>

const int SCREEN_HEIGHT = 450;
const int SCREEN_WIDTH = 800;
// TODO: have a const file
int main(void)
{
    //--------------------------------------------------------------------------------------
    Game game{SCREEN_WIDTH, SCREEN_HEIGHT, "Deities Vessel"};
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    while (!game.shouldRunGame())
    {

        float delta = GetFrameTime();
        game.handleEvents();
        game.tick(delta);
    }

    return 0;
}
