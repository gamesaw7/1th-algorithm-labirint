#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "drawData.h"
#include "texter.h"
//std::vector<data>




	class Drawler
	{
	private:
		std::vector<sf::Texture> _Textures;
		std::vector<std::string> _name;
		std::vector<std::string> _tex_list;
		
	protected:
		
	public:		
		Drawler();
		~Drawler();
		void clear();
		void loadTexture(std::string name);
		void loadTextures_F(std::string filename, texter &tex);
		std::vector<std::string> tex_list()
		{
			return _tex_list;
		}
		void DrawTexture(drawData dt, sf::RenderWindow &window);
	};

