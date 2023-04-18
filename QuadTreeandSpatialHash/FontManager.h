#pragma once

#include<SFML/Graphics.hpp>
#include<map>

class FontManager
{

public:
	FontManager() {};
	~FontManager() {};

	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);

private:
	std::map<std::string, sf::Font> _fonts;
};