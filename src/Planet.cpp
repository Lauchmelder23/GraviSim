#include "Planet.hpp"

Planet::Planet(float xPos, float yPos, float radius, QColor color) :
	position{ xPos, yPos }, radius(radius)
{
	circle = QBrush(color);
}

Planet::Planet(QPointF pos, float radius, QColor color) :
	position(pos), radius(radius)
{
	circle = QBrush(color);
}

void Planet::Draw(QPainter* painter)
{
	painter->setBrush(circle);
	painter->drawEllipse(position, radius, radius);
}
