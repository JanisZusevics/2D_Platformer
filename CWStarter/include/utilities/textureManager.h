#pragma once

/*! \file textureManager.h
 * \brief Header file for the texture manager
 *
 * This manager prevents a texture being loaded in multiple times. saving compute 
 * This is an overview of how the simple manager operates operate
 */


#include <map>
#include <ExternalLibraries/SFML-2.4.2/include/SFML/Graphics.hpp>
 
 /*! \class textureManager
 \brief A class that controls the textures of the game
 */
class textureManager
{
private:
	std::map<unsigned char, sf::Texture*> m_textures; //!< map stores a texture and an unsigned char for identification 
public:
	~textureManager(); //!< deconstructor
	bool addTexture(unsigned char key, std::string fileName); //!< Add a textuer to the manager
	sf::Texture* getTexture(unsigned char key) const; //!< Get a texture from the managers
};

