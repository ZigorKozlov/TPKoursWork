#include "GamePazzle.h"

GamePazzle::~GamePazzle()
{
	delete viewController[menu];

	if (viewController[game] != nullptr)
		delete viewController[game];
}

int GamePazzle::startGame()
{
	bool flag = menu;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
				
			//Выполнение одного из controller
			switch (event.type) {

			case Event::Closed:
				window.close();
				std::cout << "exit" << std::endl;
				break;

			case Event::MouseButtonPressed://Нажатие кнопки мыши

				//if (event.mouseButton.button = Mouse::Left) {
				if (event.key.code == Mouse::Left)// В игре используется только левая кнопка мыши
				{
					if (viewController[flag]->controller(window, event.mouseButton.x, event.mouseButton.y)) {


						//=> началась игра (картинка выбрана, сложность выбрана и нажата кнопка старт)
						if (viewController[game] == nullptr) {
							flag = game;
							viewController[game] = new ViewControllerGame(viewController[menu]->getNumImage(), viewController[menu]->getDiffLvl());

						}
						else//Выход из игры в меню
						{

							delete viewController[game];
							viewController[game] = nullptr;
							flag = menu;
						}
					}
				}
				
			
				break;

			default: break;
			}

		}
		
		window.clear();

		//Выполнение одного из View
		viewController[flag]->getView(window);
		
		window.display();
	}

	return 0;
}

