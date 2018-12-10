#pragma once
#include "Drawler.h"




	class TwodObj
	{
	protected:
		float _x, _y;//координаты
		float _rot=0;//угол
		float _w, _h;//длина и ширина изображения
		int _wn = 0;
		int _hn = 0;
		int _wmax = 1;
		int _hmax = 1;
		std::string _name = "";
	public:		
		 TwodObj();
		~TwodObj();
		float getX();
		float getY();
		void initS(float x, float y, float scaleX, float scaleY);
		void initS(float x, float y, float scale);
		void initWH(float w, float h);
		void setCoord(float x, float y);
		void setPic(std::string _tex, Drawler &dr);
		void moveCoord(float defX, float defY);
		void setRotation(float angle);
		void rot(float defangle);
		float getTop();
		float getBot();
		float getLeft();
		float getRight();
		void draw(Drawler &dr);
	};

