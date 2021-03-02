/*! \file textureManager.cpp
 * \brief Functions and Logic behind the texture manager
 *
 * A simple map which holds an index and a map 
 * Contains functions used by the texture manager, and the destructor 
 */
#include "textureManager.h"

 //! Function deconstruct the textures that have been loaded in 
 /*!
 */
textureManager::~textureManager()
{
	for (auto& pair : m_textures) delete pair.second; // for each textuer
	m_textures.clear(); // delete

}

//! Function to add a texture to the manager
/*!
\param key will assign a key
\param fileName will choose what file is loaded in 
\return bool used to check if the texture has already been loaded in 
*/
bool textureManager::addTexture(unsigned char key, std::string fileName)
{
	//Has this file already loaded? 
	if (m_textures.find(key) != m_textures.end()) return false;

	//Can we load the file 
	sf::Texture tmp;
	if (!tmp.loadFromFile(fileName)) return false;

	//Add the texture to the container
	m_textures[key] = new sf::Texture(tmp);
	return true;
}

//! Function to return a texture from the manager
/*!
\param key will choose which texture to load
\return Texture pointer to be assigned to an object 
*/
sf::Texture* textureManager::getTexture(unsigned char key) const
{
	auto it = m_textures.find(key); // find the key
	if (it != m_textures.end()) return it->second; // if the texture is found then return it
 	return nullptr; // else return a null pointer
} 
