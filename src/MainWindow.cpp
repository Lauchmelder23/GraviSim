#include "MainWindow.hpp"

#include "Screen.hpp"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);

	Screen* screen = new Screen(this);
	ui.layout->addWidget(screen, 0, 0);
}