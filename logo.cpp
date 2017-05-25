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

#include "logo.h"
#include <qmath.h>
#include<iostream>
Logo::Logo()
    : m_count(0)
{
    m_data.resize(1000000);

    const GLfloat x1 = +0.06f;
    const GLfloat y1 = -0.14f;
    const GLfloat x2 = +0.14f;
    const GLfloat y2 = -0.06f;
    const GLfloat x3 = +0.08f;
    const GLfloat y3 = +0.00f;
    const GLfloat x4 = +0.30f;
    const GLfloat y4 = +0.22f;

    //quad(x1, y1, x2, y2, y2, x2, y1, x1);
    //quad(x3, y3, x4, y4, y4, x4, y3, x3);
/*
    extrude(x1, y1, x2, y2);
    extrude(x2, y2, y2, x2);
    extrude(y2, x2, y1, x1);
    extrude(y1, x1, x1, y1);
    extrude(x3, y3, x4, y4);
    extrude(x4, y4, y4, x4);
    extrude(y4, x4, y3, x3);
*/
    const int NumSectors = 100;
    const int NumSectors1 = 100;
    double r = 0.3f;

    for (int j=0;j<=NumSectors1;j++)
    {
        GLfloat phi = (-0.5 + double(j) / double(NumSectors1)) * M_PI ;
        std::cout<<phi<<std::endl;
        GLfloat phi1 = (-0.5 + double(j+1) / double(NumSectors1)) * M_PI ;
        GLfloat phiSin = qSin(phi); GLfloat phiCos = qCos(phi);
        GLfloat phi1Sin = qSin(phi1);GLfloat phi1Cos = qCos(phi1);

    for (int i = 0; i<= NumSectors; i++)
    {
        GLfloat angle =(i*2*M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        const GLfloat x5 = r * angleCos * phiCos;
        const GLfloat y5 = r * angleSin *phiCos;
        const GLfloat z5 = r * phiSin;
        const GLfloat x6 = r * angleCos * phi1Cos;
        const GLfloat y6 = r * angleSin * phi1Cos;
        const GLfloat z6 = r * phi1Sin;

        angle = ((i+1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        const GLfloat x7 = r * angleCos * phiCos;
        const GLfloat y7 = r * angleSin *phiCos;
        const GLfloat z7 = r * phiSin;
        const GLfloat x8 = r * angleCos * phi1Cos;
        const GLfloat y8 = r * angleSin * phi1Cos;
        const GLfloat z8 = r * phi1Sin;
         //std::cout<<x5<< " "<<x6<< " "<<x7<< " "<<x8<< std::endl;
         //std::cout<<y5<< " "<<y6<< " "<<y7<< " "<<y8<< std::endl;
         //std::cout<<z5<< " "<<z6<< " "<<z7<< " "<<z8<< std::endl;
        quad1(x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);

    }

    }
/*
    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        const GLfloat x5 = 0.30f * angleSin;
        const GLfloat y5 = 0.30f * angleCos;
        const GLfloat x6 = 0.20f * angleSin;
        const GLfloat y6 = 0.20f * angleCos;

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        const GLfloat x7 = 0.20f * angleSin;
        const GLfloat y7 = 0.20f * angleCos;
        const GLfloat x8 = 0.30f * angleSin;
        const GLfloat y8 = 0.30f * angleCos;

        quad(x5, y5, x6, y6, x7, y7, x8, y8);

        extrude(x6, y6, x7, y7);
        extrude(x8, y8, x5, y5);
    }
*/
}

void Logo::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
    //std::cout<<"m_count:"<<m_count<<std::endl;
}



void Logo::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.05f), n);
    add(QVector3D(x4, y4, -0.05), n);
    add(QVector3D(x2, y2, -0.05), n);

    add(QVector3D(x3, y3, -0.05), n);
    add(QVector3D(x2, y2, -0.05), n);
    add(QVector3D(x4, y4, -0.05), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, -0.05), n);
    add(QVector3D(x1, y1, -0.05), n);
    add(QVector3D(x2, y2, -0.05), n);

    add(QVector3D(x2, y2, -0.05), n);
    add(QVector3D(x3, y3, -0.05), n);
    add(QVector3D(x4, y4, -0.05), n);
}

void Logo::quad1(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, z4-z1), QVector3D(x2 - x1, y2 - y1, z2-y1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x2, y2, z2), n);

    n = QVector3D::normal(QVector3D(x1 - x3, y1 - y3, z1-z3), QVector3D(x4 - x3, y4 - y3, z4-z3));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);


/*
    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);*/

}


void Logo::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +0.05f), n);
    add(QVector3D(x1, y1, -0.05f), n);
    add(QVector3D(x2, y2, +0.05f), n);

    add(QVector3D(x2, y2, -0.05f), n);
    add(QVector3D(x2, y2, +0.05f), n);
    add(QVector3D(x1, y1, -0.05f), n);
}
