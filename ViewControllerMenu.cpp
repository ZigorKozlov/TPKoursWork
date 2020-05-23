#include "ViewControllerMenu.h"

ViewControllerMenu::ViewControllerMenu()
{

	Image Im_I;//image для загрузки туда текстур и получения спрайтов

	Im_I.loadFromFile("Fon.jpg");
	//Спрайт фона
	T5.loadFromImage(Im_I);

	Fon.setTexture(T5);
	Fon.setPosition(0, 0);
	
	//1
	int count = 0;

	Im_I.loadFromFile("Image1.jpg");

	if (T1.loadFromImage(Im_I)) {//Если картинка загружена пользователем в папку проекта

		Image1.setTexture(T1);

		changeScale(Image1, 271, 386);// Подгоняем размеры (соотношение расширения не искажается)
		Image1.setPosition(9, 135);// устанавливаем Спрайт на нужную нам позицию
		count++;
	}
	else {
		std::cout << "Файл Image1 не найден" << std::endl;
	}

	//картинка2
	Im_I.loadFromFile("Image2.jpg");

	if (T2.loadFromImage(Im_I)) {//Если картинка загружена пользователем в папку проекта

		Image2.setTexture(T2);

		changeScale(Image2, 271, 377);// Подгоняем размеры (соотношение расширения не искажается)
		Image2.setPosition(397, 135);// устанавливаем Спрайт на нужную нам позиц
		count++; 
	}
	else {
		std::cout << "Файл Image2 не найден" << std::endl;
	}

	//3
	Im_I.loadFromFile("Image3.jpg");

	if (T3.loadFromImage(Im_I)) {//Если картинка загружена пользователем в папку проекта

		Image3.setTexture(T3);

		changeScale(Image3, 299, 386);// Подгоняем размеры (соотношение расширения не искажается)
		Image3.setPosition(9, 408);// устанавливаем Спрайт на нужную нам позицию
		count++;
	}
	else {
		std::cout << "Файл Image3 не найден" << std::endl;
	}


	//4
	Im_I.loadFromFile("Image4.jpg");

	if (T4.loadFromImage(Im_I)) {//Если картинка загружена пользователем в папку проекта

		Image4.setTexture(T4);

		changeScale(Image4, 299, 377);// Подгоняем размеры (соотношение расширения не искажается)
		Image4.setPosition(397, 408);// устанавливаем Спрайт на нужную нам позицию
		count++;
	}
	else {
		std::cout << "Файл Image4 не найден" << std::endl;
	}

	if (count == 0)
	{
		std::cout << "Ошибка, не загружена ни одна картинка, проверте в папке игры(формат картинок д.б. jpg). Закрытие игры." << std::endl;
		exit(0);
	}

	//For controller 

	BattonExit1 = new Button(9,   7,   69,   67);
	BattonExit2 = new Button(70,  24,  177,  51);
	BattonStart = new Button(977, 24,  1312, 73);
	BattonIm1   = new Button(9,   135, 395,  406);
	BattonIm2   = new Button(397, 135, 774,  406);
	BattonIm3   = new Button(9,   409, 395,  706);
	BattonIm4   = new Button(397, 408, 774,  706);
	BattonR9    = new Button(815, 150, 1175, 214);
	BattonR16   = new Button(815, 280, 1175, 345);
	BattonR25   = new Button(815, 409, 1175, 473);
	BattonR36   = new Button(815, 540, 1175, 604);

	numImage = diffLvl = none;
}

ViewControllerMenu::~ViewControllerMenu()
{
	delete BattonExit1;
	delete BattonExit2;
	delete BattonStart;
	delete BattonIm1;
	delete BattonIm2;
	delete BattonIm3;
	delete BattonIm4;
	delete BattonR9;
	delete BattonR16;
	delete BattonR25;
	delete BattonR36;
}

int ViewControllerMenu::controller(RenderWindow & window, int x, int y)
{
	if ((BattonExit1->isPress(window, x, y)) || (BattonExit2->isPress(window, x, y))) {
		window.close();
		return 0;
	}


	if (BattonStart->isPress(window, x, y)) {
		if ((numImage == none) || (diffLvl == none)) {

			Image Im_I;

			Im_I.loadFromFile("er.png");
			
			Texture T;
			T.loadFromImage(Im_I);

			Sprite er;
			er.setTexture(T);
			er.setPosition(402, 269);
			window.draw(er);
			window.display();
			sleep(seconds(3));
			return 0;
		}
		return 1;
	}

	if (BattonIm1->isPress(window, x, y)) {
		numImage = Im1;
		return 0;
	}

	if (BattonIm2->isPress(window, x, y)) {
		numImage = Im2;
		return 0;
	}

	if (BattonIm3->isPress(window, x, y)) {
		numImage = Im3;
		return 0;
	}

	if (BattonIm4->isPress(window, x, y)) {
		numImage = Im4;
		return 0;
	}

	if (BattonR9->isPress(window, x, y)) {
		diffLvl = 9;
		return 0;
	}

	if (BattonR16->isPress(window, x, y)) {
		diffLvl = 16;
		return 0;
	}

	if (BattonR25->isPress(window, x, y)) {
		diffLvl = 25;
		return 0;
	}

	if (BattonR36->isPress(window, x, y)) {
		diffLvl = 36;
		return 0;
	}

}

void ViewControllerMenu::getView(RenderWindow & window)
{
	window.draw(Fon);
	window.draw(Image1);
	window.draw(Image2);
	window.draw(Image3);
	window.draw(Image4);
}
