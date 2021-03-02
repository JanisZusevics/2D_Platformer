#pragma once

/*! \file player.cpp
 * \brief Functions and Logic behind the player
 *
 * player controls an animated sprite that can move left, right, or jump
 * This file shows logic behind the movement, animation, and collisions of the player
 */

#include "..\gameObject\player.h"
/*! \class Player
\brief A simple block which can move, rotate and collide with stuff and be controlelr
*/

// Character states
enum _state {
	MOVING_LEFT, // for when the character is moving left
	MOVING_RIGHT, // for when th echaracter is moving right 
	STOP, // for when the character isn't moving
};

_state state; // initialise the states

//! Constructor for player
/*!
\param world The game world the object will spawn in
\param position is the position the object will spawn in
\param size will be the size of the object
\param texture is the sprite that will be assigned to the object
*/
player::player(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture) {
	//////////////// BOX2D BODY //////////////////////////////////////////////////////////////////////////////////////
	// set the layer ID
	setLayerId(layers('p')); // 'p' for player
	// set the body values
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	// set the body position
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.type = b2_dynamicBody;
	// create the body with user data
	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener
	// shape of the body
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	// fixture description
	l_fixtureDef.density = 70;
	l_fixtureDef.friction = 0.2;
	l_fixtureDef.restitution = 0.0;
	l_fixtureDef.filter.categoryBits = 2;
	l_fixtureDef.filter.maskBits = 1;
	l_fixtureDef.shape = &l_shape;
	// fixture initiation
	m_body->CreateFixture(&l_fixtureDef);
	m_body->SetGravityScale(2);
	m_body->SetFixedRotation(true);
	// default state
	state = STOP; // Default state
	/////////////// SPRITE //////////////////////////////////////////////////////////////////////////////////////
	spriteLocation = sf::IntRect(0, 32, 32, 32);
	sprite = sf::Sprite(*texture, sf::IntRect(spriteLocation));
	sprite.setScale(0.2f, 0.2f);


}

//! Function to draw the sprite
/*!
\param target will choose what gets drawn
\param states defines the state for the target
*/
void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite); // draw the sprite
}

//! Function that is called every timestep
/*!
*/
void player::update()
{
	jumpVelocity = m_body->GetLinearVelocity().y; // work out jump velocity  - used to prevent jumping in air
	//  ANIMATION //////////////////////////////////////////////////////////////////////////////////////
	sprite.setPosition(m_body->GetPosition().x - xAdjust, m_body->GetPosition().y - 4.2f); // set the position of the sprite
	float animationTime = anim.getElapsedTime().asSeconds(); // time elapsed - used to animate
	if (animationTime > 0.2f) { // after each time interwal 
		if (spriteLocation.left >= 150)
			spriteLocation.left = 0;
		else
			spriteLocation.left += 38; // Move sprite image to next image
		sprite.setTextureRect(spriteLocation);
		anim.restart(); // restart the timer 
	}
	// update the body position each time
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	// velocity controls the player movement 
	b2Vec2 vel = m_body->GetLinearVelocity();
	float desiredVelocity = 0;
	// Switch case for player states
	switch (state)
	{
	case MOVING_LEFT: // moving left state makes player move left
		desiredVelocity = -30.5f;
		spriteLocation.top = 32; // ensures the animation is on the walk animation 
		break;
	case MOVING_RIGHT: // moving right state makes player move right
		desiredVelocity = 30.5f;
		spriteLocation.top = 32; // ensures the animation is on the walk animation 
		break;
	case STOP: // stop state for when the player is standing still
		desiredVelocity = 0.f;
		spriteLocation.top = 0; // animations are on idle
		break;
	}
	// applies force according to the state
	float velChange = desiredVelocity - vel.x;
	float impulse = m_body->GetMass() * velChange;
	m_body->ApplyForceToCenter(b2Vec2(impulse, 0), true);
}

//! Function to get player input
/*!
\param code refers to the key pressed
*/
void player::keyboard(sf::Keyboard::Key code) {
	// switch case for which key is pressed
	switch (code)
	{
	case sf::Keyboard::A: // if A is pressed then move left 
		state = MOVING_LEFT;
		 // Re-adjust sprite 
		if (sprite.getScale().x == 0.2f) {
			sprite.scale(-1.f, 1.f);
			xAdjust = -3.2f;
			sprite.setPosition(m_body->GetPosition().x - xAdjust, m_body->GetPosition().y - 4.2f);
		}

		break;
	case sf::Keyboard::D:// if D is pressed then move right 
		state = MOVING_RIGHT;
		// Re-adjust sprite
		xAdjust = 3.2f;
		if (sprite.getScale().x == -0.2f) {
			sprite.scale(-1.f, 1.f);
			sprite.setPosition(m_body->GetPosition().x - xAdjust, m_body->GetPosition().y - 4.2f);
		}
		break;
	case sf::Keyboard::Space: // if SPACE is pressed then jump
		if ( grounded() && jumpVelocity == 0) // if grounded and jump velocity is 0
		{
			// jump
			float jumpImpulse = m_body->GetMass() * -31;
			m_body->ApplyLinearImpulse(b2Vec2(0, jumpImpulse), m_body->GetWorldCenter(), true);
		}
		break;
	}
}

//! Function to get player input on release
/*!
\param code refers to the key pressed
*/
void player::onKeyRelease(sf::Keyboard::Key code)
{
	switch (code)
	{
	case sf::Keyboard::A: // when released exit state
		if (state == MOVING_LEFT) {
			state = STOP;

		}
		break;
	case sf::Keyboard::D: // when released exit state
		if (state == MOVING_RIGHT) {
			state = STOP;
		}
		break;
	}
}

//! Function that gets called when the player enters a collision
/*!
\param contact refers to the contact that occured that the player was involved with
\param layer is the layerID of the other object it collided with
*/
void player::BeginContact(b2Contact* contact, layers layer) {

	touching = touching + 1; // touching something

	if (layer == layers('c')) { // c for coin
		score = score + 5; // if coin then increase score
	}
}

//! Function that gets called when the player exits a collision
/*!
\param contact refers to the contact that occured that the player was involved with
\param layer is the layerID of the other object it collided with
*/
void player::EndContact(b2Contact* contact, layers layer) {
	touching = touching - 1; // no longer touching something 
}

//! Function that returns the score 
/*!
\return an int with the curent score
*/
float player::getScore()
{
	return score; // return score
}


