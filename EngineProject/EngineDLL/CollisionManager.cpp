#include "CollisionManager.h"
#include <glm\glm.hpp>
#include <math.h>
CollisionManager* CollisionManager::instance = 0;

CollisionManager* CollisionManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CollisionManager();
	}
	return instance;
}

CollisionManager::CollisionManager()
{}
void CollisionManager::AddToGroup(std::string groupName, Shape* collider)
{
	colliderMap[groupName].push_back(collider);
}

void CollisionManager::Update()
{
	CheckLineBoxCollisions();
}
void CollisionManager::SetLinesVertices(list<b2Vec2> _lineVertices)
{
	lineVertices = _lineVertices;
}
void CollisionManager::CheckLineBoxCollisions()
{
	list<Shape*>::iterator iterA = colliderMap["A"].begin();
	list<b2Vec2>::iterator iterB = lineVertices.begin();
	for (iterA; iterA != colliderMap["A"].end(); iterA++)
	{
		for (iterB; iterB != lineVertices.end(); iterB++)
		{
			if (std::next(iterB, 1) != lineVertices.end())
			{
				float x1 = (*iterB).x;
				float y1 = (*iterB).y;
				iterB++;
				float x2 = (*iterB).x;
				float y2 = (*iterB).y;
				iterB--;
				float rx = (*iterA)->GetPos().x;
				float ry = (*iterA)->GetPos().y;
				float rw = (*iterA)->GetCollider()->width / 4;
				float rh = (*iterA)->GetCollider()->height/2;
				if (lineRect(x1, y1, x2, y2, rx, ry, rw, rh))
				{
					(*iterA)->CollisionCallback();
					break;
				}
			}
		}
	}
}

bool CollisionManager::lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

	// calculate the direction of the lines
	float uA = ((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
	float uB = ((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		return true;

	return false;
}

bool CollisionManager::lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	bool left = lineLine(x1, y1, x2, y2, rx, ry, rx, ry + rh);
	bool right = lineLine(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
	bool top = lineLine(x1, y1, x2, y2, rx, ry, rx + rw, ry);
	bool bottom = lineLine(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) {
		return true;
	}
	return false;
}
void CollisionManager::CheckBoxCollisions()
{
	list<Shape*>::iterator iterA = colliderMap["A"].begin();
	list<Shape*>::iterator iterB = colliderMap["B"].begin();
	for(iterA; iterA != colliderMap["A"].end();iterA++)
	{		
		glm::vec3 diff;

		for (iterB; iterB != colliderMap["B"].end(); iterB++)
		{
			diff = (*iterB)->GetPos() - (*iterA)->GetPos();
			float modX = 0;
			float modY = 0;
			modX = std::abs(diff.x);
			modY = std::abs(diff.y);
			if (modX < (*iterA)->GetCollider()->width / 2 + (*iterB)->GetCollider()->width / 2 &&
				modY < (*iterA)->GetCollider()->height / 2 + (*iterB)->GetCollider()->height / 2)
			{
				if ((*iterA)->GetCollider()->isTrigger || (*iterB)->GetCollider()->isTrigger)
				{
					(*iterA)->OnCollision();
					(*iterB)->OnCollision();
				}
				else						
				{
					float pX = ((*iterA)->GetCollider()->width / 2 + (*iterB)->GetCollider()->width / 2) - modX;
					float pY = ((*iterA)->GetCollider()->height / 2 + (*iterB)->GetCollider()->height / 2) - modY;
					if (pX > pY)
					{
						//vertical
						if ((*iterA)->GetPos().y < (*iterB)->GetPos().y)
						{
							if((*iterA)->GetCollider()->isStatic)
								(*iterB)->MoveIn(0, pY, 0);
							else if((*iterB)->GetCollider()->isStatic)
								(*iterA)->MoveIn(0, -pY , 0);
							else
							{
								(*iterA)->MoveIn(0, -pY / 2, 0);
								(*iterB)->MoveIn(0, pY / 2, 0);
							}
						}
						else
						{
							if ((*iterA)->GetCollider()->isStatic)
							(*iterB)->MoveIn(0, -pY / 2, 0);
							else if ((*iterB)->GetCollider()->isStatic)
							(*iterA)->MoveIn(0, pY / 2, 0);
							else
							{
								(*iterA)->MoveIn(0, pY / 2, 0);
								(*iterB)->MoveIn(0, -pY / 2, 0);
							}
						}
					}
					else
					{
						//horizontal
						if ((*iterA)->GetPos().x < (*iterB)->GetPos().x)
						{
							if ((*iterA)->GetCollider()->isStatic)
							(*iterB)->MoveIn(pX / 2, 0, 0);
							else if ((*iterB)->GetCollider()->isStatic)
							(*iterA)->MoveIn(-pX / 2, 0, 0);
							else
							{
								(*iterA)->MoveIn(-pX / 2, 0, 0);
								(*iterB)->MoveIn(pX / 2, 0, 0);
							}
						}
						else
						{
							if ((*iterA)->GetCollider()->isStatic)
							(*iterB)->MoveIn(-pX / 2, 0, 0);
							else if ((*iterB)->GetCollider()->isStatic)								
							(*iterA)->MoveIn(pX / 2, 0, 0);
							else
							{
								(*iterA)->MoveIn(pX / 2, 0, 0);
								(*iterB)->MoveIn(-pX / 2, 0, 0);
							}
						}
					}
				}
			}
		}
	}
}
void CollisionManager::CheckCircleCollisions()
{
	list<Shape*>::iterator iterA = colliderMap["C"].begin();
	list<Shape*>::iterator iterB = colliderMap["D"].begin();
	for (iterA; iterA != colliderMap["C"].end(); iterA++)
	{
		glm::vec3 diff;

		for (iterB; iterB != colliderMap["D"].end(); iterB++)
		{
			diff = (*iterB)->GetPos() - (*iterA)->GetPos();
			float modX = 0;
			float modY = 0;
			float distSqr;
			modX = std::abs(diff.x);
			modY = std::abs(diff.y);
			distSqr = modX * modX + modY * modY;			
		}
	}
}


