/*! \file enemySensors.cpp
 * \brief Functions and Logic behind the sensors
 *
 * sensors are used to control the slime and keep them in place
 */

#include "utilities/enemySensor.h"


 //! Constructor for the enemy sensore
 /*!
 \param world The game world the object will spawn in
 \param position is the position the object will spawn in
 \param layerID is the layer by which the contact listener will identify the object
 */
enemySensors::enemySensors(b2World* world, const sf::Vector2f& position, const char layerID) // constructor
{
	//////////////// BOX2D BODY //////////////////////////////////////////////////////////////////////////////////////
	// set the layer ID
	setLayerId(layers(layerID));
	// set the body values
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	// set the body position
	l_bodyDef.position.Set(position.x, position.y);
	// create the body with user data
	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener
	// shape of the body
	l_shape.SetAsBox(1.5f, 1.5f);
	// fixture description
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;
	l_fixtureDef.filter.categoryBits = 8;
	// fixture initiation
	m_body->CreateFixture(&l_fixtureDef);
}
