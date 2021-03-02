/*! \file gameObject.cpp
 * \brief Functions and Logic behind the gameObjects
 *
 * gameObject is a parent class of every object in the game
 * Contains vital information used by the contact listener
 */

#include "gameObject.h"

// list of the possible contact layers and theor meaning
enum layers : unsigned char
{
	a, // All/Undefined
	p, // player
	c, // collectable
	e, // enemy
	s, // sensor
	w, // walls
	d, // dynamic block
};

//! Function that sets the contact ID for a given object
/*!
\param layer is the layerID of the other object it collided with
*/
void PhysicalThing::setLayerId(layers layer) {
	objectLayerId = layer; // set layer ID to the given layer
}