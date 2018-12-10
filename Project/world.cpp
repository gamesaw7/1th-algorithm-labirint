#include "world.h"
#include <sstream>
#define inTheMatrix xx >= 0 && xx < _x&&yy >= 0 && yy < _y


world::world()
{
}


world::~world()
{
}

bool world::isDown(int x, int y)
{
	int curX = x;
	int curY = y;
	if (x >= 0 && y >= 0 && x < _x && (y+1) < _y)//if (x >= 0 && y-1 >= 0 && x < _x && y < _y)
	{
		if (_map[curX][curY + 1] ==0 )return true;
	}
	return false;

	//return false;
}

bool world::isUp(int x, int y)
{
	int curX = x;
	int curY = y;
	if (x >= 0 && y >= 0 && x < _x && (y-1 )< _y)//if (x >= 0 && y >= 0 && x < _x && y+1 < _y)
	{
		if(_map[curX][curY - 1] ==0)return true;
	}
	return false;
}

bool world::isLeft(int x, int y)
{
	
	int curX = x;
	int curY = y;
	if ((x-1 ) >= 0 && y >= 0 && x < _x && y < _y)//if (x -1 >= 0 && y >= 0 && x < _x && y < _y)
	{
		if (_map[curX-1][curY] ==0)return true;
	}
	return false;
}

bool world::isRight(int x, int y)
{
	int curX = x;
	int curY = y;
	if ((x +1)>= 0 && y >= 0 && (x+1) < _x && y < _y)//	if (x >= 0 && y >= 0 && x + 1 < _x && y < _y)
	{
		if (_map[curX + 1][curY] ==0)return true;
	}
	return false;
}

int world::getX()
{
	return _x;
}

int world::getY()
{
	return _y;
}

void world::setValue(int x, int y, int value)
{
	if (x >= 0 && y >= 0 && x < _x && y < _y)
	{
		_map[x][y] = value;
	}
}

void world::initMap(int x, int y, sf::RenderWindow &window)
{
	_x = x;
	_y = y;
	_map = new int*[x];
	for (int i = 0; i < x; i++)
	{
		_map[i] = new int[y];
	}
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			_map[i][j] = 0;
	_delX = window.getSize().x / _x;
	_delY = window.getSize().y / _y;
}

void world::resizeMap(int delX, int delY, sf::RenderWindow &window)
{
	int oldX = _x;
	int oldY = _y;
	int ** oldMap = _map;
	_x += delX;
	_y += delY;
	if (_x <= 0)_x = 1;
	if (_y <= 0)_y = 1;
	initMap(_x, _y, window);
	for (int i = 0; i < _x && i < oldX; i++)
		for (int j = 0; j < _y && j < oldY; j++)
			_map[i][j] = oldMap[i][j];
}

void world::update(mouseStater ms, int set)
{
	if (ms.lbDown)
	{
		int xx = ms.x / _delX;//nomer yacheiki
		int yy = ms.y / _delY;
		if (inTheMatrix)
			if (_map[xx][yy] != set) _map[xx][yy] = set;// part of labirint
	}
	if (ms.rbDown)
	{
		int xx = ms.x / _delX;//nomer yacheiki
		int yy = ms.y / _delY;
		if (inTheMatrix)
			if (_map[xx][yy] != 0) _map[xx][yy] = 0;// part of labirint
	}

}

std::string intToString(int a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
}

void world::save(std::string filename)
{
	std::string save_string;
	save_string = intToString(_y);
	save_string += "\n";
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++)
		{
			save_string += intToString(_map[i][j]);
			save_string += " ";
		}
		save_string += "\n";
	}
	T.uploadToFile(filename, save_string);
}

void world::download(std::string filename, sf::RenderWindow &window)
{
	std::vector<std::string> dwnV = T.downloadFromFile_VA(filename);
	for (int i = 0; i < _x; i++)
	{
		delete _map[i];
	}
	delete _map;
	_y = atoi(dwnV[0].c_str());
	_x = dwnV.size() / _y;
	initMap(_x, _y, window);
	int z = 1;
	for (int i = 0; i < _x; i++)
		for (int j = 0; j < _y; j++)
		{
			_map[i][j] = atoi(dwnV[z].c_str());
			z++;
		}

}

void world::draw(sf::RenderWindow &window)
{
	sf::Vertex* line;
	sf::RectangleShape rectangle(sf::Vector2f(_delX, _delY));
	for (int i = 0; i < _x; i++)
		for (int j = 0; j < _y; j++)
			if (_map != 0)
			{
				
				switch (_map[i][j])
				{
				case 1:
				{
					rectangle.setPosition(sf::Vector2f(_delX*i, _delY*j));
					rectangle.setFillColor(sf::Color::Green);
					window.draw(rectangle); 
					break;
				}
				case 2:
				{
					rectangle.setPosition(sf::Vector2f(_delX*i, _delY*j));
					rectangle.setFillColor(sf::Color::Red);
					window.draw(rectangle); 
					break;
				}
				case 3:
				{
					rectangle.setPosition(sf::Vector2f(_delX*i, _delY*j));
					rectangle.setFillColor(sf::Color::Yellow);
					window.draw(rectangle);
					break;
				}



				default:
					break;
				}





			}
	for (int i = 1; i < _x; i++)
	{
		line = new sf::Vertex[2];
		line[0] = sf::Vertex(sf::Vector2f(i*_delX, 0), sf::Color::Black);
		line[1] = sf::Vertex(sf::Vector2f(i*_delX, window.getSize().y), sf::Color::Black);
		window.draw(line, 2, sf::Lines);
	}
	for (int i = 1; i < _y; i++)
	{
		line = new sf::Vertex[2];
		line[0] = sf::Vertex(sf::Vector2f(0, i*_delY), sf::Color::Black);
		line[1] = sf::Vertex(sf::Vector2f(window.getSize().x, i*_delY), sf::Color::Black);
		window.draw(line, 2, sf::Lines);
	}

}

sf::Vector2f world::whereAmI(float x, float y)
{
	sf::Vector2f pos;
	pos.x = -1;
	pos.y = -1;
	int curX = x / _delX;
	int curY = y / _delY;
	if (curX >= 0 && curY >= 0 && curX < _x&&curY < _y)
	{
		pos.x = curX;
		pos.y = curY;
	}
	return pos;
}

sf::Vector2f world::whereAmIinPixels(float worldX, float worldY)
{
	//(_delX*(worldX + 0.5), _delY*(worldY+0.5))
	//sf::vector2f
	return sf::Vector2f(_delX*(worldX + 0.5), _delY*(worldY + 0.5));
}

int world::whatAmIInPixels(float x, float y)
{
	int stat;
	stat = -1;
	int curX = x / _delX;
	int curY = y / _delY;
	if (curX >= 0 && curY >= 0 && curX < _x&&curY < _y)
	{
		stat = _map[curX][curY];
	}
	return stat;
}

int world::whatAmI(int x, int y)
{
	int stat;
	stat = -1;
	int curX = x;
	int curY = y;
	if (curX >= 0 && curY >= 0 && curX < _x&&curY < _y)
	{
		stat = _map[curX][curY];
	}
	return stat;
}
