#include "Player.h"
#include "Map.h"
#include "CombatText.h"
#include "Game.h"

Player::Player() : Character()
{

}

// Static player
Player::Player(Game * pGame, const string pTexturePath, const sf::Vector2i pPosition) : Character(pGame, pTexturePath, pPosition)
{
	UpdateAnimation();
	mSpeedBuffDuration = 5.f;
}

// Animated player
Player::Player(Game * pGame, const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition) : Character(pGame, pTexturePath, pSpriteSheetSize, pPosition)
{
	UpdateAnimation();
	mSpeedBuffDuration = 5.f;
}

Player::~Player()
{

}

// Update the player
void Player::Update(const float pDeltaSeconds)
{
	Character::Update(pDeltaSeconds);

	if (IsActive()) {
		MoveTo();
	}

	CheckSpeedBuff();
}

// Draw the player
void Player::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	Character::draw(pTarget, pStates);
}

// Check the movement direction
void Player::MoveTo()
{
	// Make sure that the player is not currently moving
	if (IsAtWantedPosition())
	{
		// Get the keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// Set the wanted position and the current direction
			SetWantedPosition(GetPosition() + sf::Vector2i(0, -1));
			SetCurrentDirection(Map::Direction::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			SetWantedPosition(GetPosition() + sf::Vector2i(0, 1));
			SetCurrentDirection(Map::Direction::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			SetWantedPosition(GetPosition() + sf::Vector2i(-1, 0));
			SetCurrentDirection(Map::Direction::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			SetWantedPosition(GetPosition() + sf::Vector2i(1, 0));
			SetCurrentDirection(Map::Direction::Right);
		}
		else 
		{
			// If the player is not moving and no key is being pressed, set the player state to idle
			if (IsAtWantedPosition()) {
				SetIsIdle(true);
			}
		}
	}
}

//Override the update of the wantedposition
void Player::SetWantedPosition(const sf::Vector2i pWantedPosition)
{
	Character::SetWantedPosition(pWantedPosition);

	// Make the player not idle
	SetIsIdle(false);
}

// Override the update of the current position
void Player::SetPosition(const sf::Vector2i pPosition)
{
	Character::SetPosition(pPosition);

	// Check if any food is at the new position
	Food * food = GetGame()->GetMap().GetFoodAtPosition(pPosition);
	if (food != nullptr)
	{
		// Add combat text
		GetGame()->AddCombatText(new CombatText("Yum", Map::GetTruePosition(GetPosition()), sf::Color((sf::Uint8) 255.f, (sf::Uint8) 127.5f, (sf::Uint8) 0.f)));

		// If the food is superfood, add the speedbuff
		if (food->GetFoodType() == Food::FoodType::Speed) {
			AddSpeedBuff(2.f);
		}

		//Eat the food
		food->Eat();

		// Let the game know a food has been eaten
		GetGame()->FoodUpdated();
	}
}

// Add a speedbuff to the player
void Player::AddSpeedBuff(const float pSpeedMultiplier)
{
	SetSpeedMultiplier(pSpeedMultiplier);
	mSpeedBuffTimer.restart();
}

// Check if the speedbuff duration has exceeded the limit
void Player::CheckSpeedBuff()
{
	if (GetSpeedMultiplier() > 1 && mSpeedBuffTimer.getElapsedTime().asSeconds() > mSpeedBuffDuration)
	{
		// Reset the speed
		SetSpeedMultiplier(1.0);
	}
}

// Kill the player
void Player::Die()
{
	SetIsActive(false);
	SetIsIdle(true);
}