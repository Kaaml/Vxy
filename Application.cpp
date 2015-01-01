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
	Renderer::GetSingletonPtr()->SetActiveCamera( pCamera.get() );
	//std::cout << "INFO: OpenGL Ver: " << glfwGetWindowParam( GLFW_OPENGL_VERSION_MAJOR) <<"."<<glfwGetWindowParam( GLFW_OPENGL_VERSION_MINOR ) <<std::endl;
	//std::cout << "INFO: sizeof( Uniform )= " << sizeof( Uniform ) << std::endl;

	TextureManager *TextureMgr =TextureManager::GetSingletonPtr();
	TextureMgr->LoadTexture( "tekstura5", "Data/tekstura5.tga" );
	Texture2D  *tex =  TextureMgr->GetTexturePtr( "tekstura5" );
	TextureSampler *sampler = new TextureSampler( tex, 0, TF_LINEAR, TF_LINEAR, WM_CLAMP, WM_CLAMP );
	sampler->Update();
	cShaderManager *Manager = cShaderManager::GetInstance();
	
	Manager->LoadXmlFile( "Shader/diffuse.xml" );
	//Manager->LoadXmlFile( "plik.xml" );
	ObjLoader obj;
	//obj.Load( "Data/cube_textured.obj");
	obj.Load( "Data/plane_kratka.obj");
	Surfaces = obj.GetSurfaces();
	Surfaces[0]->SetMaterial( pMaterial.get() );

	RenderPass *Diffuse = new RenderPass();
	Diffuse->SetShader( Manager->GetProgram( "diffuse" ) );
	Diffuse->AddTexture( sampler );
	pMaterial->AddRenderPass( Diffuse );
	MaterialManager *MatMgr = MaterialManager::GetSingletonPtr();
	MatMgr->LoadMaterialXML( "Shader/mat1.xml" );
}

void Application::Run()
{
	
	Renderer *render = Renderer::GetSingletonPtr();
	render->AddLight( new Light( glm::vec3( 0.f, 1.f, 0.f ), glm::vec3( 0.8, 0.8, 0.8 ) ) );
	while( mRun )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable( GL_DEPTH_TEST );
		Timer();
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		//glFrontFace( GL_CW )
		pCamera->Update();
		render->AddToRender( Surfaces[0] );
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
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	mWindow = glfwCreateWindow( 1366, 766, "Opengl_GLFW_3.0", NULL, NULL );

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