//#pragma once
//#include "hjBehaviorTree.h"
//#include "hjInput.h"
//#include "hjTime.h"
//
//namespace hj
//{
//	class IsCharWalk: public CompositeNode
//	{
//		virtual bool Invoke() override
//		{
//			if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::LEFT))
//			{
//				GetChildren()[0]
//			}
//			
//			return false;
//		}
//	};
//	class IsCharRun : public CompositeNode
//	{
//		virtual bool Invoke() override
//		{
//
//			return false;
//		}
//	};
//	class IsCharJump : public CompositeNode
//	{
//		virtual bool Invoke() override
//		{
//
//			return false;
//		}
//	};
//}
//
//
//class Node
//{
//public:
//	virtual bool Invoke() = 0;
//};
//
//class CompositeNode : public Node
//{
//public:
//	void AddChild(Node* node)
//	{
//		mChildren.push_back(node);
//	}
//	const std::vector<Node*>& GetChildren()
//	{
//		return mChildren;
//	}
//private:
//	std::vector<Node*> mChildren;
//};
//
//class Decorator : public CompositeNode
//{
//public:
//	virtual bool Invoke() override
//	{
//		if (GetChildren()[0]->Invoke())
//		{
//			return true;
//		}
//		return false;
//	}
//private:
//	BehaviorTree
//};
//
//class Selector : public CompositeNode
//{
//public:
//	virtual bool Invoke() override
//	{
//		for (auto node : GetChildren())
//		{
//			if (node->Invoke())
//			{
//				/*decorator
//				if(dynamic_cast<Decorator*>(node))*/
//				return true;
//			}
//		}
//		return false;
//	}
//private:
//	std::vector<Node*> mChildren;
//};
//
//class Sequence : public CompositeNode
//{
//public:
//	virtual bool Invoke() override
//	{
//		for (auto node : GetChildren())
//		{
//			if (!node->Invoke())
//				return false;
//		}
//		return true;
//	}
//};