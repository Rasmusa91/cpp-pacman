#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "ArrayList.h"
#include "CombatText.h"
#include "EndScreen.h"
#include "Text.h"

class Game : public sf::Drawable
{
private:
	Map mMap;
	ArrayList<Character> mCharacters;
	ArrayList<CombatText> mCombatTexts;
	EndScreen * mEndScreen;

	sf::Clock mGameTimer;
	Text * mTimeText;
	Text * mScoreText;

	bool mIsPlaying;

	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;
	string GetGameTimeFormated() const;
public:
	Game();
	virtual ~Game();

	void Update(const float pDeltaSeconds, sf::RenderWindow & pWindow);

	void AddCombatText(CombatText * pCombatText);
	Map & GetMap();

	bool IsEnemyAtLocation(const sf::Vector2i pPosition) const;
	bool IsPlayerLocation(const sf::Vector2i pPosition) const;
	Player * GetPlayer() const;

	void FoodUpdated();

	void Restart();
	void GameOver(const string pTitle);
};

#endif