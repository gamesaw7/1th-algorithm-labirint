
#include "Drawler.h"

	Drawler::Drawler()
	{

	}
	
	Drawler::~Drawler()
	{
	}


		void Drawler::clear()
		{

		}

		void Drawler::loadTexture(std::string name)
		{
			//_texture.push_back(Core::resourceManager.Get<Render::Texture>(name));
			sf::Image im;
			im.loadFromFile(name);
			sf::Texture tx;
			tx.loadFromImage(im);
			_Textures.push_back(tx);
			_name.push_back(name);			
		}
		void Drawler::loadTextures_F(std::string filename, texter & tex)
		{
			_tex_list = tex.downloadFromFile_M(filename);
			int n = std::stoi(_tex_list[0]);
			for (int i = 1; i < _tex_list.size(); i += n)
			{
				loadTexture(_tex_list[i]);
			}

		}
		void Drawler::DrawTexture(drawData dt, sf::RenderWindow &window)
		{
			sf::Sprite spr;
			spr.setPosition(dt._x, dt._y);
			spr.setRotation(dt._rot);
			spr.setScale(dt._scaleX, dt._scaleY);


		for (int i = 0; i < _name.size(); i++)
		{
			if (_name[i] == dt._name)
			{
				spr.setTexture(_Textures[i]);
				break;
			}
			if (i == _name.size() - 1)spr.setTexture(_Textures[i]);
		}
		window.draw(spr);
		}