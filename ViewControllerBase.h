#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class ViewControllerBase {

protected:
	int numImage;// номер текущей выбраной картинки
	int diffLvl;// уровень сложности 

public:
	//ViewControllerBase() = default;
	//ViewControllerBase(const ViewControllerBase &) = default;
	virtual ~ViewControllerBase() = default;

	virtual void getView(RenderWindow &window) = 0;
	virtual int controller(RenderWindow &window, int x, int y) = 0;

	int getNumImage() { return numImage; };
	int getDiffLvl()  { return diffLvl;  };
	void setnumImage(int num) { numImage = num; };
	void setDiffLvl(int dif) { diffLvl = dif; };

	void changeScale(Sprite &spr, float height, float width) {
		//void changeScale(Sprite &spr, int height, wight)// нужные высота и ширина (1366, 768)

		auto a = spr.getGlobalBounds();
		float b = a.height, c = a.width;
		if ((b > height) || (c > width)) {
			float scale = ((height / b) < (width / c)) ? (height / b) : (width / c);
			spr.scale(scale, scale);
			a = spr.getGlobalBounds();
			b = a.height, c = a.width;
		}
		else {
			if ((b < height) || (c < width)) {
				float scale = ((height / b) < (width / c)) ? (height / b) : (width / c);
				spr.setScale(scale, scale);
			}
		}
	};
};
