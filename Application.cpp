#include "Application.hpp"


Application::Application(void)
{
	pMaterial.reset( new Material );
}

Application::Application( float Width, float Height )
{
	pMaterial.reset( new Material );
	mWidth = Width;
	mRun = true;
	mHeight = Height;
}

void Application::Init()
{
	InitUtilities();
	pCamera.reset( new cCamera );
	pCamera->InitPerspectiv( mWidth, mHeight );
	pCamera->Move( glm::vec3( 0.f, 0.f, 10.f ) );
	MaterialManager *MatMgr = MaterialManager::GetSingletonPtr();
	MatMgr->LoadMaterialXML( "Shader/mat1.xml" );

	Renderer::GetSingletonPtr()->InitRendering();
	Renderer::GetSingletonPtr()->SetActiveCamera( pCamera.get() );

	//TextureManager *TextureMgr =TextureManager::GetSingletonPtr();
	//TextureMgr->LoadTexture( "tekstura5", "Data/tekstura5.tga" );
	//TextureMgr->LoadTexture( "tekstura6", "Data/Banana.jpg" );
	ObjLoader obj, obj2;
	//obj.Load( "Data/banana3.obj");
	//obj.Load( "Data/banana3.obj" );
	obj.Load( "Data/dabrovic-sponza/sponza2.obj" );
	//obj.Load( "Data/Knife.obj" );
	Surfaces = obj.GetSurfaces();
	//Surfaces[0]->SetMaterial( pMaterial.get() );

	//tmp
	//Surfaces = obj2.GetSurfaces();
	/*for( int i = 0; i < Surfaces.size(); ++i )
	{
		Surfaces[i]->SetMaterial( MatMgr->GetMaterialPtr( "default" ) );
	}
	for( int i = 0; i < 6; ++i )
	{
		Surfaces[i]->SetMaterial( MatMgr->GetMaterialPtr( std::string( "sponza" ) + std::to_string( i) ) );
	}*/
	

	
	//auto ptrMaterial = MatMgr->GetMaterialPtr( "point_light" );
	//Surfaces[0]->SetMaterial( ptrMaterial );
	//IndexBuffer *pindx = new IndexBuffer();
	pSurface = PrefabShape::GeneratePlane();
	Material* ptrMaterialFlat = MatMgr->GetMaterialPtr( "flat" );
	Material* ptrMatTerrain = MatMgr->GetMaterialPtr( "terrain" );
	pSurface->SetMaterial( ptrMatTerrain );


}

void Application::Run()
{
	Renderer *render = Renderer::GetSingletonPtr();
	render->AddLight( new Light( glm::vec3( 0.f, 1.f, 0.f ), glm::vec3( 0.8, 0.8, 0.8 ), LightType::DIRECTION ) );
	Light *light = new Light( glm::vec3( 1.f ), glm::vec3( 1.f ), LightType::SPOT );
	light->SetSpotLight( glm::vec3( 0.f, 1.f, 0.f ), glm::vec3( 0.f, -1.f, 0.f ), 45.f );
	//render->AddLight( new Light( glm::vec3( 0.f, 1.0, 0.f ), glm::vec3( 1.f, 1.f, 0.f ), LightType::SPOT ) );
	//render->AddLight( light );
	while( mRun )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable( GL_DEPTH_TEST );
		Timer();
		pCamera->Update();
		//render->AddToRender( Surfaces[0] );
		for( int i = 0; i < Surfaces.size(); ++i )
		{
			render->AddToRender( Surfaces[i] );
		}
		render->AddToRender( pSurface );
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glFrontFace( GL_CCW );
		render->Render();



		
		glfwGetCursorPos( mWindow, &mMousePosition.x, &(mMousePosition.y) );
		if( glfwGetMouseButton( mWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ) pCamera->AddToYaw(   0.002f * (float)DeltaTime * float( mWidth/2.f -  (float)mMousePosition.x  ));		
		if( glfwGetMouseButton( mWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ) pCamera->AddToPitch( 0.002f * (float)DeltaTime * float( mHeight/2.f - (float)mMousePosition.y )); 
		if( glfwGetKey( mWindow, GLFW_KEY_LEFT ) == GLFW_PRESS  )	pCamera->Move( glm::vec3( 10.f * DeltaTime, 0.0f, 0.f )); 
		if( glfwGetKey( mWindow, GLFW_KEY_RIGHT ) == GLFW_PRESS  )  pCamera->Move( glm::vec3( -10.f * DeltaTime, 0.0f, 0.f ));
		if( glfwGetKey( mWindow, GLFW_KEY_UP ) == GLFW_PRESS  )		pCamera->Move( glm::vec3( 0.0f, 0.f , -10.f * DeltaTime));
		if( glfwGetKey( mWindow, GLFW_KEY_DOWN ) == GLFW_PRESS  )	pCamera->Move( glm::vec3( 0.0f, 0.f, 10.f * DeltaTime ));		


		glfwSwapBuffers( mWindow );
		glfwPollEvents();
		mRun = !glfwWindowShouldClose( mWindow );		
	}

}

void Application::CleanUp()
{
	glfwDestroyWindow( mWindow );
	glfwTerminate();

}

Application::~Application(void)
{

}


void Application::InitUtilities()
{
	if( !glfwInit() )
	{
		std::cerr << "EROR: Inicjalizacja GLFW nie powiodla sie\n";
	}
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	mWindow = glfwCreateWindow( 1366, 766, "Opengl_GLFW_3.0", NULL, NULL );
	glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB );

	if( !mWindow )
	{
		glfwTerminate();
		std::cerr << "EROR: Inicjalizacja GLFW nie powiodla sie\n";
	}
	glfwMakeContextCurrent( mWindow );
	if( glewInit() != GLEW_OK )
	{
		std::cerr << "EROR: Inicjalizacja GLEW nie powiodla sie\n";
	}
	ilInit();
	iluInit();
	ilutInit();
	cShaderManager::GetInstance()->LoadXmlFile( "Shader/default.xml" );
	new TextureManager();
	new Renderer( glm::vec2( 1366, 766 ) );
}

void Application::Timer()
{
	DeltaTime = glfwGetTime() - mTime;
	mTime = glfwGetTime();
}