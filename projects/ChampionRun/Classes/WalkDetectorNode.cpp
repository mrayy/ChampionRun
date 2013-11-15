//
//  WalkDetectorNode.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/5/13.
//
//

#include "WalkDetectorNode.h"
#include "libs/FFTW/CFft.h"

namespace cocos2d
{
    
    WalkDetectorNode::WalkDetectorNode(const std::string&trainingFile)
    {
        
        
        m_detectNet=new FANN::neural_net();
        m_detectNet->create_standard(3,m_windows.size()*2,10,1);
        m_detectNet->set_activation_function_hidden( FANN::SIGMOID_SYMMETRIC);
        m_detectNet->set_activation_function_output(FANN::SIGMOID_SYMMETRIC);
        
        m_detectNet->set_training_algorithm(FANN::TRAIN_QUICKPROP);
    }
    WalkDetectorNode::~WalkDetectorNode()
    {
        delete m_detectNet;
    }
    
    void WalkDetectorNode::draw()
    {
        WalkNodeBase::draw();
    }
    void WalkDetectorNode::_updateHistogram()
    {
        WalkNodeBase::_updateHistogram();
        
    }
    
    void WalkDetectorNode::update(float dt)
    {
        WalkNodeBase::update(dt);
    }
    
    std::string WalkDetectorNode::GetCycleName()
    {
        return "";
    }
    
}