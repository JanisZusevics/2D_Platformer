/*! \file slime.cpp
 * \brief Functions and Logic behind the slimes
 *
 * slimes are the enemy of the game, they launch the player away on contact 
 * This file shows how I animated and created the slime-like movement using Revolute Joints
 */

#include "slime.h"
#define DEG2RAD 0.017453f


 //! Constructor for slime
 /*!
 \param world The game world the object will spawn in
 \param position is the position the object will spawn in
 \param size will be the size of the object
 \param texture is the sprite that will be assigned to the object
 */
slime::slime(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture) // constructor
{
	//////////////// BOX2D BODY //////////////////////////////////////////////////////////////////////////////////////
	// set the layer ID
	setLayerId(layers('e'));
	// set the body values
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2FixtureDef bodyFixture;
	b2FixtureDef launcherFixture;
	// fixture description
	launcherFixture.density = 90000;
	launcherFixture.restitution = 3;
	launcherFixture.filter.maskBits = 2 | 8;
	bodyFixture.density = 90000;
	bodyFixture.friction = 1000;
	bodyFixture.restitution = 0.6;
	bodyFixture.filter.categoryBits = 4;
	//two shapes
	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x * 3, size.y * 0.3);
	b2CircleShape bodyCirlce;
	bodyCirlce.m_radius = size.x * 1.5;
	b2CircleShape launcherCircle;
	launcherCircle.m_radius = size.x * 1.4;
	// create the launcher with user data
	launcherFixture.shape = &launcherCircle;
	bodyDef.position.Set(position.x, position.y);
	bodyFixture.shape = &launcherCircle;
	m_launcher = world->CreateBody(&bodyDef);
	m_launcher->SetUserData(this); // used by our contact listener
	m_launcher->CreateFixture(&launcherFixture);
	// create the arm with user data
	bodyDef.position.Set(position.x, position.y);
	bodyFixture.shape = &boxShape;
	m_arm = world->CreateBody(&bodyDef);
	m_arm->SetUserData(this); // used by our contact listener
	m_arm->CreateFixture(&bodyFixture);
	// create the body with user data
	bodyDef.position.Set(position.x, position.y);
	boxShape.SetAsBox(size.x, size.x);
	m_body = world->CreateBody(&bodyDef);
	m_body->SetUserData(this); // used by our contact listener
	m_body->CreateFixture(&bodyFixture);
	m_body->SetFixedRotation(true); // doesnt rotate
	// joint definitions 
	b2DistanceJointDef distanceJointDef; // Distance joint ensures that the launcher is attached to the body
	distanceJointDef.bodyA = m_body;
	distanceJointDef.bodyB = m_launcher;
	distanceJointDef.collideConnected = false;
	distanceJointDef.length = 0.0f;
	distanceJointDef.localAnchorA.Set(0, 0);//the top right corner of the box
	distanceJointDef.localAnchorB.Set(0, 0);//center of the circle
	distanceJointDef.dampingRatio = 999; // ensure that they are tighly together and player doesn't knock it away
	distanceJointDef.frequencyHz = 0;
	// Revoluition joint makes the arm rotate around the body 
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_body;
	revoluteJointDef.bodyB = m_arm;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(0, -0.7);//the top right corner of the box
	revoluteJointDef.localAnchorB.Set(0, 0);//center of the circle
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 200000000; // high torque ensures consistent speed of the arm 
	revoluteJointDef.motorSpeed = -140 * DEG2RAD;//90 degrees per second
	// Initiate joints
	m_distJoint = (b2DistanceJoint*)world->CreateJoint(&distanceJointDef);
	m_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
	//////////////// SPRITE //////////////////////////////////////////////////////////////////////////////////////
	// set the default sprite position 
	spriteLocation = sf::IntRect(0, 0, 75, 84);
	sprite = sf::Sprite(*texture, sf::IntRect(spriteLocation));
	sprite.setScale(0.05f, 0.05f);
	sprite.setColor(sf::Color(255, 255, 255, 188));
	sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
}

//! Function to draw the sprite
/*!
\param target will choose what gets drawn
\param states defines the state for the target
*/
void slime::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite); // draw the sprite

}

//! Function that is called every cycle
/*!
*/
void slime::update()
{
	if (direction) // if direction has chnagesd then make the revolute joint spin the other way 
	{
		m_joint->SetMotorSpeed(-140 * DEG2RAD);
	}
	else {
		m_joint->SetMotorSpeed(140 * DEG2RAD);
	}
	// animation 
	sprite.setPosition(m_body->GetPosition().x + xAdjust, m_body->GetPosition().y - 3.f); // set sprite position
	float animationTime = anim.getElapsedTime().asSeconds();
	if (animationTime > 0.4f) { // move image after each time interwal
		if (spriteLocation.left >= 200)
			spriteLocation.left = 0;
		else
			spriteLocation.left += 75;
		sprite.setTextureRect(spriteLocation);
		anim.restart();
	}
}

//! Function that gets called when the slime enters a collision
/*!
\param contact refers to the contact that occured that the slime was involved with
\param layer is the layerID of the other object it collided with
*/
void slime::BeginContact(b2Contact* contact, layers layer)
{
	if (layer == layers('s')) { // if interacting with the sensors
		if (direction) {
			direction = false; // change direction 
			// re-adjust sprite
			xAdjust = 2.f;
			sprite.scale(-1, 1);
			sprite.setPosition(m_body->GetPosition().x + xAdjust, m_body->GetPosition().y - 3.0f);
		}
		else
		{
			direction = true;// change direction
			// re-adjust sprite
			sprite.scale(-1, 1);
			xAdjust = -2.f;
			sprite.setPosition(m_body->GetPosition().x + xAdjust, m_body->GetPosition().y - 3.0f);
		}
	}

}
