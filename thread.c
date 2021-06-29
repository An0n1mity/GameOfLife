#include <pthread.h>
#include <stdbool.h>
#include "thread.h"
#include <SDL2/SDL.h>
#include "world.h"
#include "cells.h"

void* AcessWorld()
//Every 10 seconds update the world randomly
{
	while(thread){
		RandomCells(world);
		RandomCells(world);
		RandomCells(world);
		DrawCells(world, world->renderer);
		printf("Thread\n");
		SDL_Delay(1000);

	}
	return NULL;
}

