#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
struct Bullet {
	float x, y;
	float direction;
	int radius;
};

class SpaceShip
{
public:
	SpaceShip(int size);
	sf::Color color;
	bool overlap = false;
private:
	const float PI = 3.14159f;
	const float acceleration = 1.001f;
	float centerX;
	float centerY;
	float rotation;
	float screen_size;
	float speed;
	sf::Vector2f points[3];
	std::vector<Bullet> bullet_buffer;
public :
	sf::Vector2f* getVertices();

	float getCenterX();
	void setCenterX(float value);
	
	float getCenterY();
	void setCenterY(float value);
	
	float getRotation();
	void setRotation(float value);

	float getScreenSize();
	void setScreenSize(float value);

	float getSpeed();
	void setSpeed(float value);

	void drawSpaceShip(sf::RenderWindow& window);
	
	void checkCrossBorder();

	void leftRotation();
	void rightRotation();

	void moveShip();

	void addBullet();
	void drawBullets(sf::RenderWindow& window);
	std::vector<Bullet> getBullets();
	
	void checkBadges();
};

