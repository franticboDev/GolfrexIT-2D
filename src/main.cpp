#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	return true;
}

bool SDLinit = init();
RenderWindow window("GolfrexIT - Deluxe2D Edition", 1270, 720); 

SDL_Texture* ballTexture = window.loadTexture("res/gfx/balls/Default-ball.png");

/*std::vector<Tile> loadTiles(int level)
{
	std::vector<Tile> temp = {};
	switch(level)
	{

	}
	return temp;
}*/

int level = 0;
//std::vector<Tile> tiles = loadTiles(level);

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;

SDL_Event event;
int state = 0; //0 = menu, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
//	tiles = loadTiles(level);

	switch(level)
	{

	}
}

const char* getStrokeText()
{
	return 0;
}

const char* getLevelText()
{
	return 0;
}

void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency());

	mousePressed = false;
	//Get controls and events
	while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					gameRunning = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						mouseDown = true;
						mousePressed = true;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						mouseDown = false;
					}
					break;
			}
		}
}

void graphics()
{
	window.clear();
	Entity player(Vector2f(600, 360), ballTexture);
	window.display();
}

void game()
{
	update();
	graphics();
}

int main(int argc, char* args[])
{

	game();
	window.cleanUp();
	SDL_Quit();

	return 0;
}