#pragma once

#include "ViewControllerBase.h"
#include <iostream>
#include <cmath>
#include "Button.h"


using namespace sf;

class GameSprite
{
private:
	Sprite spr;
	int xPos;// ������� � ������� �� x �����
	int yPos;// ������� � ������� �� y �����
	int position;
	int xBeg;
	int yBeg;
	int xEn;
	int yEn;

	void swap(GameSprite &obg) {
		int tmp;

		//x
		tmp = xBeg;
		xBeg = obg.xBeg;
		obg.xBeg = tmp;

		tmp = xEn;
		xEn = obg.xEn;
		obg.xEn = tmp;

		tmp = xPos;
		xPos = obg.xPos;
		obg.xPos = tmp;


		//y		
		tmp = yBeg;
		yBeg = obg.yBeg;
		obg.yBeg = tmp;

		tmp = yEn;
		yEn = obg.yEn;
		obg.yEn = tmp;

		tmp = yPos;
		yPos = obg.yPos;
		obg.yPos = tmp;

		//position
		tmp = position;
		position = obg.position;
		obg.position = tmp;

		//��������� ������ ������ �������

		spr.setPosition(xBeg, yBeg);
		obg.spr.setPosition(obg.xBeg, obg.yBeg);

	};

	friend class ViewControllerGame;
};

class ViewControllerGame : public ViewControllerBase {

	//View

	RectangleShape *BackFon;

	Texture tGame;//�������� ��������, ������� ����� �������
	Texture tFon;// �������� ����

	Sprite Fon;// ������ ���� 
	Sprite t;

	GameSprite *mapGame;

	int length;// ���������� ������ � ����� ������

	int height;//������ � ������ ���� ����
	int width;

	int Sheight;//������ � ������ ����� �������� �������
	int Swidth;

	int Theight;//������ ��������
	int Twidth;// ������ ��������
	
	//Controller

	Button *BMenu;


	bool isWin(RenderWindow &window);
public:

	ViewControllerGame(int numI, int diff);
	~ViewControllerGame();
	
	void getView(RenderWindow &window) override;
	int controller(RenderWindow &window, int x, int y) override;

	

	friend class GameSprite;

};