#pragma once

/*! \file staticBlock.h
 * \brief Header file for the staticBlock
 *
 * Static blocks don't move and form the level
 * This is an overview of how static blocks operate
 * There are 2 types of static block
 */



#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../gameObject/gameObject.h"

/*! \class StaticBlock
\brief A simple block which can not move or rotate but can collide with stuff
*/
class StaticBlock : public PhysicalThing
{
public:
	StaticBlock() {}; //!< Default constructor
	StaticBlock(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size);//!<  constructor
};

/*! \class Wall
\brief A simple block like static block but bounces the player away
*/
class wall : public StaticBlock 
{
public:
	wall() { };//!< Default constructor
	wall(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size);//!<  constructor
};





