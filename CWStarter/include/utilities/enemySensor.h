#pragma once

/*! \file enemySensor.h
 * \brief Header file for the sensors
 *
 * Simple Sensors are used to make the NPC slimes turn around 
 * This is an overview of how the sensors operate
 */


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "..\gameObject\gameObject.h"
#include <iostream>

/*! \class enemySensors
\brief A class that controls the sensors that control the slime
*/

class enemySensors : public PhysicalThing
{
private:
	//////////// BODY ///////////////////////////
	b2BodyDef l_bodyDef; //!< body definition 
	sf::Vector2f size = sf::Vector2f(2.f, 2.f); //!< set size for the all the sensors
public:
	enemySensors(b2World* world, const sf::Vector2f& position, const char layerID); //!< constructor
};

