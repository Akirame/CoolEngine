#include "Entity.h"


Entity::Entity(Renderer* _renderer) :
	renderer(_renderer)
{		
	pos[0] = pos[1] = pos[2] = 0;
	rot[0] = rot[1] = rot[2] = 0;
	scl[0] = scl[1] = scl[2] = 1;

	model = glm::mat4(1.0f);
	translate = glm::mat4(1.0f);
	rotateX = glm::mat4(1.0f);
	rotateY = glm::mat4(1.0f);
	rotateZ = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);
}
glm::vec3 Entity::GetPos() 
{ 
	return pos; 
}
void Entity::CreateCollider(float width, float height, bool trigger, bool _isStatic)
{
	BBHeight = height;
	BBWidth = width;
	collider = new BoxCollider(width, height, trigger, _isStatic);
}

Entity::~Entity()
{
}

