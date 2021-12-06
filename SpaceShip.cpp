#include "SpaceShip.h"
#include <SFML/Graphics.hpp>

SpaceShip::SpaceShip(int size) : screen_size(size) {
    //initializing fields
	centerX = screen_size / 2;
	centerY = screen_size / 2;
	rotation = 0;
    speed = 0;
}
sf::Vector2f* SpaceShip::getVertices() {
    return points;
}
float SpaceShip::getCenterX() {
	return centerX;
}
void SpaceShip::setCenterX(float value) {
	centerX = value;
}
float SpaceShip::getCenterY() {
	return centerY;
}
void SpaceShip::setCenterY(float value) {
	centerY = value;
}
float SpaceShip::getRotation() {
	return rotation;
}
void SpaceShip::setRotation(float value) {
	rotation = value;
}
float SpaceShip::getScreenSize() {
	return screen_size;
}
void SpaceShip::setScreenSize(float value) {
	screen_size = value;
}
float SpaceShip::getSpeed() {
    return speed;
}
void SpaceShip::setSpeed(float value) {
    speed = value;
}
std::vector<Bullet> SpaceShip::getBullets() {
    return bullet_buffer;
}
void SpaceShip::drawSpaceShip(sf::RenderWindow& window) {
    //calculating coordinates 3 points which based our spaceship and save them
    points[0].x = centerX + 15 * sin(rotation * PI / 180);
    points[0].y = centerY - 15 * cos(rotation * PI / 180);
    points[1].x = centerX + 10 * sin((rotation + 120) * PI / 180);
    points[1].y = centerY - 10 * cos((rotation + 120) * PI / 180);
    points[2].x = centerX + 10 * sin((rotation - 120) * PI / 180);
    points[2].y = centerY - 10 * cos((rotation - 120) * PI / 180);
    //creating polygon by points
    sf::ConvexShape convex;
    convex.setPointCount(3);
    convex.setPoint(0, points[0]);
    convex.setPoint(1, points[1]);
    convex.setPoint(2, points[2]);
    convex.setFillColor(sf::Color::Transparent);
    convex.setOutlineColor(color);
    convex.setOutlineThickness(1.5);
    window.draw(convex);
}
void SpaceShip::checkCrossBorder() {
    //if our space x or y position more than screen size we need to put point with offset in the start of window 
    //if our space x or y position less than screen size we need to put point with offset in the end of window 
    if (centerX > screen_size + 10) centerX = -10;
    if (centerX < -10) centerX = screen_size + 10;
    if (centerY < -10) centerY = screen_size + 10;
    if (centerY > screen_size + 10) centerY = -10;
}
void SpaceShip::leftRotation() {
    //change angle value counterclockwise
    rotation -= 20;
}
void SpaceShip::rightRotation() {
    //change angle value clockwise
    rotation += 20;
}
void SpaceShip::moveShip() {
    //adding acceleretion to speed
    speed += acceleration;
    //move center our space ship 
    centerX += (12 + speed) * sin(rotation * PI / 180);
    centerY -= (12 + speed) * cos(rotation * PI / 180);
}
void SpaceShip::addBullet() {
    //calculating start x and y position of our bullet
    float startX = centerX + 10 * sin(rotation * PI / 180);
    float startY = centerY- 10 * cos(rotation * PI / 180);
    Bullet bullet = { startX,startY,rotation,3 };
    //adding new bullet in buffer
    bullet_buffer.push_back(bullet);
}
void SpaceShip::drawBullets(sf::RenderWindow& window) {
    //drawing bullets from buffer
    for (auto& bullet : bullet_buffer) {
        //move bullet by direction
        bullet.x += 1.0f * sin(bullet.direction * PI / 180);
        bullet.y -= 1.0f * cos(bullet.direction * PI / 180);
        sf::CircleShape circle;
        circle.setRadius(bullet.radius);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(sf::Vector2f(bullet.x - bullet.radius, bullet.y - bullet.radius));
        window.draw(circle);
    }
}
void SpaceShip::checkBadges() {
    //if bullet coordinates more or less screen size we will delete it
    for (auto bullet = bullet_buffer.begin(); bullet != bullet_buffer.end();) {
        double x = bullet->x;
        double y = bullet->y;
        if (x > screen_size || x < 0 || y > screen_size || y < 0) bullet = bullet_buffer.erase(bullet);
        else {
            ++bullet;
        }
    }
}
