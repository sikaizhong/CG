#ifndef CONSOLEWIDGET_
#define CONSOLEWIDGET_

#include"DockWidget.h"
#include<QtCore/QString>
#include"QtWidgets\QTextEdit"
#include<QtWidgets/QLabel>
#include<QtCore/qstring.h>

enum class LogLevel : int { Info, rst };
class ConsoleWidget : public DockWidget  //  bug, maybe too many lines
{

	Q_OBJECT
public:
	QTextEdit* textField_;
	QColor  textcolor;

	QLabel* clearLabel_;
	//LogLevel LVL;


	public slots:
    void LogMessage( QString message);
	void Message();
	void clear();

public:
	ConsoleWidget(QWidget* parent);
	~ConsoleWidget();
};


#endif
