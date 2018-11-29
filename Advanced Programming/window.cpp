#include "window.h"
#include <iostream>


Window::Window(const std::string &Gamename= "game", int width = 800, int height=600) :
	Game(Gamename), m_width(width), m_height(height)
{
	init(); /** calling the init() function to create window*/
}
Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_Quit();
	window = nullptr;
}

void Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL not initialised" << std::endl;
		
	}
	window = SDL_CreateWindow(Game.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_RESIZABLE);
}

void Window::PressEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			SDL_Log("Window closed");
			Window::~Window();
			break;
		
		default:
			break;
		}
	}
}

void Window::torender()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); //*Exception*/
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); /**Setting a color to renderer*/
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 50;
	rectangle.h = 50;
	SDL_RenderFillRect(renderer, &rectangle);*/
	SDL_RenderClear(renderer); /**Giving color to renderer*/	
	SDL_RenderPresent(renderer);/**To present renderer solor on the screen*/
}
		

