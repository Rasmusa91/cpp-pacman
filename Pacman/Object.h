#ifndef OBJECT_H
#define OBJECT_H

#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

using namespace std;

class Object : public sf::Drawable
{
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2i mSpriteSheetSize;
	sf::Vector2i * mCustomSpriteSheet;
	int mCustomSpriteSheetSize;
	sf::Vector2i mSpriteSheetPosition;
	float mSpriteSheetTimer;
	float mSpriteSheetDuration;
	bool mIsSpriteSheet;

	sf::Vector2i mPosition;
	sf::Vector2f mOffsetPosition;

	bool mIsActive;

	void UpdateAnimation();
	void UpdateCustomAnimation();

public:
	Object();
	Object(const string pTexturePath, const sf::Vector2i pPosition);
	Object(const string pTexturePath, const sf::Vector2i pSpriteSheetSize, const sf::Vector2i pPosition);
	virtual ~Object();

	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;
	virtual void Update(const float pDeltaSeconds);

	void SetCustomSpriteSheet(sf::Vector2i * pCustomSpriteSheet, const int pCustomSpriteSheetSize);

	sf::Vector2i GetPosition() const;
	virtual void SetPosition(const sf::Vector2i pPosition);
	sf::Vector2f GetOffsetPosition() const;
	void SetOffsetPosition(const sf::Vector2f pOffsetPosition);

	bool IsActive() const;
	void SetIsActive(const bool pState);
};

#endif