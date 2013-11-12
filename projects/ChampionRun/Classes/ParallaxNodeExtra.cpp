//
//  ParallaxNodeExtra.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/4/13.
//
//

#include "ParallaxNodeExtra.h"

namespace cocos2d {
    
    class PointObject:public Object
    {
        CC_SYNTHESIZE(Point, m_tRatio, Ratio);
        CC_SYNTHESIZE(Point, m_tOffset, Offset);
        CC_SYNTHESIZE(Node*, m_pChild, Child);
    };
    ParallaxNodeExtra::ParallaxNodeExtra():ParallaxNode()
    {
    }
    ParallaxNodeExtra* ParallaxNodeExtra::create()
    {
        return new ParallaxNodeExtra();
    }
    void ParallaxNodeExtra::incrementOffset(Point offset, Node* node)
    {
        for( unsigned int i = 0; i < _parallaxArray->num; i++) {
            PointObject *point = static_cast<PointObject*>(_parallaxArray->arr[i]);
            Node * curNode = point->getChild();
            if( curNode->isEqual(node) ) {
                point->setOffset( point->getOffset()+ offset );
                break;
            }
        }
    }
    
}