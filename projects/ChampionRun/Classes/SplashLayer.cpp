//
//  SplashLayer.cpp
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#include "SplashLayer.h"
#include "SceneManager.h"
#include "MainMenuLayer.h"


bool SplashLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    Node* node=Node::create();
    addChild(node);
    node->runAction(CCSequence::create(CCDelayTime::create(5),CCCallFunc::create(this, callfunc_selector(SplashLayer::switchToNextScreen)), NULL));
	
	Size sz= Director::getInstance()->getWinSize();
	LayerColor* bg = LayerColor::create(Color4B(0, 0, 0, 255), sz.width, sz.height);
	/*Node* screen=(Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("SplashScreen.json");

	bg->addChild(screen);
	screen->setAnchorPoint(Point(0, 0));*/

	armature::Armature* logo=armature::Armature::create("LogoAnimation");
	if (logo)
	{
		logo->getAnimation()->playByIndex(0);
		bg->addChild(logo);
		logo->setPositionX(sz.width / 2);
		logo->setPositionY(sz.height / 2);
	}

	addChild(bg);

    return true;
}


void SplashLayer::registerLoader()
{
    SceneManager::instance()->registerLoader(SplashLayerLoader::loader());
}


void SplashLayer::switchToNextScreen()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuLayer::scene()));
}

// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* SplashLayer::scene()
{
    
    // 'scene' is an autorelease object
  //  Scene *scene = SceneManager::instance()->LoadScene("SplashScene");
        // return the scene
	Scene* scene = new Scene();
    SplashLayer* layer=new SplashLayer();
    layer->init();
	scene->addChild(layer);
    return scene;
}
