//
// Created by an0n1mity on 27/06/2021.
//

#include "cells.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

void main(){
    //Initi SDL libraries
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
        printf("Error\n");
    }
    long seed = 28474958696052;
    srand(seed);

    //Create the world in wich the cells will evolute
    World* world = CreateWorld(1000, 1000);
    RandomizeWorld(world);


    bool simulate = false;
    bool automata = true;
    bool draw = false;
    int mouse_x, mouse_y;

    SDL_Window* window = SDL_CreateWindow("CellularAutomata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, world->width, world->height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event events;

    SDL_RenderClear(renderer);

    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            if(world->array[i][j].alive)
             DrawCell(&world->array[i][j], renderer);
        }
    }

    SDL_RenderPresent(renderer);
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
                DrawCell(&world->array[mouse_y/10][mouse_x/10], renderer);
                SDL_RenderPresent(renderer);

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

        while(simulate){

            DetectNeighbors(world);
            UpdateWorld(world);
            DrawCells(world, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }

    }
