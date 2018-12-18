//
// Created by harald on 07.12.18.
//

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include "Obstacle.h"
/*
 * Obstacle, or could also be referenced as a block. Will be expanded to include killing the player and other properties.
 * Currently more of a framework for future work.
 */
Obstacle::Obstacle(double x, double y, int width, int type) : posX(x), posY(y), obstacleWidth(width), obstacleType(type){}
//Setting the position of the obstacle/block, and other parameters that will be used.
void Obstacle::setX(double x) {posX = x;}
void Obstacle::setY(double y) {posY = y;}
void Obstacle::setObstacleWidth(int width) { obstacleWidth = width;}
void Obstacle::setType(int type) {obstacleType = type;}

void Obstacle::loadObstacle(SDL_Renderer* renderer) { //This function loads the given obstacles/block, but does not outright render it
    int x = (int)posX;
    int y = (int)posY;
    int width = obstacleWidth;
    int height = obstacleWidth;

    SDL_Rect rect{x, y, width, height}; //Currently SDL_rect is used to draw rectangles on the window, depending on time might expand to use images instead.
    if (obstacleType == 1){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Sets colour of obstacles of type 1

    } else if(obstacleType == 2){
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    }else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    }
    SDL_RenderFillRect(renderer, &rect);


}
//Some of these getters are not used, might remove.
double Obstacle::getX() { return posX;}
double Obstacle::gety() { return posY;}
int Obstacle::getType() { return obstacleType;}




