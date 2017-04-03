#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
private:
	sf::Clock mTalkTimer;

public:
	Enemy();
	Enemy(Game * pGame, const string pTexturePath, const sf::Vector2i pPosition);
	Enemy(Game * pGame, const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition);
	virtual ~Enemy();

	virtual void Update(const float pDeltaSeconds);

	void FindDirecton();

	virtual void MoveTo();
	virtual void SetPosition(const sf::Vector2i pPosition);
};

#endif