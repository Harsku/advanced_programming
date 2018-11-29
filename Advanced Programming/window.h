#pragma once
#include <string>
#include <SDL.h>

class Window {
public:
	Window(const std::string &Gamename, int width, int height);
	~Window();

	void PressEvents();
	void torender();
	SDL_Window *window = nullptr;

private:
	void init();

	std::string Game;
	int m_height;
	int m_width;

	SDL_Renderer *renderer = nullptr;
	int x = 0;
	int y = 0;
	int w = 50;
	int h = 50;
};
