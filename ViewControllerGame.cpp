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
		std::cout << "Ошибка, не выбрана картинка закрытие игры." << std::endl;
		exit(0);
	}

	length = sqrt(diff);

	// Выбор картинки из данных меню + Загрузка Фона
	try {


		Image Im_I;

		if (Im_I.loadFromFile("FonGame.jpg") != false) {
			tFon.loadFromImage(Im_I);

			Fon.setTexture(tFon);
			Fon.setPosition(0, 0);
		}
		else {
			std::cout << "Ошибка загрузки фона игры, фона игры не будет, рекомендуетя перезапустить игру" << std::endl;
		}

		//Выбор картинки для игры, исзодя из данных из меню
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
	catch (int numImage) { // Данной ошибки быть не должно, но всё же, на всякий случай
		std::cout << "Ошибка, не выбрана картинка или она вообще не загружена, проверте в папке игры(формат картинок д.б. jpg). Закрытие игры."<<std::endl;
		exit(0);
	}
	
	//Вычисление размеров игрового поля, в зависимости от картинки что бы не искажать соотношение
	//строн картинки .Размеры игрового поля примерно  1300х700
	try {
		//y
		height = int(700 / length) * length;

		//x
		width = int(1300 / length) * length;// что бы избавиться от дробей при делении

		//Вычисление размеров игрового поля:
		Sprite tmpSpr;
		tmpSpr.setTexture(tGame);

		Theight = tmpSpr.getGlobalBounds().height;//получаем истиные высоту и ширину текстуры
		Twidth = tmpSpr.getGlobalBounds().width;
		if ((Theight < 100) || (Twidth < 100))
			throw Theight;

		changeScale(tmpSpr, height, width);//Деформируем картинку под размер поля 

		// смотрим истиное значение игрового поля
		height = (int)tmpSpr.getGlobalBounds().height;
		width = (int)tmpSpr.getGlobalBounds().width;

		height = int(height / length) *length;
		width = int(width / length) *length;

		
	}
	catch (int th) {
		std::cout << "Внимание, качество картинки будет плохом, так как у неё слишком низкое разрешение." << std::endl;
	}
	//Ширина и высота 1 пазла на игровом поле
	Sheight = height / length;
	Swidth = width / length;


	//Размеры игрового поля заданы
	mapGame = new GameSprite[diff];//Создаём массив из dif(9||16||25||36) спрайтов
	
	//начальная инициализация позиций
	for (int i = 0; i < diff; i++) {
		mapGame[i].position = diff - i - 1;
	}
	
	srand(time(NULL));
	//В случайном порядке перемешиваем спрайты
	for (int i = 0; i < 1000; i++) {

		int a = rand() % (diff);
		int b = rand() % (diff);
		int tmp = 0;

		//swap
		tmp = mapGame[a].position;
		mapGame[a].position = mapGame[b].position;
		mapGame[b].position = tmp;
	
	}


	//инициализация x, y, и spr(Sprite)
	for (int i = 0; i < diff; i++) {
		mapGame[i].xPos = mapGame[i].position % length; //Расставление позиций в мозайке в зависимости от рандомного распределения по строкам
		mapGame[i].yPos = mapGame[i].position / length;//по стобцами

		//вычисление координат начала и конца спрайта относительно глобальной системы координат - (0,0) на экране
		mapGame[i].xBeg = mapGame[i].xPos *Swidth;
		mapGame[i].yBeg = mapGame[i].yPos *Sheight;

		mapGame[i].xEn = (mapGame[i].xPos + 1)  * Swidth  - 1;
		mapGame[i].yEn = (mapGame[i].yPos + 1 ) * Sheight - 1;

		//Загружаем необходимый спрайт, устанавливаем размер(вырезая из текстуры) и устанавливаем точку начало спрайта
		mapGame[i].spr.setTexture(tGame);

		//-------------------------------------------------------------------------------------------------------------------------------------
		//                                    |x начала спрайта |y начала спрайта  | ширина | высота|
		mapGame[i].spr.setTextureRect(IntRect((i % length) * (Twidth/ length), (i / length) * (Theight/ length), (Twidth / length), (Theight / length)));//0 элемент массива - 0,0 куосчк мозайки, 1 - 0,1 и т.д
		changeScale(mapGame[i].spr, Sheight, Swidth);
		mapGame[i].spr.setPosition(mapGame[i].xBeg, mapGame[i].yBeg);//Но истиная позиция на игровом поле задана position
	}

	//СОздание заднего фона игрового поля
	BackFon = new RectangleShape(Vector2f(width+5, height+5));
	BackFon->setFillColor(Color::Black);


	//Controller
	BMenu = new Button(0, 705, 475, 759);//Кнопка выхода в меню
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
	window.draw(Fon);//Рисуем фон
	//Рисуем Задний фон игрового пространства
	window.draw(*BackFon);

	
	//Написать функцию GetviewMap(Вычисляет изменённые координаты спрайтов по x, y и pos)
	//Ножно сделать только SetPposition(xBeg, yBeg)
	for (int i = 0; i < diffLvl; i++) {
		window.draw(mapGame[i].spr);
	}

}

int ViewControllerGame::controller(RenderWindow & window, int x, int y)
{
	 
	//Кнопка меню
	if (BMenu->isPress(window, x, y)) {
		return 1;//Возвращаем 1, выходим в меню
	}

	//Перемещение элементов мозайки сборка()

	//Если нажато на игровом поле, иначе обработка бессмысленна
	if (x < width, y < height) {
		//Нажатие было на игровом поле

		bool isReleased = false;
		int xEndState;
		int yEndState;
		int pressedPosition = -1;

	
		try {

			//Ищем номер cпрайта на который нажали
			for (int i = 0; i < diffLvl; i++) {
				if ((mapGame[i].xBeg < x) && (mapGame[i].yBeg < y) && (mapGame[i].xEn > x) && (mapGame[i].yEn > y)) {
					pressedPosition = i;//Вычислили элемент мозаки на который нажали 
					break;
				}
			}
			if (pressedPosition == -1)//Что-то пошло не так, что бы игра не зависла позвращаемся в основной цикл игры
				throw pressedPosition;
		}
		catch (int pp) {
			return 0;
		}
		//

		while (window.isOpen()) {

			//считываем координаты мышки
			
			Vector2i pixelPos = Mouse::getPosition(window);//забираем координаты курсора
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			Event event;

			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
					std::cout << "exit" << std::endl;
				}

				if (event.type == Event::MouseButtonReleased) {//Если кнопка отжата

					if (event.key.code == Mouse::Left) {// В игре используется только левая кнопка мыши
						//Почучаем x, y конечного состояния мыши
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
			//Вывод данных, 
			window.clear();

			window.draw(Fon);//Рисуем фон
			//Рисуем Задний фон игрового пространства
			window.draw(*BackFon);


			//Написать функцию GetviewMap(Вычисляет изменённые координаты спрайтов по x, y и pos)
			//Ножно сделать только SetPposition(xBeg, yBeg)
			for (int i = 0; i < diffLvl; i++) {
				//Рисуем все спрайты, кроме pressedPosition
				if(i != pressedPosition)
					window.draw(mapGame[i].spr);
			}

			//Рисуем перетаскиваемый спрайт Drug and drop
			mapGame[pressedPosition].spr.setPosition(mapGame[pressedPosition].xBeg - x + pos.x, //x
												     mapGame[pressedPosition].yBeg - y + pos.y); // y
			window.draw(mapGame[pressedPosition].spr);

			window.display();
		}
		//Вычисляем куда перетащили обект 
		int EndPos = -1;
		try {

			//Ищем номер cпрайта на который нажали
			for (int i = 0; i < diffLvl; i++) {
				if ((mapGame[i].xBeg < xEndState) && (mapGame[i].yBeg < yEndState) && (mapGame[i].xEn > xEndState) && (mapGame[i].yEn > yEndState)) {
					EndPos = i;//Вычислили элемент мозаки на который нажали 
					break;
				}
			}
			if (EndPos == -1)//Что-то пошло не так, что бы игра не зависла позвращаемся в основной цикл игры
				throw EndPos;
		}
		catch (int pp) {
			return 0;
		}

		//Меняем местами Спрайты НАчало, конец, и позицию
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

	//Вывод картинки "Вы выйграли"
	
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
	//Возвращение в меню
	return true;
}
