#include "Player.h"
#include "stdafx.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Graphics/harry_potter.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load image!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 64, 32, 32);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(5.f, 5.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 8.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.93f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}


Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//acceleration
	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.x += dir_y * this->acceleration; gravity

	//limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//deceleration
	this->velocity *= this->drag;

	//limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
	{
		this->sprite.move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
	{
		this->sprite.move(0.f, 1.f);
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		
	}*/
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
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
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
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

	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
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
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}



