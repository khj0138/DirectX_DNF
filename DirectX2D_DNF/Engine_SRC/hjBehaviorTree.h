//#pragma once
////#include "hjGameObject.h"
//#include "hjEngine.h"
//#include "hjNode.h"
////#include "hjComponent.h"
////#include "hjTransform.h"
//
//namespace hj
//{
//
//	class BehaviorTree
//	{
//	public:
//		BehaviorTree();
//		~BehaviorTree();
//
//		/*enum class eNodeType
//		{
//			Node,
//			CompositeNode,
//			Selector,
//			Sequence,
//			End,
//		};*/
//		/*struct Behavior
//		{
//			std::wstring name;
//
//			std::vector<Behavior*> next;
//			Behavior* root;
//		};*/
//		void Update();
//
//		void AddNode(std::wstring name, Node* child) { mNodes.insert(std::make_pair(name , child)); }
//		Node* FindNode(std::wstring name) { return  mNodes.find(name)->second; }
//		void AddChild(std::wstring parent, std::wstring child);
//		void SetRoot(Node* root) { mRoot = root; }
//		Node* GetRoot() { return mRoot; }
//		void SetActiveNode(Node* node) { mActiveNode = node; }
//	private:
//		Node* mRoot;
//		Node* mActiveNode;
//		std::map<std::wstring, Node*> mNodes;
//	};
//}
//
