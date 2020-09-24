#include "Screen.hpp"

#include <time.h>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QtMath>

Screen::Screen(QWidget* parent) :
	QOpenGLWidget(parent)
{
	srand(time(NULL));

	background = QBrush(Qt::black);

	renderTimer = new QTimer(this);
	connect(
		renderTimer, &QTimer::timeout,
		this, &Screen::Render
	);
	renderTimer->start(1000.f / 60.0f);
}

void Screen::mouseMoveEvent(QMouseEvent* event)
{
	if (mouseDown)
	{
		Planet* planet = planets.back();
		QPointF distance = event->localPos() - mouseClickPos;
		planet->Resize(qSqrt(distance.x()*distance.x() + distance.y() *distance.y()));
	}
}

void Screen::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		planets.push_back(new Planet(event->localPos(), 0,
			QColor(rand() % 256, rand() % 256, rand() % 256)
		));
		mouseClickPos = event->localPos();
		mouseDown = true;
	}

	if (event->button() == Qt::MouseButton::RightButton)
	{
		if (mouseDown)
		{
			planets.pop_back();
			mouseDown = false;
		}
	}
}

void Screen::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
		mouseDown = false;
}

void Screen::Render()
{
	update();
}

void Screen::paintEvent(QPaintEvent* event)
{
	QPainter painter;
	painter.begin(this);
	painter.fillRect(rect(), background);

	for (Planet* planet : planets)
		planet->Draw(&painter);

	painter.end();
}