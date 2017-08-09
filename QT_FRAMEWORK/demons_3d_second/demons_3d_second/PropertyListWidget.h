#pragma once
#include"DockWidget.h"
#include"QtWidgets/QVBoxLayout"
#include"QtWidgets/qscrollarea.h"
class PropertyListWidget : public DockWidget
{
	Q_OBJECT

public :
	QVBoxLayout* listLayout_;
	QWidget* listWidget_;
	QScrollArea* scrollArea_;
public:
	PropertyListWidget(QWidget* parent);
	~PropertyListWidget();
};

