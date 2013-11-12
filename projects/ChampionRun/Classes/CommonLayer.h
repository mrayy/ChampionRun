//
//  CommonLayer.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#ifndef __ChampionRun__CommonLayer__
#define __ChampionRun__CommonLayer__

#include <iostream>
#include "cocos2d.h"

#include "cocos-ext.h"


USING_NS_CC;
using namespace extension;

class CommonLayer:public Layer
{
public:
};

class CommonLayerLoader
{
protected:
    std::string m_name;
public:
    CommonLayerLoader(const std::string& name):m_name(name)
    {
    }
    
    const std::string& GetName()const{return m_name;}
    virtual NodeLoader* GetLoader()=0;
};

#define COMMON_LAYER_LOADER_BEGIN(name,base)\
class name##Loader:public CommonLayerLoader,public base\
{\
public:\
    name##Loader():CommonLayerLoader(#name){}\
CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(name##Loader, loader);\
virtual NodeLoader* GetLoader(){return this;}\
protected:\
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(name);\

#define COMMON_LAYER_LOADER_END()\
};

#endif /* defined(__ChampionRun__CommonLayer__) */
