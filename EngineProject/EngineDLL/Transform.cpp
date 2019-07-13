#include "Transform.h"
#include "EntityNode.h"

glm::vec3 World::up = glm::vec3(0, 1, 0);
glm::vec3 World::right = glm::vec3(1, 0, 0);
glm::vec3 World::foward = glm::vec3(0, 0, 1);

Transform::Transform(EntityNode* _entity) : Component(_entity)
{
	SetType(ComponentType::TRANSFORM);

	modelMatrix = glm::mat4(1.0f);

	translateMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	position = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	rotation = glm::vec3(0.0f);

	right = World::right;
	foward = World::foward;
	up = World::up;
}

void Transform::Update(float deltaTime) 
{
	UpdateModelMatrix();
}

void Transform::UpdateModelMatrix() {
	modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;

	if (entity->GetParent() != nullptr) 
	{
		Transform* parentTransform = entity->GetParent()->GetTransform();
		modelMatrix = parentTransform->GetModelMatrix() * modelMatrix;
	}
}

void Transform::SetPosition(const glm::vec3& _position)
{
	position = _position;
	translateMatrix = glm::translate(glm::mat4(1.0f), position);
}

void Transform::SetPosition(float x, float y, float z) 
{
	position = glm::vec3(x, y, z);
	translateMatrix = glm::translate(glm::mat4(1.0f), position);
}

void Transform::SetScale(const glm::vec3& _scale)
{
	scale = _scale;
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
}

void Transform::SetScale(float x, float y, float z) 
{
	scale = glm::vec3(x, y, z);
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
}

void Transform::Walk(float speed) 
{
	position += foward * speed;
}

void Transform::Strafe(float speed) 
{
	position += right * speed;
}

void Transform::Elevate(float speed) 
{
	position += up * speed;
}
void Transform::Pitch(float angle) 
{
	rotation.x = angle;
	rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), World::right);
	UpdateUnitVectors();
}

void Transform::Yaw(float angle) {
	rotation.y = angle;
	rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), World::up);
	UpdateUnitVectors();
}

void Transform::Roll(float angle) {
	rotation.z = angle;
	rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), World::foward);
	UpdateUnitVectors();
}

void Transform::UpdateUnitVectors() 
{
	glm::vec4 newFoward = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	newFoward = rotateMatrix * newFoward;
	foward.x = newFoward.x;
	foward.y = newFoward.y;
	foward.z = newFoward.z;

	glm::vec4 newUp = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	newUp = rotateMatrix * newUp;
	up.x = newUp.x;
	up.y = newUp.y;
	up.z = newUp.z;

	right = glm::normalize(glm::cross(foward, up));
}