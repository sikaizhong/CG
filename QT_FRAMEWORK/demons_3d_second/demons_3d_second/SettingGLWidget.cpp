

#include <Qtwidgets/QLayout>
#include <Qtwidgets//QFrame>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/QFrame>
#include"SettingGLWidget.h"



SettingGLWidget::SettingGLWidget(QString title, QWidget* parent)
	: DockWidget(title, parent) {
	setObjectName("SettingsWidget");
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->setStyleSheet("background-color:   #FFFFFF;");
	scrollArea_ = new QScrollArea();
	scrollArea_->setWidgetResizable(true);
	scrollArea_->setMinimumWidth(300);
	scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea_->setFrameShape(QFrame::NoFrame);
	scrollArea_->setContentsMargins(0, 0, 0, 0);
	mainWidget_ = new QWidget();
	layout_ = new QVBoxLayout(mainWidget_);
	layout_->setAlignment(Qt::AlignTop);
	layout_->setContentsMargins(0, 10, 0, 10);
	layout_->setSpacing(7);

	QFrame *frame = new QFrame();
	frame->setFrameStyle(QFrame::Raised | QFrame::Box);
	frame->setGeometry(50, -2, 100, 15);

	bt1 = new QPushButton(frame);
	bt1->setText("sunken button");
	layout_->addWidget(bt1);


	scrollArea_->setWidget(mainWidget_);

	setWidget(scrollArea_);
}

SettingGLWidget::SettingGLWidget(QWidget* parent)
	: SettingGLWidget(tr("Setting OpenGL"), parent) {}

SettingGLWidget::~SettingGLWidget() {}


