#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>
#include "Player.h"
#include "Obstacle.h"

#undef main

//#define WINDOW_WIDTH 600
using namespace std;


int main(void) {
	/*
	 * Initializing key variables used later on
	 * For use of ease during development window size and game speed are hardcoded.
	 * Will probably give back control to end user.
	 */
	int WINDOW_WIDTH = 500; //This will be used to set the window size to 500x500 pixels
	int speed = 50; 		//This sets the speed which works inversely, so smaller number give faster speeds.
	SDL_Renderer *renderer; //The renderer that is used to render everything in the window.
	SDL_Window *window;		//The window everything is rendered in
	double playerx = WINDOW_WIDTH / 2; //Initializing player vars
	double playery = WINDOW_WIDTH / 2;
	double direction = 0;


	/*
	 * Creating two players, currently hardcoded. Sets colour, starting position and direction.
	 */
	Player player1(255, 0, 0, 255, playerx, playery, direction);
	Player player2(0, 255, 0, 255, WINDOW_WIDTH * 3 / 4, playery, direction);

	/*
	 * Initializing the SDL/graphics used to visualize the game
	 */
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);



    /*
     * This is where the game level is filled with blocks/obtacles. Every part of the level is covered, but only obstacles
     * are actually visible.
     */
    auto mapWidth = WINDOW_WIDTH / 20;
    vector<vector<Obstacle>> mapMatrix; //Creating the 2-D vector/array that houses the obstacles
    mapMatrix.resize(mapWidth, vector<Obstacle>(mapWidth, Obstacle(0, 0, 0, 1))); //Resizing so it fits to the board
    for (int j = 0; j < mapWidth ; j++){
        for (int i = 0; i < mapWidth; i++){		//Iterating through all the elements in the 2-D vector
            int type = (int)floor(rand()%10); 	//Object type is randomly generated
            mapMatrix[j][i].setX(j*mapWidth);	//Setting x coordinates for the object
            mapMatrix[j][i].setY(i*mapWidth); 	// Setting y coordinates for the object
            mapMatrix[j][i].setType(type); 		//Object type is randomly generated
            mapMatrix[j][i].setObstacleWidth(mapWidth); //Setting the width og each obstacle, simply makes sure that the squares cover everything and don't have gaps in between.
            mapMatrix[j][i].loadObstacle(renderer); //Rendering the obstacles

        }
    }

	/*
	 * The game itself runs in this while loop, as long as quit is false the game runs.
	 */
	bool quit = false;

	while (!quit) {
		// set timeout to limit frame rate
		Uint32 timeout = SDL_GetTicks() + speed;
		// Handle the input
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			// All keydown events, which means that when a key is pressed an action/function is performed
			// In this case left, right, a and d changes the direction where the player is going. Q is used to exit the game
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					player1.setDir(player1.getDir()- 0.01*M_PI);
					break;
				case SDLK_RIGHT:
					player1.setDir(player1.getDir() + 0.01*M_PI);
					break;
				case SDLK_a:
					player2.setDir(player2.getDir() - 0.01*M_PI);
					break;
				case SDLK_d:
					player2.setDir(player2.getDir() + 0.01*M_PI);
					break;
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}

		/*
		 * The rendering/drawing of each player, the position is also updated
		 */

		//Uint8 r, g, b, a;
		SDL_Rect srcrect;
		srcrect.x = (int)playerx;
		srcrect.y = (int)playery;
		srcrect.h = 1;
		srcrect.w = 1;
		int* pixels[4];
		int pitch = 0;
		SDL_RenderReadPixels(renderer, &srcrect, 0, &pixels, pitch);
		player1.posUpdate();
		player2.posUpdate();
		SDL_SetRenderDrawColor(renderer, player1.getR(), player1.getG(), player1.getB(), player1.getA());
		SDL_RenderDrawPoint(renderer, (int)player1.getX(), (int)player1.getY());
		SDL_SetRenderDrawColor(renderer, player2.getR(), player2.getG(), player2.getB(), player2.getA());
		SDL_RenderDrawPoint(renderer, (int)player2.getX(), (int)player2.getY());
		SDL_RenderPresent(renderer);


		/*
		 * This part is the prototype of hit detection. It currently only checks for player one.
		 * When the coordinates of player one match that of a certain type of block/obstacle, currently simply named 1,
		 * it changes the colour of the player. Only works with obstacles, a different solution will have to be used to detect collision with a player line.
		 * This will be expanded to either outright kill a player, or bump the player away etc.
		 */
        int obstacleTypeAtPlayerPos = mapMatrix[floor(player1.getX()/mapWidth)][floor(player1.getY()/mapWidth)].getType();
        if (obstacleTypeAtPlayerPos == 1) {
            player1.setR(0);
            player1.setA(0);
            player1.setG(0);

        } else{
        	player1.setR(255);
        	player1.setG(255);
        	player1.setA(255);
        	player1.setB(255);
        }


		while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
			// ... do work until timeout has elapsed
		}
	}
	/*
	 * Destroys the renderer and window, shutting down SDL properly
	 */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}