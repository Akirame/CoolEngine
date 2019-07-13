#pragma once
#include "Exports.h"
#include "Component.h"
#include <vector>

class Transform;
enum ComponentType;

class ENGINEDLL_API SceneNode {
private:
	void SetParent(SceneNode* parent);

protected:
	Transform * transform;
	SceneNode* parent;

	std::vector<SceneNode*> children;
	std::vector<Component*> componentList;

public:
	SceneNode() : parent(nullptr), transform(nullptr) {	}

	virtual ~SceneNode();
	void Release();

	virtual void Update(float deltaTime);
	void Destroy();
	void AddNode(SceneNode* node);

	void AddComponent(Component* component) { componentList.push_back(component); }
	Component* GetComponent(ComponentType componentType);

	SceneNode* GetParent();
	Transform* GetTransform();
	SceneNode* GetChildrenByIndex(int index);
};