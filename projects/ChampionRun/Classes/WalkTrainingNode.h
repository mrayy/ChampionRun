//
//  WalkTrainingNode.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/10/13.
//
//

#ifndef __ChampionRun__WalkTrainingNode__
#define __ChampionRun__WalkTrainingNode__

#include "WalkNodeBase.h"
#include "libs/FANN/floatfann.h"
#include "libs/FANN/fann_cpp.h"

namespace cocos2d
{
    struct WalkTrainingData;
class WalkTrainingNode:public WalkNodeBase
{
public:
    enum EStatus
    {
        EIdle,
        ESampling,
        ETraining,
        EFinished
    };
    struct TrainingVector
    {
        std::vector<float> inputs;
        std::vector<float> output;
    };

protected:
    
    enum EMode
    {
        EMode_Training,
        EMode_Detecting
    };
    EMode m_mode;
    EStatus m_status;
    FANN::neural_net * m_detectNet;
    WalkTrainingData* m_trainingData;
    
    std::string m_trainingName;
    int m_detectedCycle;
    
    void _updateHistogram();
    void CreateVector(TrainingVector* v);
    void _exportData();
public:
    
    WalkTrainingNode();
    virtual~WalkTrainingNode();

    static WalkTrainingNode* create(bool training,const std::string& trainingFile)
    {
        WalkTrainingNode* node=new WalkTrainingNode();
        if(!node->init(training,trainingFile))
        {
            delete node;
            return NULL;
        }
        return node;
    }
    virtual bool init(bool training,const std::string& trainingFile);
    void SetTraining();
    void SetDetecting();
    
    bool IsTraining(){return m_mode==EMode_Training;}
    bool IsDetecting(){return m_mode==EMode_Detecting;}
    
    void SetTrainingName(const std::string& name){m_trainingName=name;}
    void LoadTraining(const std::string& name);
    
    void RestartTraining();    
    bool NextTraining();
    void StartTraining();
    void Stop(){m_status=EIdle;}
    void EndTraining();
    int GetRemainingTraining();
    std::string GetCurrentTrainingLabel();
    
    float GetError();
    int GetCurrentSamples();
    int GetDetectedCycle(){return m_detectedCycle;}
    
    EStatus GetStatus(){return m_status;}
};
}


#endif /* defined(__ChampionRun__WalkTrainingNode__) */
