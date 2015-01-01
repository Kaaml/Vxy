#include "Renderer.hpp"

//Renderer *MainRender = new Renderer( glm::vec2(1366, 768 ) );
Renderer::Renderer( const glm::vec2 &viewsize )
{
	std::cout << "class Renderer()" << std::endl;
	mViewSize = viewsize;

	mModelViewProjection = glm::mat4( 1.0f );
	mModelViewProjection = glm::perspective( 45.f, 1366.f/768.f, 0.01f, 10000.f );
	mModelViewProjection*= glm::translate( 0.f, 0.f, -10.f );
	mModelMatrix = glm::mat4( 1.0f );
	mViewMatrix = glm::mat4( 1.0f );
	mProjectionMatrix = glm::mat4( 1.0f );
	mNormalMatrix = glm::mat3( 1.0f );
	InitRendering();
}


Renderer::~Renderer(void)
{
}

void Renderer::AddToRender( Surface* surface )
{
	if( surface )
		mSurfaceToRender.push_back( surface );
}

	

void Renderer::Render()
{
	GeometryPass();
	LightPass();
}

void Renderer::InitRendering()
{
	ScreenSurface = PrefabShape::GenerateRectangle();
	RenderPass *PointLight = new RenderPass();
	cShaderManager::GetInstance()->LoadXmlFile( "Shader/PointLight.xml" );
	cProgramShader *ShaderPoint = cShaderManager::GetInstance()->GetProgram( "PointLight" );
	//cProgramShader *ShaderPoint = cShaderManager::GetInstance()->GetProgram( "default" );
	PointLight->SetShader( ShaderPoint );
	Material *PointMat = new Material();
	PointMat->AddRenderPass( PointLight );
	ScreenSurface->SetMaterial( PointMat );

	pDeferred = new Fbo( (GLuint) mViewSize.x, (GLuint)mViewSize.y );

	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGBA16F ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::DEPTH24 ) );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT0, mLayers[0] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT1, mLayers[1] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT2, mLayers[2] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT3, mLayers[3] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT4, mLayers[4] );
	pDeferred->AddDepthAtachament( mLayers[5] );
	pDeferred->SetDrawBuffers( COLOR_ATTACHMENT0, COLOR_ATTACHMENT1, COLOR_ATTACHMENT2, COLOR_ATTACHMENT3, COLOR_ATTACHMENT4 );
	

	TextureSampler *sampler1 = new TextureSampler( mLayers[0], 0, TF_LINEAR, TF_LINEAR, WM_CLAMP, WM_CLAMP );
	TextureSampler *sampler2 = new TextureSampler( mLayers[1], 1 );
	TextureSampler *sampler3 = new TextureSampler( mLayers[2], 2 );
	TextureSampler *sampler4 = new TextureSampler( mLayers[3], 3 );
	TextureSampler *sampler5 = new TextureSampler( mLayers[4], 4 ); 
	PointLight->AddTexture( sampler1 );
	PointLight->AddTexture( sampler2 );
	PointLight->AddTexture( sampler3 );
	PointLight->AddTexture( sampler4 );
	PointLight->AddTexture( sampler5 );
	
}

void Renderer::GeometryPass()
{
	pDeferred->SetDrawBuffers( COLOR_ATTACHMENT0, COLOR_ATTACHMENT1, COLOR_ATTACHMENT2, COLOR_ATTACHMENT3, COLOR_ATTACHMENT4 );
	pDeferred->BindBuffer( FBOBIND::FB );
	pDeferred->ClearBuffer();
	std::vector< Surface* >::iterator it;

	for( it = mSurfaceToRender.begin(); it != mSurfaceToRender.end(); ++it )
	{		
		pActiveMaterial = (*it)->GetMaterialPtr();
		if( pActiveMaterial )
			pActiveMaterial->Bind();
		(*it)->Render();			
	}
	mSurfaceToRender.clear();
	pDeferred->UnBind();


}

void Renderer::LightPass()
{
	glm::mat4 OldProjectionMat = mModelViewProjection;
	mModelViewProjection = glm::mat4( 1.f );
	//TO DO !!!
	for( auto &light : mLightsToRender )
	{
		//light->Render()?
		pActiveLight = light;
		pActiveMaterial = ScreenSurface->GetMaterialPtr();
		if( pActiveMaterial )
		{
			pActiveMaterial->Bind();
		}
		ScreenSurface->Render();


	}
	

	mModelViewProjection = OldProjectionMat;
}


void Renderer::SetActiveMaterial( Material *pMaterial )
{
	pActiveMaterial = pMaterial;
}

void Renderer::SetActiveCamera( cCamera *pCamera )
{
	pActiveCamera = pCamera;
}
void Renderer::SetMVPMatrix( const glm::mat4 &mvp )
{
	mModelViewProjection = mvp;
	UpdateMatrix();
}

void Renderer::SetModelMatrix( const glm::mat4 &model )
{
	mModelMatrix = model;
	UpdateMatrix();
}

void Renderer::SetViewMatrix( const glm::mat4 &view )
{
	mViewMatrix = view;
	UpdateMatrix();
}

void Renderer::SetProjectionMatrix( const glm::mat4 &projection )
{
	mProjectionMatrix = projection;
}
void Renderer::SetNormalMatrix( const glm::mat3 &normalmat )
{
	mNormalMatrix = normalmat;
}
void Renderer::UpdateMatrix()
{
	mModelViewProjection = mProjectionMatrix * mViewMatrix * mModelMatrix;
	mNormalMatrix = glm::mat3( glm::inverseTranspose( mViewMatrix * mModelMatrix ) );
}

void Renderer::AddLight( Light *pLigth )
{
	mLightsToRender.push_back( pLigth );;
}