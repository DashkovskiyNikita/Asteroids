#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<map>
struct Point {
	float x, y;
};

class Asteroid
{

public:
	Asteroid(int screen_size,int ast_size);
	Asteroid(Point pos, int screen_size, int ast_size,float dir);
private:
	const float PI = 3.14159f;
	std::map<int, int> lengths = { {4,10},{5,50},{6,100} };
	Point position;
	int size;
	int window_size;
	float rotation;
	float direction;
	sf::Vector2f* points;
	std::vector<int> points_length;
public:
	void drawAsteroid(sf::RenderWindow& window);
	sf::Vector2f* getVertices();
	Point getPosition();
	int getSize();
private:
	void moveAsteroid();
	void checkBorder();
	void rotateAsteroid();
};

