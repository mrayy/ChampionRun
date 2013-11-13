#include "AppDelegate.h"
#include "WalkDetectorScene.h"
#include "SceneManager.h"
#include "Helpers.h"
#include "SplashLayer.h"
#include "MainMenuLayer.h"

USING_NS_CC;

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
    
    
	Size designSize = Size(1136, 640);
	Size resorceSize = Size(1136, 640);
    Size screenSize = CCEGLView::getInstance()->getFrameSize();
    
    std::vector<std::string> resDir;
	Application::Platform platform = CCApplication::getInstance()->getTargetPlatform();
	std::vector<std::string> searchPaths = CCFileUtils::getInstance()->getSearchPaths();
	searchPaths.insert(searchPaths.begin(), "Published-iOS");
	searchPaths.insert(searchPaths.begin(), "Published-iOS/Scenes");
	CCFileUtils::getInstance()->setSearchPaths(searchPaths);
    if(platform==Application::Platform::OS_IPHONE || platform==Application::Platform::OS_IPAD)
    {
        
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
                    resorceSize=Size(1136,640);
                    resDir.push_back("resources-iphonehd");
                }else
                {
                    resDir.push_back("resources-iphone");
                }
    }else if(platform==kTargetAndroid || platform==kTargetWindows)
    {
        
        if(screenSize.width>720)
        {
			resorceSize = Size(1136, 640);
			resDir.push_back("resources-iphonehd");
        }else
            if(screenSize.width>568)
            {
				resorceSize = Size(720, 480);
				resDir.push_back("resources-iphonehd");
            } else
            {
                resorceSize=Size(568,320);
                resDir.push_back("resources-small");
            }
    }
    
    CCFileUtils::getInstance()->setSearchResolutionsOrder(resDir);
    pDirector->setContentScaleFactor(resorceSize.width/designSize.width);
    CCEGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	
	SceneManager::instance();//make sure it is inited
#ifdef _DEBUG
    // turn on display FPS
    pDirector->setDisplayStats(true);
#endif
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // run
    //pDirector->runWithScene(SceneManager::instance()->LoadScene("MainMenuScene"));
    // 
	pDirector->runWithScene(MainMenuLayer::scene());// SplashLayer::scene());
    //WalkDetectorScene::scene());//

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
