#include "mainwindow.h"
#include <QtWidgets/QApplication>

#include"glm/vec3.hpp"
#include"glm/matrix.hpp"
#include"glm/vec2.hpp"
#include"rawvolumewidget.h"
#include<iostream>

using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow mainwindow;
	mainwindow.show();


	
	return a.exec();
}
