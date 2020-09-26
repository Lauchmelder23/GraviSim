#pragma once

#include <vector>
#include <functional>

#include <QOpenGLWidget>


class Planet;
class MainWindow;

class Screen : public QOpenGLWidget
{
public:
	Screen(QWidget* parent);

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void DeletePlanet(Planet* planet);

private slots:
	void Render();

private:
	void lmb_MakePlanet(QMouseEvent* event);
	void lmb_SelectPlanet(QMouseEvent* event);

protected:
	void paintEvent(QPaintEvent* event) override;

public:
	bool simulate = false;

private:
	bool mouseDown = false;

	std::function<void(QMouseEvent*)> lmbAction;

	QPointF mouseClickPos;

	QBrush background;
	QTimer* renderTimer;

	Planet* selected = nullptr;
	Planet* hovered = nullptr;
};