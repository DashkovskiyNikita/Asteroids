#include "Asteroid.h"
#include<SFML/Graphics.hpp>
#include<ctime>
Asteroid::Asteroid(int screen_size,int ast_size) : window_size(screen_size){
	//initializing fields
	size = ast_size;
	rotation = 0;
	position.x = rand() % screen_size;
	position.y = rand() % screen_size;
	direction = rand() % 361;
	points = new sf::Vector2f[size];
	//randomly generate length polygon's vectors
	for (int i = 0; i < size; i++) {
		int length = rand() % 41 + 100;
		points_length.push_back(length);
	}
}
Asteroid::Asteroid(Point pos, int screen_size, int ast_size,float dir) : window_size(screen_size) {
	size = ast_size;
	rotation = 0;
	position.x = pos.x;
	position.y = pos.y;
	direction = dir;
	points = new sf::Vector2f[size];
	for (int i = 0; i < size; i++) {
		int length = rand() % 41 + lengths[size];
		points_length.push_back(length);
	}
}
sf::Vector2f* Asteroid::getVertices() {
	return points;
}
Point Asteroid::getPosition() {
	return position;
}
int Asteroid::getSize() {
	return size;
}
void Asteroid::drawAsteroid(sf::RenderWindow& window) {
	checkBorder();
	rotateAsteroid();
	moveAsteroid();
	//calculate angle step
	float angle = 360 / size;
	//drawing asteroid
	sf::ConvexShape convex;
	convex.setFillColor(sf::Color::Transparent);
	convex.setOutlineColor(sf::Color::Blue);
	convex.setOutlineThickness(3);
	convex.setPointCount(size);
	for (int i = 0; i < size; i++) {
		points[i].x = position.x + points_length[i] * sin((rotation + i * angle) * PI / 180);
		points[i].y = position.y - points_length[i] * cos((rotation + i * angle) * PI / 180);
		convex.setPoint(i, points[i]);
	}
	window.draw(convex);

}
void Asteroid::moveAsteroid() {
	//move asterois center coordinates
	position.x += 0.15f * sin(direction * PI / 180);
	position.y -= 0.15f * cos(direction * PI / 180);
}
void Asteroid::checkBorder() {
	//the same as the ship but offset more
	if (position.x > window_size + 30) position.x = -30;
	if (position.y > window_size + 30) position.y = -30;
	if (position.x < -30) position.x = window_size + 30;
	if (position.y < -30) position.y = window_size + 30;
}
void Asteroid::rotateAsteroid() {
	if (direction >= 0 && direction <= 180) {
		rotation += 0.05f;
	}
	else {
		rotation -= 0.05f;
	}
}
