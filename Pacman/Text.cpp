#include "Text.h"

Text::Text()
{
}

// Create a string object
Text::Text(const string pString, const sf::Color pColor, const sf::Vector2f pPosition, const int mFontSize)
{
	// Get the font
	if (mFont.loadFromFile("../Assets/Fonts/arial.ttf")) {
		mText.setFont(mFont);
	}

	// Set some attributes
	mText.setString(pString);
	mText.setColor(pColor);
	mText.setPosition(pPosition);
	mText.setCharacterSize(mFontSize);
	mText.setStyle(sf::Text::Bold);
	mShadowText = mText;
	mShadowText.setColor(sf::Color::Black);
	mShadowText.setPosition(mText.getPosition() - sf::Vector2f(2, 2));

	mAlignment = Alignment::Left;
	SetAlignment(mAlignment);
}


Text::~Text()
{

}

// Draw the text object and its shadow
void Text::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	pTarget.draw(mShadowText);
	pTarget.draw(mText);
}

// Update the string of the text
void Text::SetText(const string pText)
{
	mText.setString(pText);
	mShadowText.setString(pText);

	// Make sure it's still aligning
	SetAlignment(mAlignment);
}

// Align the text
void Text::SetAlignment(const Alignment pAlignment)
{
	mAlignment = pAlignment;
	sf::FloatRect r = mText.getLocalBounds();

	if (pAlignment == Alignment::Left) {
		mText.setOrigin(r.left, r.top + r.height * 0.5f);
		mShadowText.setOrigin(r.left, r.top + r.height * 0.5f);
	}
	else if (pAlignment == Alignment::Center) {
		mText.setOrigin(r.left + r.width * 0.5f, r.top + r.height * 0.5f);
		mShadowText.setOrigin(r.left + r.width * 0.5f, r.top + r.height * 0.5f);
	}
	else if (pAlignment == Alignment::Right) {
		mText.setOrigin(r.left + r.width, r.top + r.height * 0.5f);
		mShadowText.setOrigin(r.left + r.width, r.top + r.height * 0.5f);
	}

}

// Set the text underlined
void Text::SetUnderlined()
{
	mText.setStyle(sf::Text::Underlined);
}

// Get the bounds of the text
sf::FloatRect Text::GetGlobalBounds() const
{
	return mText.getGlobalBounds();
}

// Set the position of the text
void Text::SetPosition(const sf::Vector2f pPosition)
{
	mText.setPosition(pPosition);
	mShadowText.setPosition(pPosition - sf::Vector2f(2, 2));
}

// Get the position of the text
sf::Vector2f Text::GetPosition() const
{
	return mText.getPosition();
}
