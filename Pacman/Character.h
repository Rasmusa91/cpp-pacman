#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"
#include "Map.h"

class Game;
class Character : public Object
{
private:
	Game * mGame;
	sf::Vector2i mWantedPosition;
	Map::Direction mCurrentDirection;
	bool mIsIdle;

	float mSpeed;
	float mSpeedMultiplier;

	virtual void Initialize(Game * pGame, const sf::Vector2i pPosition);
	void UpdateMovement(const float pDeltaSeconds);
	float Vector2Distance(const sf::Vector2f pVector, const sf::Vector2f pVector2) const;
public:
	Character();
	Character(Game * pGame, const string pTexturePath, const sf::Vector2i pPosition);
	Character(Game * pGame, const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition);
	virtual ~Character();

	virtual void Update(const float pDeltaSeconds);
	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;

	Game * GetGame() const;

	sf::Vector2i GetWantedPosition() const;
	virtual void SetWantedPosition(const sf::Vector2i pWantedPosition);
	bool IsAtWantedPosition() const;

	void UpdateAnimation();
	virtual void MoveTo() = 0;

	void SetIsIdle(const bool pIsIdle);
	bool GetIsIdle() const;
	Map::Direction GetCurrentDirection() const;
	void SetCurrentDirection(const Map::Direction pDirection);

	void SetSpeedMultiplier(const float pSpeedMultiplier);
	float GetSpeedMultiplier() const;
};

#endif