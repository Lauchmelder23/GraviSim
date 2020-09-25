#pragma once

#include <QWidget>

#include "ui_PlanetConfig.h"

class PlanetConfig : public QWidget
{
public:
	PlanetConfig(QWidget* parent);

	void Disable();
	void Enable();

	void SetTitle(const QString& title);
	void SetRadius(double radius);
	void SetX(double x);
	void SetY(double y);

private:
	Ui::Form ui;
};