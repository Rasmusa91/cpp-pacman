#include "Object.h"
#include "Map.h"

Object::Object()
{
}

// Initialize a static sprite
Object::Object(const string pTexturePath, const sf::Vector2i pPosition)
{
	if (mTexture.loadFromFile(pTexturePath)) {
		mSprite.setTexture(mTexture);
	}

	mPosition = pPosition;
	mSprite.setPosition(Map::GetTruePosition(mPosition));

	mCustomSpriteSheet = nullptr;

	mIsActive = true;
}

// Initialize a animation with a spritesheet
Object::Object(const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition) : Object(pTexturePath, pPosition)
{
	mIsSpriteSheet = true;

	mSpriteSheetSize = pSpriteSheetSize;
	mSpriteSheetPosition = sf::Vector2i(0, 0);
	mSprite.setTextureRect(sf::IntRect(mSpriteSheetPosition.x * Map::TILESIZE, mSpriteSheetPosition.y * Map::TILESIZE, Map::TILESIZE, Map::TILESIZE));

	mSpriteSheetTimer = 0;
	mSpriteSheetDuration = 0.5f;
}

Object::~Object()
{
	if (mCustomSpriteSheet != nullptr) {
		delete[] mCustomSpriteSheet;
	}
}

// Update the spritesheet animation
void Object::Update(const float pDeltaSeconds)
{
	// Makesure that the object is an animation
	if (mIsSpriteSheet)
	{
		mSpriteSheetTimer += pDeltaSeconds;

		if (mSpriteSheetTimer > mSpriteSheetDuration)
		{
			if (mCustomSpriteSheet == nullptr) {
				UpdateAnimation();
			}
			else {
				UpdateCustomAnimation();
			}

			mSpriteSheetTimer = 0;
		}
	}
}

// Draw the sprite
void Object::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	pTarget.draw(mSprite);
}

// Animate a normal spritesheet (at a normal spritesheet every frame is checked in the sheet)
void Object::UpdateAnimation()
{
	mSpriteSheetPosition.x++;

	if (mSpriteSheetPosition.x >= mSpriteSheetSize.x)
	{
		mSpriteSheetPosition.y++;
		mSpriteSheetPosition.x = 0;

		if (mSpriteSheetPosition.y >= mSpriteSheetSize.y) {
			mSpriteSheetPosition.y = 0;
		}
	}

	mSprite.setTextureRect(sf::IntRect(mSpriteSheetPosition.x * Map::TILESIZE, mSpriteSheetPosition.y * Map::TILESIZE, Map::TILESIZE, Map::TILESIZE));
}

// Animate a custom spritesheet (at a custom spritesheet, the frames to be checked is specified manually with an array of vectors)
void Object::UpdateCustomAnimation()
{
	mSpriteSheetPosition.x++;

	if (mSpriteSheetPosition.x >= mCustomSpriteSheetSize) {
		mSpriteSheetPosition.x = 0;
	}

	mSprite.setTextureRect(sf::IntRect(mCustomSpriteSheet[mSpriteSheetPosition.x].x * Map::TILESIZE, mCustomSpriteSheet[mSpriteSheetPosition.x].y * Map::TILESIZE, Map::TILESIZE, Map::TILESIZE));
}

// Update the custom spritesheet
void Object::SetCustomSpriteSheet(sf::Vector2i * pCustomSpriteSheet, const int pCustomSpriteSheetSize)
{
	delete[] mCustomSpriteSheet;

	mCustomSpriteSheet = pCustomSpriteSheet;
	mCustomSpriteSheetSize = pCustomSpriteSheetSize;
	mSpriteSheetPosition = sf::Vector2i(0, 0);
	UpdateCustomAnimation();
}

// Get the tile position of the object
sf::Vector2i Object::GetPosition() const
{
	return mPosition;
}

// Update the position of the object
void Object::SetPosition(const sf::Vector2i pPosition)
{
	mPosition = pPosition;

	// Let the sprite know that the position has been updated
	mSprite.setPosition(Map::GetTruePosition((sf::Vector2f) mPosition + mOffsetPosition));
}

// Get the offset position
sf::Vector2f Object::GetOffsetPosition() const
{
	return mOffsetPosition;
}

// Update the offsetposition of the object
void Object::SetOffsetPosition(const sf::Vector2f pOffsetPosition)
{
	mOffsetPosition = pOffsetPosition;

	//Let the sprite know
	mSprite.setPosition(Map::GetTruePosition((sf::Vector2f) mPosition + mOffsetPosition));
}

// Check if the object is active
bool Object::IsActive() const
{
	return mIsActive;
}

// Update the activity status of the object
void Object::SetIsActive(const bool pState)
{
	mIsActive = pState;
}