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

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include<iostream>
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      m_program(0)
{

    m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    m_transparent = QCoreApplication::arguments().contains(QStringLiteral("--transparent"));
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);

    }



}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(500, 500);
}

QSize GLWidget::sizeHint() const
{
    return QSize(500, 500);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::cleanup()
{
    makeCurrent();
    m_logoVbo.destroy();
    m_logoVbo1.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}


void GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    m_program = new QOpenGLShaderProgram;
    //m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    //m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,m_core? ":shaders/shad.vert" : ":shaders/shad1.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, m_core ? "shaders/shad.frag" :":shaders/shad1.frag");
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);

    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");
    m_color = m_program->uniformLocation("colorv");
    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_logoVbo.create();
    m_logoVbo.bind();
    m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

//Here I should declare a new vao pointer first
    //m_vao1.create();
    //QOpenGLVertexArrayObject::Binder vaoBinder1(&m_vao1);


    // Store the vertex attribute bindings for the program.
    setupVertexAttribs(m_logoVbo);
    m_vao.release();

    m_vao1.create();
    QOpenGLVertexArrayObject::Binder vaoBinder1(&m_vao1);

    m_logoVbo1.create();
    m_logoVbo1.bind();
    m_logoVbo1.allocate(m_desk.constData(), m_desk.count() * sizeof(GLfloat));
    setupVertexAttribs(m_logoVbo1);
    m_vao1.release();

    m_vaoleg.create();
    QOpenGLVertexArrayObject::Binder vaoBinder2(&m_vaoleg);

    m_logoVboleg.create();
    m_logoVboleg.bind();
    m_logoVboleg.allocate(m_leg.constData(), m_leg.count() * sizeof(GLfloat));
    setupVertexAttribs(m_logoVboleg);
    m_vaoleg.release();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    //m_camera.translate(0, 0, -10);
    m_camera.lookAt(QVector3D(0.0f,0.0f,50.0f), QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f));
     // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();


}

void GLWidget::setupVertexAttribs(QOpenGLBuffer logoVbo)
{
    logoVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    logoVbo.release();

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_PERSPECTIVE_CORRECTION_HINT);


    m_camera.setToIdentity();
    //std::cout<< cos(m_yRot*2*M_PI/180) * sin(m_xRot*2*M_PI/180)<<" "<<sin(m_yRot*2*M_PI/180)<<" "<<cos(m_yRot*2*M_PI/180)*cos(m_xRot*2*M_PI/180)<<std::endl;
    //The norm vector of the camera is fixed, so that the scene can always viewed from above.
    double r = 200-m_zRot;

    m_camera.lookAt(QVector3D(r * cos((m_yRot-180)*2*M_PI/180) * sin(m_xRot*2*M_PI/180), r*sin((m_yRot-180)*2*M_PI/180),r*cos((m_yRot-180)*2*M_PI/180)*cos(m_xRot*2*M_PI/180)), QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f));

    m_world.setToIdentity();
/*


     m_world.translate(-1.0f,2.0f,0.0f);

     m_world.rotate(180.0f - ((ball_xRot) / 16.0f), 1, 0, 0);
     m_world.rotate(ball_yRot / 16.0f, 0, 1, 0);
     m_world.rotate(ball_zRot / 16.0f, 0, 0, 1);

     m_vao.bind();
     m_program->bind();
     m_program->setUniformValue(m_projMatrixLoc, m_proj);
     m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
     QMatrix3x3 normalMatrix = m_world.normalMatrix();
     m_program->setUniformValue(m_color, QVector3D(1.0,0.8,0.0));
     m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

     glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());
     m_vao.release();
*/


    QMatrix3x3 normalMatrix;
      for (int k=0;k<x.size();k++)
      {
         m_world.setToIdentity();
         m_world.translate(x[k]*7.5f,y[k]*7.5f,z[k]*7.5f);


         m_vao.bind();
         m_program->bind();

         m_program->setUniformValue(m_projMatrixLoc,m_proj);
              m_program->setUniformValue(m_color, QVector3D(1.0,0.8,0.0));
              normalMatrix = m_world.normalMatrix();
         m_program->setUniformValue(m_mvMatrixLoc, m_camera*m_world);
         normalMatrix = m_world.normalMatrix();
         m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
         glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());
         m_vao.release();
      }





     m_world.setToIdentity();
     //m_world.translate(1.0f,1.0f,-15.0f);

     m_vao1.bind();
     m_program->bind();
     m_program->setUniformValue(m_projMatrixLoc, m_proj);
     m_program->setUniformValue(m_mvMatrixLoc, m_camera*m_world);
     m_program->setUniformValue(m_color, QVector3D(0.0,0.0,1.0));
     normalMatrix = m_world.normalMatrix();
     m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
     glDrawArrays(GL_TRIANGLES, 0, m_desk.vertexCount());
     m_vao1.release();

     for (int k=0;k<4;k++)
     {
     m_world.setToIdentity();
     m_world.translate(leg_trans[k][0],leg_trans[k][1],leg_trans[k][2]);

     m_vaoleg.bind();
     m_program->setUniformValue(m_projMatrixLoc, m_proj);
     m_program->setUniformValue(m_mvMatrixLoc, m_camera*m_world);
     m_program->setUniformValue(m_color, QVector3D(0.0,0.5,0.5));
     normalMatrix = m_world.normalMatrix();
     m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);
     glDrawArrays(GL_TRIANGLES, 0, m_leg.vertexCount());
     m_vaoleg.release();
    }

     m_program->release();


}

void GLWidget::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
    //std::cout<<elapsed<<std::endl;
    ball_xRot = 10*(elapsed)%5520;
    ball_yRot = (elapsed)%5520;
    ball_zRot = (elapsed) % 5520;
    //emit xRotationChanged(m_xRot);
   // emit yRotationChanged(m_yRot);
    //emit zRotationChanged(m_zRot);
    update();
}


void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  /*  int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
    m_camera.rotate(0.0,0.0,-5.0f);*/
}


/*
static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";

*/
