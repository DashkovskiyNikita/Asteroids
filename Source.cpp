#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include"SpaceShip.h"
#include"Asteroid.h"
#include"CollisionDetector.h"


const std::string GAME_TITLE = "Asteroids";
const int SCREEN_SIZE = 600;
SpaceShip ship(SCREEN_SIZE);
CollisionDetector collisonDetector;
std::vector<Asteroid*> asteroidsBuffer;



void handleEvent(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            ship.addBullet();
            continue;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            ship.moveShip();
        }
        else {
            float speed = ship.getSpeed() * 0.05f;
            ship.setSpeed(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            ship.leftRotation();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ship.rightRotation();
        }
    }
}

void generateAsteroids(const int count,const int size) {
    for (int i = 0; i < count; i++) {
        asteroidsBuffer.push_back(new Asteroid(SCREEN_SIZE,size));
    }
}
void generateAsteroids(std::vector<Asteroid*> & asteroids, const int count, const int size,Point pos) {
    float x, y,angle;
    for (int i = 0; i < count; i++) {
        if (i % 2 == 0 || i == 0) {
            angle = rand() % 180;
            x = pos.x + 100 * sin(angle * 3.14f / 180);
            y = pos.y - 100 * cos(angle * 3.14f / 180);
        }else {
            angle = rand() % 181 - 180;
            x = pos.x + 100 * sin(angle * 3.14f / 180);
            y = pos.y - 100 * cos(angle * 3.14f / 180);
        }
        Point p = { x,y };
        asteroids.push_back(new Asteroid(p,SCREEN_SIZE, size,angle));
    }
}
void drawAsteroids(sf::RenderWindow& window) {
    for (auto asteroid : asteroidsBuffer) {
        asteroid->drawAsteroid(window);
    }
}
void checkAsteroidOverlap() {
    sf::Vector2f* p1 = ship.getVertices();
    for (auto asteroid : asteroidsBuffer) {
        sf::Vector2f* p2 = asteroid->getVertices();
        int size2 = asteroid->getSize();
        ship.overlap = collisonDetector.detectOverlap(p1, 2, p2, size2);
        if (ship.overlap) {
            ship.color = sf::Color::Red;
            break;
        }
        else {
            ship.color = sf::Color::Yellow;
        }
    }
}
void checkBulletOverlap() {
    std::vector<Bullet> bulletBuffer = ship.getBullets();
    std::vector<Asteroid*> newAsteroids;
    for (auto bullet : bulletBuffer) {
        int radius = bullet.radius;
        float cx = bullet.x + radius;
        float cy = bullet.y + radius;
        for (auto asteroid = asteroidsBuffer.begin(); asteroid != asteroidsBuffer.end();) {
            Asteroid* ast_val = *asteroid;
            sf::Vector2f* p = ast_val->getVertices();
            int size = ast_val->getSize();
            bool isOverlap = collisonDetector.detectOverlap(p, size, cx, cy, radius);
            if (isOverlap) {
                int newAstSize = ast_val->getSize() - 1;
                Point pos = ast_val->getPosition();
                if (newAstSize >= 4) generateAsteroids(newAsteroids,3, newAstSize,pos);
                //asteroidsBuffer.reserve(asteroidsBuffer.size() + 2);
                asteroid = asteroidsBuffer.erase(asteroid);
            }
            else asteroid++;
        }
    }
    asteroidsBuffer.reserve(asteroidsBuffer.size() + newAsteroids.size());
    asteroidsBuffer.insert(asteroidsBuffer.end(), newAsteroids.begin(), newAsteroids.end());
}

int main()
{
    srand(time(0));
    //set antialiasing level
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    
    //setup window
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), GAME_TITLE, sf::Style::Close | sf::Style::Titlebar,settings);
    
    generateAsteroids(3,6);
    //starting game loop
    while (window.isOpen())
    {
        //handle keyboard events
        handleEvent(window);
        
        //clear previous rendering
        window.clear();
        ship.checkCrossBorder();
        ship.checkBadges();
        drawAsteroids(window);
        ship.drawSpaceShip(window);
        checkAsteroidOverlap();
        checkBulletOverlap();
        ship.drawBullets(window);
        //show current rendering
        window.display();
        
    }
    return 0;
}

