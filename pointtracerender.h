#ifndef POINTTRACERENDER_H
#define POINTTRACERENDER_H

#include "batch.h"
#include <QGL>
//#include <QGLFunctions>
#include <QGLShaderProgram>
#include <vector>

using std::vector;

class PointTraceRender// : protected QGLFunctions
{
public:
    PointTraceRender();
    ~PointTraceRender();

    void SetupRC();
    void Update();

    void Render(const QMatrix4x4& projection, const QQuaternion& rotation);

private:
    Batch triangleBatch;
    //Batch sysbomBatch;

    QGLShaderProgram program;

private:
    //float *pVerts;
    vector<GLfloat> vVerts;
    int nVerts;
};

#endif // POINTTRACERENDER_H
