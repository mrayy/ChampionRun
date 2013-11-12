//
//  WalkNodeBase.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/10/13.
//
//

#include "WalkNodeBase.h"

namespace cocos2d
{
    
    
    std::vector<std::string> WalkNodeBase::s_TrainingLabels;
    bool WalkNodeBase::s_trainingLabelInit=false;
    
    const  std::vector<std::string> & WalkNodeBase::GetTrainingLabels()
    {
        if(!s_trainingLabelInit)
        {
            s_trainingLabelInit=true;
            s_TrainingLabels.push_back("Standing");
            s_TrainingLabels.push_back("Slow Walk");
            s_TrainingLabels.push_back("Fast Walk");
            s_TrainingLabels.push_back("Running");
        }
        return s_TrainingLabels;
    }
    
    WalkNodeBase::WalkNodeBase()
    {
        m_time=0;
        scheduleUpdate();
        m_added=false;
        int samplesCount=64;
        m_frequency=1.0f/samplesCount;
        
        m_accelerationSamples[0].resize(samplesCount, 0);
        m_accelerationSamples[1].resize(samplesCount, 0);
        m_accelerationSamples[2].resize(samplesCount, 0);
        m_fft[0]=CFft::create(samplesCount, OF_FFT_WINDOW_HAMMING,OF_FFT_BASIC);
        m_fft[1]=CFft::create(samplesCount, OF_FFT_WINDOW_HAMMING,OF_FFT_BASIC);
        m_fft[2]=CFft::create(samplesCount, OF_FFT_WINDOW_HAMMING,OF_FFT_BASIC);
        
        int binSize=m_fft[0]->getBinSize();
        m_histogram.resize(binSize);
        
        m_mean=0;
        m_stdDev=0;
        
        int n=10;
        float windowSize=(float)binSize/(float)n;
        for(int i=0;i<n;++i)
        {
            WaveWindow* wnd=new WaveWindow(i*windowSize,(i+1)*windowSize);
            m_windows.push_back(wnd);
        }
        m_histogramMesh.init(binSize);
        m_histogramMesh.SetIndexCount(binSize);
        m_histogramMesh.SetDrawingType(GL_LINE_STRIP);
        
        
        m_windowMesh.init(m_windows.size()*4*2);
        m_windowMesh.SetDrawingType(GL_LINES);
    }
    
    bool WalkNodeBase::init()
    {
        if(!Node::init())
            return false;
        setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR));
        return true;
    }
    
    void WalkNodeBase::_updateHistogram()
    {
        
        AccelerationList::iterator it=m_accelerations.begin();
        
        for (int i=0; it!=m_accelerations.end(); ++it,++i) {
            Acceleration& acc=*it;
            m_accelerationSamples[0][i]=acc.x;
            m_accelerationSamples[1][i]=acc.y;
            m_accelerationSamples[2][i]=acc.z;
        }
        
        m_fft[0]->setSignal(m_accelerationSamples[0]);
        m_fft[1]->setSignal(m_accelerationSamples[1]);
        m_fft[2]->setSignal(m_accelerationSamples[2]);
        float* amps[3];
        amps[0]=m_fft[0]->getAmplitude();
        amps[1]=m_fft[1]->getAmplitude();
        amps[2]=m_fft[2]->getAmplitude();
        int binSize=m_histogram.size();
        
        
        float max=0;
        m_mean=0;
        
        for(int i=0;i<binSize;++i)
        {
            m_histogram[i]=(amps[0][i]+amps[1][i]+amps[2][i])/3.0f;
            if(m_histogram[i]>max)
                max=m_histogram[i];
        }
        
        float invMax=1.0f/max;
        
        float midPoint=0;
        //normalize
        for(int i=0;i<binSize;++i)
        {
            m_histogram[i]*=invMax;
            m_mean+=m_histogram[i];
            midPoint+=m_histogram[i]*i/(float)binSize;
        }
        m_mean/=(float)binSize;
        m_stdDev=0;
        
        for(int i=0;i<binSize;++i)
        {
            
            float diff=(m_histogram[i]-m_mean);
            //    m_histogram[i]=diff;
            m_stdDev+=diff*diff;
        }
        m_stdDev/=(float)binSize;
        
        m_mean=midPoint;
        
        //calculate windows
        for(int i=0;i<m_windows.size();++i)
        {
            m_windows[i]->Calculate(&m_histogram[0]);
        }
    }
    
    
    void WalkNodeBase::draw()
    {
        CC_NODE_DRAW_SETUP();;
        m_histogramMesh.Draw();
        m_windowMesh.Draw();
        
    }
    void WalkNodeBase::_updateBuffer()
    {
        int count=m_histogram.size();
        m_histogramMesh.SetVertexCount(count);
        m_histogramMesh.SetIndexCount(count);
        V2F_C4B_T2F *vertex = m_histogramMesh.GetVertexPointer();
        GLuint *idxPtr=m_histogramMesh.GetIndexPointer();
        float invWidth=getContentSize().width/(float)m_histogram.size();
        
        for(int i=0;i<count;++i)
        {
            Point pt(i*invWidth+getPositionX(),m_histogram[i]*getContentSize().height+getPositionY());
            vertex->vertices.x=pt.x;
            vertex->vertices.y=pt.y;
            vertex->colors=Color4B(255-255*m_histogram[i], 255, 255, 255);
            vertex++;
            
            *idxPtr=i;
            idxPtr++;
        }
        
        
        m_windowMesh.SetVertexCount(m_windows.size()*8);
        m_windowMesh.SetIndexCount(m_windows.size()*8);
        
        idxPtr=m_windowMesh.GetIndexPointer();
        vertex=m_windowMesh.GetVertexPointer();
        for(int i=0;i<m_windows.size();++i)
        {
            WaveWindow* wnd= m_windows[i];
            float mean=wnd->Mean();
            float dev=wnd->Dev();
            float x1=wnd->Start()*invWidth+getPositionX();
            float x2=wnd->End()  *invWidth+getPositionX();
            float meanY=mean*getContentSize().height+getPositionY();
            float StdY1=(mean+dev)*getContentSize().height+getPositionY();
            float StdY2=(mean-dev)*getContentSize().height+getPositionY();
            vertex[0].vertices=Vertex2F(x1,meanY);
            vertex[1].vertices=Vertex2F(x2,meanY);
            vertex[2].vertices=Vertex2F(x1,StdY1);
            vertex[3].vertices=Vertex2F(x2,StdY1);
            vertex[4].vertices=Vertex2F(x1,StdY2);
            vertex[5].vertices=Vertex2F(x2,StdY2);
            
            vertex[6].vertices=Vertex2F(x2,0);
            vertex[7].vertices=Vertex2F(x2,getContentSize().height);
            
            vertex[0].colors=vertex[1].colors=Color4B(255, 0  ,   0, 255);
            vertex[2].colors=vertex[3].colors=
            vertex[4].colors=vertex[5].colors=Color4B(255, 255, 255, 255);
            vertex[6].colors=vertex[7].colors=Color4B(0  , 255,   0, 255);
            
            for(int j=0;j<8;++j)
            {
                idxPtr[j]=8*i+j;
            }
            idxPtr+=8;
            vertex+=8;
        }
        
        m_windowMesh.SetDirty();
        m_histogramMesh.SetDirty();
    }
    
    
    
    void WalkNodeBase::OnAcceleration(Acceleration* acc)
    {
    //    if(m_added)
      //      return;
        m_added=true;
        m_accelerations.push_back(*acc);
        if(m_accelerations.size()>m_accelerationSamples[0].size())
        {
            m_accelerations.erase(m_accelerations.begin());
        }
        
        _updateHistogram();
        _updateBuffer();
    }
    
    void WalkNodeBase::update(float dt)
    {
        Node::update(dt);
        
        m_time+=dt;
        if(m_time>m_frequency)
        {
            m_added=false;
            m_time-=m_frequency;
        }
    }
    
    
}