#pragma once

/*! \file contactListener.h
 * \brief Header file for the contact listener
 *
 * The contact listener uses parent class 'PhysicalThing' from every object to distinguish between collisions 
 * This is an overview of how the contact listener operate
 */

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../gameObject/gameObject.h"

/*! \class contactListener
\brief A class that controls the Collisions of the game
*/

class contactListener : public b2ContactListener, public PhysicalThing
{
private:
	//////////// Object ID ///////////////////////////
	char A_Id; //!< Single byte long object identifier used to distiguish between objects
	char B_Id; //!< Single byte long object identifier used to distiguish between objects
public:
	void contactListener::BeginContact(b2Contact* contact); //!< Begin contact function 
	void contactListener::EndContact(b2Contact* contact); //!< End contact functiom 
};

