#include "Screen.hpp"

#include <time.h>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QtMath>

#include "MainWindow.hpp"
#include "PlanetManager.hpp"

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
	if (mouseDown && selected == nullptr && hovered == nullptr)
	{
		Planet* planet = PlanetManager::GetLastPlanet();
		QPointF distance = event->localPos() - mouseClickPos;
		planet->Resize(qSqrt(distance.x()*distance.x() + distance.y() *distance.y()));
	}
	else if (mouseDown && selected != nullptr)
	{
		selected->velocity = event->localPos() - selected->position;
	}
	else
	{
		hovered = PlanetManager::IsInPlanet(event->localPos());
		if (hovered == nullptr)
		{
			setCursor(Qt::ArrowCursor);
			if(selected == nullptr)
				BIND_LMB(lmb_MakePlanet);
		}
		else
		{
			BIND_LMB(lmb_SelectPlanet);
			setCursor(Qt::PointingHandCursor);
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
			PlanetManager::RemoveLastPlanet();
			mouseDown = false;
		}
	}
}

void Screen::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
		mouseDown = false;
}

void Screen::DeletePlanet(Planet* planet)
{
	PlanetManager::RemovePlanet(planet->id);
	hovered = nullptr;
	selected = nullptr;
}

void Screen::Render()
{
	update();
}

void Screen::lmb_MakePlanet(QMouseEvent* event)
{
	Planet* newPlanet = PlanetManager::AddPlanet(event->localPos(), 0,
		QColor(rand() % 200, rand() % 200, rand() % 200)
	);

	newPlanet->velocity = QPointF(rand() % 400 - 200, rand() % 400 - 200);

	mouseClickPos = event->localPos();
	mouseDown = true;
}

void Screen::lmb_SelectPlanet(QMouseEvent* event)
{
	if (hovered != nullptr)
	{
		if (selected != hovered)
		{
			if (selected != nullptr)
				selected->Select(false);

			hovered->Select(true);
			selected = hovered;
			MainWindow::Instance()->OpenPlanetDialog(selected);
		}
		else
		{
			mouseDown = true;
		}
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
	if (simulate)
	{
		PlanetManager::Update();
		if (selected != nullptr)
		{
			MainWindow::Instance()->UpdatePlanetPositionInDialog(selected->position);
		}
	}

	QPainter painter;
	painter.begin(this);
	painter.fillRect(rect(), background);

	PlanetManager::Render(painter);

	painter.end();
}