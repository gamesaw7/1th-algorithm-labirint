#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Source/Drawler.h"
#include "Source/TwodObj.h"
#include "keyboard.h"
#include "mouse.h"
#include "world.h"
#include "robot.h"
#include "RRT.h"
#include <Box2D.h>
#include "task.h"

using namespace std;


#define myWindow 1920,1080
#define mouseInWindow M.MS.x > window.getPosition().x - 15 && M.MS.x<window.getPosition().x + window.getSize().x + 15 && M.MS.y > window.getPosition().y - 15 && M.MS.y < window.getPosition().y + window.getSize().y + 15
#define SLIP sf::sleep(sf::milliseconds(50));



//sf::VideoMode(1600, 900), "Window"
//sf::VideoMode(SM_CXSCREEN, SM_CYSCREEN), "Window", sf::Style::Fullscreen
sf::RenderWindow window(sf::VideoMode(1900, 1000), "Window");
bool closeApp = false;
keyboard K(window);
mouseStater MS;
mouse M(window, MS);
int mouseSet = 1;//1 - lab / 2 - base


texter T;
Drawler dr(window);
TwodObj ob;//object of mouse
world myMap;
task MyTask;

sirc s;
sf::CircleShape circle1;
sirc tar;
sf::CircleShape circle2;








//box2d
//b2World* Box2dworld;
/*
b2Body* addRect(int x, int y, int w, int h, bool dyn = true)
{
	b2BodyDef bodydef;
	bodydef.position.Set(x, y);
	if (dyn)
		bodydef.type = b2_dynamicBody;
	b2Body* body = Box2dworld->CreateBody(&bodydef);

	b2PolygonShape shape;
	shape.SetAsBox(w, h);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1.0;
	body->CreateFixture(&fixturedef);
}
*/

void UPDATOR()
{
	while (window.isOpen())
	{
		if (mouseInWindow)
		{
			if (MS.lbDown)
			{
				ob.rot(1);
			}
			if (MS.rbDown)
			{
				ob.rot(-1);
			}
			ob.setCoord(MS.x, MS.y);
		}
		myMap.update(MS, mouseSet);
		if (K.simulation)
		{
			/////////////////////////////////////////////////
			//simulation works



			///////////////////////////////////////////////////
		}
		sf::sleep(sf::milliseconds(10));
	}
}

void KEYBOARD_FUNK()
{
	while (window.isOpen())
	{
		K.keyboardFUNK();
		sf::sleep(sf::milliseconds(20));
	}
}

void MOUSE_FUNK()
{
	while (window.isOpen())
	{
		M.mouseFunk();
		sf::sleep(sf::milliseconds(20));
	}
}

void comfort_starting()
{
	//taskbar icon

	//icon
	sf::Image im;
	im.loadFromFile("textures/def/defsmall.png");
	window.setIcon(im.getSize().x, im.getSize().y, im.getPixelsPtr());
	window.setTitle("Labirint. Authors - A. Bulatov, A. Vorontsov");
	//set window position
	sf::Vector2i v;
	v.x = -10;
	v.y = 0;
	window.setPosition(v);
	//some starting funcs
	//FreeConsole();//off console 
	srand(time(0));//rand starter
	dr.loadTextures_F("Data/texture_list_1.dat", T);//download texture list
	//mouse set
	window.setMouseCursorVisible(false);
	ob.setPic("mouse_1", dr);//mouse_1
	ob.setCoord(500, 500);
	ob.initWH(80, 80);
	//box2d
	/*
	Box2dworld = new b2World(b2Vec2(0.0, 0.0));

	b2Vec2 vertices[5];
	vertices[0].Set(-1, 2);
	vertices[1].Set(-1, 0);
	vertices[2].Set(0, -3);
	vertices[3].Set(1, 0);
	vertices[4].Set(1, 1);

	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 5); //pass array to the shape

		*/

	s.r = 200;
	s.x = 800;
	s.y = 500;
	circle1.setRadius(s.r);
	circle1.setOutlineColor(sf::Color::Red);
	circle1.setFillColor(sf::Color::Red);
	circle1.setPosition(s.x - s.r, s.y - s.r);
	
	tar.r = 50;
	tar.x = 1100;
	tar.y = 700;
	circle2.setRadius(tar.r);
	circle2.setOutlineColor(sf::Color::Green);
	circle2.setFillColor(sf::Color::Green);
	circle2.setPosition(tar.x - tar.r, tar.y - tar.r);
	



	
	
}






int main(void)
{
	comfort_starting();


	task ttt;
	ttt.add(3, 4);
	ttt.add(5, 7);
	int xxxx = ttt.top()._x;
	cout << xxxx;




	myMap.initMap(20, 20, window);

	//multithread
	sf::Thread threadK(&KEYBOARD_FUNK);
	threadK.launch();
	sf::Thread threadM(&MOUSE_FUNK);
	threadM.launch();
	sf::Thread thread(&UPDATOR);
	thread.launch();

	robot a;
	myMap.download("Saves/saveSlot5.dat", window);// загружаем нужную дл€ теста карту (красные =2 / зеленые =1)
	a.init(14, 0, myMap, window, dr);
	a.initTaskRobot(myMap, MyTask);// Ќулева€ нода в графе задач
	/////////////////////////////////////////////////////////////////////////////////
	/*for (int i = 0; i < 150; i++) {
		a.Going(myMap);
	}*/
	/////////////////////////////////////////////////////////////////////////////////
	//a.setTarget(2, 15);
	a.setSpeed(15);
	
	




	RRT rr(a.curX, a.curY, 100);

	rr.setTar(tar);

	while (window.isOpen())
	{
		//a.Going(myMap,MyTask);
		a.FindTask(myMap, MyTask,dr,window);
		/*a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget();
		a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget();
		a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget();
		a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget(); a.goToTarget();*/
#pragma region events
		if (K.saveSlot1)
		{
			myMap.save("Saves/saveSlot1.dat"); SLIP
		}
		if (K.downSlot1)
		{
			myMap.download("Saves/saveSlot1.dat", window); SLIP
		}
		if (K.saveSlot2)
		{
			myMap.save("Saves/saveSlot2.dat"); SLIP
		}
		if (K.downSlot2)
		{
			myMap.download("Saves/saveSlot2.dat", window); SLIP
		}
		if (K.saveSlot3)
		{
			myMap.save("Saves/saveSlot3.dat"); SLIP
		}
		if (K.downSlot3)
		{
			myMap.download("Saves/saveSlot3.dat", window); SLIP
		}
		if (K.saveSlot4)
		{
			myMap.save("Saves/saveSlot4.dat"); SLIP
		}
		if (K.downSlot4)
		{
			myMap.download("Saves/saveSlot4.dat", window); SLIP
		}
		if (K.saveSlot5)
		{
			myMap.save("Saves/saveSlot5.dat"); SLIP
		}
		if (K.downSlot5)
		{
			myMap.download("Saves/saveSlot5.dat", window); SLIP
		}
		if (K.saveSlot6)
		{
			myMap.save("Saves/saveSlot6.dat"); SLIP
		}
		if (K.downSlot6)
		{
			myMap.download("Saves/saveSlot6.dat", window); SLIP
		}
		if (K.saveSlot7)
		{
			myMap.save("Saves/saveSlot7.dat"); SLIP
		}
		if (K.downSlot7)
		{
			myMap.download("Saves/saveSlot7.dat", window); SLIP
		}
		if (K.saveSlot8)
		{
			myMap.save("Saves/saveSlot8.dat"); SLIP
		}
		if (K.downSlot8)
		{
			myMap.download("Saves/saveSlot8.dat", window);  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		if (K.saveSlot9)
		{
			myMap.save("Saves/saveSlot9.dat"); SLIP
		}
		if (K.downSlot9)
		{
			myMap.download("Saves/saveSlot9.dat", window); SLIP
		}
		if (K.plusX)
		{
			myMap.resizeMap(1, 0, window); SLIP
		}
		if (K.plusY)
		{
			myMap.resizeMap(0, 1, window); SLIP
		}
		if (K.minusX)
		{
			myMap.resizeMap(-1, 0, window); SLIP
		}
		if (K.minusY)
		{
			myMap.resizeMap(0, -1, window); SLIP
		}
		if (K.mouseBase)
		{
			ob.setPic("button_1", dr);
			ob.setCoord(500, 500);
			ob.initWH(80, 80);
			mouseSet = 2;
			SLIP
		}
		if (K.mouseLab)
		{
			mouseSet = 1;
			ob.setPic("mouse_1", dr);
			ob.setCoord(500, 500);
			ob.initWH(80, 80); SLIP
		}



#pragma endregion
				
		//a.goToTarget();

		//rr.rrtIteration(s);
		//a.update(myMap);
		window.clear(sf::Color::White);
		myMap.draw(window);
		//window.draw(circle1);
		//window.draw(circle2);
		ob.draw(dr);
		a.draw(dr, window);
		//rr.draw(window);
		window.display();
		sf::sleep(sf::milliseconds(33));
	}
	//thread.wait();
	return 0;
}