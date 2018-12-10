
#include "TwodObj.h"
#include "drawData.h"

	
	
TwodObj::TwodObj() 
{


}


TwodObj::~TwodObj()
	{
	}

	void TwodObj::initS(float x, float y, float scaleX, float scaleY)
	{
		setCoord(x, y);
	}

	void TwodObj::initS(float x, float y, float scale)
	{
		setCoord(x, y);
	}
	
	void TwodObj::initWH(float w, float h)
	{
		_w = w; 
		_h = h;
	}

	void TwodObj::setCoord(float x, float y)
	{
		_x = x; 
		_y = y;		
	}



	float TwodObj::getX()
	{
		return _x;
	}
	float TwodObj::getY()
	{
		return _y;
	}

	void TwodObj::setPic(std::string _tex, Drawler &dr)
	{
		_name = _tex;
		std::vector<std::string> list = dr.tex_list();
		bool default_tex = true;
		int n = std::stoi(list[0]);
		for (int i = 1; i < list.size(); i += n)
		{
			if (_name == list[i])
			{
				default_tex = false;
				break;
			}
		}
		if (default_tex)
		{
			_name = list[1];
		}

	}

	void TwodObj::moveCoord(float defX, float defY)
	{
		_x += defX;
		_y += defY;
	}

	void TwodObj::setRotation(float angle)
	{
		_rot = angle;
	}

	void TwodObj::rot(float defangle)
	{
		_rot += defangle;
		if (_rot > 720)_rot -= 360;
		if (_rot < -720)_rot += 360;
	}

	
	float TwodObj::getTop()
		{
			return _y + _h / 2;
		}
	float TwodObj::getBot()
		{
			return _y - _h / 2;
		}
	float TwodObj::getLeft()
		{
			return _x - _w / 2;
		}
	float TwodObj::getRight()
		{
			return _x + _w / 2;
		}



	

	void TwodObj::draw(Drawler &dr)
	{
		drawData dt;
		dt._x = _x - sqrt(_w*_w + _h*_h)*cos((_rot + 57.29*atan(_h / _w))/57.29)/2;
		dt._y = _y - sqrt(_w*_w + _h*_h)*sin((_rot + 57.29*atan(_h / _w))/57.29)/2;
		dt._rot = _rot;
		dt._w = _w;
		dt._h = _h;
		dt._name = _name;
		dr.DrawTexture(dt, _wn, _hn);
	}
