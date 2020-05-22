#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
	const int xBegin;
	const int yBegin;
	const int xEnd;
	const int yEnd;
public:
	Button(int xB, int yB, int xE, int yE) : xBegin(xB), yBegin(yB), xEnd(xE), yEnd(yE) {};

	bool isPress(RenderWindow &window, int x, int y);
};