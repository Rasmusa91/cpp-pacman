#include "Food.h"

Food::Food() : Object()
{

}

Food::Food(const FoodType pFoodType, const string pTexturePath, const sf::Vector2i pPosition) : Object(pTexturePath, pPosition)
{
	mFoodType = pFoodType;
}

Food::~Food()
{

}

// Set the type of food (normal or superfood (buff))
void Food::SetFoodType(const FoodType pFoodType)
{
	mFoodType = pFoodType;
}

// Check the type of food
Food::FoodType Food::GetFoodType() const
{
	return mFoodType;
}

// Eat the food by inactivating it (it wont be rendered)
void Food::Eat()
{
	SetIsActive(false);
}