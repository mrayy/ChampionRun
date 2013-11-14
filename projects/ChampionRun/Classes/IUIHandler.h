

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   10:48
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\IUIHandler.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	IUIHandler
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __IUIHandler__
#define __IUIHandler__


#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


namespace ChampionRun
{

class IUIHandler :public Object,public ISceneReaderListener
{
protected:
	UIWidget* m_panel;

	IUIHandler* m_prev;
	UILayer* m_root;
public:
	IUIHandler():m_panel(0),m_prev(0)
	{}
	virtual~IUIHandler(){}


	virtual void SetPanel(UIWidget* panel){ m_panel = panel; if (m_panel)m_panel->retain(); }
	virtual UIWidget* GetPanel(){ return m_panel; }

	virtual void OnWidgetLoaded(UIWidget* widget)=0;

	virtual void Push(IUIHandler* prev, UILayer* root) 
	{
		m_prev = prev; 
		m_root = root; 
		if (m_root)
		{
			m_root->addWidget(m_panel);
			m_panel->setVisible(true);
		}
	}
	virtual void Pop()
	{
		if (m_root)
			m_root->removeWidget(m_panel);
		m_panel->setVisible(false);

		if(m_prev)
			m_prev->Restore();
		m_prev = 0;
	}
	virtual void Restore()
	{
		if (m_root && m_panel->getParent()!=m_root->getRootWidget())
		{
			m_panel->removeFromParent();
			m_root->addWidget(m_panel);
		}
		m_panel->setVisible(true);
	}
};

}


#endif
