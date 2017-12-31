#include "Player.h"


Player::Player(const char *name)
{
	transform = new Transform();
	spr = new SpriteRenderer(transform, "Textures/knight.png");
}

Player::Player(const char *name, const char *tag)
{
	transform = new Transform();
	spr = new SpriteRenderer(transform, "Textures/knight.png");
}

void Player::Move(float x, float y)
{
	glm::vec2 vel(x, y);
	vel = glm::normalize(vel);
	transform->SetPosition(transform->GetPosition().x + vel.x, transform->GetPosition().y + vel.y);
}

void Player::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Move(0.1f, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Move(-0.1f, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Move(0, -1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Move(0, 1.0f);
	}
}

void Player::Update(float dt)
{

}

void Player::Draw()
{
	spr->Draw();
}
