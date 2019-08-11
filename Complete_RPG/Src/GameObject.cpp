#include "GameObject.h"

GameObject::GameObject() :
	pos(0.0f, 0.0f),
	vel(0.0f, 0.0f)
{
	collider.w = 64;
	collider.h = 64;
}

GameObject::~GameObject()
{

}

bool GameObject::CheckCollision(const GameObject& other)
{
	return CheckCollision(*this, other);
}

bool GameObject::CheckCollision(const GameObject& a, const GameObject& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.collider.x;
	rightA = a.collider.x + a.collider.w;
	topA = a.collider.y;
	bottomA = a.collider.y + a.collider.h;

	//Calculate the sides of rect B
	leftB = b.collider.x;
	rightB = b.collider.x + b.collider.w;
	topB = b.collider.y;
	bottomB = b.collider.y + b.collider.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}