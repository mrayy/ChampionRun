//
//  WalkTrainingNode.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/10/13.
//
//

#include "WalkTrainingNode.h"
#include "libs/tinyxml2.h"


namespace cocos2d
{
    
    struct WalkTrainingData
    {
    public:
        FANN::training_data netData;
        std::vector<WalkTrainingNode::TrainingVector*> trainingSet;
        
        int currentTraining;
        int lastTrainingSample;
        
        float** inputs;
        float** outputs;
        WalkTrainingData()
        {
            inputs=0;
            outputs=0;
        }
        ~WalkTrainingData()
        {
            Clean();
        }
        
        void PrepareTraining(int inCnt,int outCnt)
        {
            inputs=new float*[trainingSet.size()];
            outputs=new float*[trainingSet.size()];
            
            for(int i=0;i<trainingSet.size();++i)
            {
                inputs[i]=&trainingSet[i]->inputs[0];
                outputs[i]=&trainingSet[i]->output[0];
            }
            
            netData.set_train_data(trainingSet.size(), inCnt, inputs, outCnt, outputs);
            

        }
        
        void Clean()
        {
            currentTraining=0;
            lastTrainingSample=0;
            for (int i=0; i<trainingSet.size(); ++i)
            {
                delete trainingSet[i];
            }
            trainingSet.clear();
            netData.destroy_train();
            
            inputs=0;
            outputs=0;
        }
        
    };
    WalkTrainingNode::WalkTrainingNode()
    {
        m_detectNet=new FANN::neural_net();
        m_detectNet->create_standard(3,m_windows.size()*2+2,10,GetTrainingLabels().size());
        m_detectNet->set_activation_function_hidden( FANN::SIGMOID_SYMMETRIC);
        m_detectNet->set_activation_function_output(FANN::SIGMOID_SYMMETRIC);
        
        m_detectNet->set_training_algorithm(FANN::TRAIN_QUICKPROP);
        m_trainingData=new WalkTrainingData;
        m_mode=EMode_Detecting;
        RestartTraining();
        
        
    }
    WalkTrainingNode::~WalkTrainingNode()
    {
        delete m_detectNet;
        delete m_trainingData;
    }
    
    void WalkTrainingNode::_updateHistogram()
    {
        WalkNodeBase::_updateHistogram();
        
        if(m_mode==EMode_Training)
        {
            if(m_status==ESampling)
            {
                TrainingVector* v=new TrainingVector();
                CreateVector(v);
                //add training vector
                m_trainingData->trainingSet.push_back(v);
            }else if(m_status==ETraining)
            {
                m_detectNet->train_epoch(m_trainingData->netData);
            }
        }else if(m_mode==EMode_Detecting)
        {
            TrainingVector v;
            CreateVector(&v);
            float* result=m_detectNet->run(&v.inputs[0]);
            float maxV=0;
            m_detectedCycle=0;
            for(int i=0;i<GetTrainingLabels().size();++i)
            {
                if(result[i]>maxV)
                {
                    maxV=result[i];
                    m_detectedCycle=i;
                }
            }
        }
    }
    
    void WalkTrainingNode::CreateVector(WalkTrainingNode::TrainingVector* v)
    {
        
        v->inputs.resize(m_detectNet->get_num_input());
        v->inputs[0]=m_mean;
        v->inputs[1]=m_stdDev;
        for(int i=0;i<m_windows.size();++i)
        {
            v->inputs[2*(i+1)]=(m_windows[i]->Mean());
            v->inputs[2*(i+1)+1]=(m_windows[i]->Dev());
        }
        v->output.resize(GetTrainingLabels().size(),0);
        v->output[m_trainingData->currentTraining]=1;
    }
    
    bool WalkTrainingNode::init(bool training,const std::string& trainingFile)
    {
        if(!WalkNodeBase::init())
            return false;
        if(training)
        {
            SetTraining();
            SetTrainingName(trainingFile);
        }
        else
        {
            SetDetecting();
            LoadTraining(trainingFile);
        }
        
        return true;
    }
    
    void WalkTrainingNode::SetTraining()
    {
        m_mode=EMode_Training;
    }
    void WalkTrainingNode::SetDetecting()
    {
        m_mode=EMode_Detecting;
    }
    void WalkTrainingNode::LoadTraining(const std::string& name)
    {
        std::string path=FileUtils::getInstance()->fullPathForFilename(name+".network");
        if(path=="" || path==name+".network")
            return;
        m_detectNet->create_from_file(path);
    }

    void WalkTrainingNode::RestartTraining()
    {
        m_status=EIdle;
        m_detectNet->randomize_weights(0, 1);
        m_trainingData->Clean();
        m_detectedCycle=0;
    }
    bool WalkTrainingNode::NextTraining()
    {
        if(m_status==ETraining)
            return false;
        if(m_trainingData->currentTraining==GetTrainingLabels().size()-1)
        {
            m_trainingData->PrepareTraining(m_detectNet->get_num_input(),m_detectNet->get_num_output());
            m_status=ETraining;
            return false;
        }
        m_trainingData->currentTraining++;
        m_status=EIdle;
        m_trainingData->lastTrainingSample=m_trainingData->trainingSet.size();
        return true;
    }
    
    void WalkTrainingNode::StartTraining()
    {
        if(m_status!=EIdle)
            return;
        m_status=ESampling;
    }
    void WalkTrainingNode::EndTraining()
    {
        m_status=EFinished;
        std::string path=FileUtils::getInstance()->getWritablePath()+m_trainingName+".network";
        m_detectNet->save(path);
     //   _exportData();
    }
    
    void WalkTrainingNode::_exportData()
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* root=doc.NewElement("Training");
        root->SetAttribute("Name", m_trainingName.c_str());
        root->SetAttribute("Input", m_detectNet->get_num_input());
        root->SetAttribute("Output", m_detectNet->get_num_output());
        doc.InsertFirstChild(root);
        
        
        for(int i=0;i<m_trainingData->trainingSet.size();++i)
        {
            tinyxml2::XMLElement* data=doc.NewElement("Data");
            root->InsertEndChild(data);
            
            tinyxml2::XMLElement* input=doc.NewElement("Input");
            tinyxml2::XMLElement* output=doc.NewElement("Output");
            
            std::string inputVector="";
            std::string outputVector="";
            char buffer[32];
            for(int j=0;j<m_trainingData->trainingSet[i]->inputs.size();++j)
            {
                sprintf(buffer,"%f",m_trainingData->trainingSet[i]->inputs[i]);
                inputVector+=buffer;
                
                if(j<m_trainingData->trainingSet[i]->inputs.size()-1)
                    inputVector+=",";
            }
            for(int j=0;j<m_trainingData->trainingSet[i]->output.size();++j)
            {
                sprintf(buffer,"%f",m_trainingData->trainingSet[i]->output[i]);
                outputVector+=buffer;
                if(j<m_trainingData->trainingSet[i]->output.size()-1)
                    outputVector+=",";
            }
            input->SetValue(inputVector.c_str());
            output->SetValue(outputVector.c_str());
            
            data->InsertEndChild(input);
            data->InsertEndChild(output);
        }
        
        std::string path=FileUtils::getInstance()->getWritablePath()+m_trainingName+".training";
        doc.SaveFile(path.c_str());
    }
    int WalkTrainingNode::GetRemainingTraining()
    {
        return GetTrainingLabels().size()-m_trainingData->currentTraining;
    }
    
    std::string WalkTrainingNode::GetCurrentTrainingLabel()
    {
        return GetTrainingLabels()[m_trainingData->currentTraining];
    }
    
    float WalkTrainingNode::GetError()
    {
        return m_detectNet->get_MSE();
    }
    int WalkTrainingNode::GetCurrentSamples()
    {
        return m_trainingData->trainingSet.size()-m_trainingData->lastTrainingSample;
    }
}