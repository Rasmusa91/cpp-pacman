#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class Text : public sf::Drawable
{
public:
	static enum Alignment { Left, Center, Right };

private:
	sf::Text mText;
	sf::Text mShadowText;
	sf::Font mFont;

	Alignment mAlignment;

	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;

public:
	Text();
	Text(const string pString, const sf::Color pColor, const sf::Vector2f pPosition, const int mFontSize);
	~Text();

	void SetText(const string pText);
	void SetAlignment(const Alignment pAlignment);
	void SetUnderlined();
	sf::FloatRect GetGlobalBounds() const;
	void SetPosition(const sf::Vector2f pPosition);
	sf::Vector2f GetPosition() const;
};

#endif