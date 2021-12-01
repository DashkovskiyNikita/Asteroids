#include "CollisionDetector.h"
#include<SFML/Graphics.hpp>
bool CollisionDetector::detectOverlap(sf::Vector2f* polygon1, int size1, sf::Vector2f* polygon2, int size2) {
	for (int i = 0; i < size1; i++) {
		int b = (i + 1) % size1;
		sf::Vector2f p1 = polygon1[i];
		sf::Vector2f p2 = polygon1[b];
		bool overlap = polyLine(polygon2, size2, p1, p2);
		if (overlap) return true;
	}

	return false;
	//old code working not very well
	/*sf::Vector2f* p1 = polygon1;
	sf::Vector2f* p2 = polygon2;
	int s1 = size1;
	int s2 = size2;
	for (int i = 0; i < 1; i++) {
		if (true) {
			p1 = polygon2;
			p2 = polygon1;
			s1 = size2;
			s2 = size1;
		}
		for (int a = 0; i < s1; i++) {
			int b = (i + 1) % s1;

			sf::Vector2f axis = { -(p1[b].y - p1[a].y),p1[b].x - p1[a].x };
			float dot = getDistance(axis.x, axis.y);
			axis = { axis.x / dot,axis.y / dot };

			float min_r1 = INFINITY, max_r1 = -INFINITY;
			
			for (int p = 0; p < s1; p++) {
				float q = p1[p].x * axis.x + p1[p].y * axis.y;
				min_r1 = std::min(min_r1, q);
				max_r1 = std::max(max_r1, q);
			}

			float min_r2 = INFINITY, max_r2 = -INFINITY;

			for (int e = 0; e < s2; e++) {
				float q = p2[e].x * axis.x + p2[e].y * axis.y;
				min_r2 = std::min(min_r2, q);
				max_r2 = std::max(max_r2, q);
			}

			if (!(min_r1 <= max_r2 && max_r1 >= min_r2)) {
				return false;
			}
		}
	}
	return true;*/
}
bool CollisionDetector::polyLine(sf::Vector2f* polygon,int size, sf::Vector2f p1, sf::Vector2f p2) {
	for (int i = 0; i < size; i++) {
		int b = (i + 1) % size;
		sf::Vector2f p3 = polygon[i];
		sf::Vector2f p4 = polygon[b];
		bool hit = lineLine(p1, p2, p3, p4);
		if (hit) return true;
	}
	return false; 
}
bool CollisionDetector::lineLine(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4) {
	float uA = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) /
		((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
	
	float uB = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) /
		((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

	return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}
bool CollisionDetector::detectOverlap(sf::Vector2f* polygon, int size, float cx, float cy, int radius) {
	for (int i = 0; i < size; i++) {
		int p = (i + 1) % size;
		sf::Vector2f p1 = polygon[i];
		sf::Vector2f p2 = polygon[p];
	    bool collision = lineCicle(p1, p2, cx, cy, radius);
		if (collision) return true;
	}
	return false;
}
bool CollisionDetector::lineCicle(sf::Vector2f p1, sf::Vector2f p2, float cx, float cy, int radius) {
	bool inside1 = pointCicle(p1, cx, cy, radius);
	bool inside2 = pointCicle(p2, cx, cy, radius);
	if (inside1 || inside2) return true;
	float difX = p1.x - p2.x;
	float difY = p1.y - p2.y;
	float length = getDistance(difX, difY);
	float dot = ((cx - p1.x) * (p2.x - p1.x) + (cy - p1.y) * (p2.y - p1.y)) / pow(length,2);
	float closestX = p1.x + dot * (p2.x - p1.x);
	float closestY = p1.y + dot * (p2.y - p1.y);
	bool onSegment = linePoint(p1,p2,closestX,closestY);
	if (!onSegment) return false;
	float distX = closestX - cx;
	float distY = closestY - cy;
	float distance = getDistance(distX, distY);
	return distance <= radius;
}
bool CollisionDetector::pointCicle(sf::Vector2f p, float cx, float cy, int radius) {
	float difX = p.x - cx;
	float difY = p.y - cy;
	float length = getDistance(difX, difY);
	return length <= radius;
}
bool CollisionDetector::linePoint(sf::Vector2f p1, sf::Vector2f p2, float closestX, float closestY) {
	float dx1 = closestX - p1.x;
	float dy1 = closestY - p1.y;
	float dx2 = closestX - p2.x;
	float dy2 = closestY - p2.y;
	float dist1 = getDistance(dx1, dy1);
	float dist2 = getDistance(dx2, dy2);
	float dl1 = p2.x - p1.x;
	float dl2 = p2.y - p1.y;
	float lenLine = getDistance(dl1, dl2);
	return dist1 + dist2 >= lenLine && dist1 + dist2 <= lenLine;
}
float CollisionDetector::getDistance(float x, float y) {
	return sqrt(x * x + y * y);
}
