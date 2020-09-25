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
	ui.config->SetTitle(planet->name);
	ui.config->SetRadius(planet->radius);
	ui.config->SetColor(planet->GetColor());
	ui.config->SetX(planet->position.rx());
	ui.config->SetY(planet->position.ry());

	activePlanet = planet;
}

void MainWindow::ClosePlanetDialog()
{
	activePlanet = nullptr;

	ui.config->SetTitle("No planet selected");
	ui.config->Disable();
	ui.config->SetColor(QColor(0, 0, 0, 0));
	ui.config->SetRadius(0.f);
	ui.config->SetX(0.f);
	ui.config->SetY(0.f);
}

void MainWindow::OnNameChanged(const QString& name)
{
	if (activePlanet != nullptr)
		activePlanet->name = name;
}

void MainWindow::OnRadiusChanged(double radius)
{
	if(activePlanet != nullptr)
		activePlanet->radius = radius;
}

void MainWindow::OnColourChanged(const QColor& color)
{
	if (activePlanet != nullptr)
		activePlanet->SetColor(color);
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

void MainWindow::OnToggle()
{
	isSimulating = !isSimulating;
	ui.config->SetButtonLabel((isSimulating) ? "Stop Simulation" : "Start Simulation");
}
