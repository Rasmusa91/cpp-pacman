#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
private:
	sf::Clock mSpeedBuffTimer;
	float mSpeedBuffDuration;
	void CheckSpeedBuff();
	void AddSpeedBuff(const float pSpeedMultiplier);

public:
	Player();
	Player(Game * pGame, const string pTexturePath, const sf::Vector2i pPosition);
	Player(Game * pGame, const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition);
	virtual ~Player();

	virtual void Update(const float pDeltaSeconds);
	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;

	virtual void MoveTo();
	virtual void SetWantedPosition(const sf::Vector2i pWantedPosition);
	virtual void SetPosition(const sf::Vector2i pPosition);
	
	void Die();
};

#endif