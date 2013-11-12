//
//  WalkDetectorNode.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/5/13.
//
//

#ifndef __ChampionRun__WalkDetectorNode__
#define __ChampionRun__WalkDetectorNode__

#include <iostream>
#include "WalkNodeBase.h"

#include "libs/FANN/floatfann.h"
#include "libs/FANN/fann_cpp.h"


namespace cocos2d
{
    
    class WaveWindow;
    
    enum EWalkDetectorMode
    {
        EIdle,
        EDetection,
        ETraining
    };
    
 //walk detection node
class WalkDetectorNode:public WalkNodeBase
{
protected:
    
    
    int m_selectedWindow;
    FANN::neural_net * m_detectNet;
    float m_speed;
    
    EWalkDetectorMode m_mode;
    
    void _updateHistogram();
public:
    WalkDetectorNode(const std::string&trainingFile);
    virtual~WalkDetectorNode();
        
    virtual void draw();
    
    void update(float dt);
    
    static WalkDetectorNode* create(const std::string &trainingFile)
    {
        WalkDetectorNode* node=new WalkDetectorNode(trainingFile);
        if(node->init())
            return node;
        return NULL;
    }
    
    float GetMean(){return m_mean;}
    float GetStandardDeviation(){return m_stdDev;}
    
    std::string GetCycleName();
    float GetSpeed();
};
    
}   
#endif /* defined(__ChampionRun__WalkDetectorNode__) */
