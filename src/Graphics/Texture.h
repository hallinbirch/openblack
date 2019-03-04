#pragma once
#ifndef OPENBLACK_GRAPHICS_TEXTURE_H
#define OPENBLACK_GRAPHICS_TEXTURE_H

#include <Graphics/OpenGL.h>

namespace OpenBlack {
namespace Graphics {

class Texture {
public:
	Texture();
	~Texture();

	GLuint GetHandle() const;
protected:
	GLuint _textureID;

private:
	// No copying or assignment
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
};

}
}

#endif
