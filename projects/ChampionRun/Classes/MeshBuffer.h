//
//  MeshBuffer.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/11/13.
//
//

#ifndef __ChampionRun__MeshBuffer__
#define __ChampionRun__MeshBuffer__

#include <iostream>
#include <cocos2d.h>

namespace cocos2d
{
    class MeshBuffer
    {
    protected:
        GLuint _vbo;
        GLuint _vao;
        int m_drawingType;
        std::vector<V2F_C4B_T2F> m_verticies;
        std::vector<GLuint> m_indicies;
        bool _dirty;
        
        BlendFunc _blendFunc;
    public:
        
        MeshBuffer();
        virtual~MeshBuffer();
        
        bool init(int capacity);
        
        void SetBlendFunc(const BlendFunc& blendFunc){_blendFunc=blendFunc;}
        
        void SetDrawingType(int type);
        void SetVertexCount(int count);
        void SetIndexCount(int count);
        
        V2F_C4B_T2F* GetVertexPointer();
        GLuint* GetIndexPointer();
        
        void SetDirty(){_dirty=true;}
        
        void Draw();
    };
}

#endif /* defined(__ChampionRun__MeshBuffer__) */
