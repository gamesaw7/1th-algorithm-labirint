#pragma once
#include "Drawler.h"




	class TwodObj
	{
	protected:
		float _x, _y;//координаты
		float _rot=0;//угол
		float _w, _h;//длина и ширина изображения
		float _wPic, _hPic;//длина и ширина текстуры
		//float _scale = 1;//растянутость текстуры
		float _scaleX = 1;
		float _scaleY = 1;
		std::string _name = "";
		sf::RenderWindow &window;
	public:		
		TwodObj(sf::RenderWindow &w);
		~TwodObj();
		
		float getX();
		float getY();
		void initS(float x, float y, float scaleX, float scaleY);
		void initS(float x, float y, float scale);
		void initWH(float x, float y, float w, float h);
		void setCoord(float x, float y);
		void setScale(float scaleX, float ScaleY);
		void setScale(float scale);		
		void setPic(std::string _tex, Drawler &dr);

		float getTop();
		float getBot();
		float getLeft();
		float getRight();
		void draw(Drawler &dr);
		void doScales(float w, float h);
	};

