//
//  SplashLayer.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#ifndef __ChampionRun__SplashLayer__
#define __ChampionRun__SplashLayer__

#include <iostream>
#include "cocos2d.h"
#include "CommonLayer.h"
#include "cocos-ext.h"

USING_NS_CC;

class SplashLayer:public Layer
{
public:
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    static void registerLoader();
    
    void switchToNextScreen();
    
    // implement the "static node()" method manually
    CREATE_FUNC(SplashLayer);
    
    
};

COMMON_LAYER_LOADER_BEGIN(SplashLayer,LayerLoader);
COMMON_LAYER_LOADER_END();

#endif /* defined(__ChampionRun__SplashLayer__) */
