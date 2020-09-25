#pragma once

#include <QWidget>

#include "ui_PlanetConfig.h"

class PlanetConfig : public QWidget
{
	Q_OBJECT

public:
	PlanetConfig(QWidget* parent);

	void Disable();
	void Enable();

	void SetTitle(const QString& title);
	void SetRadius(double radius);
	void SetColor(const QColor& color);
	void SetX(double x);
	void SetY(double y);

	void SetButtonLabel(const QString& label);

public slots:
	void TextBoxSlot();
	void ColourTBSlot();

private:
	Ui::Form ui;
	QWidget* temp;
};