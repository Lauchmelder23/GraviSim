#pragma once

#include <QBrush>
#include <QPainter>
#include <QPaintEvent>

class Planet
{
public:
	Planet(uint32_t id, float xPos, float yPos, float radius, QColor color);
	Planet(uint32_t id, QPointF pos, float radius, QColor color);

	void Resize(float newRadius) { radius = newRadius; }
	void Select(bool select);

	void SetColor(const QColor& color);
	const QColor& GetColor() { return circle.color(); }

	void Update();
	void Draw(QPainter & painter);

	bool IsInside(QPointF point) const;

private:
	void Initialize(QColor color);

public:
	const uint32_t id;

	QPointF position;
	QPointF velocity;
	QPointF acceleration;
	QString name;
	float radius;
	float mass;

private:

	QColor selectionColor;

	QBrush circle;
	QPen outline;

	static QPen arrowColor;
	static QLine arrow;
};