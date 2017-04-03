#ifndef MAP_H
#define MAP_H

#include <random>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "Object.h"
#include "ArrayList.h"
#include "Food.h"

class Map : public sf::Drawable
{
public:
	static enum Direction { Down, Left, Right, Up };

	const static int TILESIZE = 32;
	const static int MAPWIDTH = 40;
	const static int MAPHEIGHT = 23;

	static sf::Vector2f GetTruePosition(const sf::Vector2i pTilePosition);
	static sf::Vector2f GetTruePosition(const sf::Vector2f pTilePosition);
	static sf::Vector2i GetDirection(const Direction pDirection);
	static Direction GetOppositeDirection(const Direction pDirection);

	Map();
	~Map();

	bool IsWalkable(sf::Vector2i pTilePosition) const;
	sf::Vector2i GetRandomPlayerSpawn() const;
	ArrayList<sf::Vector2i> GetEnemySpawns() const;
	Food * GetFoodAtPosition(const sf::Vector2i pTilePosition) const;

	int GetFoodLeft() const;
	int GetMaxFood() const;
	void ResetFood();

private:
	int mData[MAPHEIGHT][MAPWIDTH];

	ArrayList<Object> mEnvironment;
	ArrayList<Food> mFood;
	ArrayList<sf::Vector2i> mPlayerSpawns;
	ArrayList<sf::Vector2i> mEnemySpawns;

	virtual void draw(sf::RenderTarget & pTarget, sf::RenderStates pStates) const;

	void AddEnvironment(Object * pObject);
};

#endif