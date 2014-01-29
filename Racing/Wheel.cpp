#include "stdafx.h"
#include "Wheel.h"


Wheel::Wheel(b2World *world, Car* car, const WheelType type, const float init_pos_x, const float init_pos_y) :
BoxGameObject(world),
car_ptr(car), 
wheeltype(type)
{
	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(init_pos_x, init_pos_y);
	body = world->CreateBody(&bodydef);
	body->SetUserData(this);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.1f, 0.3f);

	b2FixtureDef *fixtureDef = new b2FixtureDef();
	fixtureDef->shape = &dynamicBox;
	fixtureDef->density = 1.f;
	fixtureDef->friction = 0.5f;

	//Permet d'avoir des collision qu'avec les checkpoints (sensor)
	fixtureDef->filter.maskBits = BoxGameObject::CHECKPOINT_MASK;
	fixtureDef->filter.categoryBits = BoxGameObject::WHEEL_MASK;
	//fixtureDef->filter.groupIndex = -8;

	body->CreateFixture(fixtureDef);

	delete fixtureDef;
}


Wheel::~Wheel()
{
}

void Wheel::update(float delta)
{
	killOrthogonalVelocity();
	if (wheeltype == Wheel::FRONTLEFT || wheeltype == Wheel::FRONTRIGHT) // les pneux de devant
	{
		
		float carangle = car_ptr->getBody()->GetAngle();

		if (car_ptr->getlastControl().rotation) // l'utilisateur veut tourn�.
		{
			float angle = car_ptr->getlastControl().rotation * 1.6f * delta;

			angle += getBody()->GetAngle();

			if (std::abs(angle - carangle) <= car_ptr->getMaxFrontWheelsAngle()) // verification de l'angle max que peut avoir un pneu par rapport a la voiture
			{
				getBody()->SetTransform(getBody()->GetPosition(), angle);
			}
		}

		//auto centrage des pneux
		float angle = getBody()->GetAngle();
		const float diffangle = angle - carangle;
		b2RevoluteJoint *joint = static_cast<b2RevoluteJoint *> (car_ptr->wheelsJoints[wheeltype]);
		if (diffangle > 0.005f)
		{
			joint->SetMotorSpeed(-1.2f);
		}
		else if (diffangle < -0.005f)
		{
			joint->SetMotorSpeed(+1.2f);
		}
		else if (getBody()->IsAwake()) //condition pour ne pas r�veiller inutilement le body
		{
			joint->SetMotorSpeed(0.f);
			getBody()->SetTransform(getBody()->GetPosition(), carangle); //centrages des roues par rapport au vehicle
		}

		if (car_ptr->getlastControl().direction) //l'utilisateur veut faire fonctionner le moteur
		{
			b2Vec2 force(0.f, car_ptr->engine->getBaseImpulseY() * 0.016666666666666666666666666666f * car_ptr->getlastControl().direction);
			force = Utils::RotateVect(force, getBody()->GetAngle());
			getBody()->ApplyLinearImpulse(force, getBody()->GetWorldCenter(), true);
		}

	}
	else // pneux arrieres
	{
		b2Vec2 rightNormal = getBody()->GetWorldVector(b2Vec2(1, 0));
		const float speed = car_ptr->getSpeed();
		b2Vec2 force = -0.0045f * getBody()->GetAngularVelocity() * speed * rightNormal;
		getBody()->ApplyLinearImpulse(force, getBody()->GetWorldCenter(), false);
	}

	//MixedGameObject::update(delta);
}

void Wheel::killOrthogonalVelocity(void)
{
	b2Vec2 velocity = getBody()->GetLinearVelocity();
	b2Vec2 sidewayaxis = getBody()->GetTransform().q.GetYAxis();
	sidewayaxis *= b2Dot(velocity, sidewayaxis);
	getBody()->SetLinearVelocity(sidewayaxis);
}

const GameObjectTypes Wheel::getGType(void) const
{
	return GameObjectTypes::WheelType;
}