#include <SDL2/SDL.h>
//#include <SDL2/SDL_timer.h>
//#include <SDL2/SDL_image.h>
#include <stdio.h>
int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	printf("Window Initialization!\n");

	SDL_Window *window;

	//printf("SDL_WINDOWPOS_CENTERED is %d\n", SDL_WINDOWPOS_CENTERED);

	window = SDL_CreateWindow(
				"SDL2 Test",	
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				640,
				480,
				0
			);

	if(window == NULL){
		printf("Creation of Window Failed\n");
		SDL_Quit();
		return -1;
	}

	SDL_Delay(3000);	//delay for 3000 ms

	SDL_Renderer* rend = NULL;

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
