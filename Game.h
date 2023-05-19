#pragma once
#include "Player.h"
#include "Enemy.h"
#include "stdafx.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;
	Enemy* enemy;
	/*Spell* spell; */
	
	void initWindow();
	void initPlayer();
	void initEnemy();
	/*void initSpell();*/

public:
	

	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void updateEnemy();
	void updateCollision();
	void update();
	void renderPlayer();
	void renderEnemy();
	void render();
	const sf::RenderWindow& getWindow() const;
};
