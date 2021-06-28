
// Created by an0n1mity on 27/06/2021.
//

#include "structures.h"

Menu* CreateMenu(SDL_Renderer* renderer, SDL_Surface** surfaces, SDL_Texture** textures, TTF_Font* font, SDL_Window* window)
{
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    int window_w, window_h;
    SDL_GetWindowSize(window, &window_w, &window_h);
    menu->title_texture = textures[0];
    menu->random_texture = textures[1];
    menu->draw_texture = textures[2];
 
    menu->renderer = renderer;
    menu->font = font;

    menu->title_surface = surfaces[0];
    menu->random_surface = surfaces[1];
    menu->draw_surface = surfaces[2];

    menu->title_shape.w = (window_w/100)*3;
    menu->title_shape.h = 100;
    menu->title_shape.x = window_w/2 - menu->title_shape.w;
    menu->title_shape.y = 50;

    menu->random_shape.w = (window_w/100)*3;
    menu->random_shape.h = 100;
    menu->random_shape.x = menu->random_shape.w;
    menu->random_shape.y = window_h/2;			
    
    menu->draw_shape.w = (window_w/100)*3;
    menu->draw_shape.h = 100;
    menu->draw_shape.x = window_w - menu->draw_shape.w - 100;
    menu->draw_shape.y = window_h/2;

    menu->random = false;
    menu->draw = false;
    
    return menu;
}

void DrawMenu(Menu* menu)
{
    SDL_QueryTexture(menu->title_texture, NULL, NULL, &menu->title_shape.w, &menu->title_shape.h);
    SDL_RenderCopy(menu->renderer, menu->title_texture, NULL, &menu->title_shape);

    SDL_QueryTexture(menu->random_texture, NULL, NULL, &menu->random_shape.w, &menu->random_shape.h);
    SDL_RenderCopy(menu->renderer, menu->random_texture, NULL, &menu->random_shape);

    SDL_QueryTexture(menu->draw_texture, NULL, NULL, &menu->draw_shape.w, &menu->draw_shape.h);
    SDL_RenderCopy(menu->renderer, menu->draw_texture, NULL, &menu->draw_shape);

    SDL_RenderPresent(menu->renderer);

}

void CheckOverlightClick(Menu* menu, int mouse_x, int mouse_y)
{
	//Check if the mouse is cursor is above the button 
	int random_tl_corner_x = menu->random_shape.x;
        int random_tl_corner_y = menu->random_shape.y;
	int random_lr_corner_x = menu->random_shape.x + menu->random_shape.w;
 	int random_lr_corner_y = menu->random_shape.y + menu->random_shape.h;

	int draw_tl_corner_x = menu->draw_shape.x;
        int draw_tl_corner_y = menu->draw_shape.y;
	int draw_lr_corner_x = menu->draw_shape.x + menu->draw_shape.w;
 	int draw_lr_corner_y = menu->draw_shape.y + menu->draw_shape.h;
	
	SDL_Color color_r = {255, 0, 0};
	SDL_Color color_w = {255, 255, 255};


	if((mouse_x > random_tl_corner_x && mouse_x < random_lr_corner_x) && (mouse_y > random_tl_corner_y && mouse_y < random_lr_corner_y))
	{
		//Change the button color
		menu->random_surface = TTF_RenderText_Solid(menu->font, "Random", color_r);
		menu->random_texture = SDL_CreateTextureFromSurface(menu->renderer, menu->random_surface);
		DrawMenu(menu);
		menu->random = true;
	}

	else
	{
			menu->random_surface = TTF_RenderText_Solid(menu->font, "Random", color_w);
		menu->random_texture = SDL_CreateTextureFromSurface(menu->renderer, menu->random_surface);
		DrawMenu(menu);
		menu->random = false;
	}

	if((mouse_x > draw_tl_corner_x && mouse_x < draw_lr_corner_x) && (mouse_y > draw_tl_corner_y && mouse_y < draw_lr_corner_y))
	{
		//Change the button color
		menu->draw_surface = TTF_RenderText_Solid(menu->font, "Draw", color_r);
		menu->draw_texture = SDL_CreateTextureFromSurface(menu->renderer, menu->draw_surface);
		DrawMenu(menu);
		menu->draw = true;
	}

	else
	{
			menu->draw_surface = TTF_RenderText_Solid(menu->font, "Draw", color_w);
		menu->draw_texture = SDL_CreateTextureFromSurface(menu->renderer, menu->draw_surface);
		DrawMenu(menu);
		menu->draw = false;
	}
		
}
