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
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include "plotwidget.h"
#include "udp.h"
class QSlider;
class QPushButton;
class QLabel;
class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT


public:

    Window(MainWindow *mw);
Client* client = new Client;
protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void plotChanged(double, double);

private slots:
    void dockUndock();
    void startFnc();
    void stopFnc();
    void showTrajFnc();
    void addPoint();


private:

    QSlider *createSlider();

    PlotWidget *dataPlot;

    GLWidget *glWidget;
    GLWidget *glWidget1;
    QLabel *xLabel;
    QLabel *yLabel;
    QLabel *zLabel;

    QLabel *landptLabel;
    QLabel *actionLabel;
    QLabel *distanceLabel;

    QLabel *landptxValue;
    QLabel *landptyValue;
    QLabel *landptzValue;


    QLabel *actionnxValue;
    QLabel *actionnyValue;
    QLabel *actionnzValue;
    QLabel *actionvxValue;
    QLabel *actionvyValue;
    QLabel *actionvzValue;

    QLabel *distanceValue;
    QTimer * timer = new QTimer(this);
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QPushButton *dockBtn;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *showTrajBtn;
    MainWindow *mainWindow;
    QTime time;
    std::vector<double> x,y,z;
    std::vector<double> ptx;
    std::vector<double> pty;
    double normx, normy, normz;
    double velx, vely, velz;
};

#endif
/*
#ifndef WINDOW_H
#define WINDOW_H
#include <QOpenGLWindow>
#include <QOpenGLFunctions>

class Window:public QOpenGLWindow, protected QOpenGLFunctions

{
  Q_OBJECT

public:

    ~Window();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();

private:
    void printContextInformation();

};
#endif // WINDOW_H
*/
