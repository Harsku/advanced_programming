#include <iostream>
#include <SDL.h>
#include "window.h"


int main(int argc, char *argv[]) {
	Window Window("Game",600,500);
	while (Window.window != nullptr) {
		Window.torender();
		Window.PressEvents();
		
	}
	return 0;
}

