#include "mouse.h"



mouse::mouse(sf::RenderWindow &w, mouseStater &ms) : window(w), MS(ms)
{
}


mouse::~mouse()
{
}

void mouse::mouseFunk()
{
	MS.x = (float)sf::Mouse::getPosition().x;
	MS.y = (float)sf::Mouse::getPosition().y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		MS.lbDown = true;
	else MS.lbDown = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		MS.rbDown = true;
	else MS.rbDown = false;
}