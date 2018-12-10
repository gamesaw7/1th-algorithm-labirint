
#include "TwodObj.h"
#include "drawData.h"

	
	
TwodObj::TwodObj(sf::RenderWindow &w) : window(w)
{


}

TwodObj::~TwodObj()
	{
	}

	void TwodObj::initS(float x, float y, float scaleX, float scaleY)
	{
		setCoord(x, y);
		setScale(scaleX, scaleY);
	}

	void TwodObj::initS(float x, float y, float scale)
	{
		setCoord(x, y);
		setScale(scale);
	}
	
	void TwodObj::initWH(float x, float y, float w, float h)
	{
		setCoord(x, y);
		doScales(w, h);
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
				_wPic = stoi(list[i + 1]);
				_hPic = stoi(list[i + 2]);
				default_tex = false;
				break;
			}
		}
		if (default_tex)
		{
			_name = list[1];
			_wPic = stoi(list[2]);
			_hPic = stoi(list[3]);
		}

	}

	
	void TwodObj::setScale(float scaleX, float scaleY)
	{
		_scaleX = scaleX;
		_scaleY = scaleY;
		_w = _wPic*_scaleX;
		_h = _hPic*_scaleY;
	}
	void TwodObj::setScale(float scale)
	{
		_scaleX = scale;
		_scaleY = scale;
		_w = _wPic*_scaleX;
		_h = _hPic*_scaleY;
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
		dt._scaleX = _scaleX;
		dt._scaleY = _scaleY;
		dt._name = _name;
		dr.DrawTexture(dt, window);
	}

	void TwodObj::doScales(float w, float h)
	{
		_w = w; _h = h;
		_scaleX = _w / _wPic;
		_scaleY = _h / _hPic;

		
	}