//
// Created by an0n1mity on 27/06/2021.
//

#ifndef CELLULARAUTOMATA_MENU_H
#define CELLULARAUTOMATA_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "structures.h"


void DrawMenu(Menu* menu);
Menu* CreateMenu(SDL_Renderer* renderer, SDL_Surface** surfaces, SDL_Texture** textures, TTF_Font* font, SDL_Window* window);
void CheckOverlightClick(Menu* menu, int mouse_x, int mouse_y);
#endif //CELLULARAUTOMATA_MENU_H
