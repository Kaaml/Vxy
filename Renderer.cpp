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
	//InitRendering();
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
	// TO DO: NAPISAC SHADERY DO DIR LIGHT, SPOT LIGHT I POINT LIGHT I PRZETESTOWAC DZIALANIE!!!!!!!!!!
	DirectLightSurface = PrefabShape::GenerateRectangle();
	SpotLightSurface = PrefabShape::GenerateRectangle();
	//PointLightSurface = PrefabShape::GenerateRectangle();

	cShaderManager *ShaderMgr = cShaderManager::GetInstance();
	cProgramShader *DirectLightShader = ShaderMgr->GetProgram( "DirectLight" );
	cProgramShader *SpotLightShader   = ShaderMgr->GetProgram( "SpotLight" );
	//cProgramShader *PointLightShader  = ShaderMgr->GetProgram( "PointLight" );

	MaterialManager& MatMgr = MaterialManager::GetSingleton();
	//auto DirLight = MatMgr.GetMaterialPtr( "DirectLight" );	

	RenderPass *DirectLight = new RenderPass();
	RenderPass *SpotLight = new RenderPass();
	//RenderPass *PointLight = new RenderPass();
	
	DirectLight->SetShader( DirectLightShader );
	SpotLight->SetShader( SpotLightShader );
	//PointLight->SetShader( PointLightShader );

	Material *DirectLightMaterial = new Material();
	Material *SpotLightMaterial = new Material();
	//Material *PointLightMaterial = new Material();

	DirectLightMaterial->AddRenderPass( DirectLight );
	SpotLightMaterial->AddRenderPass( SpotLight );
	//PointLightMaterial->AddRenderPass( PointLight );

	DirectLightSurface->SetMaterial( DirectLightMaterial );
	SpotLightSurface->SetMaterial( SpotLightMaterial );
	//PointLightSurface->SetMaterial( pPointLightMaterial );

	pDeferred = new Fbo( (GLuint) mViewSize.x, (GLuint)mViewSize.y );

	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGBA16F ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	//mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::RGB ) );
	mLayers.push_back( new Texture2D( (int)mViewSize.x, (int)mViewSize.y, 0, FORMAT::DEPTH24 ) );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT0, mLayers[0] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT1, mLayers[1] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT2, mLayers[2] );
	pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT3, mLayers[3] );
	//pDeferred->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT4, mLayers[4] );
	pDeferred->AddDepthAtachament( mLayers[4] );
	pDeferred->SetDrawBuffers( COLOR_ATTACHMENT0, COLOR_ATTACHMENT1, COLOR_ATTACHMENT2, COLOR_ATTACHMENT3/*, COLOR_ATTACHMENT4*/ );
	
	TextureSampler *sampler1 = new TextureSampler( mLayers[0], 0, TF_LINEAR, TF_LINEAR, WM_CLAMP, WM_CLAMP );
	TextureSampler *sampler2 = new TextureSampler( mLayers[1], 1, TF_LINEAR, TF_LINEAR, WM_CLAMP, WM_CLAMP );
	TextureSampler *sampler3 = new TextureSampler( mLayers[2], 2, TF_LINEAR, TF_LINEAR, WM_CLAMP, WM_CLAMP );
	//TextureSampler *sampler4 = new TextureSampler( mLayers[3], 3, TF_LINEAR, TF_LINEAR, WM_CLAMP, WM_CLAMP );
	//TextureSampler *sampler5 = new TextureSampler( mLayers[4], 4 ); 
	DirectLight->AddTexture( sampler1 );				    // OutputAmbient = 0
	DirectLight->AddTexture( sampler2 );					// OutputNormal =1
	DirectLight->AddTexture( sampler3 );					// OutputPosition =2
	//PointLight->AddTexture( sampler4 );					// OutputDiffuse =3
	//PointLight->AddTexture( sampler5 );		

	SpotLight->AddTexture( sampler1 );						// OutputAmbient = 0
	SpotLight->AddTexture( sampler2 );					    // OutputNormal =1
	SpotLight->AddTexture( sampler3 );					    // OutputPosition =2

	//PointLight->AddTexture( sampler1 );						//OutputAmbient = 0
	//PointLight->AddTexture( sampler2 );					    // OutputNormal =1
	//PointLight->AddTexture( sampler3 );					    // OutputPosition =2
														  
}

void Renderer::GeometryPass()
{
	pDeferred->SetDrawBuffers( COLOR_ATTACHMENT0, COLOR_ATTACHMENT1, COLOR_ATTACHMENT2, COLOR_ATTACHMENT3/*, COLOR_ATTACHMENT4*/ );
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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( 0.f, 0.f, 0.0f, 1.f );
	glEnable( GL_BLEND );
	glBlendEquation( GL_FUNC_ADD );
	glBlendFunc( GL_ONE, GL_ONE );
	glDisable( GL_DEPTH_TEST );
	//direct lighting first
	for( auto &light : mLightsToRender )
	{
		//light->Render()?
		pActiveLight = light;
		
		if( light->GetLightType() == LightType::DIRECTION )
		{
			pActiveMaterial = DirectLightSurface->GetMaterialPtr();
			if( pActiveMaterial )
			{
				pActiveMaterial->Bind();
			}
			DirectLightSurface->Render();
		} else if( light->GetLightType() == LightType::SPOT )
		{
			pActiveMaterial = SpotLightSurface->GetMaterialPtr();
				//spot light
			if( pActiveMaterial )
			{
				pActiveMaterial->Bind();
			}
			SpotLightSurface->Render();

		} else if( light->GetLightType() == LightType::POINT_LIGHT )
		{
			//pActiveMaterial = PointightSurface->GetMaterialPtr();
			if( pActiveMaterial )
			{
				pActiveMaterial->Bind();
			}
			DirectLightSurface->Render();
		}
		
	}
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );

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