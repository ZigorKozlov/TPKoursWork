#pragma once
#include "ViewControllerBase.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "iostream"

enum {none, Im1, Im2, Im3, Im4};

using namespace sf;

class ViewControllerMenu;

class ViewControllerMenu: public ViewControllerBase {

	//For ViewMenu
	Texture T1, T2, T3, T4, T5;

	Sprite Fon;

	Sprite Image1;//4 загруженных пользователем картинки
	Sprite Image2;
	Sprite Image3;
	Sprite Image4;

	//For ControllerMenu
	Button *BattonExit1;
	Button *BattonExit2;
	Button *BattonStart;
	Button *BattonIm1;
	Button *BattonIm2;
	Button *BattonIm3;
	Button *BattonIm4;
	Button *BattonR9;
	Button *BattonR16;
	Button *BattonR25;
	Button *BattonR36;


	ViewControllerMenu();
	ViewControllerMenu(const ViewControllerMenu &obg) = delete;
public:

	~ViewControllerMenu();

	static ViewControllerBase* Instance() {
		static ViewControllerBase *shared;
		if (!shared)
			shared = new ViewControllerMenu();
		return shared;
	};

	int controller(RenderWindow &window, int x, int y) override;
	void getView   (RenderWindow &window) override;
};