#include "mainwindow.h"
#include <QApplication>

#include"glm/vec3.hpp"
#include"glm/matrix.hpp"
#include"glm/vec2.hpp"
#include"rawvolumewidget.h"
#include<iostream>
#include<qDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::string objectModel;
    std::string format;
    int numFrames;
     glm::ivec3 dim;
     glm::vec3 spacing;
     int headerSkip;
     bool bigEndian;

     RawVolumeWidget* rawVW = new RawVolumeWidget(&w,  "ACG",
            objectModel, format, numFrames, dim, spacing, headerSkip, bigEndian);

     rawVW->show();
        if (!rawVW->exec() == QDialog::Accepted)
      w.show();


        std::cout<<"number of frames:"<<numFrames<<endl;
    return a.exec();
}
