/*! \file static.cpp
 * \brief Functions and Logic behind the gameObjects
 *
 * There are 2 static block classes
 * 'wall' which inherits from static block is very similar except has higher restitution to make the player bounce away 
 */

#include "..\gameObject\staticBlock.h"
#include <iostream>

 //! Constructor for static block 
 /*!
 \param world The game world the object will spawn in
 \param position is the position the object will spawn in
 \param size will be the size of the object
 */
StaticBlock::StaticBlock(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size)
{
	//set layer ID
	setLayerId(layers('w'));
	// set the body values
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	// set the body position
	l_bodyDef.position.Set(position.x, position.y);
	// create the body with user data
	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener
	m_body->SetType(b2_staticBody);
	// shape of the body
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	// fixture description
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0.f;
	l_fixtureDef.shape = &l_shape;
	// fixture initiation 
	m_body->CreateFixture(&l_fixtureDef);

}

//! Constructor for wall
/*!
\param world The game world the object will spawn in
\param position is the position the object will spawn in
\param size will be the size of the object
*/
wall::wall(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size) {
	//set layer ID
	setLayerId(layers('w'));
	// set the body values
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	// set the body position
	l_bodyDef.position.Set(position.x, position.y);
	// create the body with user data
	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener
	m_body->SetType(b2_staticBody);
	// shape of the body
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	// fixture description
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 1.2f;
	l_fixtureDef.shape = &l_shape;
	// fixture initiation 
	m_body->CreateFixture(&l_fixtureDef);
}
