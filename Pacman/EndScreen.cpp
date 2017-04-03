#include "EndScreen.h"
#include "Map.h"
#include "Game.h"

// Initialize the endscreen
EndScreen::EndScreen()
{
	mBG = sf::RectangleShape(sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE, Map::MAPHEIGHT * Map::TILESIZE));

	// Create the title
	mTitle = new Text("Game Over", sf::Color::White, sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE * 0.5f, Map::MAPHEIGHT * Map::TILESIZE * 0.35f), 50);
	mTitle->SetAlignment(Text::Alignment::Center);

	// Create the score text
	mScore = new Text("Score: ", sf::Color::White, sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE * 0.5f, Map::MAPHEIGHT * Map::TILESIZE * 0.45f), 25);
	mScore->SetAlignment(Text::Alignment::Center);

	// Create the time text
	mTime = new Text("Time: ", sf::Color::White, sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE * 0.5f, Map::MAPHEIGHT * Map::TILESIZE * 0.5f), 25);
	mTime->SetAlignment(Text::Alignment::Center);

	// Create the restart "button"
	mRestart = new Text("Restart ", sf::Color::White, sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE * 0.5f, Map::MAPHEIGHT * Map::TILESIZE * 0.575f), 30);
	mRestart->SetAlignment(Text::Alignment::Center);
	mRestart->SetUnderlined();
}

// Initialize with a game object
EndScreen::EndScreen(Game * pGame) : EndScreen()
{
	mGame = pGame;
}

EndScreen::~EndScreen()
{
	delete mTitle;
	delete mScore;
	delete mTime;
	delete mRestart;
}

// Update the values
void EndScreen::GameOver(const string pTitle, const string pScore, const string pTime)
{
	mTitle->SetText(pTitle);
	mScore->SetText("Score: " + pScore);
	mTime->SetText("Time: " + pTime);

	Initialize();
}

// Initialize the fade
void EndScreen::Initialize()
{
	mBGAlpha = 0.f;
	mBGMaxAlpha = 0.75f;
	mBG.setFillColor(sf::Color(0, 0, 0, (sf::Uint8) (255 * mBGAlpha)));
	mIsBGFading = true;
}

// Update the endscreen
void EndScreen::Update(const float pDeltaSeconds, sf::RenderWindow & pWindow)
{
	// Fade the background
	if (mIsBGFading)
	{
		mBGAlpha += pDeltaSeconds * 1.5f;

		if (mBGAlpha > mBGMaxAlpha)
		{
			mBGAlpha = mBGMaxAlpha;
			mIsBGFading = false;
		}

		mBG.setFillColor(sf::Color(0, 0, 0, (sf::Uint8) (255 * mBGAlpha)));
	}

	// If the mouse position is inside the text bounds and the the mouse is pressed, restart the game
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRestart->GetGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(pWindow))) {
		mGame->Restart();
	}
}

// Draw everything
void EndScreen::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	pTarget.draw(mBG);
	pTarget.draw(* mTitle);
	pTarget.draw(* mScore);
	pTarget.draw(* mTime);
	pTarget.draw(* mRestart);
}

