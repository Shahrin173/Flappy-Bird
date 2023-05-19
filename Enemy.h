#pragma once
#include "stdafx.h"
#include "Spell.h"

enum season {spring = 0};

class Enemy
{
private:

	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	//Core

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	/*void initPhysics();*/

public:
	Enemy();
	virtual ~Enemy();

	//Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void resetVelocityX();

	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);

	/*Enemy(sf::Vector2f size)
	{
		enemy.setSize(size);
		enemy.setFillColor(sf::Color::Red);
	}

	void setPos(sf::Vector2f newPos)
	{
		enemy.setPosition(newPos);
	}
	void checkColl(Spell spell)
	{
		if (spell.getRight() > enemy.getPosition().x &&
			spell.getTop() < enemy.getPosition().y + enemy.getSize().y &&
			spell.getBottom() > enemy.getPosition().y)
		{
			enemy.setPosition(sf::Vector2f(57785, 68378));
		}
	}*/
};