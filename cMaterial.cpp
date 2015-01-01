#include "cMaterial.hpp"


//cMaterial::cMaterial(void){}
cMaterial::cMaterial()
{
	
	
}


cMaterial::~cMaterial(void)
{

}




//void cMaterial::SetImage( std::string ImageName )
//{
//	ILuint image;
//	ilGenImages(1, &image);
//	ilBindImage( image );
//	ilLoadImage( ImageName.c_str() );
//	ILenum Error;
//	Error = ilGetError();
//	if( Error != IL_NO_ERROR )
//		std::cout << "ERROR: Blad wczytania pliku: " << ImageName << " w materiale: " << m_Name << std::endl;
//	int width, height, depth;
//	ILenum type, format;
//	width = ilGetInteger(IL_IMAGE_WIDTH);
//	height = ilGetInteger(IL_IMAGE_HEIGHT);
//	depth = ilGetInteger( IL_IMAGE_DEPTH );
//	type = ilGetInteger( IL_IMAGE_TYPE );
//	format = ilGetInteger( IL_IMAGE_FORMAT );
//	ILubyte *pixmap = ilGetData();
//	glBindTexture( m_Type, h_Texture );
//	switch (m_Type)
//	{
//	case GL_TEXTURE_1D:
//		break;
//	case GL_TEXTURE_2D:
//		glTexImage2D( m_Type, 0, GL_RGB, width, height, 0, format, type, pixmap );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		break;
//	case GL_TEXTURE_3D:
//		break;
//	case GL_TEXTURE_CUBE_MAP:
//		break;
//
//	default:
//		break;
//	}
//	ilDeleteImage( image );
//	glBindTexture( m_Type, 0 );
//
//}
