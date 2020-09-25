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
	void OnNameChanged(const QString& name);
	void OnRadiusChanged(double radius);
	void OnColourChanged(const QColor& color);
	void OnXChanged(double x);
	void OnYChanged(double y);
	void OnDelete();
	void OnToggle();

private:
	MainWindow();
	void Setup();

private:
	Ui::MainWindow ui;

	bool isSimulating = false;

	Planet* activePlanet;
	static MainWindow* instance;
};
