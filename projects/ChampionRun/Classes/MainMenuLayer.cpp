//
//  MainMenuLayer.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#include "MainMenuLayer.h"
#include "SceneManager.h"
#include "Helpers.h"

class CloudsGenerator:public Layer
{
    struct CloudData
    {
        Node* sprite;
        float distance;
    };
    std::vector<CloudData> m_clouds;
    
    GLProgram* m_shader;
    int m_timeUniform;
    float m_time;
    
    
    float m_speed;
    
    ParallaxNode* _cloudsLayer;

public:
    CloudsGenerator()
    {
        this->scheduleUpdate();
        m_time=0;
        
        setAccelerometerEnabled(true);
    }
    
    void onAcceleration(Acceleration* acc, Event* event)
    {
        m_speed=acc->x;
    }
    
    virtual void update(float dt)
    {
        Layer::update(dt);
        
        Size winSize=CCDirector::getInstance()->getWinSize();
        for(int i=0;i<m_clouds.size();++i)
        {
            Point pos= _cloudsLayer->convertToWorldSpace(m_clouds[i].sprite->getPosition());
            float width=m_clouds[i].sprite->getContentSize().width*m_clouds[i].sprite->getScaleX()*0.5;
            if(pos.x>winSize.width+width)
            {
                _cloudsLayer->incrementOffset(Point(-pos.x-width,0), m_clouds[i].sprite);
                
            }
        }
        
        _cloudsLayer->setPosition(_cloudsLayer->getPosition()+Point(100,0)*dt);
        m_time+=dt;
        
        if(m_shader)
        {
            m_shader->use();
            glUniform1f(m_timeUniform, m_time);
        }
        Acceleration acc;
        acc.x=rand01();
        acc.y=rand01();
        acc.z=rand01();
        
     //   m_accNode->OnAcceleration(&acc);
        
    }
    
    virtual bool init()
    {
        if(!CCNode::init())
            return  false;
        Size winSize=CCDirector::getInstance()->getWinSize();
      //  CCSpriteBatchNode* cloudBatch=CCSpriteBatchNode::create("Menu/Cloud.png");
      //  addChild(cloudBatch);
        if(false)
        {
            std::string shaderPath=FileUtils::getInstance()->fullPathFromRelativeFile("Clouds.vsh","");
        
            unsigned long pSize=0;
            std::string shaderSrc=(char*)FileUtils::getInstance()->getFileData(shaderPath.c_str(), "r", &pSize);
            GLProgram* shaderProgram=new GLProgram();
            char* str=(char*)shaderSrc.c_str();
            str[shaderSrc.length()]=0;
            shaderProgram->initWithVertexShaderByteArray(str,ccPositionTextureColor_frag);
            shaderProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
            shaderProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);

            shaderProgram->link();
            shaderProgram->updateUniforms();
            m_timeUniform=shaderProgram->getUniformLocationForName("u_time");
            this->getPositionX();
        
            m_shader=shaderProgram;
        }else
            m_shader=NULL;
        
        _cloudsLayer=ParallaxNode::create();
        addChild(_cloudsLayer);
        for(int i=0;i<5;++i)
        {
            CloudData cloud;
            cloud.sprite=CCSprite::createWithSpriteFrameName("Menu/Cloud.png");
            int zOrder=randRange(0, 4);
            cloud.distance=zOrder;
            cloud.sprite->setScale((cloud.distance+1)/5+1);
            //sprite->setPosition(Point(randRange(-50, winSize.width+50),100+randRange(-100, 300)));
            if(m_shader)
                cloud.sprite->setShaderProgram(m_shader);
            
            m_clouds.push_back(cloud);
            _cloudsLayer->addChild(cloud.sprite, zOrder, Point(0.01*(zOrder+1),0), Point(randRange(-50, winSize.width+50),200+randRange(-100, 100)));
        }
        
        return true;
    }
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(CloudsGenerator);
};


COMMON_LAYER_LOADER_BEGIN(CloudsGenerator,LayerLoader);
COMMON_LAYER_LOADER_END();



class MenuAvatar:public Node
{
public:
    MenuAvatar()
    {
    }
    
    virtual bool init()
    {
        if(!CCNode::init())
            return  false;
        
        //Node*node=SceneManager::instance()->LoadNode("Yusha");
       // addChild(node);
        
        armature::ArmatureDataManager::getInstance()->addArmatureFileInfo("Characters/Yusha.ExportJson");
        armature::Armature* hero=armature::Armature::create("Yusha");
        addChild(hero);
        hero->setScale(0.1);
        hero->getAnimation()->play("stand");
        return true;
    }
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(MenuAvatar);
};


COMMON_LAYER_LOADER_BEGIN(MenuAvatar,NodeLoader);
COMMON_LAYER_LOADER_END();


MainMenuLayer::MainMenuLayer()
{
    m_yusha=0;
}
bool MainMenuLayer::init()
{
    if(!CCLayer::init())
        return false;

	Size sz = Director::getInstance()->getWinSize();
	Node* screen = (Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("MainMenuScreen.json");

	screen->setAnchorPoint(Point(0, 0));
	addChild(screen);

    this->setAccelerometerEnabled(true);
    return true;
}


void MainMenuLayer::onAcceleration(Acceleration* acc, Event* event)
{

}
void MainMenuLayer::registerLoader()
{
    SceneManager::instance()->registerLoader(MainMenuLayerLoader::loader());
    SceneManager::instance()->registerLoader(CloudsGeneratorLoader::loader());
    SceneManager::instance()->registerLoader(MenuAvatarLoader::loader());
}

 bool MainMenuLayer::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
    if(pMemberVariableName==NULL)
        return  false;
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "YushaMenu", MenuAvatar*, this->m_yusha);
    
    return false;
}
SEL_MenuHandler MainMenuLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onKingdomPress:", MainMenuLayer::onKingdomPress);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStatusPress:" , MainMenuLayer::onStatusPress);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onQuestPress:"  , MainMenuLayer::onQuestPress);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStartPress:"  , MainMenuLayer::onStartPress);
    return NULL;
}
extension::Control::Handler MainMenuLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
    return  NULL;
}
void MainMenuLayer::switchToNextScreen()
{
}

void MainMenuLayer::onKingdomPress(Object* pSender)
{
    CCLOG("onKingdom\n");
}
void MainMenuLayer::onStatusPress(Object* pSender)
{
    CCLOG("onStatusPress\n");
}
void MainMenuLayer::onQuestPress(Object* pSender)
{
    CCLOG("onQuestPress\n");
    
}
void MainMenuLayer::onStartPress(Object* pSender)
{
    CCLOG("onStartPress\n");
}
// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* MainMenuLayer::scene()
{
    
    // 'scene' is an autorelease object
    //Scene *scene = SceneManager::instance()->LoadScene("MainMenuScene");
	// return the scene
	Scene* scene = new Scene();
	MainMenuLayer* layer = new MainMenuLayer();
	layer->init();
	scene->addChild(layer);
    return scene;
}
