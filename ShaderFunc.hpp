#pragma once
#include "Include.hpp"
#include "Renderer.hpp"

void MVP( void* data, uint size );
void ModelMatrix( void* data, uint size );
void ViewMatrix( void* data, uint size );
void ModelViewMatrix( void* data, uint size );
void NormalMatrix( void* data, uint size );
void ProjectionMatrix( void* data, uint size );
void Emission( void* data, uint size );
void Shininess( void* data, uint size );
void Ambient( void* data, uint size );
void Diffuse( void* data, uint size );
void Specular( void* data, uint size );
void LightRadius( void* data, uint size );
void LightPosition( void* data, uint size );
void LightAmbient( void* data, uint size );
void LightDiffuse( void* data, uint size );
void LightSpecular( void* data, uint size );
void LightSpecularPower( void* data, uint size );
void LightSpotCutoff( void* data, uint size );
void LightSpotDirection( void* data, uint size );

void CameraPosition( void* data, uint size );
void ScreenResolution( void* data, uint size );


