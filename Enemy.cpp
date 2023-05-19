#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->animState = season::spring;
}

void Enemy::initTexture()
{
	if (!this->textureSheet.loadFromFile("Graphics/dragonfly.png"))
	{
		std::cout << "ERROR::ENEMY::Could not load image!" << "\n";
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 100, 133);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.f, 1.f);
}

void Enemy::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

const sf::FloatRect Enemy::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Enemy::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Enemy::resetVelocityY()
{
	this->velocity.y = 0.f;
}

Enemy::Enemy()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	/*this->initPhysics();*/
}

Enemy::~Enemy()
{

}

const bool& Enemy::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

void Enemy::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Enemy::updateMovement()
{
	this->animState = season::spring;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animState = ENEMY_ANIMATION_STATES::IDLE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animState = ENEMY_ANIMATION_STATES::IDLE;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
	{
		this->sprite.move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
	{
		this->sprite.move(0.f, 1.f);
	}*/

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{

	}*/
}

void Enemy::updateAnimations()
{
	if (this->animState == season::spring)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 64.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 32.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	/*else if (this->animState == ENEMY_ANIMATION_STATES::IDLES)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 192.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 128.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == ENEMY_ANIMATION_STATES::IDLES)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 160.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 128.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}*/
}

void Enemy::update()
{
	this->updateMovement();
	this->updateAnimations();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
