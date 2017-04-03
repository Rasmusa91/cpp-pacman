#include "Enemy.h"
#include "Map.h"
#include "CombatText.h"
#include "Game.h"

Enemy::Enemy() : Character()
{
}

// Static enemy
Enemy::Enemy(Game * pGame, const string pTexturePath, const sf::Vector2i pPosition) : Character(pGame, pTexturePath, pPosition)
{

}

// Animated enemy
Enemy::Enemy(Game * pGame, const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition) : Character(pGame, pTexturePath, pSpriteSheetSize, pPosition)
{
	SetSpeedMultiplier(2);
	SetIsIdle(false);

	FindDirecton();
	SetWantedPosition(GetPosition() + Map::GetDirection(GetCurrentDirection()));
}

Enemy::~Enemy()
{

}

// Update the enemy
void Enemy::Update(const float pDeltaSeconds)
{
	Character::Update(pDeltaSeconds);

	// 20% chance every second to growl
	if (IsActive() && (int)mTalkTimer.getElapsedTime().asSeconds() > 1)
	{
		if (rand() % 5 < 1)
		{
			GetGame()->AddCombatText(new CombatText("Rawwr!!", Map::GetTruePosition(GetPosition()), sf::Color((sf::Uint8) 255.f, (sf::Uint8) 127.5f, (sf::Uint8) 0.f)));
		}

		mTalkTimer.restart();
	}
}

// Find a random direction
void Enemy::FindDirecton()
{
	Map::Direction directions[4] = {
		Map::Direction::Down,	
		Map::Direction::Left,
		Map::Direction::Right,
		Map::Direction::Up
	};

	Map::Direction availableDirections[4];
	int availableDirectionsCount = 0;

	// Iterate all possible directions
	for (int i = 0; i < 4; i++) 
	{
		// Check if the direction is not the opposite to the current,
		// Make sure that the direction is walkable
		// Make sure that there is not another enemy at the position
		if (Map::GetOppositeDirection(GetCurrentDirection()) != directions[i] && 
			GetGame()->GetMap().IsWalkable(GetPosition() + Map::GetDirection(directions[i])) && 
			!GetGame()->IsEnemyAtLocation(GetPosition() + Map::GetDirection(directions[i])))
		{
			// Add the direction to the available directions array
			availableDirections[availableDirectionsCount++] = directions[i];
		}
	}

	// If any available direcions was found
	if(availableDirectionsCount > 0) 
	{
		// Select a random one
		SetCurrentDirection(availableDirections[(int)rand() % availableDirectionsCount]);
	}
	// If not available directions was found
	else 
	{
		// Turn around
		SetCurrentDirection(Map::GetOppositeDirection(GetCurrentDirection()));
	}
}

void Enemy::MoveTo()
{
	
}

// Override the updated position
void Enemy::SetPosition(const sf::Vector2i pPosition)
{
	Character::SetPosition(pPosition);

	// Check if a player is at the new location
	if (GetGame()->IsPlayerLocation(pPosition)) {
		GetGame()->GameOver("Game Over");
	}

	// Instantly move to the next location
	FindDirecton();
	SetWantedPosition(GetPosition() + Map::GetDirection(GetCurrentDirection()));
}