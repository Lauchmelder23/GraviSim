#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

#include "Planet.hpp"
#include "PlanetConfig.hpp"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	static MainWindow* Instance();

public:
	void OpenPlanetDialog(Planet* planet);
	void ClosePlanetDialog();

public slots:
	void OnRadiusChanged(double radius);
	void OnXChanged(double x);
	void OnYChanged(double y);

private:
	MainWindow();
	void Setup();

private:
	Ui::MainWindow ui;

	Planet* activePlanet;
	static MainWindow* instance;
};
