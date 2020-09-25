#include "PlanetConfig.hpp"

#include <qcolordialog.h>
#include "MainWindow.hpp"

PlanetConfig::PlanetConfig(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);

	ui.color = new QColorDialog(this);

	MainWindow* instance = MainWindow::Instance();

	connect(ui.radius, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		instance, [instance](double d) { instance->OnRadiusChanged(d); });

	connect(ui.xPos, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		instance, [instance](double d) { instance->OnXChanged(d); });

	connect(ui.yPos, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		instance, [instance](double d) { instance->OnYChanged(d); });

}

void PlanetConfig::Disable()
{
	ui.radius->setDisabled(true);
	ui.xPos->setDisabled(true);
	ui.yPos->setDisabled(true);
}

void PlanetConfig::Enable()
{
	ui.radius->setDisabled(false);
	ui.xPos->setDisabled(false);
	ui.yPos->setDisabled(false);
}

void PlanetConfig::SetTitle(const QString& title)
{
	ui.name->setText(title);
}

void PlanetConfig::SetRadius(double radius)
{
	ui.radius->setValue(radius);
}

void PlanetConfig::SetX(double x)
{
	ui.xPos->setValue(x);
}

void PlanetConfig::SetY(double y)
{
	ui.yPos->setValue(y);
}
