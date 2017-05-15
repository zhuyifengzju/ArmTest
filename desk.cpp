#include "desk.h"
#include <qmath.h>

Desk::Desk()
    : m_count(0)
{
    double l = 20.7f;
    double h = 0.5f;
    m_data.resize(1000000);
    width = 11.475f;
    const GLfloat x1 = +l/2;
    const GLfloat y1 = -h/2;
    const GLfloat x2 = +l/2;
    const GLfloat y2 = +h/2;



    const GLfloat x3 = +0.08f;
    const GLfloat y3 = +0.00f;
    const GLfloat x4 = +0.30f;
    const GLfloat y4 = +0.22f;

    quad(x1, y1, x2, y2, -x1, y2, -x2, y1);
    //quad(x3, y3, x4, y4, y4, x4, y3, x3);

    extrude(x1, y1, x2, y2);
    extrude(x2, y2, -x1, y2);
    extrude(-x1, y2, -x2, y1);
    extrude(-x2, y1, x1, y1);
    //extrude(x3, y3, x4, y4);
   // extrude(x4, y4, y4, x4);
    //extrude(y4, x4, y3, x3);
    const int NumSectors = 100;
    const int NumSectors1 = 100;




    }



void Desk::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void Desk::quad1(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);



}

void Desk::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -width), n);
    add(QVector3D(x4, y4, -width), n);
    add(QVector3D(x2, y2, -width), n);

    add(QVector3D(x3, y3, -width), n);
    add(QVector3D(x2, y2, -width), n);
    add(QVector3D(x4, y4, -width), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, width), n);
    add(QVector3D(x1, y1, width), n);
    add(QVector3D(x2, y2, width), n);

    add(QVector3D(x2, y2, width), n);
    add(QVector3D(x3, y3, width), n);
    add(QVector3D(x4, y4, width), n);
}

void Desk::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +width), n);
    add(QVector3D(x1, y1, -width), n);
    add(QVector3D(x2, y2, +width), n);

    add(QVector3D(x2, y2, -width), n);
    add(QVector3D(x2, y2, +width), n);
    add(QVector3D(x1, y1, -width), n);
}
