#pragma once

#include <vector>

#include <QOpenGLWidget>

#include "Planet.hpp"

class Screen : public QOpenGLWidget
{
public:
	Screen(QWidget* parent);

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void Render();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	bool mouseDown = false;
	QPointF mouseClickPos;

	QBrush background;
	QTimer* renderTimer;

	std::vector<Planet*> planets;
};