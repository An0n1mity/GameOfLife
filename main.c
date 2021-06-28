//
// Created by an0n1mity on 27/06/2021.
//

#include "cells.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(){
    //Initi SDL libraries
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        printf("Error\n");
    }

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    long seed = 28474958696052;
    srand(seed);

    //Create the world in wich the cells will evolute
    World* world = CreateWorld(1000, 1000);
    //RandomizeWorld(world);

    bool show_menu = true;
    bool simulate = false;
    bool automata = true;
    bool draw = false;
    int mouse_x, mouse_y;

    //Simulation interface
    SDL_Window* simulation_window = SDL_CreateWindow("CellularAutomata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, world->width, world->height, SDL_WINDOW_SHOWN);
    SDL_Renderer* simulation_renderer = SDL_CreateRenderer(simulation_window, -1, SDL_RENDERER_ACCELERATED);
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
	    case SDL_KEYDOWN:
		show_menu = false;
		break;

	     case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouse_x, &mouse_y);
		CheckOverlightClick(menu, mouse_x, mouse_y);
    		break;
	}

    }

    SDL_DestroyWindow(menu_window);

    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            if(world->array[i][j].alive)
             DrawCell(&world->array[i][j], simulation_renderer);
        }
    }

    SDL_RenderPresent(simulation_renderer);
     //Wait for a mouse event
        while(SDL_WaitEvent(&events) && automata){
            //If the mouse is clicked
            switch(events.type) {
                case SDL_MOUSEBUTTONDOWN:
                    draw = true;
                    break;

                case SDL_MOUSEBUTTONUP:
                    draw = false;
                    break;

                case SDL_KEYDOWN:
                    draw = false;
                    simulate = true;
                    automata = false;
                    break;
            }

            if(draw)
            {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                MakeAlive(world, mouse_x, mouse_y);
                DrawCell(&world->array[mouse_y/10][mouse_x/10], simulation_renderer);
                SDL_RenderPresent(simulation_renderer);

                while(SDL_PollEvent(&events)){
                    switch(events.type) {
                        case SDL_KEYDOWN:
                            draw = false;
                            simulate = true;
                            automata = false;
                            break;
                    }
                }
            }
        }

        while(simulate && SDL_PollEvent(&events)){
	    switch(events.key.keysym.sym)
	    {
	    	case SDLK_ESCAPE:
			simulate = false;
	    }

            DetectNeighbors(world);
            UpdateWorld(world);
            DrawCells(world, simulation_renderer);
            SDL_RenderPresent(simulation_renderer);
            SDL_Delay(10);
        }

	SDL_DestroyWindow(simulation_window);
	SDL_Quit();
	return 0;
    }
