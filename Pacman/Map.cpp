#include "Map.h"

Map::Map()
{
	srand((unsigned) time(NULL));

	//0 = dirt (road) + normal food
	//1 = bush (wall)
	//2 = super food + enemy spawn
	//3 = player spawn + no food
	int data[MAPHEIGHT][MAPWIDTH] = {
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 3, 1, 1, 1, 1, 3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
			{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	// Put the temp data in the actual data array
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			mData[i][j] = data[i][j];
		}
	}

	//Generate all environment by iterating all tiles
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			stringstream ss;

			// Check if the area is walkable
			if (mData[i][j] == 0 || mData[i][j] == 2 || mData[i][j] == 3)
			{
				// Generate dirt on all walkable area
				ss << "../Assets/Road/" << (rand() % 1 + 1) << ".png";
				AddEnvironment(new Object(ss.str(), sf::Vector2i(j, i)));
				ss.str("");

				// Add borders to the ground depending on where the grass is
				if (mData[i + 1][j] == 1 && mData[i][j + 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/9.png", sf::Vector2i(j, i)));
				}
				else if (mData[i + 1][j] == 1 && mData[i][j - 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/11.png", sf::Vector2i(j, i)));
				}
				else if (mData[i - 1][j] == 1 && mData[i][j + 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/8.png", sf::Vector2i(j, i)));
				}
				else if (mData[i - 1][j] == 1 && mData[i][j - 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/10.png", sf::Vector2i(j, i)));
				}
				else
				{
					if (mData[i + 1][j] == 1) {
						AddEnvironment(new Object("../Assets/GrassBorder/5.png", sf::Vector2i(j, i)));
					}
					if (mData[i - 1][j] == 1) {
						AddEnvironment(new Object("../Assets/GrassBorder/6.png", sf::Vector2i(j, i)));
					}
					if (mData[i][j + 1] == 1) {
						AddEnvironment(new Object("../Assets/GrassBorder/4.png", sf::Vector2i(j, i)));
					}
					if (mData[i][j - 1] == 1) {
						AddEnvironment(new Object("../Assets/GrassBorder/2.png", sf::Vector2i(j, i)));
					}
				}

				if (mData[i - 1][j] != 1 && mData[i][j + 1] != 1 && mData[i - 1][j + 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/3.png", sf::Vector2i(j, i)));
				}
				if (mData[i - 1][j] != 1 && mData[i][j - 1] != 1 && mData[i - 1][j - 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/7.png", sf::Vector2i(j, i)));
				}
				if (mData[i + 1][j] != 1 && mData[i][j + 1] != 1 && mData[i + 1][j + 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/12.png", sf::Vector2i(j, i)));
				}
				if (mData[i + 1][j] != 1 && mData[i][j - 1] != 1 && mData[i + 1][j - 1] == 1) {
					AddEnvironment(new Object("../Assets/GrassBorder/1.png", sf::Vector2i(j, i)));
				}

				// Add random decoration
				if (rand() % 100 + 1 < 10) 
				{
					ss << "../Assets/Stones/" << (rand() % 5 + 1) << ".png";
					AddEnvironment(new Object(ss.str(), sf::Vector2i(j, i)));
					ss.str("");
				}
				else if (rand() % 100 + 1 < 10)
				{
					ss << "../Assets/Flowers/" << (rand() % 7 + 1) << ".png";
					AddEnvironment(new Object(ss.str(), sf::Vector2i(j, i)));
					ss.str("");
				}

				// Put food everywhere except where the superfood is
				if (mData[i][j] == 0)
				{
					ss << "../Assets/Food/" << (rand() % 4 + 1) << ".png";
					mFood.Push(new Food(Food::FoodType::Normal, ss.str(), sf::Vector2i(j, i)));
					ss.str("");
				}
				else if (mData[i][j] == 2)
				{
					ss << "../Assets/SuperFood/" << (rand() % 3 + 1) << ".png";
					mFood.Push(new Food(Food::FoodType::Speed, ss.str(), sf::Vector2i(j, i)));
					ss.str("");
				}
			}
			// If the tile is not walkable
			else if (mData[i][j] == 1)
			{
				// Spawn grass
				ss << "../Assets/Grass/" << (rand() % 16 + 1) << ".png";
				AddEnvironment(new Object(ss.str(), sf::Vector2i(j, i)));
				ss.str("");

				// Spawn a bush
				ss << "../Assets/Walls/" << (rand() % 3 + 1) << ".png";
				AddEnvironment(new Object(ss.str(), sf::Vector2i(j, i)));
				ss.str("");
			}

			// Save the player spawns
			if (mData[i][j] == 3) {
				mPlayerSpawns.Push(new sf::Vector2i(j, i));
			}

			// Save the enemy spawns
			if (mData[i][j] == 2) {
				mEnemySpawns.Push(new sf::Vector2i(j, i));
			}
		}
	}
}

Map::~Map()
{
}

// Draw the map
void Map::draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const
{
	// Draw the environment
	for (int i = 0; i < mEnvironment.GetSize(); i++)
	{
		pTarget.draw(* mEnvironment[i]);
	}

	// Draw the food
	for (int i = 0; i < mFood.GetSize(); i++)
	{
		if (mFood[i]->IsActive()) {
			pTarget.draw(*mFood[i]);
		}
	}
}

// Add environment to the list
void Map::AddEnvironment(Object * pObject)
{
	mEnvironment.Push(pObject);
}

// Find the the true position (tilePosition * tileSize) from a integer
sf::Vector2f Map::GetTruePosition(const sf::Vector2i pTilePosition)
{
	return sf::Vector2f (pTilePosition * TILESIZE);
}

// Find the the true position (tilePosition * tileSize) from a float
sf::Vector2f Map::GetTruePosition(const sf::Vector2f pTilePosition)
{
	return pTilePosition * (float) TILESIZE;
}

// Convert the direction to a vector
sf::Vector2i Map::GetDirection(const Direction pDirection)
{
	sf::Vector2i dir;

	if (pDirection == Direction::Up) {
		dir = sf::Vector2i(0, -1);
	}
	if (pDirection == Direction::Down) {
		dir = sf::Vector2i(0, 1);
	}
	if (pDirection == Direction::Left) {
		dir = sf::Vector2i(-1, 0);
	}
	if (pDirection == Direction::Right) {
		dir = sf::Vector2i(1, 0);
	}

	return dir;
}

// Get the oppposite direction of a direction
Map::Direction Map::GetOppositeDirection(const Direction pDirection)
{
	Direction dir;

	if (pDirection == Direction::Up) {
		dir = Direction::Down;
	}
	if (pDirection == Direction::Down) {
		dir = Direction::Up;
	}
	if (pDirection == Direction::Left) {
		dir = Direction::Right;
	}
	if (pDirection == Direction::Right) {
		dir = Direction::Left;
	}

	return dir;
}

// Check if a tile is walkable (no wall)
bool Map::IsWalkable(const sf::Vector2i pTilePosition) const
{
	return (mData[pTilePosition.y][pTilePosition.x] != 1);
}

// Find a random player spawn
sf::Vector2i Map::GetRandomPlayerSpawn() const
{
	return * mPlayerSpawns[rand() % mPlayerSpawns.GetSize()];
}

// Return ALL enemy spawns
ArrayList<sf::Vector2i> Map::GetEnemySpawns() const
{
	return ArrayList<sf::Vector2i>(mEnemySpawns);
}

// Check if there is food on a tile, if so: return the food
Food * Map::GetFoodAtPosition(const sf::Vector2i pTilePosition) const
{
	Food * food = nullptr;

	for (int i = 0; i < mFood.GetSize(); i++)
	{
		if (mFood[i]->IsActive() && mFood[i]->GetPosition() == pTilePosition)
		{
			food = mFood[i];
		}
	}

	return food;
}

// Get the amount of food left in the game
int Map::GetFoodLeft() const
{
	int n = 0;

	for (int i = 0; i < mFood.GetSize(); i++)
	{
		if (mFood[i]->IsActive()) {
			n++;
		}
	}

	return n;
}

// Get the total amount of food
int Map::GetMaxFood() const
{
	return mFood.GetSize();
}

// Make all food active
void Map::ResetFood()
{
	for (int i = 0; i < mFood.GetSize(); i++) 
	{
		mFood[i]->SetIsActive(true);
	}
}