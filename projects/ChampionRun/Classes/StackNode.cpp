

#include "StackNode.h"


namespace cocos2d
{



StackNode::StackNode()
{
	m_direction = EStackDirection::Vertical;
	m_spacing = 2;
}

StackNode::~StackNode()
{
}


void StackNode::_updateChildren()
{
	if (_children && _children->count() > 0)
	{
		Object* child;
		float offset = 0;
		CCARRAY_FOREACH(_children, child)
		{
			Node* pNode = static_cast<Node*>(child);
			if (!pNode)
				continue;

			Rect bb= pNode->getBoundingBox();
		}
	}
}


bool StackNode::init()
{
	if (!Node::init())
		return false;
	return true;
}


void StackNode::setDirection(EStackDirection dir)
{
}

void StackNode::setSpacing(float s)
{
}


void StackNode::addChild(Node *child, int zOrder, int tag)
{
}

void StackNode::removeChild(Node* child, bool cleanup)
{
}


}

