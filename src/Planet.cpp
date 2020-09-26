#include "Planet.hpp"

#define LENGTH(v) (sqrtf(v.x()*v.x() + v.y()*v.y()))

QPen Planet::arrowColor = QPen(Qt::white);
QLine Planet::arrow = QLine();

Planet::Planet(uint32_t id, float xPos, float yPos, float radius, QColor color) :
	position{ xPos, yPos }, radius(radius), id(id)
{
	Initialize(color);
}

Planet::Planet(uint32_t id, QPointF pos, float radius, QColor color) :
	position(pos), radius(radius), id(id)
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

void Planet::Update()
{
	velocity += acceleration * (1.f / 60.f);
	position += velocity * (1.f / 60.f);
}

void Planet::Draw(QPainter & painter)
{
	painter.setBrush(circle);
	painter.setPen(outline);
	painter.drawEllipse(position, radius, radius);

	// Draw velocity arrow
	if (!velocity.isNull())
	{
		painter.save();
		qreal angle = QPointF::dotProduct(velocity, QPointF(1.0f, 0.0f)) / LENGTH(velocity);
		painter.rotate(angle);
		
		arrow.setP1(position.toPoint());
		arrow.setP2((position + velocity).toPoint());

		painter.setPen(arrowColor);
		painter.drawLine(arrow);

		painter.restore();
	}
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
	arrowColor.setWidthF(2.0f);
	acceleration = QPointF(0.f, 0.f);
}
