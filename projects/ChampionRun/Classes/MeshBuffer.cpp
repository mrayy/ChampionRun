//
//  MeshBuffer.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/11/13.
//
//

#include "MeshBuffer.h"


namespace cocos2d
{
    MeshBuffer::MeshBuffer()
    {
        _dirty=false;
        _blendFunc=BlendFunc::ALPHA_PREMULTIPLIED;
    }
    MeshBuffer::~MeshBuffer()
    {
    }
    
    bool MeshBuffer::init(int capacity)
    {
        
#if CC_TEXTURE_ATLAS_USE_VAO
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
#endif
        
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
       
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
        
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
        
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
#if CC_TEXTURE_ATLAS_USE_VAO
        GL::bindVAO(0);
#endif
        
        CHECK_GL_ERROR_DEBUG();
        
        _dirty = true;
        
        
        return true;

    }
    
    void MeshBuffer::SetDrawingType(int type)
    {
        m_drawingType=type;
    }
    void MeshBuffer::SetVertexCount(int count)
    {
        if(m_verticies.size()==count)
            return;
        m_verticies.resize(count);
    }
    void MeshBuffer::SetIndexCount(int count)
    {
        if(m_indicies.size()==count)
            return;
        m_indicies.resize(count);
    }
    
    V2F_C4B_T2F* MeshBuffer::GetVertexPointer()
    {
        if(m_verticies.size()==0)
            return 0;
        return &m_verticies[0];
    }
    GLuint* MeshBuffer::GetIndexPointer()
    {
        if(m_indicies.size()==0)
            return 0;
        return &m_indicies[0];
    }
    
    void MeshBuffer::Draw()
    {
        if(m_indicies.size()==0 || m_verticies.size()==0)
            return;
        GL::blendFunc(_blendFunc.src, _blendFunc.dst);
        if (_dirty)
        {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*m_verticies.size(), GetVertexPointer(), GL_STREAM_DRAW);
            _dirty = false;
        }
#if CC_TEXTURE_ATLAS_USE_VAO
        GL::bindVAO(_vao);
#else
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // vertex
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
        
        // color
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
        //
        // texcood
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
#endif
        
        glDrawElements(m_drawingType, m_indicies.size(), GL_UNSIGNED_INT, GetIndexPointer());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        CC_INCREMENT_GL_DRAWS(1);
        CHECK_GL_ERROR_DEBUG();
    }
}