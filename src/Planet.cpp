#include "Planet.hpp"

Planet::Planet(float xPos, float yPos, float radius, QColor color) :
	position{ xPos, yPos }, radius(radius)
{
	Initialize(color);
}

Planet::Planet(QPointF pos, float radius, QColor color) :
	position(pos), radius(radius)
{
	Initialize(color);
}

void Planet::Select(bool select)
{
	if (select)
		outline.setColor(selectionColor);
	else
		outline.setColor(Qt::transparent);
}

void Planet::SetColor(const QColor& color)
{
	circle = QBrush(color);
	outline = QPen(Qt::transparent);
	outline.setWidthF(4.f);

	int h, s, v, a;
	color.getHsv(&h, &s, &v, &a);
	selectionColor = QColor::fromHsv((h + 180) % 360, s, v, a);
}

void Planet::Draw(QPainter* painter)
{
	painter->setBrush(circle);
	painter->setPen(outline);
	painter->drawEllipse(position, radius, radius);
}

bool Planet::IsInside(QPointF point) const
{
	QPointF distance = point - position;
	return (distance.x() * distance.x() + distance.y() * distance.y() < radius * radius);
}

void Planet::Initialize(QColor color)
{
	name = "Unnamed";
	SetColor(color);
}
