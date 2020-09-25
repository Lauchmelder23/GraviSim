#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	MainWindow* window = MainWindow::Instance();
	window->show();
	
	return app.exec();
}