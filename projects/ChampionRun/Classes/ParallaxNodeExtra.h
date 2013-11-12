//
//  ParallaxNodeExtra.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/4/13.
//
//

#ifndef __ChampionRun__ParallaxNodeExtra__
#define __ChampionRun__ParallaxNodeExtra__

#include <iostream>
#include "cocos2d.h"

namespace cocos2d {
    class ParallaxNodeExtra:public ParallaxNode
    {
    public:
        ParallaxNodeExtra();
        static ParallaxNodeExtra* create();
        void incrementOffset(Point offset, Node* node);
    };
}

#endif /* defined(__ChampionRun__ParallaxNodeExtra__) */
