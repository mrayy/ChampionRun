//
//  SceneManager.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#ifndef __ChampionRun__SceneManager__
#define __ChampionRun__SceneManager__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC;

class CommonLayerLoader;

class SceneManager
{
    static SceneManager* s_instance;
    extension::NodeLoaderLibrary* m_loaders;
    typedef std::map<std::string,extension::CCBSelectorResolver*> ResolversMap;
    ResolversMap m_resolvers;
public:
    
    
    SceneManager();
    
    cocos2d::Scene* LoadScene(const std::string& scene);
    cocos2d::Node* LoadNode(const std::string& scene);
    
    void registerLoader(CommonLayerLoader* loader);
    
    void registerDefaults();
    
    static SceneManager* instance()
    {
        if(s_instance==NULL)
        {
            s_instance=new SceneManager();
            s_instance->registerDefaults();
        }
        
        return s_instance;
    }
};


#endif /* defined(__ChampionRun__SceneManager__) */
