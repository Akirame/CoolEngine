#include "SceneNode.h"
#include "Transform.h"

void SceneNode::SetParent(SceneNode* _parent)
{
	parent = _parent;
}

void SceneNode::AddNode(SceneNode* node) 
{
	if (node != nullptr) {
		children.push_back(node);
		node->SetParent(this);
	}
}

void SceneNode::Update(float deltaTime) 
{
	for (std::vector<Component*>::iterator iter = componentList.begin();
		iter != componentList.end(); iter++) {
		(*iter)->Update(deltaTime);
	}

	for (std::vector<SceneNode*>::iterator iter = children.begin();
		iter != children.end(); iter++) {
		(*iter)->Update(deltaTime);
	}
}

Component* SceneNode::GetComponent(ComponentType componentType) {
	for (std::vector<Component*>::iterator iter = componentList.begin();
		iter != componentList.end(); iter++) {
		if ((*iter)->GetType() == componentType)
			return *iter;
	}
	return nullptr;
}

SceneNode::~SceneNode() 
{
	Destroy();
}

void SceneNode::Destroy() 
{
	for (std::vector<SceneNode*>::iterator iter = children.begin();
		iter != children.end(); iter++) 
	{
		if ((*iter) != nullptr)
			(*iter)->Release();
	}
	children.clear();
}

void SceneNode::Release() 
{
	delete this;
}

SceneNode* SceneNode::GetParent() 
{
	return parent;
}

Transform* SceneNode::GetTransform() 
{
	return transform;
}

SceneNode* SceneNode::GetChild(int index) 
{
	if (index >= 0 && index < children.size())
		return children[index];
	return nullptr;
}