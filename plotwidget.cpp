#include "plotwidget.h"
#include <iterator>
#include<iostream>
PlotWidget::PlotWidget(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout;
    plot = new QCustomPlot;
    mainLayout->addWidget(plot);
    plot->xAxis->setLabel("x-axis");
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
    plot->legend->setVisible(true);
    plot->yAxis->setRangeLower(-2);
    plot->yAxis->setRangeUpper(2);

    plot->xAxis->setRangeLower(-2);
    plot->xAxis->setRangeUpper(2);
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(plot, "landpt coordinates"));

    this->setLayout(mainLayout);
    this->setMinimumHeight(300);
}

PlotWidget::~PlotWidget()
{
   delete plot;
}

void PlotWidget::addGraph(QString label, QString color)
{
    auto graph = plot->addGraph();
    graph->setName(label);    

    graph->setPen(QPen(QColor(color)));
    graph->setPen(QPen());
}

void PlotWidget::plotNewPoint(double x, double y)
{
    int graphNo = 0;
    plot->graph(0)->addData(x,y);
    plot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,4));
    plot->replot();    std::cout <<x<<" "<<y<< std::endl;
}


void PlotWidget::removeAllGraphs()
{
    plot->clearGraphs();
}

void PlotWidget::setXAxisLabel(QString xlabel)
{
    plot->xAxis->setLabel(xlabel);
}

void PlotWidget::setYAxisLabel(QString ylabel)
{
    plot->yAxis->setLabel(ylabel);
}
