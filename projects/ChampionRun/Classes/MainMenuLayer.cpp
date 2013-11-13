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
#include "UIEvents.h"


static const ButtonEventHandler MainMenuEvents[]=
{
	{ "btnQuest", (SEL_TouchEvent)&MainMenuLayer::onQuestPress },
	{ "btnStatus", (SEL_TouchEvent)&MainMenuLayer::onStatusPress },
	{ "btnKingdom", (SEL_TouchEvent)&MainMenuLayer::onKingdomPress },
	{ "btnStart", (SEL_TouchEvent)&MainMenuLayer::onStartPress},

	{ "btnQuestBack", (SEL_TouchEvent)&MainMenuLayer::onQuestBackPressed },
	{ "btnQuestConfirm", (SEL_TouchEvent)&MainMenuLayer::onQuestConfirmPressed },

	{ "btnStatusBack", (SEL_TouchEvent)&MainMenuLayer::onStatusBackPressed},

	{ "btnRankingBack", (SEL_TouchEvent)&MainMenuLayer::onRankingBackPressed},
};
static const int MainMenuEvents_cnt = sizeof(MainMenuEvents) / sizeof(ButtonEventHandler);

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
protected:
	armature::Armature* m_hero;
public:
    MenuAvatar()
    {
		m_hero = 0;
    }
    
    virtual bool init()
    {
        if(!CCNode::init())
            return  false;
        
        //Node*node=SceneManager::instance()->LoadNode("Yusha");
       // addChild(node);
        
        m_hero=armature::Armature::create("Yusha");
		m_hero->setAnchorPoint(Point(0.5, 0));
		addChild(m_hero);
		m_hero->setScaleX(-0.3);
		m_hero->setScaleY(0.3);
		m_hero->getAnimation()->play("stand");
        return true;
    }

	void PlayStart()
	{
		m_hero->getAnimation()->play("victory");
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
	Node* screen = (Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("MainMenuScreen.json",this);	
	screen->setAnchorPoint(Point(0, 0));
	addChild(screen);

	m_mainUI = CCUIHELPER->createWidgetFromJsonFile("ui/MainMenuUI.ExportJson",this);
	m_questUI = CCUIHELPER->createWidgetFromJsonFile("ui/QuestMenuUI.ExportJson", this);
	m_statusUI = CCUIHELPER->createWidgetFromJsonFile("ui/StatusMenuUI.ExportJson", this);
	m_rankingUI = CCUIHELPER->createWidgetFromJsonFile("ui/RankingMenuUI.ExportJson", this);

	m_UILayer = extension::UILayer::create();
	addChild(m_UILayer, 10);

	m_UILayer->addWidget(m_mainUI);

	m_mainUI->retain();
	m_questUI->retain();
	m_statusUI->retain();
	m_rankingUI->retain();

    this->setAccelerometerEnabled(true);
    return true;
}
void MainMenuLayer::OnWidgetLoaded(UIWidget* widget)
{
	if (!widget->getName())
		return;

	CCLOG("Widget loaded:%s", widget->getName());
	UIButton* btn = dynamic_cast<UIButton*>(widget);
	if (btn)
	{
		SEL_TouchEvent e = ButtonEventHandler::GetEvent(widget->getName(), MainMenuEvents, MainMenuEvents_cnt);
		if (e)
			btn->addTouchEventListener(this, e);
	}
}
void MainMenuLayer::OnNodeLoaded(Node* node)
{
	if (node->GetName()=="")
		return;

	CCLOG("Node loaded:%s", node->GetName().c_str());
	if (node->GetName() == "Avatar")
	{
		m_yusha =MenuAvatar::create();
		node->addChild(m_yusha);
	}
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
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onKingdomPress:", MainMenuLayer::onKingdomPress);
 //   CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStatusPress:" , MainMenuLayer::onStatusPress);
 //   CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onQuestPress:"  , MainMenuLayer::onQuestPress);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStartPress:"  , MainMenuLayer::onStartPress);
    return NULL;
}
extension::Control::Handler MainMenuLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
    return  NULL;
}
void MainMenuLayer::switchToNextScreen()
{
}

void MainMenuLayer::onKingdomPress(Object* pSender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
		CCLOG("onKingdom\n");
}
void MainMenuLayer::onStatusPress(Object* pSender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_UILayer->removeWidget(m_mainUI);
		m_UILayer->addWidget(m_statusUI);
	}
}
void MainMenuLayer::onQuestPress(Object* pSender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_UILayer->removeWidget(m_mainUI);
		m_UILayer->addWidget(m_questUI);
	}
    
}
void MainMenuLayer::onStartPress(Object* sender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_yusha->PlayStart();
	}
}
void MainMenuLayer::onQuestBackPressed(Object* sender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_UILayer->removeWidget(m_questUI);
		m_UILayer->addWidget(m_mainUI);
	}
}
void MainMenuLayer::onQuestConfirmPressed(Object* sender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
		CCLOG("onQuestConfirmPressed\n");
}
void MainMenuLayer::onStatusBackPressed(Object* sender, TouchEventType event)
{

	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_UILayer->removeWidget(m_statusUI);
		m_UILayer->addWidget(m_mainUI);
	}
}
void MainMenuLayer::onRankingBackPressed(Object* sender, TouchEventType event)
{
	if (event == TouchEventType::TOUCH_EVENT_ENDED)
	{
		m_UILayer->removeWidget(m_rankingUI);
		m_UILayer->addWidget(m_mainUI);
	}
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
