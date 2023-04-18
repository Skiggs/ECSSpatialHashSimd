#pragma once

#include<vector>
#include"EntityComponent.h"
#include"Shapes.h"

class CircleShape;

class AbstractTechnique
{
public:
	virtual ~AbstractTechnique() {};
	virtual void Setup(const std::vector<Entity*>& allEntities) = 0;
	virtual std::vector<Entity*> findShapesInRange(float range, Component& shape) = 0;
};


class NaiveTechnique : public AbstractTechnique
{
public:
	NaiveTechnique() = default;

	void Setup(const std::vector<Entity*>& allEntities )
	{
		shapes = (allEntities);
	}

	std::vector<Entity*> findShapesInRange(float range, Component& shape)
	{
		std::vector<Entity*> shapesinRange;
		for (int i = 0; i < shapes.size(); ++i)
		{
			if (dynamic_cast<CircleShape&>(shape).entity != shapes[i]->getComponent<CircleShape>().entity)
			{
				if (Distance(dynamic_cast<CircleShape&>(shape).GetPosition(), shapes[i]->getComponent<CircleShape>().GetPosition()) < range)
				{
					shapesinRange.push_back(shapes[i]);
				}
			}
		}

		return shapesinRange;
	}


private:
	std::vector<Entity*> shapes;
};


//class Quad
//{
//public:
//	Quad() :northEast(nullptr), northWest(nullptr), southEast(nullptr), southWest(nullptr) {}
//	Quad(float x, float y, float pwidth, float pheight) {
//		posX = x;
//		posY = y;
//		height = pheight;
//		width = pwidth;
//	}
//	~Quad()
//	{
//		if (isDivided)
//		{
//			Destroy();
//			isDivided = false;
//		}
//		shapesInNode.clear();
//	};
//	bool containsShape(float x, float y, float height, float width) {};
//	void subDivide() {};
//	bool insert(CircleShape* curShape)
//	{
//		if (currentCount < maxCapacity)
//		{
//			curShape->isInserted = true;
//			++currentCount;
//		
//			shapesInNode.push_back(curShape);
//			return 1;
//		}
//
//		else
//		{
//			northEast = new  Quad(posX + width / 2, posY - height / 2, width / 2, height / 2);
//			northWest = new  Quad(posX - width / 2, posY - height / 2, width / 2, height / 2);
//			southEast = new  Quad(posX + width / 2, posY + height / 2, width / 2, height / 2);
//			southWest = new  Quad(posX - width / 2, posY + height / 2, width / 2, height / 2);
//			isDivided = true;
//			northEast->curLevel = curLevel + 1;
//			northWest->curLevel = curLevel + 1;
//			southEast->curLevel = curLevel + 1;
//			southWest->curLevel = curLevel + 1;
//			if (maxLevel < northEast->curLevel) maxLevel = northEast->curLevel;
//
//		}
//
//
//		shapesInNode.push_back(curShape);
//
//		//curShape->isInserted = true;
//		for (int i = 0; i < shapesInNode.size(); ++i)
//		{
//			
//				int NORS = (shapesInNode[i]->GetPosition().y >= posY - height && shapesInNode[i]->GetPosition().y < posY) ? 1 : 0;
//				int WORS = (shapesInNode[i]->GetPosition().x >= posX - width && shapesInNode[i]->GetPosition().x < posX) ? 1 : 0;
//				if (NORS == 1 && WORS == 1)
//				{
//					northEast->shapesInNode.push_back(curShape);
//					northEast->currentCount++;
//				}
//
//				if (NORS == 1 && WORS == 0)
//				{
//					northWest->shapesInNode.push_back(curShape);
//					northWest->currentCount++;
//				}
//
//				if (NORS == 0 && WORS == 0)
//				{
//					southWest->shapesInNode.push_back(curShape);
//					southWest->currentCount++;
//				}
//
//				if (NORS == 0 && WORS == 1)
//				{
//					southEast->shapesInNode.push_back(curShape);
//					southEast->currentCount++;
//				}
//				//NORS == 1 ? (WORS == 1) ? childQuads["NW"].quadHoldingShapes.push_back(quadHoldingShapes[i]) : childQuads["NE"].quadHoldingShapes.push_back(quadHoldingShapes[i]) : (WORS == 1) ? childQuads["SW"].quadHoldingShapes.push_back(quadHoldingShapes[i]) : childQuads["SE"].quadHoldingShapes.push_back(quadHoldingShapes[i]);
//			}
//			shapesInNode.clear();
//			return 0;
//		
//	}
//	void Destroy() {
//		delete northEast;
//
//		delete northWest;
//
//		delete southWest;
//
//		delete southEast;
//
//		northEast = northWest = southEast = southWest = nullptr;
//	}
//	float GetY() const { return posY; }
//	float GetX() const { return posX; }
//	float GetWidth() const { return width; }
//	float GetHeight() const { return height; }
//	Quad* northEast;
//	Quad* northWest;
//	Quad* southEast;
//	Quad* southWest;
//	 std::vector<CircleShape*> shapesInNode;
//	static int maxLevel;
//	bool isDivided = false;
//private:
//	int curLevel = 0;
//	int maxCapacity = 50;
//	Quad* parentQuad;
//	float posX, posY;
//	float height, width;
//	int currentCount = 0;
//
//};
//
//
//
//class QuadTreeTechnique : public AbstractTechnique
//{
//public:
//	QuadTreeTechnique() :parentNode(nullptr) {};
//	~QuadTreeTechnique()
//	{
//		if (parentNode != nullptr)
//		{
//			delete parentNode;
//			parentNode = nullptr;
//		}
//	};
//
//	/*void Setup(std::vector<CircleShape*>& allShapes)
//	{
//		parentNode = new Quad(600.0, 400.0, 600, 400);
//		std::vector<Quad*> quads;
//		quads.push_back(parentNode);
//		std::vector<Quad*>::iterator curIt = quads.begin();
//		int currentIndex = 0;
//		for (int i = 0; i < allShapes.size(); ++i)
//		{
//			while (curIt != quads.end())
//			{
//				if ((allShapes[i]->GetPosition().x > 0.0f && allShapes[i]->GetPosition().x < 1200.0f) && (allShapes[i]->GetPosition().y > 0.0f && allShapes[i]->GetPosition().y < 800.0f))
//				{
//					if ((allShapes[i]->GetPosition().y <= (*curIt)->GetY() + ((*curIt))->GetHeight() && allShapes[i]->GetPosition().y >= ((*curIt))->GetY() - ((*curIt))->GetHeight()) && (allShapes[i]->GetPosition().x <= ((*curIt))->GetX() + ((*curIt))->GetWidth() && allShapes[i]->GetPosition().x >= ((*curIt))->GetX() - ((*curIt))->GetWidth()))
//					{
//						bool result = ((*curIt))->insert(allShapes[i]);
//
//						if (!result)
//						{
//							{
//								Quad* NW = (*curIt)->northWest;
//								Quad* NE = (*curIt)->northEast;
//								Quad* SW = (*curIt)->southWest;
//								Quad* SE = (*curIt)->southEast;
//								quads.push_back(NW);
//								quads.push_back(NE);
//								quads.push_back(SW);
//								quads.push_back(SE);
//							}
//							quads.erase(quads.begin() + currentIndex);
//							curIt = quads.begin() + currentIndex;
//						}
//						break;
//					}
//					else
//					{
//						if (currentIndex < quads.size() - 1) ++currentIndex;
//						else currentIndex = 0;
//						curIt = quads.begin() + currentIndex;
//					}
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//	}*/
//	std::vector<CircleShape*> findShapesInRange(float range, CircleShape* targetShape)
//	{
//		float RangePosX = targetShape->GetPosition().x;
//		float RangePosY = targetShape->GetPosition().y;
//
//		float width = 0.05f;
//		std::vector<CircleShape*> shapesInRange;
//		std::vector<Quad*> quads;
//		quads.push_back(parentNode);
//		std::vector<Quad*>::iterator curIt = quads.begin();
//		int currentIndex = 0;
//
//		while (curIt != quads.end())
//		{
//			if (abs((*curIt)->GetX() - RangePosX) <= (*curIt)->GetWidth() + width && abs((*curIt)->GetY() - RangePosY) <= (*curIt)->GetHeight() + width)
//			{
//				if ((*curIt)->isDivided)
//				{
//					Quad* NW = (*curIt)->northWest;
//					Quad* NE = (*curIt)->northEast;
//					Quad* SW = (*curIt)->southWest;
//					Quad* SE = (*curIt)->southEast;
//					quads.push_back(NW);
//					quads.push_back(NE);
//					quads.push_back(SW);
//					quads.push_back(SE);
//				}
//
//				else
//				{
//					shapesInRange.insert(shapesInRange.end(), (*curIt)->shapesInNode.begin(), (*curIt)->shapesInNode.end());
//				}
//				quads.erase(quads.begin() + currentIndex);
//				curIt = quads.begin() + currentIndex;
//			}
//			else
//			{
//				quads.erase(quads.begin() + currentIndex);
//				curIt = quads.begin() + currentIndex;
//			}
//		}
//
//		return shapesInRange;
//	}
//
//private:
//	Quad* parentNode;
//};
//
//
class GridNode
{
public:
	GridNode(float x, float y, float size)
	{
		posX = x;
		posY = y;
	}
	~GridNode() {

	}
	float GetX() const { return posX; }
	float GetY() const { return posY; }
	 std::vector<Entity*> shapesInNode;
private:
	float posX, posY;
};

inline float Clamp(float value, float Min, float Max)
{
	if (value < Min) return Min;
	else if (value > Max) return Max;
	return value;
}

class SpatialHash : public AbstractTechnique
{
public:
	SpatialHash() {}
	~SpatialHash()
	{
		if (grid.size() > 0)
		{
			for (int i = 0; i < totalCellsPerLine; ++i)
			{
				for (int j = 0; j < totalCellsPerLine; ++j)
				{
					if (grid[i][j] != nullptr)
						delete grid[i][j];
				}
				grid[i].clear();
			}
			grid.clear();
		}
	}

	void Setup(const std::vector<Entity*>& allShapes)
	{
		for (int i = 0; i < grid.size(); ++i)
		{
			for (int j = 0; j < grid[i].size(); ++j)
			{
				/*grid[i].push_back(new GridNode(0.1 + nextValueToAddX, 0.1 + nextValueToAddY, 0.2));
				nextValueToAddX += addonValue;*/
				delete grid[i][j];
			}
			grid[i].clear();
		}
		grid.clear();

		int totalShapes = allShapes.size();
		int shapesPerLine = sqrt(totalShapes);
		shapeSize = Clamp((float)1200 / shapesPerLine, 5, 240);
		//totalCellsPerLine =Clamp(2 / shapeSize,10,60);
		totalCellsPerLine = 1200 / shapeSize;
		gridOffset = totalCellsPerLine / 2;


		for (int i = 0; i < totalCellsPerLine; ++i)
		{
			std::vector<GridNode*> _gridnodes;
			grid.push_back(_gridnodes);
			for (int j = 0; j < totalCellsPerLine; ++j)
			{
				/*grid[i].push_back(new GridNode(0.1 + nextValueToAddX, 0.1 + nextValueToAddY, 0.2));
				nextValueToAddX += addonValue;*/
				grid[i].push_back(new GridNode(0, 0, shapeSize));
			}

		}

		for (int i = 0; i < allShapes.size(); ++i)
		{
			int x = Clamp((int)(allShapes[i]->getComponent<CircleShape>().GetPosition().x / shapeSize), 0, totalCellsPerLine - 1);
			int y = Clamp((int)(allShapes[i]->getComponent<CircleShape>().GetPosition().y / shapeSize), 0, totalCellsPerLine - 1);
			//allShapes[i]->gridX = x;
			//allShapes[i]->gridY = y;
			//int attractShapeType = allShapes[i]->GetType();

				grid[x][y]->shapesInNode.push_back(allShapes[i]);
			
		}


	}
	std::vector<Entity*> findShapesInRange(float range, Component& shp)
	{
		
		int x = Clamp((int)(dynamic_cast<CircleShape&>(shp).GetPosition().x / shapeSize) , 0, totalCellsPerLine - 1);
		int y = Clamp((int)(dynamic_cast<CircleShape&>(shp).GetPosition().y / shapeSize) , 0, totalCellsPerLine - 1);
		int maxPrevCheck = 200 / shapeSize + 1;
		std::vector<Entity*> shapesInRange;

		shapesInRange = grid[x][y]->shapesInNode;

		//if (shapesInRange.size() == 0)
		//{
		//	for (int i = (int)Clamp(x - 1, 0, totalCellsPerLine - 1); i < (int)Clamp(x + 1, 0, totalCellsPerLine - 1); ++i)
		//	{
		//		for (int j = Clamp(y - 1, 0, totalCellsPerLine - 1); j < Clamp(y + 1, 0, totalCellsPerLine - 1); ++j)
		//		{
		//			for (auto p : grid[i][j]->shapesInNode)
		//			{
		//				shapesInRange.insert(shapesInRange.end(), grid[i][j]->shapesInNode[AttractorType[shp.GetType()]].begin(), grid[i][j]->shapesInNode[AttractorType[shp.GetType()]].end());
		//			}

		//		}
		//	}
		//}

		return shapesInRange;
	}

private:
	uint8_t gridOffset;
	float shapeSize;
	uint8_t totalCellsPerLine;
	std::vector<std::vector<GridNode*>> grid;
};