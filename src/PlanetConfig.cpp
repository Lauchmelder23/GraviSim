#include "PlanetConfig.hpp"

#include <iostream>

#include <qcolordialog.h>
#include "MainWindow.hpp"

PlanetConfig::PlanetConfig(QWidget* parent) :
	QWidget(parent), temp(nullptr)
{
	ui.setupUi(this);

	MainWindow* instance = MainWindow::Instance();

	connect(ui.name, SIGNAL(returnPressed()),
		this, SLOT(TextBoxSlot()));

	connect(ui.radius, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		instance, [instance](double d) { instance->OnRadiusChanged(d); });

	connect(ui.colour, SIGNAL(returnPressed()),
		this, SLOT(ColourTBSlot()));

	connect(ui.xPos, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		instance, [instance](double d) { instance->OnXChanged(d); });

	connect(ui.yPos, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		instance, [instance](double d) { instance->OnYChanged(d); });

	connect(ui.remove, SIGNAL(clicked()),
		instance, SLOT(OnDelete()));

	connect(ui.toggle, SIGNAL(clicked()), 
		instance, SLOT(OnToggle()));

}

void PlanetConfig::Disable()
{
	ui.radius->setDisabled(true);
	ui.colour->setDisabled(true);
	ui.xPos->setDisabled(true);
	ui.yPos->setDisabled(true);
	ui.remove->setDisabled(true);
}

void PlanetConfig::Enable()
{
	ui.radius->setDisabled(false);
	ui.colour->setDisabled(false);
	ui.xPos->setDisabled(false);
	ui.yPos->setDisabled(false);
	ui.remove->setDisabled(false);
}

void PlanetConfig::SetTitle(const QString& title)
{
	ui.name->setText(title);
}

void PlanetConfig::SetRadius(double radius)
{
	ui.radius->setValue(radius);
}

void PlanetConfig::SetColor(const QColor& color)
{
	ui.colour->setText(QString::number(color.rgb() << 8, 16));
}

void PlanetConfig::SetX(double x)
{
	ui.xPos->setValue(x);
}

void PlanetConfig::SetY(double y)
{
	ui.yPos->setValue(y);
}

void PlanetConfig::SetButtonLabel(const QString& label)
{
	ui.toggle->setText(label);
}

void PlanetConfig::ColourTBSlot()
{
	// std::cout << ui.colour->text().toStdString() << std::endl;
	MainWindow::Instance()->OnColourChanged(QColor::fromRgb(ui.colour->text().toUInt(NULL, 16)));
}

void PlanetConfig::TextBoxSlot()
{
	MainWindow::Instance()->OnNameChanged(ui.name->text());
}
