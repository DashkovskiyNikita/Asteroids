#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
class CollisionDetector
{
public:
	bool detectOverlap(sf::Vector2f* polygon1,int size1,sf::Vector2f* polygon2,int size2);
	bool detectOverlap(sf::Vector2f* polygon, int size, float cx, float cy, int radius);
private:
	bool polyLine(sf::Vector2f* polygon,int size, sf::Vector2f p1, sf::Vector2f p2);
	bool lineLine(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4);
	bool lineCicle(sf::Vector2f p1, sf::Vector2f p2, float cx, float cy, int radius);
	bool pointCicle(sf::Vector2f p, float cx, float cy, int radius);
	bool linePoint(sf::Vector2f p1, sf::Vector2f p2,float closestX,float closestY);
	float getDistance(float x, float y);
};

