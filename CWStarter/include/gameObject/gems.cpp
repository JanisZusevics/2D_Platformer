/*! \file gems.cpp
 * \brief Functions and Logic behind the gems
 *
 * gems or "coins" are collectables that give the player points
 * Coins dissappear on contact and reappear after a time
 */

#include "..\gameObject\gems.h"

 //! Constructor for gems
 /*!
 \param world The game world the object will spawn in
 \param position is the position the object will spawn in
 \param texture is the sprite that will be assigned to the object
 */
gems::gems(b2World* world, const sf::Vector2f& position, sf::Texture* texture) // constructor
{
	/////////////// AUDIO //////////////////////////////////////////////////////////////////////////////////////////
	//buffer.loadFromFile("../Assets/ping.wav");//) std::cout << "error" << std::endl; // error			 // commented out audio code
																										 // commented out audio code
	//ping.setBuffer(buffer);																			 // commented out audio code
																										 // commented out audio code
	//////////////// BOX2D BODY //////////////////////////////////////////////////////////////////////////////////////
	// set layer ID
	setLayerId(layers('c'));
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
	l_shape.SetAsBox(1.8f, 1.8f);
	// fixture description
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.isSensor = true;
	// fixture initiation 
	m_body->CreateFixture(&l_fixtureDef);
	//////////////// SPRITE //////////////////////////////////////////////////////////////////////////////////////
	spriteLocation = sf::IntRect(0, 16, 16, 16); // location and size of the sprite in the source image 
	sprite = sf::Sprite(*texture, sf::IntRect(spriteLocation)); // assign the location and size
	sprite.setScale(0.2f, 0.2f); // set the size of the image in the game 
}

//! Function that is called every cycle
/*!
*/
void gems::update() // Gets called every frame
{
	//////////////// SPRITE //////////////////////////////////////////////////////////////////////////////////////
	sprite.setPosition(m_body->GetPosition().x - 1.6, m_body->GetPosition().y - 1.6);
	// Sprite animation controller
	if (anim.getElapsedTime().asSeconds() > 0.1f) { // for each 0.1 seconds
		if (spriteLocation.left == 112)
			spriteLocation.left = 16; // movve imagine in sprite sheet
		else
			spriteLocation.left += 16;
		sprite.setTextureRect(spriteLocation);
		anim.restart(); // restart clock after each time frame
	}
	////////////////// COLLECTION //////////////////////////////////////////////////////////////////////////////////
	if (collected) { // If collection bool is true
		//ping.play(); // commented out audio code
		sprite.setColor(sf::Color::Transparent); // Make the sprite invisible
		collected = 0; // Reset the bool
		m_body->SetActive(false); // Make the object not interact with the world anymore
		respawn.restart(); // Start the timer for the resapwn
	};
	//////////////// RESPAWN ////////////////////////////////////////////////////////////////////////////////////
	if (sprite.getColor() == sf::Color::Transparent && respawn.getElapsedTime().asSeconds() > 5) // if collected, respawn after five secodns
	{
		m_body->SetActive(true); // actiavte the fixture again
		sprite.setColor(sf::Color::White);// set colour to white
	}
}

//! Function to draw the sprite
/*!
\param target will choose what gets drawn
\param states defines the state for the target
*/
void gems::draw(sf::RenderTarget& target, sf::RenderStates states) const // Draw function overriden for sprite only
{
	target.draw(sprite); // draw the sprite
}

//! Function that gets called when the object enters a collision
/*!
\param contact refers to the contact that occured that the object was involved with
\param layer is the layerID of the other object it collided with
*/
void gems::BeginContact(b2Contact* contact, layers layer) {
	if (layer == layers('p'))
	 collected = 1; 
}

//! Function that gets called when the object exits a collision
/*!
*/
void gems::endContact()
{
	collected = 1; // ensures the coin was collected
}

