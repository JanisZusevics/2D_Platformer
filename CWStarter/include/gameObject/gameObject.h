#pragma once

/*! \file gameObject.h
 * \brief Header file for the game object
 *
 * The parent class of every game Object
 * Allows for collision distinction
 */

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <ExternalLibraries/SFML-2.4.2/include/SFML/Graphics.hpp>

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

/*!
\class PhysicalThing
\brief A simple class with common attributes and functions used in all objects in the game.
*/

class PhysicalThing  // public sf::Shape 
{
protected:
	///// CONTACT LISTENER ///////////////////////////////////////////////////////////////////////////////////////
	enum class layers : unsigned char;	 //!< 1 byte identifier for layers which distinguish between collisions 
	layers objectLayerId; //!< Layers that correspond to collisons * p = player c = collectable = e enemy w = walls etc.
	///// DEFAULT BODY VALUES ///////////////////////////////////////////////////////////////////////////////////////
	b2Body* m_body = nullptr; //!< Box2D body, no need to delete this as BOX2D will look after it
	const float mk_fDensity = 1.0f; //!< Density of the material - used to give mass
	const float mk_fFriction = 0.4f; //!< Friction - I guess this is only friction from movement, not when static
	const float mk_fRestitution = 0.6f; //!< Restitution - bouncyness of stuff

public:
	void setUserData(void* data) { m_body->SetUserData(data); }; //!< Set the userdata of the body
	virtual void draw() const {} //!< virtual draw function used by the children of the class
	virtual void BeginContact(b2Contact* contact, layers layer) {} //!< virtual Begin Contact function used by the children of the class and called by the contact listener 
	virtual void EndContact(b2Contact* contact, layers layer) {} //!< virtual end Contact function used by the children of the class and called by the contact listener 
	layers getLayerId() { return objectLayerId; }; //!< Returns the objects layered ID - called to distinguish between objects in collisions 
	void setLayerId(layers layer); //!< Changes the current objects layer ID - used by children when constructing.
};
