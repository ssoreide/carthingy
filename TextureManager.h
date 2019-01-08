#pragma once

#include <windows.h>
#include <gl/gl.h>
#include "FreeImage.h"
#include <map>
#include <string>

class TextureManager
{
public:
	static TextureManager* Inst();
	virtual ~TextureManager();

	//load a texture an make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	void LoadTexture(const std::string & filename,	//where to load the file from
		GLenum image_format = GL_BGR_EXT,		//format the image is in
		GLint internal_format = GL_RGB,		//format to store the image in
		GLint level = 0,					//mipmapping level
		GLint border = 0);					//border size

	//free the memory for a texture
	bool UnloadTexture(const unsigned int texID);

	//set the current texture
	void BindTexture(const std::string & filename);

	//free all texture memory
	void UnloadAllTextures();

protected:
	TextureManager();
	TextureManager(const TextureManager& tm);
	TextureManager& operator=(const TextureManager& tm);

	static TextureManager* m_inst;
	std::map<std::string, GLuint> m_texID;
};

