#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include"Game.h"
#include <immintrin.h>
#include"EntityComponent.h"

class CircleShape : public Component
{
public:
	CircleShape(GameDataRef _data ,sf::Vector2f pos) : data(_data)
	{
		cir.setPosition(pos);
		cir.setRadius(2);
		cir.setFillColor(sf::Color::Cyan);
	}

	void update()
	{
		cir.setPosition(sf::Vector2f(cir.getPosition() + direction * speed));
		if (cir.getPosition().x > 1200.0f)
		{
			cir.setPosition(sf::Vector2f(0, cir.getPosition().y));
		}

		else if (cir.getPosition().x < 0)
		{
			cir.setPosition(sf::Vector2f(1200, cir.getPosition().y));
		}

		if (cir.getPosition().y > 800.0f)
		{
			cir.setPosition(sf::Vector2f(cir.getPosition().y,0));
		}

		else if (cir.getPosition().y < 0)
		{
			cir.setPosition(sf::Vector2f(cir.getPosition().x,800));
		}
	}

	void draw()
	{
		data->window.draw(cir);
	}

	void SetDirection(const sf::Vector2f& dir)
	{
		direction = dir;
	}

	sf::Vector2f GetDirection() const
	{
		return direction;
	}

	sf::Vector2f GetPosition() const
	{
		return cir.getPosition();
	}

	float GetRadius() const
	{
		return cir.getRadius();
	}

	bool isInserted = false;
private:
	sf::CircleShape cir;
	GameDataRef data;
	sf::Vector2f direction;

	float speed = 2.0f;
};

inline float Distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
	return sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y));
}


inline bool CheckCollision(const CircleShape& c1, const CircleShape& c2)
{
	float dist = Distance(c1.GetPosition(), c2.GetPosition());
	if (dist < c1.GetRadius() + c1.GetRadius())return true;
	else return false;
}

inline bool CheckCollisionSIMD(const CircleShape& c1, const CircleShape& c2)
{
	// Load circle components into AVX registers
	__m256 xmmThisX = _mm256_set1_ps(c1.GetPosition().x);
	__m256 xmmThisY = _mm256_set1_ps(c1.GetPosition().y);
	__m256 xmmThisRadius = _mm256_set1_ps(c1.GetRadius());
	__m256 xmmOtherX = _mm256_set1_ps(c2.GetPosition().x);
	__m256 xmmOtherY = _mm256_set1_ps(c2.GetPosition().y);
	__m256 xmmOtherRadius = _mm256_set1_ps(c2.GetRadius());

	// Calculate difference in X and Y coordinates
	__m256 xmmDiffX = _mm256_sub_ps(xmmThisX, xmmOtherX);
	__m256 xmmDiffY = _mm256_sub_ps(xmmThisY, xmmOtherY);

	// Calculate square of distance
	__m256 xmmDistanceSq = _mm256_add_ps(_mm256_mul_ps(xmmDiffX, xmmDiffX), _mm256_mul_ps(xmmDiffY, xmmDiffY));

	// Calculate sum of radii
	__m256 xmmSumRadius = _mm256_add_ps(xmmThisRadius, xmmOtherRadius);

	// Compare distance squared with sum of radii squared
	__m256 xmmCollisionMask = _mm256_cmp_ps(xmmDistanceSq, _mm256_mul_ps(xmmSumRadius, xmmSumRadius), _CMP_LE_OQ);

	// Extract collision result from the mask
	int collisionMask = _mm256_movemask_ps(xmmCollisionMask);

	// Return true if any of the components have collision
	return collisionMask != 0;
}
