

/********************************************************************
	created:	2013/11/14
	created:	14:11:2013   0:31
	filename: 	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes\StackNode.h
	file path:	C:\Development\cocos2d-x-3.0alpha0\projects\ChampionRun\Classes
	file base:	StackNode
	file ext:	h
	author:		MHD Yamen Saraiji
	
	purpose:	
*********************************************************************/

#ifndef __StackNode__
#define __StackNode__

#include "cocos2d.h"


namespace cocos2d
{

	enum class EStackDirection
	{
		Horizontal,
		Vertical
	};
class StackNode:public Node
{
protected:
	EStackDirection m_direction;
	float m_spacing;

	void _updateChildren();
public:
	StackNode();
	virtual~StackNode();

	bool init();

	void setDirection(EStackDirection dir);
	void setSpacing(float s);

	virtual void addChild(Node *child, int zOrder, int tag);
	virtual void removeChild(Node* child, bool cleanup = true);

	CREATE_FUNC(StackNode);

};

}


#endif
