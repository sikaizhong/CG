
#ifndef WIDGET_H
#define WIDGET_H

/*
*  update me ;
*
*/


#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include<QtCharts/QChartView>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class TransferfunWidget : public QChartView
{
	Q_OBJECT

public:
	TransferfunWidget(QWidget *parent = 0);
	~TransferfunWidget();
protected:
	void resizeEvent(QResizeEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent*event);
	void keyPressEvent(QKeyEvent * event);

	void updateseries();
	void movePoint();
	void movePoint(int index);


private:
	QChart *m_chart;
	QLineSeries *m_series;

};

#endif // WIDGET_H
