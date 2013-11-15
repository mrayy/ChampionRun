//
//  UIBattleTurn.h
//  ChampionRun
//
//  Created by MHD Yamen Saraiji on 11/15/13.
//
//

#ifndef __ChampionRun__UIBattleTurn__
#define __ChampionRun__UIBattleTurn__

#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace ChampionRun
{
    
    
    class UIBattleTurn
    {
    protected:
        UILayer* m_UILayer;
        
        UIImageView* m_turnImage;
    public:
        UIBattleTurn();
        virtual~UIBattleTurn();
        
        void init();
        
        UILayer* GetLayer(){ return m_UILayer; }
        
        void updateStatus();
        
    };
    
}

#endif /* defined(__ChampionRun__UIBattleTurn__) */
