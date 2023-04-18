#pragma once


#include <memory>
#include <string>
#include<SFML/Graphics.hpp>
#include"FontManager.h"
#include "StateMachine.h"
#include "InputManager.h"

#define MAXX (1200.0f);
#define MAXY (800.0f);

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	InputManager input;
	FontManager font;
	const sf::Clock _Globalclock;
};

typedef std::shared_ptr<GameData> GameDataRef;

extern float fr;

class Game
{
public:
	Game(int width, int height, std::string Title);

private:
	const float dt = 1.0f / 60.0f;
	
	GameDataRef _data = std::make_shared<GameData>();

	void Run();

};