//
//  WalkNodeBase.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/10/13.
//
//

#ifndef __ChampionRun__WalkNodeBase__
#define __ChampionRun__WalkNodeBase__

#include <iostream>
#include "cocos2d.h"

#include "libs\FFTW\CFft.h"
#include "MeshBuffer.h"

namespace cocos2d
{
    
class WalkNodeBase:public Node
{
protected:
    class WaveWindow
    {
        int m_start;
        int m_end;
        
        float m_mean;
        float m_stdDev;
    public:
        WaveWindow(int start,int end):m_start(start),m_end(end)
        {
        }
        
        void Calculate(float* samples)
        {
            m_mean=0;
            for(int i=m_start;i<m_end;++i)
            {
                m_mean+=samples[i];
            }
            m_mean/=(float)(m_end-m_start);
            m_stdDev=0;
            
            for(int i=m_start;i<m_end;++i)
            {
                
                float diff=(samples[i]-m_mean);
                m_stdDev+=diff*diff;
            }
            m_stdDev/=(float)(m_end-m_start);
            m_stdDev=sqrt(m_stdDev);
        }
        
        int Start(){return m_start;}
        int End(){return m_end;}
        
        float Mean(){return m_mean;}
        float Dev(){return m_stdDev;}
        
    };
    
    
    typedef std::list<Acceleration> AccelerationList;
    AccelerationList m_accelerations;
    float m_time;
    bool m_added;
    float m_frequency;
    
    std::vector<float> m_accelerationSamples[3];
    std::vector<float> m_histogram;
    float m_mean;
    float m_stdDev;
    
    
    CFft* m_fft[3];
    std::vector<WaveWindow*> m_windows;
    
    MeshBuffer m_histogramMesh;
    MeshBuffer m_windowMesh;
    
    virtual void _updateHistogram();
    virtual void _updateBuffer();

    
    static std::vector<std::string> s_TrainingLabels;
    static bool s_trainingLabelInit;
    
public:

    
    WalkNodeBase();
    
    virtual bool init();
    
    virtual void draw();
    
    virtual void OnAcceleration(Acceleration* acc);
    
    virtual void update(float dt);
    
    static const  std::vector<std::string> & GetTrainingLabels();
};
}

#endif /* defined(__ChampionRun__WalkNodeBase__) */
