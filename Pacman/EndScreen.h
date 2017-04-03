#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <SFML/Graphics.hpp>
#include "Text.h"

class Game;
class EndScreen : public sf::Drawable
{
private:
	Game * mGame;

	sf::RectangleShape mBG;
	float mBGAlpha;
	float mBGMaxAlpha;
	bool mIsBGFading;

	Text * mTitle;
	Text * mScore;
	Text * mTime;
	Text * mRestart;

	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;
	void Initialize();
public:
	EndScreen();
	EndScreen(Game * pGame);
	virtual ~EndScreen();

	void GameOver(const string pTitle, const string pScore, const string pTime);
	void Update(const float pDeltaSeconds, sf::RenderWindow & pWindow);
};

#endif