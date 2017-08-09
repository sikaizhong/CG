#include "ConsoleWidget.h"

#define info 1
#define rst 2
#include<string>
#include<QtGui/QFontDataBase>
#include<QtWidgets/QVBoxLayout>

ConsoleWidget::ConsoleWidget( QWidget* parent) :DockWidget(tr("Console"),parent)
{
	this->setStyleSheet("background-color:   #F5F5F5;");
	textField_ = new QTextEdit(this);
	textField_->setReadOnly(true);
	textField_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	textField_->setContextMenuPolicy(Qt::CustomContextMenu);
	const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
	textField_->setFont(fixedFont);

	textcolor = QColor(255, 113, 0);
	textField_->setTextColor(textcolor);

   // clearLabel_=new QLabel(tr("Clear"));

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(textField_);

	layout->setContentsMargins(3, 0, 0, 3);

	// why?
	QWidget* w = new QWidget();
	w->setLayout(layout);
	setWidget(w);
	

}


ConsoleWidget::~ConsoleWidget()
{
}


void ConsoleWidget::LogMessage( QString message)
{
	textField_->append(message);
	QTextCursor c = textField_->textCursor();
	c.movePosition(QTextCursor::End);
	textField_->setTextCursor(c);
}

void ConsoleWidget::Message()

{
	LogMessage(QString("hello"));
}

void ConsoleWidget::clear(){
	textField_->clear();
}