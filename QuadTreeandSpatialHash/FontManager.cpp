
#include"FontManager.h"

void FontManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font fon;

	if (fon.loadFromFile(fileName))
	{
		this->_fonts[name] = fon;
	}
}

sf::Font& FontManager::GetFont(std::string name)
{
	return this->_fonts.at(name);
}

