#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GolfrexIT - Deluxe2D Edition", 1270, 720); 
	std::cout << window.getRefreshRate() << std::endl;

	SDL_Texture* ballTexture = window.loadTexture("res/gfx/balls/Default-ball.png");

	Entity player(Vector2f(600, 360), ballTexture);

	bool gameRunning = true;

	SDL_Event event;

	const float deltaTime = 0.01f;
	float acumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while (gameRunning)
	{
		int startTick = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		acumulator += frameTime;

		while(acumulator >= deltaTime)
		{
				// Get our controls and events
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			acumulator -= deltaTime;

		}

		//const float alpha = acumulator / deltaTime; //50% ?


		window.clear();

		window.render(player);
		window.display();

		int frameTicks = SDL_GetTicks() - startTick;

		if(frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}