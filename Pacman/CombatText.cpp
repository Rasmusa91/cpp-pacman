#include "CombatText.h"
#include <iostream>
#include "Map.h"

CombatText::CombatText()
{

}

// Initialize the combat text
CombatText::CombatText(const string pString, const sf::Vector2f pPosition, const sf::Color pColor)
{
	mText = new Text(pString, pColor, pPosition, 13);

	mIsActive = true;
	mSpeed = 50.f;

	mTimerDuration = 1;
}


CombatText::~CombatText()
{
	delete mText;
}

// Update the combat text
void CombatText::Update(const float pDeltaSeconds)
{
	// Move it upwards
	mText->SetPosition(mText->GetPosition() + sf::Vector2f(0, -mSpeed * pDeltaSeconds));

	// Deactivate after the duration
	if (mTimer.getElapsedTime().asSeconds() > mTimerDuration) {
		mIsActive = false;
	}
}

// Draw the combat text
void CombatText::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	pTarget.draw(* mText);
}

// Check if the combat text is active
bool CombatText::IsActive() const
{
	return mIsActive;
}