#include "Game.h"
#include "Enemy.h"
#include "Spell.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1200, 800), "Triwizardry", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemy()
{
	this->enemy = new Enemy();
}

/*void Game::initSpell()
{
	this->spell = new Spell();
}*/

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initEnemy();
}

Game::~Game()
{
	delete this->player;
	delete this->enemy;
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if(this->ev.type == sf::Event::Closed)
			this->window.close();
		else if(this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();

		if(this->ev.type == sf::Event::KeyReleased && 
		(this->ev.key.code == sf::Keyboard::A || 
		 this->ev.key.code == sf::Keyboard::D || 
		 this->ev.key.code == sf::Keyboard::S || 
		 this->ev.key.code == sf::Keyboard::W ||
		 this->ev.key.code == sf::Keyboard::Space))
			this->player->resetAnimationTimer();

	}

	this->updatePlayer();
	this->updateEnemy();

	this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderEnemy()
{
	this->enemy->render(this->window);
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateEnemy()
{
	this->enemy->update();
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left, this->window.getSize().y - this->player->getGlobalBounds().height);
	}

	//Collision left side of the screen
	if (this->player->getGlobalBounds().left < 0)
	{
		this->player->resetVelocityX();
		this->player->setPosition(0, this->player->getGlobalBounds().top);
	}

	//Collision right side of  the screen
	if (this->player->getGlobalBounds().left > (this->window.getSize().x) / 3)
	{
		this->player->resetVelocityX();
		this->player->setPosition((this->window.getSize().x) / 3, this->player->getGlobalBounds().top);
	}
}

void Game::render()
{
	this->window.clear(sf::Color::White);

	//Render game
	this->renderPlayer();
	this->renderEnemy();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	//TODO: insert return statement here
	return this->window;
}