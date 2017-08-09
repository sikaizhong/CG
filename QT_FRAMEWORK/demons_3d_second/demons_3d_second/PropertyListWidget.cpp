#include "PropertyListWidget.h"


PropertyListWidget::PropertyListWidget(QWidget* parent) : DockWidget(tr("Properties"),parent)
{
	setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->setStyleSheet("background-color:   #FFFFFF;");
	QSizePolicy sp(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	sp.setVerticalStretch(1);
	sp.setHorizontalStretch(1);
	setSizePolicy(sp);

	scrollArea_ = new QScrollArea(this);
	scrollArea_->setWidgetResizable(true);
	scrollArea_->setMinimumWidth(320);
	scrollArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	scrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


	scrollArea_->setFrameShape(QFrame::NoFrame);
	scrollArea_->setContentsMargins(0, 5, 0, 5);

	listWidget_ = new QWidget(this);
	listLayout_ = new QVBoxLayout();
	listWidget_->setLayout(listLayout_);
	listLayout_->setAlignment(Qt::AlignTop);

	scrollArea_->setWidget(listWidget_);

	
	setWidget(scrollArea_);

}


PropertyListWidget::~PropertyListWidget()
{
}
