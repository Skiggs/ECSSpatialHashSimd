#pragma once
//
//
//#include<SFML/Graphics.hpp>
//
//
//class Shape
//{
//public:
//	Shape(float x, float y);
//	virtual ~Shape(void);
//
//	virtual void Update(float dt);
//	//virtual void Update(float dt, QuadTree&);
//	virtual int Draw(float dt) = 0;
//	void CheckCollision(Shape* shape);
//
//private:
//	sf::Vector2f position;
//};
//
//
//class CircleShape : public Shape
//{
//public:
//	CircleShape(sf::Vector2f pos);
//	virtual void Update(float dt);
//	virtual int Draw(float dt) = 0;
//};