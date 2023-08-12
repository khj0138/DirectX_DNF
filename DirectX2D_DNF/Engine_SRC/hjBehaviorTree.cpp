//#include "hjBehaviorTree.h"
//
//namespace hj
//{
//	BehaviorTree::BehaviorTree()
//	{
//	}
//
//	BehaviorTree::~BehaviorTree()
//	{
//	}
//
//	void BehaviorTree::Update()
//	{
//		if (mActiveNode != nullptr)
//		{
//			if (!(mActiveNode->Invoke()))
//			{
//				mActiveNode = GetRoot();
//			}
//		}
//	}
//	void BehaviorTree::AddChild(std::wstring parent, std::wstring child)
//	{
//		Node* pNode = mNodes.find(parent)->second;
//		Node* cNode = mNodes.find(child)->second;
//
//		if (pNode == nullptr || cNode == nullptr)
//			return;
//		CompositeNode* cpNode = dynamic_cast<CompositeNode*>(pNode);
//		if (cpNode != nullptr)
//		{
//			cpNode->AddChild(cNode);
//			return;
//		}
//	}
//}