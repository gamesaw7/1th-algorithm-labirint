#pragma once
#include "Source\Drawler.h"
#include <iostream>

struct sirc
{
	float x;
	float y;
	float r;
};


struct point
{
	float x, y;//configuration
	int numParP;//number of parent points (links)
	std::vector<int> numChildP;//numers of child points (links)
};

class RRT
{
private:
	point* _points;
	int counter;
	bool goodtry(float x1, float y1, float x2, float y2, sirc s);
	bool checkOBS(float x1, float y1, sirc s);
	void drawAllForPoint(sf::RenderWindow &window, int num);
	void drawWayToTarget(sf::RenderWindow &window, int num);
	bool foundTar = false;
	sirc _tar;
public:
	RRT(float rootX, float rootY, float step);
	~RRT();
	int getCounter();
	int getLastNum();
	void setTar(sirc tar);
	float _step;
	void rrtIteration(sirc s);
	void addPoint(int parent, float px, float py);
	void setNewTree(float rootX, float rootY, float step);
	void draw(sf::RenderWindow &window);
	
};

