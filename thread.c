#include <pthread.h>
#include <stdbool.h>
#include "thread.h"
#include <SDL2/SDL.h>
#include "world.h"

void* AcessWorld()
//Every 10 seconds update the world randomly
{
	while(thread){
		RandomCells();
		printf("Thread\n");
		SDL_Delay(10000);
	}

	return NULL;
}

void RandomCells()
//Create random cells island square of 3*3
{
	int center_x = rand()%world->width;
	int center_y = rand()%world->height;
	
	world->array[center_y][center_x].alive = true;
}
