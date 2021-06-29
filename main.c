//
// Created by an0n1mity on 27/06/2021.
//

#include "cells.h"
#include "world.h"
#include "menu.h"
#include "thread.h"
#include "structures.h"

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

World* world;
bool thread = true;

int main(){
    //Initi SDL libraries
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        printf("Error\n");
    }

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    srand(time(NULL));

    //Create the world in wich the cells will evolute
    world = CreateWorld(500, 500);
    //Create a thread 
    pthread_t thread_id;
    
    if(world->array[0][0].alive)
	    printf("Thread changed it\n");

    bool show_menu = true;
    bool simulate = false;
    bool draw = false;
    bool drawing = false;
    bool random = false;  
    int mouse_x, mouse_y;

    //Simulation interface
    SDL_Window* simulation_window = SDL_CreateWindow("CellularAutomata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, world->width*10, world->height*10, SDL_WINDOW_SHOWN);
    SDL_Renderer* simulation_renderer = SDL_CreateRenderer(simulation_window, -1, SDL_RENDERER_ACCELERATED);
	world->renderer = simulation_renderer;

    //Menu interface
    SDL_Window* menu_window = SDL_CreateWindow("CellularAutomata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, world->width, world->height, SDL_WINDOW_SHOWN);
    SDL_Renderer* menu_renderer = SDL_CreateRenderer(menu_window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("/home/an0n1mity/CLionProjects/CellularAutomata/Pixeled.ttf", 25);
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surfaces[3];
    SDL_Texture* textures[3];

    //All the menu surfaces
    surfaces[0] = TTF_RenderText_Solid(font,"Game OF Life", color);
    surfaces[1] = TTF_RenderText_Solid(font,"Random", color);
    surfaces[2] = TTF_RenderText_Solid(font, "Draw", color);

    //All the menu textures
    textures[0] = SDL_CreateTextureFromSurface(menu_renderer, surfaces[0]);
    textures[1] = SDL_CreateTextureFromSurface(menu_renderer, surfaces[1]);
    textures[2] = SDL_CreateTextureFromSurface(menu_renderer, surfaces[2]);
    
    Menu* menu = CreateMenu(menu_renderer, surfaces, textures, font, menu_window);
    SDL_Event events;

    SDL_SetRenderDrawColor(menu_renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(menu_renderer);
    SDL_RenderClear(simulation_renderer);


    //Menu loop
    DrawMenu(menu);
    while(show_menu && SDL_WaitEvent(&events)){

	switch(events.type){
	     case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouse_x, &mouse_y);
		CheckOverlightClick(menu, mouse_x, mouse_y);
    		break;
		
	     case SDL_MOUSEBUTTONDOWN:
		if(menu->random)
			random = true;
		else if(menu->draw)
			draw = true;
		show_menu = false;
		break;
	}

    }

    SDL_DestroyWindow(menu_window);

    SDL_RenderPresent(simulation_renderer);

    //Generate random intital world
    if(random){
	printf("Random\n");
	draw = false;
	simulate = true;
	
	//RandomizeWorld(world);
	pthread_create(&thread_id, NULL, AcessWorld, NULL);

    	for (int i = 0; i < world->height; ++i) {
        	for (int j = 0; j < world->width; ++j) {
            	if(world->array[i][j].alive)
        	     	DrawCell(&world->array[i][j], simulation_renderer);
        	}
    	}
	SDL_RenderPresent(simulation_renderer);
    }

     //Wait for a mouse event
     if(draw){
        while(SDL_WaitEvent(&events) && draw){
            //If the mouse is clicked
            switch(events.type) {
                case SDL_MOUSEBUTTONDOWN:
              	    drawing = true;
		    draw = false;
		    printf("Drawing\n");
		    break;
		
            }
	}
       
	while(drawing)
        {
		SDL_PollEvent(&events);
        	switch(events.type) {
                        case SDL_KEYDOWN:
			    printf("Stop Drawing\n");
			    drawing = false;
                            simulate = true;
                            break;

			case SDL_MOUSEMOTION:
			 	SDL_GetMouseState(&mouse_x, &mouse_y);
                		MakeAlive(world, mouse_x, mouse_y);
                		DrawCell(&world->array[mouse_y/10][mouse_x/10], simulation_renderer);
                		SDL_RenderPresent(simulation_renderer);
			    	break;
               }
        }
     }


        while(simulate){
	    printf("Simulate\n");
	    //pthread_join(thread_id, NULL);
	    SDL_PollEvent(&events);
	    switch(events.key.keysym.sym)
	    {
	    	case SDLK_ESCAPE:
			simulate = false;
			printf("End\n");
	    		break;
	    }

            DetectNeighbors(world);
            UpdateWorld(world);
            DrawCells(world, simulation_renderer);
            SDL_RenderPresent(simulation_renderer);
            SDL_Delay(10);
        }
	thread = false;
	pthread_join(thread_id, NULL);
	SDL_DestroyWindow(simulation_window);
	SDL_Quit();
	return 0;
    }
