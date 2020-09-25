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
	void Select(bool select);

	void Draw(QPainter* painter);

	bool IsInside(QPointF point) const;

private:
	void Initialize(QColor color);

public:
	QPointF position;
	float radius;

private:

	QColor selectionColor;

	QBrush circle;
	QPen outline;
};