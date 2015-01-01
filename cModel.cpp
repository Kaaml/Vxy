#include "cModel.hpp"


cModel::cModel(void)
{
	m_Name = "unkown";
	m_Loaded = false;
	m_Scale = 1.0f;
	pMesh = 0;
}

cModel::~cModel(void){
	if( mTransform )
	{
		delete mTransform;
		mTransform = 0;
	}
	if( pMesh )
	{
		delete pMesh;
		pMesh = 0;
	}

}

void cModel::SetMesh( cMesh3d* mesh )
{
	pMesh = mesh;
}

void cModel::SetShader( const std::string &ShaderName )
{
	mShaderName = ShaderName;
}

void cModel::Draw()
{
	pMesh->BindVertexArray();
	
	//ShaderManager.Use( mShaderName );
	//SetUniform();
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	glDrawElements( GL_TRIANGLES, pMesh->GetIndicesCout(), GL_UNSIGNED_INT, 0 );
	//ShaderManager.UnUse();
	pMesh->UnbindVertexArray();
}

void cModel::SetUniform()
{
	
	/*glm::mat4 ModelView = pCamera->GetViewMatrix() * mModelMatrix;
	glm::mat3 NormalMatrix = glm::mat3( glm::transpose( glm::inverse( ModelView ) ) );
	glUniformMatrix3fv( ShaderManager[mShaderName]->GetUniformLocation( "normalMatrix"), 1, GL_FALSE, glm::value_ptr( NormalMatrix ) );
	glUniformMatrix4fv( ShaderManager[mShaderName]->GetUniformLocation( "modelViewProjectionMatrix" ),1, GL_FALSE, glm::value_ptr(  pCamera->GetProjectionMatrix() * ModelView  ) );

	if( mShaderName != "a" )
	{
		glUniformMatrix4fv( ShaderManager[mShaderName]->GetUniformLocation( "mvMatrix"), 1, GL_FALSE, glm::value_ptr( ModelView ) );
	}*/
}

void cModel::SetTransform( Transform* transform )
{
	mTransform = transform;
}

Transform* cModel::GetTransform()
{
	return mTransform;
}

/*/#################################        UBO        #######################################################	
	/*	GLuint ubo;
		glGenBuffers(1, &ubo );		
		glBindBuffer( GL_UNIFORM_BUFFER, ubo );
		
		const int Count = 10;
		const GLchar *UniformNames[] =
		{
			"Lights.position",
			"Lights.ambient",
			"Lights.diffuse",
			"Lights.specular",
			"Lights.constant_attenuation",
			"Lights.linear_attenuation",
			"Lights.quadratic_attenuation",
			"Lights.spot_direction",
			"Lights.spot_cutoff",
			"Lights.spot_exponent"
		};
		GLuint UniformIndices[Count]; // identyfikatory do poszczegolnych pol
		glGetUniformIndices( ShaderManager["Light"]->GetID(), Count, UniformNames, UniformIndices );

		GLint UniformOffsets[Count];
		GLint ArrayStrides[Count];
		
		glGetActiveUniformsiv( ShaderManager["Light"]->GetID(), Count, UniformIndices, GL_UNIFORM_OFFSET, UniformOffsets );
		glGetActiveUniformsiv( ShaderManager["Light"]->GetID(), Count, UniformIndices, GL_COLOR_ARRAY_STRIDE, ArrayStrides );
		GLuint UniformBlockIndex = glGetUniformBlockIndex( ShaderManager["Light"]->GetID(), "Lights" );

		
		unsigned char * Buffer = (unsigned char *) malloc( 4096 );
		//wrzucenie danych do buffora tymczasowego
				//position
			*( (glm::vec4 *) ( Buffer + UniformOffsets[0] )) =  Light.position ;
				//ambient
			*( (glm::vec4 *) ( Buffer + UniformOffsets[1] )) =  Light.ambient ;
				//difuse
			*( (glm::vec4 *) ( Buffer + UniformOffsets[2] )) =  Light.diffuse ;
				//specular
			*( (glm::vec4 *) ( Buffer + UniformOffsets[3] )) =  Light.diffuse ;
				//constatn_attenaution
			*( (float * )  ( Buffer + UniformOffsets[4] ))	 = Light.constant_attenuation;
				//linear_atte
			*( (float * )  ( Buffer + UniformOffsets[5] ))	 = Light.linear_attenuation;
				//quadratic
			*( (float * )  ( Buffer + UniformOffsets[4] ))	 = Light.quadratic_attenuation;
				//spot_dir
			*( (glm::vec3 * )( Buffer + UniformOffsets[4] )) = Light.spot_direction;
				//spot cutoff
			*( (float * )  ( Buffer + UniformOffsets[4] ))	= Light.spot_cutoff;
				//spot_exponent
			*( (float * )  ( Buffer + UniformOffsets[4] ))	= Light.spot_exponent;
		
		GLint uboSize = 0;
		glGetActiveUniformBlockiv( ShaderManager["Light"]->GetID(), UniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize );
		//glGetActiveUniformsiv( ShaderManager["Light"]->GetID(), Count, UniformIndices, GL_UNIFORM_SIZE, &uboSize );
		glBufferData( GL_UNIFORM_BUFFER, uboSize, Buffer, GL_STATIC_DRAW );
		glBindBufferBase( GL_UNIFORM_BUFFER, UniformBlockIndex, ubo );
		
		glBindBuffer( GL_UNIFORM_BUFFER, 0 );
	// end of ubo */