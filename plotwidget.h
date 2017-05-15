#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include<QtWidgets>
#include"qcustomplot.h"

class PlotWidget: public QWidget
{
    Q_OBJECT
 public:
    PlotWidget(QWidget * parent =0);
    ~PlotWidget();
    void addGraph(QString label, QString color);
    void plotNewPoint(double x, double y);
    void removeAllGraphs();
    void setYAxisLabel(QString ylabel);
    void setXAxisLabel(QString xlabel);


private:
    void updatePlotAxesRanges();
    double getGraphMaxValue(int index);

    QCustomPlot* plot;


};


#endif // PLOTWIDGET_H
