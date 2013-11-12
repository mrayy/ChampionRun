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
class MainMenuLayer:public CommonLayer,public extension::CCBSelectorResolver,public extension::CCBMemberVariableAssigner
{
protected:
    MenuAvatar* m_yusha;
public:
    
    MainMenuLayer();
    
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    static void registerLoader();
    
    void switchToNextScreen();
    
    void onKingdomPress(Object* pSender);
    void onStatusPress(Object* pSender);
    void onQuestPress(Object* pSender);
    void onStartPress(Object* pSender);
    
    void onAcceleration(Acceleration* acc, Event* event);
    
    
    virtual bool onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode) ;
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName) ;
    virtual extension::SEL_CCControlHandler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName) ;
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenuLayer);
    
};


COMMON_LAYER_LOADER_BEGIN(MainMenuLayer,LayerLoader);
COMMON_LAYER_LOADER_END();
#endif /* defined(__ChampionRun__MainMenuLayer__) */
