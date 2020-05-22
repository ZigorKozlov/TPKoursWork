#pragma once
#include <SFML/Graphics.hpp>
#include "ViewControllerBase.h"
#include "ViewControllerMenu.h"
#include "ViewControllerGame.h"

using namespace sf;

enum { menu, game};

class GamePazzle{

	RenderWindow window;

	ViewControllerBase *viewController[2];

public:
	GamePazzle(const GamePazzle&) = delete;
	~GamePazzle();

	GamePazzle(int x = 1366, int y = 768) : window(VideoMode(x, y), "GamePazzle", Style::Fullscreen)
	{
		viewController[ menu ] = ViewControllerMenu::Instance();
		viewController[ game ] = nullptr;
	};

	int startGame();
};