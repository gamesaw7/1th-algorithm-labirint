#include "RRT.h"
#include <algorithm>
#include <iostream>
#include <Box2D.h>

#define NEWPOINT _points[parentNum].x - dx, _points[parentNum].y - dy
#define OLDPOINT _points[parentNum].x, _points[parentNum].y

RRT::RRT(float rootX, float rootY, float step)
{
	setNewTree(rootX, rootY, step);
}


RRT::~RRT()
{
}

int RRT::getCounter()
{
	return counter;
}

int RRT::getLastNum()
{
	return counter - 1;
}

void RRT::setTar(sirc tar)
{
	_tar = tar;
}


void RRT::rrtIteration(sirc s)
{
	if (!foundTar)
	{
		float maxX = 1920;
		float maxY = 1080;
		float minX = 0;
		float minY = 0;
		//random point
		float randX = minX + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / (maxX - minX)));
		float randY = minY + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / (maxY - minY)));
		//init iteration
		int parentNum = 0;
		float lenToParent = maxX - minX + maxY - minY;
		//check for the closest
		for (int i = 0; i < counter + 1; i++)
		{
			float dx = _points[i].x - randX;
			float dy = _points[i].y - randY;
			float len = sqrtf(dx*dx + dy*dy);
			if (len < lenToParent)
			{
				parentNum = i;
				lenToParent = len;
			}
		}
		//result adding of a point
		float dx = _points[parentNum].x - randX;
		float dy = _points[parentNum].y - randY;
		lenToParent = sqrtf(dx*dx + dy*dy);
		float k = _step / lenToParent;
		if (k < 1 && k > 0)
		{
			dx *= k;
			dy *= k;
		}
		if (goodtry(OLDPOINT, NEWPOINT, s))addPoint(parentNum, NEWPOINT);
		else rrtIteration(s);
	}
}

bool RRT::goodtry(float x1, float y1, float x2, float y2, sirc s)
{
	float step = 2;
	float dx = x1 - x2;
	float dy = y1 - y2;
	float len = sqrtf(dx*dx + dy*dy);
	int k = len / step;
	if (k > 2)
	{
		for (int i = 0; i < k; i++)
			if (checkOBS(x1 - dx*i / k, y2 - dy*i / k, s))return false;
		if (checkOBS(x2, y2, s))return false;
	}
	else
	{
		if (checkOBS(x2, y2, s))return false;
		if (checkOBS(x1, y1, s))return false;
	}
	return true;
}
bool RRT::checkOBS(float x1, float y1, sirc s)
{
	float len = sqrtf((x1 - s.x)*(x1 - s.x) + (y1 - s.y)*(y1 - s.y));
	if (len < s.r) return true;
	else return false;
}

void RRT::addPoint(int parent, float px, float py)
{
	if (!foundTar)
	{
		counter++;
		//change array size
		point *npoints = new point[counter + 1];
		for (int i = 0; i < counter; i++)
			npoints[i] = _points[i];
		_points = npoints;
		//now write last point
		_points[counter].numParP = parent;
		_points[counter].x = px;
		_points[counter].y = py;
		//add new point as child of another point
		_points[parent].numChildP.push_back(counter);

		if (checkOBS(px, py, _tar))
		{
			foundTar = true;
			counter++;
			parent = counter;
			px = _tar.x;
			py = _tar.y;
			npoints = new point[counter + 1];
			for (int i = 0; i < counter; i++)
				npoints[i] = _points[i];
			_points = npoints;
			//now write last point
			_points[counter].numParP = parent;
			_points[counter].x = px;
			_points[counter].y = py;
			//add new point as child of another point
			_points[parent].numChildP.push_back(counter);
		}


	}
}

void RRT::setNewTree(float rootX, float rootY, float step)
{
	_step = step;
	counter = 0;
	_points = new point[counter + 1];
	_points[counter].numParP = -1;
	_points[counter].x = rootX;
	_points[counter].y = rootY;
}

void RRT::draw(sf::RenderWindow &window)
{
	if (counter > 1)
	{
		drawAllForPoint(window, 0);
	}
	if (foundTar)
	{
		drawWayToTarget(window, getLastNum());
	}
}

void RRT::drawAllForPoint(sf::RenderWindow & window, int num)
{
	sf::Vertex* line;
	for each (int nchild in _points[num].numChildP)
	{
		line = new sf::Vertex[2];
		line[0] = sf::Vertex(sf::Vector2f(_points[num].x, _points[num].y), sf::Color::Black);
		line[1] = sf::Vertex(sf::Vector2f(_points[nchild].x, _points[nchild].y), sf::Color::Black);
		window.draw(line, 2, sf::Lines);
		drawAllForPoint(window, nchild);
	}

}

void RRT::drawWayToTarget(sf::RenderWindow & window, int num)
{
	sf::Vertex* line;
	int parent = _points[num].numParP;
	if (parent != -1)
	{
		line = new sf::Vertex[2];
		line[0] = sf::Vertex(sf::Vector2f(_points[num].x, _points[num].y), sf::Color::Red);
		line[1] = sf::Vertex(sf::Vector2f(_points[parent].x, _points[parent].y), sf::Color::Red);
		window.draw(line, 2, sf::Lines);
		drawWayToTarget(window, parent);
	}
}
