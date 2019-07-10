#pragma once
#include "Exports.h"
#include "Box2D\Box2D.h"
#include "Shape.h"

class ENGINEDLL_API MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Shape*>(bodyUserData)->CollisionCallback();

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Shape*>(bodyUserData)->CollisionCallback();

	}

	void EndContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Shape*>(bodyUserData)->CollisionCallback();

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Shape*>(bodyUserData)->CollisionCallback();

	}
};