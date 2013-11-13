//
//  MainMenuLayer.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 10/26/13.
//
//

#ifndef __ChampionRun__MainMenuLayer__
#define __ChampionRun__MainMenuLayer__

#include <iostream>
#include "CommonLayer.h"
#include "cocos-ext.h"

class MenuAvatar;
class MainMenuLayer:public CommonLayer,public extension::CCBSelectorResolver,public extension::CCBMemberVariableAssigner,public ISceneReaderListener
{
protected:
    MenuAvatar* m_yusha;

	UILayer* m_UILayer;
	extension::UIWidget* m_mainUI;
	extension::UIWidget* m_questUI;
	extension::UIWidget* m_statusUI;
	extension::UIWidget* m_rankingUI;
public:
    
    MainMenuLayer();
    
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    static void registerLoader();
    
    void switchToNextScreen();

	void OnWidgetLoaded(UIWidget* widget);
	void OnNodeLoaded(Node* node);
    
	void onKingdomPress(Object* pSender, TouchEventType event);
	void onStatusPress(Object* pSender, TouchEventType event);
	void onQuestPress(Object* pSender, TouchEventType event);
	void onStartPress(Object* pSender, TouchEventType event);
    
    void onAcceleration(Acceleration* acc, Event* event);
    
	void onQuestBackPressed(Object* pSender, TouchEventType event);
	void onQuestConfirmPressed(Object* pSender, TouchEventType event);
	void onStatusBackPressed(Object* pSender, TouchEventType event);
	void onRankingBackPressed(Object* pSender, TouchEventType event);

    
    virtual bool onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode) ;
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName) ;
    virtual extension::SEL_CCControlHandler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName) ;
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenuLayer);
    
};


COMMON_LAYER_LOADER_BEGIN(MainMenuLayer,LayerLoader);
COMMON_LAYER_LOADER_END();
#endif /* defined(__ChampionRun__MainMenuLayer__) */
