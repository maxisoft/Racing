#include "stdafx.h"
#include "Checkpoint.h"


Checkpoint::Checkpoint(b2World *world, const std::string nameparam, const float init_pos_x, const float init_pos_y, const sf::Vector2u size) :
BoxGameObject(world),
name(nameparam)
{
	b2BodyDef bodydef;
	bodydef.position.Set(init_pos_x, init_pos_y);

	body = world->CreateBody(&bodydef);
	body->SetUserData(this);

	b2PolygonShape* dynamicBox = new b2PolygonShape();
	dynamicBox->SetAsBox(static_cast<float>(size.x), static_cast<float>(size.y));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = dynamicBox;
	fixtureDef.filter.categoryBits = BoxGameObject::CHECKPOINT_MASK;

	//actives la detection des collisions seulement pour les roues des voitures
	fixtureDef.filter.maskBits = BoxGameObject::WHEEL_MASK;

	// la voiture passe au travers
	fixtureDef.isSensor = true;

	body->CreateFixture(&fixtureDef);

	delete dynamicBox;
	
}


Checkpoint::~Checkpoint()
{
}


const GameObjectTypes Checkpoint::getGType(void) const
{
	return GameObjectTypes::CheckpointType;
}
