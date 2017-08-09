/*********************************************************************************
*
* Inviwo - Interactive Visualization Workshop
*
* Copyright (c) 2012-2016 Inviwo Foundation
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*********************************************************************************/

#include"DockWidgetTitleBar.h"


#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStyleOption>
#include <QtGui/QPainter>





DockWidgetTitleBar::DockWidgetTitleBar(QWidget *parent)
		: QWidget(parent)
		, parent_(dynamic_cast<QDockWidget *>(parent))
		, allowedDockAreas_(parent_->allowedAreas())
	{
		this->setStyleSheet("background-color:  #F0F8FF;");
		label_ = new QLabel(parent->windowTitle());
		label_->setStyleSheet("QWidget { padding-left: 3px; background-color: 'transparent'; }");

		stickyBtn_ = new QToolButton();
		QIcon icon;
		icon.addPixmap(QPixmap("./resources/stylesheets/images/dock-unsticky.png"), QIcon::Normal, QIcon::Off);
		icon.addPixmap(QPixmap("./resources/stylesheets/images/dock-sticky.png"), QIcon::Normal, QIcon::On);
	
		stickyBtn_->setIcon(icon);
		stickyBtn_->setCheckable(true);
		stickyBtn_->setChecked(true);
		stickyBtn_->setObjectName("dockBtn");

	
		floatBtn_ = new QToolButton();
		QIcon icon2;
		icon2.addPixmap(QPixmap("./resources/stylesheets/images/dock-docked.png"), QIcon::Normal, QIcon::Off);
		icon2.addPixmap(QPixmap("./resources/stylesheets/images/dock-floating.png"), QIcon::Normal, QIcon::On);
		floatBtn_->setIcon(icon2);
		floatBtn_->setCheckable(true);
		floatBtn_->setChecked(parent_->isFloating());
		floatBtn_->setObjectName("dockBtn");

		QToolButton *closeBtn = new QToolButton();
		closeBtn->setIcon(QIcon("./resources/stylesheets/images/close.png"));
		closeBtn->setObjectName("dockBtn");

		QHBoxLayout *layout = new QHBoxLayout(this);
		layout->addWidget(label_, 1);
		layout->addWidget(stickyBtn_);
		layout->addWidget(floatBtn_);
		layout->addWidget(closeBtn);
		layout->setSpacing(1);
		layout->setMargin(1);

		this->setLayout(layout);

		QObject::connect(stickyBtn_, SIGNAL(toggled(bool)), this, SLOT(stickyBtnToggled(bool)));
		QObject::connect(floatBtn_, SIGNAL(clicked()), this, SLOT(floatBtnClicked()));
		QObject::connect(closeBtn, SIGNAL(clicked()), parent_, SLOT(close()));
	}

DockWidgetTitleBar::~DockWidgetTitleBar() {}

void DockWidgetTitleBar::paintEvent(QPaintEvent *) {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		//style()->drawControl(QStyle::CE_DockWidgetTitle, &opt, &p, this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

void DockWidgetTitleBar::setLabel(const QString &str) {
		label_->setText(str);
	}

void DockWidgetTitleBar::stickyBtnToggled(bool toggle) {
		if (toggle) {
			// docking allowed, restore docking areas
			parent_->setAllowedAreas(allowedDockAreas_);
		}
		else {
			// no docking, disable all areas
			parent_->setAllowedAreas(Qt::NoDockWidgetArea);
		}
	}

void DockWidgetTitleBar::floatBtnClicked() {
		parent_->setFloating(!parent_->isFloating());
	}

void DockWidgetTitleBar::floating(bool floating) {
		floatBtn_->setChecked(floating);
	}

void DockWidgetTitleBar::setSticky(bool toggle) {
		stickyBtn_->setChecked(toggle);
	}

bool DockWidgetTitleBar::isSticky() const {
		return stickyBtn_->isChecked();
	}


