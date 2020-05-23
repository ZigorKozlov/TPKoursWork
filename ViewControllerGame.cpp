#include "ViewControllerGame.h"

ViewControllerGame::ViewControllerGame(int numI, int diff)
{


	try {
		if ((numI < 1) || (numI > 4))
			throw numI;

		if (!((diff == 9) || (diff == 16) || (diff == 25) || (diff == 36)))
			throw diff;

		numImage = numI;
		diffLvl = diff;
	}
	catch (int num) {
		std::cout << "������, �� ������� �������� �������� ����." << std::endl;
		exit(0);
	}

	length = sqrt(diff);

	// ����� �������� �� ������ ���� + �������� ����
	try {


		Image Im_I;

		if (Im_I.loadFromFile("FonGame.jpg") != false) {
			tFon.loadFromImage(Im_I);

			Fon.setTexture(tFon);
			Fon.setPosition(0, 0);
		}
		else {
			std::cout << "������ �������� ���� ����, ���� ���� �� �����, ������������ ������������� ����" << std::endl;
		}

		//����� �������� ��� ����, ������ �� ������ �� ����
		int count = 0;
		if (numImage == 1) {
			Im_I.loadFromFile("Image1.jpg");
			tGame.loadFromImage(Im_I);
			count++;
		}
		else {
			if (numImage == 2) {
				Im_I.loadFromFile("Image2.jpg");
				tGame.loadFromImage(Im_I);
				count++;
			}
			else {
				if (numImage == 3) {
					Im_I.loadFromFile("Image3.jpg");
					tGame.loadFromImage(Im_I);
					count++;
				}
				else {
					if (numImage == 4) {
						Im_I.loadFromFile("Image4.jpg");
						tGame.loadFromImage(Im_I);
						count++;
					}
					else {
						throw numImage;
					}
				}
			}
		}
		//
		if (count == 0)
			throw count;

		

	}
	catch (int numImage) { // ������ ������ ���� �� ������, �� �� ��, �� ������ ������
		std::cout << "������, �� ������� �������� ��� ��� ������ �� ���������, �������� � ����� ����(������ �������� �.�. jpg). �������� ����."<<std::endl;
		exit(0);
	}
	
	//���������� �������� �������� ����, � ����������� �� �������� ��� �� �� �������� �����������
	//����� �������� .������� �������� ���� ��������  1300�700
	try {
		//y
		height = int(700 / length) * length;

		//x
		width = int(1300 / length) * length;// ��� �� ���������� �� ������ ��� �������

		//���������� �������� �������� ����:
		Sprite tmpSpr;
		tmpSpr.setTexture(tGame);

		Theight = tmpSpr.getGlobalBounds().height;//�������� ������� ������ � ������ ��������
		Twidth = tmpSpr.getGlobalBounds().width;
		if ((Theight < 100) || (Twidth < 100))
			throw Theight;

		changeScale(tmpSpr, height, width);//����������� �������� ��� ������ ���� 

		// ������� ������� �������� �������� ����
		height = (int)tmpSpr.getGlobalBounds().height;
		width = (int)tmpSpr.getGlobalBounds().width;

		height = int(height / length) *length;
		width = int(width / length) *length;

		
	}
	catch (int th) {
		std::cout << "��������, �������� �������� ����� ������, ��� ��� � �� ������� ������ ����������." << std::endl;
	}
	//������ � ������ 1 ����� �� ������� ����
	Sheight = height / length;
	Swidth = width / length;


	//������� �������� ���� ������
	mapGame = new GameSprite[diff];//������ ������ �� dif(9||16||25||36) ��������
	
	//��������� ������������� �������
	for (int i = 0; i < diff; i++) {
		mapGame[i].position = diff - i - 1;
	}
	
	srand(time(NULL));
	//� ��������� ������� ������������ �������
	for (int i = 0; i < 1000; i++) {

		int a = rand() % (diff);
		int b = rand() % (diff);
		int tmp = 0;

		//swap
		tmp = mapGame[a].position;
		mapGame[a].position = mapGame[b].position;
		mapGame[b].position = tmp;
	
	}


	//������������� x, y, � spr(Sprite)
	for (int i = 0; i < diff; i++) {
		mapGame[i].xPos = mapGame[i].position % length; //������������ ������� � ������� � ����������� �� ���������� ������������� �� �������
		mapGame[i].yPos = mapGame[i].position / length;//�� ��������

		//���������� ��������� ������ � ����� ������� ������������ ���������� ������� ��������� - (0,0) �� ������
		mapGame[i].xBeg = mapGame[i].xPos *Swidth;
		mapGame[i].yBeg = mapGame[i].yPos *Sheight;

		mapGame[i].xEn = (mapGame[i].xPos + 1)  * Swidth  - 1;
		mapGame[i].yEn = (mapGame[i].yPos + 1 ) * Sheight - 1;

		//��������� ����������� ������, ������������� ������(������� �� ��������) � ������������� ����� ������ �������
		mapGame[i].spr.setTexture(tGame);

		//-------------------------------------------------------------------------------------------------------------------------------------
		//                                    |x ������ ������� |y ������ �������  | ������ | ������|
		mapGame[i].spr.setTextureRect(IntRect((i % length) * (Twidth/ length), (i / length) * (Theight/ length), (Twidth / length), (Theight / length)));//0 ������� ������� - 0,0 ������ �������, 1 - 0,1 � �.�
		changeScale(mapGame[i].spr, Sheight, Swidth);
		mapGame[i].spr.setPosition(mapGame[i].xBeg, mapGame[i].yBeg);//�� ������� ������� �� ������� ���� ������ position
	}

	//�������� ������� ���� �������� ����
	BackFon = new RectangleShape(Vector2f(width+5, height+5));
	BackFon->setFillColor(Color::Black);


	//Controller
	BMenu = new Button(0, 705, 475, 759);//������ ������ � ����
}

ViewControllerGame::~ViewControllerGame()
{


	if (mapGame != nullptr)
		delete []mapGame;
	if(BackFon != nullptr)
		delete BackFon;

	if (BMenu != nullptr)
	delete BMenu;
}

void ViewControllerGame::getView(RenderWindow & window)
{
	window.draw(Fon);//������ ���
	//������ ������ ��� �������� ������������
	window.draw(*BackFon);

	
	//�������� ������� GetviewMap(��������� ��������� ���������� �������� �� x, y � pos)
	//����� ������� ������ SetPposition(xBeg, yBeg)
	for (int i = 0; i < diffLvl; i++) {
		window.draw(mapGame[i].spr);
	}

}

int ViewControllerGame::controller(RenderWindow & window, int x, int y)
{
	 
	//������ ����
	if (BMenu->isPress(window, x, y)) {
		return 1;//���������� 1, ������� � ����
	}

	//����������� ��������� ������� ������()

	//���� ������ �� ������� ����, ����� ��������� ������������
	if (x < width, y < height) {
		//������� ���� �� ������� ����

		bool isReleased = false;
		int xEndState;
		int yEndState;
		int pressedPosition = -1;

	
		try {

			//���� ����� c������ �� ������� ������
			for (int i = 0; i < diffLvl; i++) {
				if ((mapGame[i].xBeg < x) && (mapGame[i].yBeg < y) && (mapGame[i].xEn > x) && (mapGame[i].yEn > y)) {
					pressedPosition = i;//��������� ������� ������ �� ������� ������ 
					break;
				}
			}
			if (pressedPosition == -1)//���-�� ����� �� ���, ��� �� ���� �� ������� ������������ � �������� ���� ����
				throw pressedPosition;
		}
		catch (int pp) {
			return 0;
		}
		//

		while (window.isOpen()) {

			//��������� ���������� �����
			
			Vector2i pixelPos = Mouse::getPosition(window);//�������� ���������� �������
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			Event event;

			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
					std::cout << "exit" << std::endl;
				}

				if (event.type == Event::MouseButtonReleased) {//���� ������ ������

					if (event.key.code == Mouse::Left) {// � ���� ������������ ������ ����� ������ ����
						//�������� x, y ��������� ��������� ����
						xEndState = event.mouseButton.x;
						yEndState = event.mouseButton.y;

						if (!(xEndState < width, yEndState < height)) {
							mapGame[pressedPosition].spr.setPosition(mapGame[pressedPosition].xBeg, mapGame[pressedPosition].yBeg);
							return 0;
						}
						//
						isReleased = true;
						break;
					}
						
				}

			}
			if (isReleased)
				break;
			//����� ������, 
			window.clear();

			window.draw(Fon);//������ ���
			//������ ������ ��� �������� ������������
			window.draw(*BackFon);


			//�������� ������� GetviewMap(��������� ��������� ���������� �������� �� x, y � pos)
			//����� ������� ������ SetPposition(xBeg, yBeg)
			for (int i = 0; i < diffLvl; i++) {
				//������ ��� �������, ����� pressedPosition
				if(i != pressedPosition)
					window.draw(mapGame[i].spr);
			}

			//������ ��������������� ������ Drug and drop
			mapGame[pressedPosition].spr.setPosition(mapGame[pressedPosition].xBeg - x + pos.x, //x
												     mapGame[pressedPosition].yBeg - y + pos.y); // y
			window.draw(mapGame[pressedPosition].spr);

			window.display();
		}
		//��������� ���� ���������� ����� 
		int EndPos = -1;
		try {

			//���� ����� c������ �� ������� ������
			for (int i = 0; i < diffLvl; i++) {
				if ((mapGame[i].xBeg < xEndState) && (mapGame[i].yBeg < yEndState) && (mapGame[i].xEn > xEndState) && (mapGame[i].yEn > yEndState)) {
					EndPos = i;//��������� ������� ������ �� ������� ������ 
					break;
				}
			}
			if (EndPos == -1)//���-�� ����� �� ���, ��� �� ���� �� ������� ������������ � �������� ���� ����
				throw EndPos;
		}
		catch (int pp) {
			return 0;
		}

		//������ ������� ������� ������, �����, � �������
		mapGame[EndPos].swap(mapGame[pressedPosition]);

		if (isWin(window)) 
			return 1;
		
		
		return 0;
	}


	return 0;
	
}

bool ViewControllerGame::isWin(RenderWindow &window)
{
	for (int i = 0; i < diffLvl; i++) {
		if (mapGame[i].position != i)
			return false;
	}

	window.clear();
	getView(window);
	window.display();

	//����� �������� "�� ��������"
	
	sleep(seconds(2));
	window.clear();
	getView(window);
	
	Texture wT;
	wT.loadFromFile("win.png");

	Sprite win;
	win.setTexture(wT);
	win.setPosition(402, 269);
	window.draw(win);
	window.display();

	sleep(seconds(3));
	//����������� � ����
	return true;
}
