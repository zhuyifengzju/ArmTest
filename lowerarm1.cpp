#include "lowerarm1.h"
#include <qmath.h>
#include<vector>
#include<iostream>
bool LowerArm1::loadOBJ(
        const char * path,
        std::vector<QVector3D> & out_vertices,

        std::vector<QVector3D> & out_normals
){
        printf("Loading OBJ file %s...\n", path);

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<QVector3D> temp_vertices;

        std::vector<QVector3D> temp_normals;


        FILE * file = fopen(path, "r");
        if( file == NULL ){
                printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
                return false;
        }

        float tx,ty,tz;
        while( 1 ){

                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                std::cout<<res<<std::endl;
                if (res == EOF)

                        break; // EOF = End Of File. Quit the loop.

                // else : parse lineHeader

                if ( strcmp( lineHeader, "v" ) == 0 ){
                    std::cout<<"Get v"<<std::endl;
                        QVector3D vertex;
                        fscanf(file, "%f %f %f\n", &tx, &ty, &tz );
                        vertex.setX(tx);
                        vertex.setY(ty);
                        vertex.setZ(tz);

                        temp_vertices.push_back(vertex);
                }
                else if ( strcmp( lineHeader, "vn" ) == 0 ){
                    std::cout<<"Get vn"<<std::endl;
                        QVector3D normal;
                        fscanf(file, "%f %f %f\n", &tx, &ty, &tz );
                        normal.setX(tx);
                        normal.setY(ty);
                        normal.setZ(tz);
                        temp_normals.push_back(normal);
                }else if ( strcmp( lineHeader, "f" ) == 0 ){
                    std::cout<<"Get f"<<std::endl;
                        std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                        int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                        if (matches != 6){
                                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                                return false;
                        }
                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                }else{
                        std::cout<<"Probably Comment"<<std::endl;
                        // Probably a comment, eat up the rest of the line
                        char stupidBuffer[1000];
                        fgets(stupidBuffer, 1000, file);
                }

}


        // For each vertex of each triangle
        for( unsigned int i=0; i<vertexIndices.size(); i++ ){

                // Get the indices of its attributes
                unsigned int vertexIndex = vertexIndices[i];
                unsigned int normalIndex = normalIndices[i];

                // Get the attributes thanks to the index
                QVector3D vertex = temp_vertices[ vertexIndex-1 ];
                QVector3D normal = temp_normals[ normalIndex-1 ];

                // Put the attributes in buffers
                out_vertices.push_back(vertex);
                out_normals .push_back(normal);

        }

        return true;

}


LowerArm1::LowerArm1()
    : m_count(0)
{
    double l = 20.7f;
    double h = 0.5f;
    m_data.resize(1000000);
    width = 11.475f;
    std::vector<QVector3D> vertices;

    std::vector<QVector3D> normals;
    bool res = loadOBJ("/home/zhuyifeng/Documents/graph/meshes/arm_test/LowerArm1.obj", vertices, normals);
    std::cout<<"Size:"<<vertices.size()<<std::endl;
    for(int i=0; i<vertices.size()-2; i=i+3)
    {
        std::cout << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z()<<std::endl;
        quad1(vertices[i].x(),vertices[i].y(),vertices[i].z(),
              vertices[i+1].x(),vertices[i+1].y(),vertices[i+1].z(),
              vertices[i+2].x(),vertices[i+2].y(),vertices[i+2].z(),
              normals[i],normals[i+1],normals[i+2]);
    }
/*
    const GLfloat x1 = +l/2;
    const GLfloat y1 = -h/2;
    const GLfloat x2 = +l/2;
    const GLfloat y2 = +h/2;



    const GLfloat x3 = +0.08f;
    const GLfloat y3 = +0.00f;
    const GLfloat x4 = +0.30f;
    const GLfloat y4 = +0.22f;
*/
    //quad(x1, y1, x2, y2, -x1, y2, -x2, y1);
    //quad(x3, y3, x4, y4, y4, x4, y3, x3);

    //extrude(x1, y1, x2, y2);
    //extrude(x2, y2, -x1, y2);
    //extrude(-x1, y2, -x2, y1);
    //extrude(-x2, y1, x1, y1);
    //extrude(x3, y3, x4, y4);
   // extrude(x4, y4, y4, x4);
    //extrude(y4, x4, y3, x3);




    }



void LowerArm1::add(const QVector3D &v, const QVector3D &n)
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

void LowerArm1::quad1(GLfloat x1, GLfloat y1,GLfloat z1,
                 GLfloat x2, GLfloat y2, GLfloat z2,
                 GLfloat x3, GLfloat y3, GLfloat z3,
                QVector3D n1, QVector3D n2, QVector3D n3)
{
    QVector3D n = QVector3D::normal(QVector3D(x2 - x1, x2 - y1, z2-z1), QVector3D(x3 - x1, y3 - y1, z3-z1));

    add(QVector3D(x1*100.0, y1*100.0, z1*100.0), n1);

    add(QVector3D(x2*100.0, y2*100.0, z2*100.0), n2);
    add(QVector3D(x3*100.0, y3*100.0, z3*100.0), n3);
    //add(QVector3D(x1, y1, z1), n);
    //add(QVector3D(x3, y3, z3), n);
    //add(QVector3D(x4, y4, z4), n);



}

void LowerArm1::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
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

void LowerArm1::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +width), n);
    add(QVector3D(x1, y1, -width), n);
    add(QVector3D(x2, y2, +width), n);

    add(QVector3D(x2, y2, -width), n);
    add(QVector3D(x2, y2, +width), n);
    add(QVector3D(x1, y1, -width), n);
}
