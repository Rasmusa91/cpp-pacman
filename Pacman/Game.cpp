#include "Game.h"
#include <sstream>

Game::Game() : sf::Drawable()
{
	mEndScreen = new EndScreen(this);
	mTimeText = new Text("Time 0:00", sf::Color::White, sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE * 0.99f, Map::MAPHEIGHT * Map::TILESIZE * 0.02f), 16);
	mTimeText->SetAlignment(Text::Alignment::Right);

	stringstream ss;
	int totalFood = mMap.GetMaxFood();
	ss << "Score: " << totalFood - mMap.GetFoodLeft() << "/" << totalFood;
	mScoreText = new Text(ss.str(), sf::Color::White, sf::Vector2f(Map::MAPWIDTH * Map::TILESIZE * 0.99f, Map::MAPHEIGHT * Map::TILESIZE * 0.05f), 16);
	mScoreText->SetAlignment(Text::Alignment::Right);

	Restart();
	//GameOver();
}

Game::~Game()
{
	delete mTimeText;
	delete mScoreText;
	delete mEndScreen;
}

// Restart the game
void Game::Restart()
{
	if (!mIsPlaying) 
	{
		// Reset game timer
		mGameTimer.restart();

		// Remove all characters
		mCharacters.Clear();

		// Reset all food
		mMap.ResetFood();

		// Update texts on the screen
		mTimeText->SetText("Time: " + GetGameTimeFormated());
		FoodUpdated();

		// Add new player at a random location
		mCharacters.Push(new Player(this, "../Assets/Characters/player.png", sf::Vector2i(3, 0), mMap.GetRandomPlayerSpawn()));

		// Add enemies
		ArrayList<sf::Vector2i> enemySpawns = mMap.GetEnemySpawns();
		for (int i = 0; i < enemySpawns.GetSize(); i++) {
			mCharacters.Push(new Enemy(this, "../Assets/Characters/monster.png", sf::Vector2i(3, 0), *enemySpawns[i]));
		}

		mIsPlaying = true;
	}
}

// Update the game
void Game::Update(const float pDeltaSeconds, sf::RenderWindow & pWindow)
{
	// Update the game timer text
	mTimeText->SetText("Time: " + GetGameTimeFormated());

	// Update all characters
	for (int i = 0; i < mCharacters.GetSize(); i++) {
		mCharacters[i]->Update(pDeltaSeconds);
	}

	// Update all combat text and remove inactives
	for (int i = 0; i < mCombatTexts.GetSize(); i++) 
	{
		if (mCombatTexts[i]->IsActive()) 
		{
			mCombatTexts[i]->Update(pDeltaSeconds);
		}
		else 
		{
			mCombatTexts.RemoveAt(i);
			i--;
		}
	}

	//Update the endscreen if the game is over
	if (!mIsPlaying) {
		mEndScreen->Update(pDeltaSeconds, pWindow);
	}
}

void Game::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	// Draw the map
	pTarget.draw(mMap);

	// Draw all characters
	for (int i = 0; i < mCharacters.GetSize(); i++) {
		pTarget.draw(* mCharacters[i]);
	}

	// Draw all combat texts
	for (int i = 0; i < mCombatTexts.GetSize(); i++) {
		pTarget.draw(* mCombatTexts[i]);
	}

	// If the game is running, draw the score and timer
	if (mIsPlaying)
	{
		pTarget.draw(*mTimeText);
		pTarget.draw(*mScoreText);
	}
	// If not, draw the endscreen
	else {
		pTarget.draw(* mEndScreen);
	}
}

// Add a combattext to the list
void Game::AddCombatText(CombatText * pCombatText)
{
	mCombatTexts.Push(pCombatText);
}

// Return the map associated with the game object
Map & Game::GetMap()
{
	return mMap;
}

// Chck if a position is at a enemies current or wanted position
bool Game::IsEnemyAtLocation(const sf::Vector2i pPosition) const
{
	bool enemyAtLocation = false;

	// Iterate all characters
	for (int i = 0; i < mCharacters.GetSize() && !enemyAtLocation; i++) 
	{
		// Check if the character is an enemy
		if (dynamic_cast<Enemy*>(mCharacters[i]) != nullptr)
		{
			// Check if the position is the enemies current or wanted position
			if (mCharacters[i]->GetPosition() == pPosition || mCharacters[i]->GetWantedPosition() == pPosition) {
				enemyAtLocation = true;
			}
		}
	}

	return enemyAtLocation;
}

// Check if a position is at the players current or wanted position
bool Game::IsPlayerLocation(const sf::Vector2i pPosition) const
{
	return GetPlayer()->GetPosition() == pPosition || GetPlayer()->GetWantedPosition() == pPosition;
}

// Find the player in the character list
Player * Game::GetPlayer() const
{
	Player * player = nullptr;

	for (int i = 0; i < mCharacters.GetSize() && player == nullptr; i++)
	{
		player = dynamic_cast<Player*>(mCharacters[i]);
	}

	return player;
}

// Tell the game it's over
void Game::GameOver(const string pTitle)
{
	// Kill the player
	GetPlayer()->Die();

	// Make all enemies idle
	for (int i = 0; i < mCharacters.GetSize(); i++)
	{
		if (dynamic_cast<Enemy*>(mCharacters[i]) != nullptr)
		{
			mCharacters[i]->SetIsActive(false);
			mCharacters[i]->SetIsIdle(true);
		}
	}

	// Get the final score and send it to the endscreen
	stringstream ss;
	int totalFood = mMap.GetMaxFood();
	ss << totalFood - mMap.GetFoodLeft() << "/" << totalFood;

	mIsPlaying = false;
	mEndScreen->GameOver(pTitle, ss.str(), GetGameTimeFormated());
}

// Format the game timer to a time format like (0:00)
string Game::GetGameTimeFormated() const
{
	int totalSeconds = (int) mGameTimer.getElapsedTime().asSeconds();
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds - minutes * 60;

	stringstream ss;
	ss << (minutes > 0 && minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
	return ss.str();
}

// Update the score text
void Game::FoodUpdated()
{
	int totalFood = mMap.GetMaxFood();
	int foodLeft = mMap.GetFoodLeft();

	stringstream ss;
	ss << "Score: " << totalFood - mMap.GetFoodLeft() << "/" << totalFood;
	mScoreText->SetText(ss.str());

	// If no food is left, win
	if (foodLeft <= 0) {
		GameOver("Victory!");
	}
}