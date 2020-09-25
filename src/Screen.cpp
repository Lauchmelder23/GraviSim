#include "Screen.hpp"

#include <time.h>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QtMath>

#include "MainWindow.hpp"

#define BIND_LMB(f) (lmbAction = std::bind(&Screen::f, this, std::placeholders::_1))

Screen::Screen(QWidget* parent) :
	QOpenGLWidget(parent)
{
	setMouseTracking(true);
	BIND_LMB(lmb_MakePlanet);

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
	if (mouseDown && hovered == nullptr)
	{
		Planet* planet = planets.back();
		QPointF distance = event->localPos() - mouseClickPos;
		planet->Resize(qSqrt(distance.x()*distance.x() + distance.y() *distance.y()));
	}
	else
	{
		hovered = nullptr;
		for (unsigned i = planets.size(); i-- > 0; )
		{
			if (planets[i]->IsInside(event->localPos()))
			{
				setCursor(Qt::OpenHandCursor);
				BIND_LMB(lmb_SelectPlanet);
				hovered = planets[i];
				break;
			}
		}

		if (hovered == nullptr)
		{
			setCursor(Qt::ArrowCursor);
			if(selected == nullptr)
				BIND_LMB(lmb_MakePlanet);
		}
	}
}

void Screen::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		lmbAction(event);
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

void Screen::lmb_MakePlanet(QMouseEvent* event)
{
	planets.push_back(new Planet(event->localPos(), 0,
		QColor(rand() % 256, rand() % 256, rand() % 256)
	));
	mouseClickPos = event->localPos();
	mouseDown = true;
}

void Screen::lmb_SelectPlanet(QMouseEvent* event)
{
	if (hovered != nullptr)
	{
		if (selected != nullptr)
			selected->Select(false);

		hovered->Select(true);
		selected = hovered;
		MainWindow::Instance()->OpenPlanetDialog(selected);
	}
	else
	{
		BIND_LMB(lmb_MakePlanet);
		selected->Select(false);
		selected = nullptr;
		MainWindow::Instance()->ClosePlanetDialog();
		return;
	}
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