//Batch.h
#ifndef BATCH_H
#define BATCH_H

//// Bring in OpenGL
//// Windows
//#ifdef WIN32
//#include <windows.h>		// Must have for Windows platform builds
//#ifndef GLEW_STATIC
//#define GLEW_STATIC
//#endif
//#include <gl\glew.h>			// OpenGL Extension "autoloader"
//#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
//#endif

//// Mac OS X
//#ifdef __APPLE__
//#include <TargetConditionals.h>
//#if TARGET_OS_IPHONE | TARGET_IPHONE_SIMULATOR
//#include <OpenGLES/ES2/gl.h>
//#include <OpenGLES/ES2/glext.h>
//#define OPENGL_ES
//#else
//#include <GL/glew.h>
//#include <OpenGL/gl.h>		// Apple OpenGL haders (version depends on OS X SDK version)
//#endif
//#endif

//// Linux
//#ifdef linux
//#define GLEW_STATIC
//#include <glew.h>
//#endif

// 用QtOpenGL

#include <QGL>

#include "batchbase.h"
//#include "shadermanager.h"
#include "math3d.h"


enum GLT_SHADER_ATTRIBUTE { GLT_ATTRIBUTE_VERTEX = 0, GLT_ATTRIBUTE_COLOR, GLT_ATTRIBUTE_NORMAL,
                                    GLT_ATTRIBUTE_TEXTURE0, GLT_ATTRIBUTE_TEXTURE1, GLT_ATTRIBUTE_TEXTURE2, GLT_ATTRIBUTE_TEXTURE3,
                                    GLT_ATTRIBUTE_LAST};
class Batch : public BatchBase//, protected QGLFunctions
{
public:
    Batch(void);
    virtual ~Batch(void);

    // Start populating the array
    void Begin(GLenum primitive, GLuint nVerts, GLuint nTextureUnits = 0);

    // Tell the batch you are done
    void End(void);

    // Block Copy in vertex data
    void CopyVertexData3f(M3DVector3f *vVerts);
    void CopyNormalDataf(M3DVector3f *vNorms);
    void CopyColorData4f(M3DVector4f *vColors);
    void CopyTexCoordData2f(M3DVector2f *vTexCoords, GLuint uiTextureLayer);

    // Just to make life easier...
    inline void CopyVertexData3f(GLfloat *vVerts) { CopyVertexData3f((M3DVector3f *)(vVerts)); }
    inline void CopyNormalDataf(GLfloat *vNorms) { CopyNormalDataf((M3DVector3f *)(vNorms)); }
    inline void CopyColorData4f(GLfloat *vColors) { CopyColorData4f((M3DVector4f *)(vColors)); }
    inline void CopyTexCoordData2f(GLfloat *vTex, GLuint uiTextureLayer) { CopyTexCoordData2f((M3DVector2f *)(vTex), uiTextureLayer); }

    virtual void Draw(void);

    // Immediate mode emulation
    // Slowest way to build an array on purpose... Use the above if you can instead
    void Reset(void);

    void Vertex3f(GLfloat x, GLfloat y, GLfloat z);
    void Vertex3fv(M3DVector3f vVertex);

    void Normal3f(GLfloat x, GLfloat y, GLfloat z);
    void Normal3fv(M3DVector3f vNormal);

    void Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void Color4fv(M3DVector4f vColor);

    void MultiTexCoord2f(GLuint texture, GLclampf s, GLclampf t);
    void MultiTexCoord2fv(GLuint texture, M3DVector2f vTexCoord);

protected:
    GLenum		primitiveType;		// What am I drawing....

    GLuint		uiVertexArray;
    GLuint      uiNormalArray;
    GLuint		uiColorArray;
    GLuint		*uiTextureCoordArray;
    GLuint		vertexArrayObject;

    GLuint nVertsBuilding;			// Building up vertexes counter (immediate mode emulator)
    GLuint nNumVerts;				// Number of verticies in this batch
    GLuint nNumTextureUnits;		// Number of texture coordinate sets

    bool	bBatchDone;				// Batch has been built


    M3DVector3f *pVerts;
    M3DVector3f *pNormals;
    M3DVector4f *pColors;
    M3DVector2f **pTexCoords;

};

#endif // __GL_BATCH__
