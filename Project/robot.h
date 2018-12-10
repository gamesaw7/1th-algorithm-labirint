#pragma once
#include <SFML/Graphics.hpp>
#include "Source\TwodObj.h"
#include "Source\Drawler.h"
#include "world.h"
#include "task.h"


class robot
{
protected:
	TwodObj _avatar;
	world _world;
	float _speed;
	sf::Vector2f tar;
	task myTask;

	pointTask last;
	//task prevx, prevy;
	pointTask prevx, prevy,prevPoint;



	int curXWorld, curYWorld;//in world
	int curXWorldOld, curYWorldOld;//in world (old)
public:
	float curX, curY;// in pixels
	float tarX = -1;//in pixels
	float tarY = -1;//in pixels
	robot();
	~robot();
	void setSpeed(float sp);
	void init(int startXWorld, int startYWorld, world &w, sf::RenderWindow &window, Drawler &dr);
	void addPoint(int worldX, int worldY, int status);
	void askWorld(world &w);//
	void Going(world &w,task &t);//
	void FindTask(world &w, task&t,Drawler &d, sf::RenderWindow &window);//
	void addTaskToStack(world &w, task &t,string *s,int i);//
	void chooseTaskAndGovoid(world &w, task &t, taskStack task);//
	void robot::initTaskRobot(world &w, task &t);//
	bool CheckPrev(task &t);//
	void goToTarget();
	void setTarget(int worldX, int worldY);
	void update(world &w);
	void draw(Drawler &dr, sf::RenderWindow &window);
};

