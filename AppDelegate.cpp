#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SceneManager.h"
#include "cocos-ext.h"

USING_NS_CC;

using namespace cocos2d::extension::armature;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    Director* pDirector = CCDirector::getInstance();
    EGLView* pEGLView = CCEGLView::getInstance();
    
    pDirector->setOpenGLView(pEGLView);
    
    
    Size designSize = Size(480, 320);
    Size resorceSize= Size(480, 320);
    Size screenSize = CCEGLView::getInstance()->getFrameSize();
    
    std::vector<std::string> resDir;
    Application::Platform platform=CCApplication::getInstance()->getTargetPlatform();
    if(platform==Application::Platform::OS_IPHONE || platform==Application::Platform::OS_IPAD)
    {
        std::vector<std::string> searchPaths=CCFileUtils::getInstance()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), "Published-iOS");
        CCFileUtils::getInstance()->setSearchPaths(searchPaths);
        
        if(screenSize.height>768)
        {
            resorceSize=Size(2048,1536);
            resDir.push_back("resources-ipadhd");
        }else
            if(screenSize.height>640)
            {
                resorceSize=Size(1536,768);
                resDir.push_back("resources-ipad");
            }else
                if(screenSize.height>480)
                {
                    resorceSize=Size(960,480);
                    resDir.push_back("resources-iphonehd");
                }else
                {
                    resDir.push_back("resources-iphone");
                }
    }else if(platform==kTargetAndroid || platform==kTargetWindows)
	{
		std::vector<std::string> searchPaths = CCFileUtils::getInstance()->getSearchPaths();
		searchPaths.insert(searchPaths.begin(), "..\Published-Android");
		CCFileUtils::getInstance()->setSearchPaths(searchPaths);
        
        if(screenSize.width>720)
        {
            resorceSize=Size(960,640);
            resDir.push_back("resources-large");
        }else
            if(screenSize.width>568)
            {
                resorceSize=Size(720,480);
                resDir.push_back("resources-medium");
            } else
            {
                resorceSize=Size(568,320);
                resDir.push_back("resources-small");
            }
    }
    
    CCFileUtils::getInstance()->setSearchResolutionsOrder(resDir);
//    pDirector->setContentScaleFactor(resorceSize.width/designSize.width);
    CCEGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);

	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // run
    //pDirector->runWithScene(SceneManager::instance()->LoadScene("MainMenuScene"));
	Scene* scene = Scene::create();
//	LayerColor* layer = LayerColor::create(Color4B(255, 0, 0, 255),pDirector->getWinSize().width,pDirector->getWinSize().height);

//	scene->addChild(layer);
//	extension::UILayer* layer = extension::UILayer::create();
//	layer->addWidget(CCUIHELPER->createWidgetFromJsonFile("DemoLogin\\DemoLogin.json"));
//	Node*node = (Node*)extension::SceneReader::getInstance()->createNodeWithSceneFile("FightScene.json");
	/*->addChild(node);
	node->setScale(0.5);*/
	
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Characters/Yusha/Yusha.ExportJson");
//	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/knight.png", "armature/knight.plist", "armature/knight.xml");
	Armature* hero = Armature::create("Yusha");
	hero->getAnimation()->play("stand");
	hero->setPosition(100, 100);
	/*layer->addChild(hero);
	layer->setScale(1);*/
	hero->setScaleX(-0.1);
	hero->setScaleY( 0.1);
	scene->addChild(hero);
	//Scene* scene = SceneManager::instance()->LoadScene("SplashScenes");
	pDirector->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
