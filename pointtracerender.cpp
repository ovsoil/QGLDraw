#include "pointtracerender.h"

PointTraceRender::PointTraceRender()
    :nVerts(0)
{
}

PointTraceRender::~PointTraceRender()
{
}

void PointTraceRender::SetupRC()
{
    glClearColor(0.0, 0.0, 1.0, 0.0);
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Enable back face culling
    glEnable(GL_CULL_FACE);

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, "/Users/ovsoil/Coding/qt/QGLDraw/vshader.glsl"))
        return;

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, "/Users/ovsoil/Coding/qt/QGLDraw/fshader.glsl"))
        return;

    // Link shader pipeline
    if (!program.link())
        return;

    // Bind shader pipeline for use
    if (!program.bind())
        return;

    // Load up a triangle
    GLfloat vec[] = { -0.5f, 0.0f, 0.0f,
                    0.5f, 0.0f, 0.0f,
                    0.0f, 0.5f, 0.0f };
    vVerts.assign(vec, vec + sizeof(vec));
    nVerts = vVerts.size();
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts.data());
    triangleBatch.End();
}

void PointTraceRender::Update()
{
    
}

void PointTraceRender::Render(const QMatrix4x4& projection, const QQuaternion& rotation)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);
    // Offset for position

    quintptr offset = 0;
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program.attributeLocation("a_position");
    program.enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (const void *)offset);

    //glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FLOOR]);
    triangleBatch.Draw();
}
