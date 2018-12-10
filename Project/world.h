#pragma once
#include <SFML/Graphics.hpp>
#include "mouse.h"
#include "Source/Drawler.h"

class world
{
private:
	int **_map;//0 - nothing / 1 - lab / 2 - base / 
	int _x, _y;
	float _delX, _delY;


public:
	world();
	~world();
	//sf::RenderWindow &window;
	texter T;

	bool isDown(int x, int y);
	bool isUp(int x, int y);
	bool isLeft(int x, int y);
	bool isRight(int x, int y);

	int getX();
	int getY();

	void setValue(int x, int y, int value);
	void initMap(int x, int y, sf::RenderWindow &window);
	void resizeMap(int delX, int delY, sf::RenderWindow &window);
	void update(mouseStater ms, int set);
	void save(std::string filename);
	void download(std::string filename, sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	sf::Vector2f whereAmI(float x, float y);//номер €чейки, при глобальных координатах
	sf::Vector2f whereAmIinPixels(float worldX, float worldY);
	int whatAmIInPixels(float x, float y);//значение в €чейке
	int whatAmI(int x, int y);

};

