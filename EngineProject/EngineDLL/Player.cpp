#include "Player.h"
#include "GLFW\glfw3.h"
#include "Tilemap.h"
Player::Player(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new Animation(this);
	animator->CreateAnimation(0, 10);
	SetPosition(-200, 0, 10);
}



Player::~Player()
{
}
void Player::OnUpdate(float deltaTime)
{
	animator->OnUpdate(deltaTime);
	// Move up
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS) {			
		MoveIn(0, speed * deltaTime, 0);
		if (Tilemap::GetInstance())
		{
			if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + 1.0f, GetPos().y + BBHeight - 1.0f) || Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + BBWidth - 1.0f, GetPos().y + BBHeight - 1.0f))
			{
				SetPosition(GetPos().x, Tilemap::GetInstance()->GetTileY(GetPos().y + BBHeight) - BBHeight * 2, GetPos().z);
			}
		}
	}
	// Move down
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		MoveIn(0, -speed * deltaTime, 0);				
		
		if (Tilemap::GetInstance())
		{
			if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + 1.0f, GetPos().y + 1.0f) || Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + BBWidth - 1.0f, GetPos().y + 1.0f))
			{
				SetPosition(GetPos().x, Tilemap::GetInstance()->GetTileY(GetPos().y), GetPos().z);
			}
		}
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		MoveIn(speed*deltaTime, 0, 0);
		if (Tilemap::GetInstance())
		{
			if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + BBWidth - 1.0f, GetPos().y + 1.0f) || Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + BBWidth - 1.0f, (GetPos().y + BBHeight - 1.0f)))
			{
				float x = Tilemap::GetInstance()->GetTileX(GetPos().x + BBWidth);
				SetPosition(x - BBWidth, GetPos().y, GetPos().z);
			}
		}
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		MoveIn(-speed * deltaTime, 0, 0);			
		if (Tilemap::GetInstance())
		{
			if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + 1.0f, GetPos().y + 1.0f) || Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + 1.0f, GetPos().y + BBHeight - 1.0f))
			{
				SetPosition(Tilemap::GetInstance()->GetTileX(GetPos().x) + BBWidth, GetPos().y, GetPos().z);
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_1) == GLFW_PRESS) {
		SetPosition(-200, 0, 5);
	}
}
