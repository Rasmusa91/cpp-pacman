#ifndef COMBATTEXT_H
#define COMBATTEXT_H

#include <string>

#include "SFML\Graphics.hpp"
#include "Text.h"

using namespace std;

class CombatText : public sf::Drawable
{
private:
	Text * mText;
	
	bool mIsActive;
	float mSpeed;
	sf::Clock mTimer;
	float mTimerDuration;

public:
	CombatText();
	CombatText(const string pString, const sf::Vector2f pPosition, const sf::Color pColor);
	~CombatText();

	virtual void Update(const float pDeltaSeconds);
	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;

	bool IsActive() const;
};

#endif