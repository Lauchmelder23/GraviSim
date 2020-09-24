#pragma once

#include <QBrush>
#include <QPainter>
#include <QPaintEvent>

class Planet
{
public:
	Planet(float xPos, float yPos, float radius, QColor color);
	Planet(QPointF pos, float radius, QColor color);

	void Resize(float newRadius) { radius = newRadius; }

	void Draw(QPainter* painter);

private:
	QPointF position;
	float radius;

	QBrush circle;
};