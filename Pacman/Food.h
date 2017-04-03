#ifndef FOOD_H
#define FOOD_H

#include "Object.h"

class Food : public Object
{
public:
	static enum FoodType { None, Normal, Speed };

	Food();
	Food(const FoodType pFoodType, const string pTexturePath, const sf::Vector2i pPosition);
	virtual ~Food();

	void SetFoodType(const FoodType pFoodType);
	FoodType GetFoodType() const;

	void Eat();

private:
	FoodType mFoodType;
};

#endif