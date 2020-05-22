#include "Button.h"

bool Button::isPress(RenderWindow &window, int x, int y)
{

	if ((x >= xBegin) && (y >= yBegin) && (x <= xEnd) && (y <= yEnd))
		return true;
	
	return false;
}
