/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
**
**  xLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    yLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);
    zLabel->setFrameStyle(QFrame::Panel | QFrame::Raised);

****************************************************************************/

#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "udp.h"
#include<vector>
int click_showTrajBtn=0;

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget;
    dataPlot = new PlotWidget;
    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    //dataPlot->plotNewPoint(1.0f,2.0f);
    connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
    connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
    connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
    connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
    connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
    connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);

    connect(timer, &QTimer::timeout,glWidget, &GLWidget::animate);


    xLabel = new QLabel();
    yLabel = new QLabel();
    zLabel = new QLabel();

    xLabel->setText("Pitch:");
    yLabel->setText("Roll:");
    zLabel->setText("Yall:");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container0 = new QHBoxLayout;

    QVBoxLayout *container = new QVBoxLayout;
    QHBoxLayout *container1 = new QHBoxLayout;
    QHBoxLayout *container2 = new QHBoxLayout;
    QHBoxLayout *container3 = new QHBoxLayout;

    container1->addWidget(xLabel);
    container1->addWidget(xSlider);
    container2->addWidget(yLabel);
    container2->addWidget(ySlider);
    container3->addWidget(zLabel);
    container3->addWidget(zSlider);
    QWidget *w1 = new QWidget;
    QWidget *w2 = new QWidget;
    QWidget *w3 = new QWidget;
    w1->setLayout(container1);
    w2->setLayout(container2);
    w3->setLayout(container3);
    container->addWidget(w1);
    container->addWidget(w2);
    container->addWidget(w3);
    container->addWidget(glWidget);


    double x = 1.123;
    double y = 2.21;
    double z = 3.323;



    QVBoxLayout *container4 = new QVBoxLayout;
    landptLabel = new QLabel();
    actionLabel = new QLabel();
    distanceLabel = new QLabel();
    landptxValue = new QLabel();
    landptyValue = new QLabel();
    landptzValue = new QLabel();

    landptxValue->setText(QString::number(x,10,4));
    landptyValue->setText(QString::number(y,10,4));
    landptzValue->setText(QString::number(z,10,4));

    actionnxValue = new QLabel();
    actionnyValue = new QLabel();
    actionnzValue = new QLabel();
    actionvxValue = new QLabel();
    actionvyValue = new QLabel();
    actionvzValue = new QLabel();
    actionnxValue->setText(QString::number(x,10,4));
    actionnyValue->setText(QString::number(y,10,4));
    actionnzValue->setText(QString::number(z,10,4));
    actionvxValue->setText(QString::number(x,10,4));
    actionvyValue->setText(QString::number(y,10,4));
    actionvzValue->setText(QString::number(z,10,4));

    QGridLayout *container_landpt = new QGridLayout;
    QGridLayout *container_an = new QGridLayout;
    QGridLayout *container_av = new QGridLayout;

    QWidget *w_landpt = new QWidget;
    QWidget *w_an = new QWidget;
    QWidget *w_av = new QWidget;

    container_landpt->addWidget(landptxValue,0,0);container_landpt->addWidget(landptyValue,0,1);container_landpt->addWidget(landptzValue,0,2);
    container_an->addWidget(actionnxValue,0,0);container_an->addWidget(actionnyValue,0,1);container_an->addWidget(actionnzValue,0,2);
    container_av->addWidget(actionvxValue,0,0);container_av->addWidget(actionvyValue,0,1);container_av->addWidget(actionvzValue,0,2);


    w_landpt->setLayout(container_landpt);
    w_an->setLayout(container_an);
    w_av->setLayout(container_av);

    landptLabel->setText("Land Point:");
    actionLabel->setText("Action:");


    distanceValue = new QLabel();
    distanceLabel->setText("Distance:");
    distanceValue->setText(QString::number(z,10,4));
    container4->addWidget(dataPlot);
    container4->addWidget(landptLabel);
    container4->addWidget(w_landpt);

    container4->addWidget(actionLabel);
    container4->addWidget(w_an);
    container4->addWidget(w_av);
    container4->addWidget(distanceLabel);
    container4->addWidget(distanceValue);

    QWidget *w = new QWidget;
    QWidget *w4 = new QWidget;
    QWidget *w5 = new QWidget;
    w4->setLayout(container);
    w5->setLayout(container4);
    container0->addWidget(w4);
    container0->addWidget(w5);
    w->setLayout(container0);
    mainLayout->addWidget(w);

    dockBtn = new QPushButton(tr("Undock"), this);
    startBtn = new QPushButton(tr("Start"),this);
    stopBtn = new QPushButton(tr("Stop"),this);
    showTrajBtn = new QPushButton(tr("show Traj"),this);
    connect(dockBtn, &QPushButton::clicked, this, &Window::dockUndock);
    connect(startBtn,&QPushButton::clicked, this, &Window::startFnc);
    connect(stopBtn,&QPushButton::clicked, this, &Window::stopFnc);
    connect(showTrajBtn,&QPushButton::clicked,this,&Window::showTrajFnc);

    mainLayout->addWidget(dockBtn);

    QHBoxLayout * container_button = new QHBoxLayout;
    container_button->addWidget(startBtn);
    container_button->addWidget(stopBtn);
    container_button->addWidget(showTrajBtn);
    QWidget *w_button = new QWidget;
    w_button->setLayout(container_button);
    mainLayout->addWidget(w_button);
    setLayout(mainLayout);
    xSlider->setValue(0);
    ySlider->setValue(180);
    zSlider->setValue(150);
    dataPlot->addGraph("a","red");
    setWindowTitle(tr("Hello GL"));
    time.start();
    client->InitSocket();
    client->start();

}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360);
    slider->setSingleStep(1);
    slider->setPageStep(15);
    slider->setTickInterval(15);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}


void Window::dockUndock()
{
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 3,
             QApplication::desktop()->height() / 2 - height() / 3);
        dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}

void Window::startFnc()
{

    timer->start(50);
    client->send();
    client->ClientStart=1;
 std::cout<<"start"<<std::endl;
}

void Window::stopFnc()
{
    timer->stop();
    client->ClientStart=0;
    std::cout<<"stop"<<std::endl;
}

void Window::showTrajFnc()
{
    client->getPositionx(x);
    client->getPositiony(z);
    client->getPositionz(y);
    x.swap(glWidget->x);
    y.swap(glWidget->y);
    z.swap(glWidget->z);
    client->getAction_norm(normx, normy, normz);
    client->getAction_vel(velx, vely,velz);
    std::cout<<"norm"<<normy<<std::endl;
    addPoint();

    if (!click_showTrajBtn){
        showTrajBtn->setText(tr("don't show Traj"));
        show();
        click_showTrajBtn=1;
    }
    else
    {

        showTrajBtn->setText(tr("show Traj"));
        show();
        click_showTrajBtn=0;
    }


}

void Window::addPoint()
{
    std::cout<<glWidget->x.size()<<std::endl;

    if (glWidget->x.size())
    {
    int l = glWidget->x.size();
    ptx.push_back(glWidget->x[l-1]);
    pty.push_back(glWidget->z[l-1]);
    actionnxValue->setText(QString::number(normx,10,4));
    actionnyValue->setText(QString::number(normy,10,4));
    actionnzValue->setText(QString::number(normz,10,4));
    actionvxValue->setText(QString::number(velx,10,4));
    actionvyValue->setText(QString::number(vely,10,4));
    actionvzValue->setText(QString::number(velz,10,4));
    landptxValue->setText(QString::number(glWidget->x[l-1],10,4));
    landptyValue->setText(QString::number(glWidget->z[l-1],10,4));
    landptzValue->setText(QString::number(glWidget->y[l-1],10,4));
    l = ptx.size();
    for (int i=0;i<l;i++)
    {
        dataPlot->plotNewPoint(ptx[i],pty[i]);

    }
    }
     std::cout<<x.size()<<std::endl;


}
