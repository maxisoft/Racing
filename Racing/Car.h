#pragma once
#include "stdafx.h"
#include "MixedGameObject.h"
#include "StartPos.h"
class CarEngine;
class Wheel;
class CarControler;

struct CarControl
{
	CarControl::CarControl(const float dir = 0.f, const float rot = 0.f) : rotation(rot), direction(dir){};
	CarControl::~CarControl(void){};
	float rotation;
	float direction;
};

enum CarSide
{
	Ahead,
	Back
};

class Car :
	public MixedGameObject
{
	friend class sf::RenderTarget;
	friend class CarControler;
	friend class Wheel;
public:
	Car(b2World* world, const std::string& file, const float init_pos_x = 0.f, const float init_pos_y = 0.f, const float angle = 0.f);
	Car(b2World* world, const std::string& file, const std::string yml, const StartPos& startpos);
	~Car(void);
	virtual void update(float delta) final;
	const float getSpeed(void) const;
	const CarControl getlastControl(void) const;
	const CarSide getSide(void) const;
	float getMaxFrontWheelsAngle(void) const;
	const virtual GameObjectTypes getGType(void) const final;
private:
	unsigned short weight;
	const float maxfrontwheelsangle;
	float lastspeed;
	CarEngine* engine;
	CarControl lastcontrol;
	std::vector<Wheel*> wheels;
	std::vector<b2Joint*> wheelsJoints;
	void applyInertia(const float delta);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

