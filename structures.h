//
// Created by an0n1mity on 27/06/2021.
//

#ifndef CELLULARAUTOMATA_STRUCTURES_H
#define CELLULARAUTOMATA_STRUCTURES_H

#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct Cells{
    //Current state of the cell : Alive or dead
    bool alive;
    bool flag;
    //Right next neighbors of the cell
    struct Cells** neighbors;
    //The shape of the cell
    SDL_Rect shape;
}Cells;

typedef struct World{
    //Number of cells in a row
    int width;
    //Number of cells in a column
    int height;
    //The cells
    Cells** array;
}World;

typedef struct Menu{
    SDL_Renderer* renderer;
    
    SDL_Surface* title_surface;
    SDL_Surface* random_surface;
    SDL_Surface* draw_surface;

    SDL_Texture* title_texture;
    SDL_Texture* random_texture;
    SDL_Texture* draw_texture;

    TTF_Font* font;

    SDL_Rect title_shape;
    SDL_Rect random_shape;
    SDL_Rect draw_shape;

}Menu;

#endif //CELLULARAUTOMATA_STRUCTURES_H
