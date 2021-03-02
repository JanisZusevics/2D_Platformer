/*! \file contactListener.cpp
 * \brief Functions and Logic behind the contact Listener
 *
 * Contact listeners get the collion data for each gameObject
 * Each object has a set 'layer' which allows me to distinguish between collisions
 */

#include "..\utilities\contactListener.h"
#include <typeinfo>
#include <iostream>

 //! Function that gets called when 2 objects collide
 /*!
 \param contact refers to the contact of 2 objects
 */
void contactListener::BeginContact(b2Contact* contact)
{
		// void pointer A gets user data 
		void* A = contact->GetFixtureA()->GetBody()->GetUserData(); // get user data
		A_Id = static_cast<char>(static_cast<PhysicalThing*>(A)->getLayerId()); // Return the layer ID of the object 
		// void pointer B gets user data 
		void* B = contact->GetFixtureB()->GetBody()->GetUserData();// get user data
		B_Id = static_cast<char>(static_cast<PhysicalThing*>(B)->getLayerId()); // Return the layer ID of the object 
		// if both pointers hold a value
		if (B && A) {
			if (B_Id == 'p') { // if player is one of the colliding objects 
				static_cast<PhysicalThing*>(B)->BeginContact(contact, layers(A_Id)); // execute player begin contact function 
			}
			if (A_Id == 'd') { // if dynamic block  is one of the colliding objects 
				static_cast<PhysicalThing*>(A)->BeginContact(contact, layers(B_Id)); // execute dynamic block begin contact function 
			}
			if (B_Id == 'e') { // if enemy slime  is one of the colliding objects 
				static_cast<PhysicalThing*>(B)->BeginContact(contact, layers(A_Id)); // execute slime begin contact function 
			}
			if (A_Id == 'c') { // if collectable  is one of the colliding objects 
				static_cast<PhysicalThing*>(A)->BeginContact(contact, layers(B_Id)); // execute collectable begin contact function 
			}
		}
}

//! Function that gets called when 2 objects stop colliding 
/*!
\param contact refers to the contact of 2 objects
*/
void contactListener::EndContact(b2Contact* contact)
{
	// void pointer A gets user data 
	void* A = contact->GetFixtureA()->GetBody()->GetUserData();// get user data
	A_Id = static_cast<char>(static_cast<PhysicalThing*>(A)->getLayerId());// Return the layer ID of the object 
	// void pointer B gets user data 
	void* B = contact->GetFixtureB()->GetBody()->GetUserData();// get user data
	B_Id = static_cast<char>(static_cast<PhysicalThing*>(B)->getLayerId());// Return the layer ID of the object 
	// if both pointers hold a value
	if (B && A) {
		if (B_Id == 'p') { // if player is one of the colliding objects 
			static_cast<PhysicalThing*>(B)->EndContact(contact, layers(A_Id));// execute player end contact function 
		}
		if (A_Id == 'd') {// if dynamic block  is one of the colliding objects 
			std::cout << B_Id << std::endl << A_Id;
			static_cast<PhysicalThing*>(A)->EndContact(contact, layers(B_Id)); // execute dynamic block begin contact function 
		}

	}
}