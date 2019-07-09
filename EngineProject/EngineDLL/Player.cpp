#include "Player.h"
#include "GLFW\glfw3.h"
#include "Tilemap.h"
Player::Player(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	flyingAnimation = new Animation(this);
	dieAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	flyingAnimation->CreateAnimation("Flying", 0, 2, false);
	dieAnimation->CreateAnimation("Die", 3, 6, false);
	animator->AddAnimation(idleAnimation);
	animator->AddAnimation(flyingAnimation);
	animator->AddAnimation(dieAnimation);
}


Player::~Player()
{
}

void Player::OnUpdate(float deltaTime)
{
	direction = b2Vec2(cos(((angleRotation * RADTODEG) + 90) * DEGTORAD), sin(((angleRotation * RADTODEG) + 90) * DEGTORAD));
	// Move UP
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_UP) == GLFW_PRESS) {
		animator->Play("Flying", deltaTime);
		rigidBody->ApplyForceToCenter(8000 * direction, true);
	}
	else
	{
		animator->Play("Idle", deltaTime);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		angleRotation -= deltaTime * 1;

	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		angleRotation += deltaTime * 1;

	}
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_1) == GLFW_PRESS) {
		SetPosition(-200, 0, 5);
	}
	if (rigidBody)
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);	
	SetRotate(0, 0, angleRotation);
}
void Player::CollisionCallback()
{
	cout << "ola: " <<rigidBody->GetLinearVelocity().x << "," << rigidBody->GetLinearVelocity().y << endl;	
	if (CloseToZero(rigidBody->GetLinearVelocity().x) && CloseToZero(rigidBody->GetLinearVelocity().y))
	{
		b2Vec2 v;
		v.Set(0.0f, 0.0f);
		rigidBody->SetLinearVelocity(v);
	}
	else
	{
		b2Vec2 vec;
		vec.Set(0.0f, 0.0f);
		rigidBody->SetLinearVelocity(vec);
		rigidBody->SetTransform(vec, 0);
	}
}
void Player::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}
bool Player::CloseToZero(float value)
{
	if (value < 3.0f && value > -3.0f)
		return true;
	return false;
}