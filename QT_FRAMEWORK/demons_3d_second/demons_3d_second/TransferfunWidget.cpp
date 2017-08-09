/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "TransferfunWidget.h"
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QValueAxis>


QT_CHARTS_USE_NAMESPACE

TransferfunWidget::TransferfunWidget(QWidget *parent) :QChartView(parent)
{
	//this->setFixedWidth(640);
	//this->setFixedHeight(300);
	m_series = new QLineSeries();
	// chart
	m_chart = new QChart;
	m_chart->setMinimumSize(840, 680);
	m_chart->setTitle("SET TRANSFER FUNCTION");
	//m_chart->legend()->hide();

	QValueAxis *axisX = new QValueAxis;
	axisX->setRange(0, 255);
	axisX->setLinePenColor(Qt::red);
	axisX->setTitleText("Grey Level");

	axisX->setMinorTickCount(5);
	QValueAxis *axisY = new QValueAxis;
	axisY->setRange(0, 1);
	axisY->setLinePenColor(Qt::red);
	axisY->setTitleText("Vaule");

	m_chart->addAxis(axisX, Qt::AlignBottom);
	m_chart->addAxis(axisY, Qt::AlignLeft);
	//m_chart->createDefaultAxes();
	m_chart->setAcceptHoverEvents(true);
	m_chart->addSeries(m_series);
	setRenderHint(QPainter::Antialiasing);

	this->setChart(m_chart);

	this->setMouseTracking(true);

}

void TransferfunWidget::updateseries()
{
	int size = m_series->count();
	QPointF t1 = m_series->at(size - 1);
	for (int i = 0; i<size; i++)
	{

		QPointF t2 = m_series->at(i);


		if (t1.rx()<t2.rx()) // need to delete all of them;
		{
			//std::cout<<  t1.rx() << "++" << t2.rx();
			m_series->removePoints(i, size - i - 1);
			break;
		}
	}
}

void TransferfunWidget::movePoint()
{

}

void TransferfunWidget::movePoint(int index)
{

}


void TransferfunWidget::resizeEvent(QResizeEvent *event)
{

}

void TransferfunWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void TransferfunWidget::mousePressEvent(QMouseEvent*event)
{
	if (m_chart->mapToValue(event->pos()).x()<0 || m_chart->mapToValue(event->pos()).x()>1 || m_chart->mapToValue(event->pos()).y()<0 || m_chart->mapToValue(event->pos()).y()>1)
		return;
	m_series->append(m_chart->mapToValue(event->pos()).x(), m_chart->mapToValue(event->pos()).y());

	updateseries();
	// m_series->clear();
	//qDebug() << m_chart->mapToValue(event->pos()).x() << " " << m_chart->mapToValue(event->pos()).y();
	//qDebug() << m_series->count();
}


void TransferfunWidget::keyPressEvent(QKeyEvent * event)
{
	if (event->key()&Qt::Key_Alt)
	{
		m_series->clear();
	}
}
TransferfunWidget::~TransferfunWidget()
{

}
