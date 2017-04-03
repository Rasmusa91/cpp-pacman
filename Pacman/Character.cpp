#include "Character.h"
#include "Map.h"
#include "Game.h"

Character::Character() : Object()
{
	
}

// Initialize a non-animated character
Character::Character(Game * pGame, const string pTexturePath, const sf::Vector2i pPosition) : Object(pTexturePath, pPosition)
{
	Initialize(pGame, pPosition);
}

// Initialize a animated character
Character::Character(Game * pGame, const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition) : Object(pTexturePath, pSpriteSheetSize, pPosition)
{
	Initialize(pGame, pPosition);
}

Character::~Character()
{

}

// Initialize the character
void Character::Initialize(Game * pGame, const sf::Vector2i pPosition)
{
	mGame = pGame;
	mWantedPosition = pPosition;
	mSpeed = 1.f;
	mSpeedMultiplier = 1.f;
	mIsIdle = true;
}

// Update the character
void Character::Update(const float pDeltaSeconds)
{
	Object::Update(pDeltaSeconds);

	// If the character is active, update the movement
	if (IsActive()) {
		UpdateMovement(pDeltaSeconds);
	}
}

// Draw the object
void Character::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	Object::draw(pTarget, pStates);
}

// Get the game of the character (for child objects)
Game * Character::GetGame() const
{
	return mGame;
}

// Get the wanted position
sf::Vector2i Character::GetWantedPosition() const
{
	return mWantedPosition;
}

// Set the wanted position
void Character::SetWantedPosition(const sf::Vector2i pWantedPosition)
{
	// Make sure the wanted position is walkable
	if (GetGame()->GetMap().IsWalkable(pWantedPosition)) {
		mWantedPosition = pWantedPosition;
	}
}

// Check if the current position is at the wanted position
bool Character::IsAtWantedPosition() const
{
	return (mWantedPosition == GetPosition());
}

// Update the movement of the character
void Character::UpdateMovement(const float pDeltaSeconds)
{
	//Only move if the character is NOT at its wanted position
	if (!IsAtWantedPosition())
	{
		//Get the value to be added to position this frame (direction * speed)
		sf::Vector2f additivePos = (sf::Vector2f) (mWantedPosition - GetPosition()) * (pDeltaSeconds * mSpeed * mSpeedMultiplier);
		// Pre-calculate the the next position of the character
		sf::Vector2f currPos = (sf::Vector2f) GetPosition() + GetOffsetPosition() + additivePos;

		// If the pre-calculated current positions distance to the start position is greated than 1 tile
		if (Vector2Distance(currPos, (sf::Vector2f) GetPosition()) >= 1.f)
		{
			// Reset the offset
			SetOffsetPosition(sf::Vector2f(0, 0));

			// Update the tile position of the character
			SetPosition(mWantedPosition);
		}
		else 
		{
			// Add the additive position (direction * speed) to the offset position
			SetOffsetPosition(GetOffsetPosition() + additivePos);
		}
	}
}

// Calculate the distance between 2 2d vectors
float Character::Vector2Distance(const sf::Vector2f pVector, const sf::Vector2f pVector2) const
{
	return sqrt(pow(pVector2.x - pVector.x, 2) + pow(pVector2.y - pVector.y, 2));
}

// Update the idle state of the character
void Character::SetIsIdle(const bool pIsIdle)
{
	if (mIsIdle != pIsIdle)
	{
		mIsIdle = pIsIdle;
		UpdateAnimation();
	}
}

// Check if the character is idle
bool Character::GetIsIdle() const
{
	return mIsIdle;
}

// Get the characters current direction
Map::Direction Character::GetCurrentDirection() const
{
	return mCurrentDirection;
}

// Update the current direction
void Character::SetCurrentDirection(const Map::Direction pDirection)
{
	if (pDirection != mCurrentDirection) 
	{
		mCurrentDirection = pDirection;
		UpdateAnimation();
	}
}

// Update the animation of the character
void Character::UpdateAnimation()
{
	int customSheetSize;
	sf::Vector2i * customSheet;

	// If the state is NOT idle, use 2 frames ({0, direction} and {2, direction})
	if (!mIsIdle)
	{
		customSheetSize = 2;
		customSheet = new sf::Vector2i[customSheetSize];
		customSheet[0] = sf::Vector2i(0, mCurrentDirection);
		customSheet[1] = sf::Vector2i(2, mCurrentDirection);
	}
	// If the state is idle, use 2 frames ({1, direction})
	else
	{
		customSheetSize = 1;
		customSheet = new sf::Vector2i[customSheetSize];
		customSheet[0] = sf::Vector2i(1, mCurrentDirection);
	}

	SetCustomSpriteSheet(customSheet, customSheetSize);
}

// Update the speed multiplier of the character
void Character::SetSpeedMultiplier(const float pSpeedMultiplier)
{
	mSpeedMultiplier = pSpeedMultiplier;
}

// Get the speed multiplier
float Character::GetSpeedMultiplier() const
{
	return mSpeedMultiplier;
}
