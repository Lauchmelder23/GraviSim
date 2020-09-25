#include "MainWindow.hpp"

#include "Screen.hpp"

MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::Instance()
{
	if (instance == nullptr)
	{
		instance = new MainWindow();
		instance->Setup();
	}

	return instance;
}

MainWindow::MainWindow() :
	QMainWindow(Q_NULLPTR), activePlanet(nullptr)
{
}

void MainWindow::Setup()
{
	ui.setupUi(this);
	ClosePlanetDialog();
}

void MainWindow::OpenPlanetDialog(Planet* planet)
{
	activePlanet = nullptr;

	ui.config->Enable();
	ui.config->SetTitle("Planets don't have names yet");
	ui.config->SetRadius(planet->radius);
	ui.config->SetX(planet->position.rx());
	ui.config->SetY(planet->position.ry());

	activePlanet = planet;
}

void MainWindow::ClosePlanetDialog()
{
	activePlanet = nullptr;

	ui.config->SetTitle("No planet selected");
	ui.config->Disable();
	ui.config->SetRadius(0.f);
	ui.config->SetX(0.f);
	ui.config->SetY(0.f);
}

void MainWindow::OnRadiusChanged(double radius)
{
	if(activePlanet != nullptr)
		activePlanet->radius = radius;
}

void MainWindow::OnXChanged(double x)
{
	if (activePlanet != nullptr)
		activePlanet->position.rx() = x;
}

void MainWindow::OnYChanged(double y)
{
	if (activePlanet != nullptr)
		activePlanet->position.ry() = y;
}
