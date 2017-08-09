

#include <dockwidget.h>
#include <QtGui/QKeyEvent>




//DockWidget::DockWidget(QString title, QWidget *parent) : QDockWidget(QString("<FONT COLOR='#ffab00' SIZE=4>%1</FONT> ").arg(title), parent) {
DockWidget::DockWidget(QString title, QWidget *parent) : QDockWidget(title, parent) {
	setObjectName(title);
setObjectName(title);

//this->setStyleSheet("background-color:   #FFFFFF;");

this->setProperty("windowOpacity", 0.5);
		// adding custom title bar to dock widget
		dockWidgetTitleBar_ = new DockWidgetTitleBar(this);
		setTitleBarWidget(dockWidgetTitleBar_);

		QObject::connect(this, SIGNAL(topLevelChanged(bool)), titleBarWidget(), SLOT(floating(bool)));
		QObject::connect(this, SIGNAL(windowTitleChanged(const QString &)), this,
			SLOT(updateWindowTitle(const QString &)));
	}

DockWidget::~DockWidget() {}

void DockWidget::showEvent(QShowEvent *showEvent) {
		raise();
		QDockWidget::showEvent(showEvent);
	}

void DockWidget::keyPressEvent(QKeyEvent *keyEvent) {
		if (keyEvent->key() == Qt::Key_Escape && isFloating()) {
			hide();
		}
		else {
			keyEvent->ignore();
		}
		QDockWidget::keyPressEvent(keyEvent);
	}

void DockWidget::setSticky(bool sticky) {
		auto titleBar = dynamic_cast<DockWidgetTitleBar *>(this->titleBarWidget());
		if (titleBar) {
			titleBar->setSticky(sticky);
		}
	}

bool DockWidget::isSticky() const { return (this->allowedAreas() != Qt::NoDockWidgetArea); }

void DockWidget::setContents(QWidget *widget) {
		QWidget *oldWidget = this->widget();
		if (oldWidget) {
			this->setWidget(nullptr);
			delete oldWidget;
		}

		this->setWidget(widget);
	}

void DockWidget::setContents(QLayout *layout) {
		QWidget *oldWidget = this->widget();
		if (oldWidget) {
			this->setWidget(nullptr);
			delete oldWidget;
		}

		QWidget *centralWidget = new QWidget();
		centralWidget->setLayout(layout);
		this->setWidget(centralWidget);
	}

void DockWidget::updateWindowTitle(const QString &str) { dockWidgetTitleBar_->setLabel(str); }
