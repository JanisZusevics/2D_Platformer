/*! \file Camera2D.cpp
 * \brief Functions and Logic behind the Camera
 *
 * This file sets up a lot of camera fucntionality that I use for the game
 */

#include "..\utilities\Camera2d.h"

 //! Function to get camera view
 /*!
 */
sf::View Camera2D::getView() const
{
	return m_view;
}

//! Function to set the camera centre
/*!
\param centre is coordinates of the camera centre
*/
void Camera2D::setCentre(sf::Vector2f centre)
{
	m_view.setCenter(centre);
}

//! Function to get camera centre
/*!
\return a vector coordinates
*/
sf::Vector2f Camera2D::getCentre()
{
	return m_view.getCenter();
}

//! Function to set the camera size
/*!
\param size is a vector of x size and y size
*/
void Camera2D::setSize(sf::Vector2f size)
{
	m_view.setSize(size);
}

//! Function to pan the camera 
/*!
\param distance is a vector holding desired movement 
*/
void Camera2D::pan(sf::Vector2f distance)
{
	m_view.move(distance);
}

//! Function to rotate the camera
/*!
\param angle tilts the camera by a set degrees
*/
void Camera2D::tilt(float angle)
{
	m_view.rotate(angle);
}

//! Function to zoom the camera centre
/*!
\param factor zooms in the camera by set amount
*/
void Camera2D::zoom(float factor)
{
	m_view.zoom(factor);
}
