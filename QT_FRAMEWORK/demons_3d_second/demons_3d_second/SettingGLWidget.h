

#ifndef SettingGLWidget_H
#define SettingGLWidget_H

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtCore/QString>
#include <QtWidgets/QScrollArea>
#include<QtWidgets/qpushbutton.h>
#include"DockWidget.h"


class  SettingGLWidget : public DockWidget {

	Q_OBJECT
	public:
		SettingGLWidget(QWidget* parent);
		SettingGLWidget(QString title, QWidget* parent);
		~SettingGLWidget();

		//virtual void updateSettingsWidget();

	public slots:

 public: 
	 QPushButton* bt1;
		
	protected:
		QVBoxLayout* layout_ = nullptr;
		QWidget* mainWidget_ = nullptr;
		QScrollArea* scrollArea_ = nullptr;
};

#endif //SettingGLWidget_H