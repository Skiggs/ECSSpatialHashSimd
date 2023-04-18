#pragma once
#include"Game.h"
#include"State.h"
#include<vector>
#include"Optimization.h"
#include"EntityComponent.h"
#include"Shapes.h"

class GameSelection : public State
{
public:
	GameSelection(GameDataRef data);
	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	AbstractTechnique* technique;
	GameDataRef _data;
	sf::Text approachSelectionText, NaiveApproach, QuadtreeApproach, SpatialHashApproach, totalnumberOfShapes, totalnumberOfShapesValue, framerate, frameRateValue;
	std::vector<CircleShape*> allshapes;
	SpatialHash sptHsh;
	//QuadTreeTechnique quadTree;
	System system;
};