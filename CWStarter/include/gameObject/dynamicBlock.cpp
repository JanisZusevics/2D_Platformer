/*! \file dynamicBlock.cpp
 * \brief Functionality and logic of how the dynamic block functions
 *
 * Dynamic blocks detect the player stepping on them and will raise like an elevator 
 * and then come back down
 */

#include "..\gameObject\dynamicBlock.h"

 //! Constructor for dynamic Blocks
 /*!
 \param world The game world the object will spawn in 
 \param position is the position the object will spawn in 
 \param texture is the sprite that will be assigned to the object
 */
dynamicBlock::dynamicBlock(b2World* world, const sf::Vector2f& position, const sf::Texture* texture)
{
	//////////////// BOX2D BODY //////////////////////////////////////////////////////////////////////////////////////
	// set the layer ID
	setLayerId(layers('d'));
	// set the body values
	b2BodyDef l_bodyDef;
	l_bodyDef.type = b2_dynamicBody;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;
	// set the body position
	l_bodyDef.position.Set(position.x, position.y);
	// create the body with user data
	m_body = world->CreateBody(&l_bodyDef);
	m_body->SetUserData(this); // used by our contact listener
	// shape of the body
	l_shape.SetAsBox(5.f, 1.f);
	l_shape.m_radius = 0.0f;
	// fixture description
	l_fixtureDef.density = 9000; // dense to not allow the player to move it
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = 0;
	l_fixtureDef.shape = &l_shape;
	l_fixtureDef.filter.maskBits = 2; // only interacts with the player. goes through other walls
	// fixture initiation 
	m_body->CreateFixture(&l_fixtureDef);
	m_body->SetGravityScale(0); // not affected by gravity 
	m_body->SetFixedRotation(true); // don't rotate
	//////////////// SPRITE //////////////////////////////////////////////////////////////////////////////////////
	spriteLocation = sf::IntRect(0, 0, 195, 46); // location and size of the sprite in the source image 
	sprite = sf::Sprite(*texture, sf::IntRect(spriteLocation)); // assign the location and size
	sprite.setScale(0.055f, 0.070f); // set the size of the image in the game 
}

//! Function to draw the sprite
/*!
\param target will choose what gets drawn 
\param states defines the state for the target
*/
void dynamicBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite); // draw the sprite
}

//! Function that is called every cycle
/*!
*/
void dynamicBlock::update()
{
	// sprite gets centered as the block moves
	sprite.setPosition(m_body->GetPosition().x - 5.4, m_body->GetPosition().y - 1.55);
	// pos is used to ensure the dynamic block stays within its set distance
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	// When the player is touching the block and the block is below a certain height
	if (touching && pos.y >= 152.3) {
		// make block go up
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0,-600000), true);
	}
	// if not touching and above the resting position 
	else if(!touching && pos.y <= 171.5) 
	{
		// make block go down 
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0, 60000), true);
	}
	else
	{
		m_body->SetAwake(false); // set block to sleep to stop it from uneccesary moving 
	}

}

//! Function that gets called when the object enters a collision
/*!
\param contact refers to the contact that occured that the object was involved with 
\param layer is the layerID of the other object it collided with
*/
void dynamicBlock::BeginContact(b2Contact* contact, layers layer)
{
	if(layer == layers('p')) touching =  1; // if touching the 'p' (player) then increase touching variable
}

//! Function that gets called when the object exits a collision
/*!
\param contact refers to the contact that occured that the object was involved with
\param layer is the layerID of the other object it collided with
*/
void dynamicBlock::EndContact(b2Contact* contact, layers layer)
{
	if (layer == layers('p')) touching = 0; // when no longer touching set the variable back to 0
}
