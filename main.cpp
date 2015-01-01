#define GLEW_STATIC
//#include <GL\glew.h>
//#include <IL\il.h>
//#include <IL\ilu.h>
//#include <IL\ilut.h>
//#include <GL\glfw.h>
//#include <iostream>
//#include "cShaderManager.hpp"
//#include "cModel.hpp"
//#include "cCamera.hpp"
//#include "cMaterial.hpp"
//#include "cMesh3d.hpp"
//#include "Fbo.hpp"
//#include "Light.hpp"
//#include "Transform.hpp"
//#include "Keyboard.hpp"
//#include "VAOManager.hpp"
#include "Application.hpp"

#define WIDTH 1366
#define HEIGHT 768
#define MOUSE_SPEED 0.002f


//VAO* CreateSimpleVAO();
//
//
//double Timer( void )
//{
//	float DeltaTime = 0.001f;
//	static float OldTime;
//	float Time = (float) glfwGetTime();
//
//	DeltaTime = Time -  OldTime;
//	OldTime = Time;
//	return DeltaTime;
//}
//	bool active = false;
//	bool active_last = false;
//	std::vector <bool> Last;
//	std::vector <bool> Keys;
//	
//void KeyUpdate()
//{
//	for( int i = 0; i < GLFW_KEY_SPECIAL + 69; i++ )
//	{
//		if( glfwGetKey( i ) == GLFW_RELEASE ) 
//		{
//			Keys[i] = false;
//			Last[i] = false;
//		}
//		if( glfwGetKey( i ) == GLFW_PRESS ) 
//		{
//			if( Keys[i] == true ) Last[i] = true;
//			Keys[i] = true;
//		}
//	}
//}
//bool IsKeyDown( int key )
//{
//	return Keys[key];
//}
//bool KeyEvent( int key )
//{
//	return Keys[key] && !Last[key] ;	
//}

//
//int main()
//{
//	Last.resize( GLFW_KEY_SPECIAL + 70 );
//	Keys.resize( GLFW_KEY_SPECIAL + 70 );
//	if( !glfwInit() )
//	{
//		return 1;
//	}
//
//	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 4 );
//	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 ); 
//	glfwOpenWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
//
//	if( !glfwOpenWindow( WIDTH, HEIGHT, 8, 8, 8, 8, 8, 8, GLFW_WINDOW ) )
//	{
//		glfwTerminate();
//		return 1;
//	}
//	if( glewInit() != GLEW_OK )
//	{
//		return 1;
//	}
//	ilInit();
//	iluInit();
//	ilutInit();
//	//###########################################################################################################
//	//									INICJALIZACJA I LADOWANIE
//	//###########################################################################################################
//	VAO *pVao = CreateSimpleVAO();
//	
//	std::cout << "INFO: OpenGL Ver: " << glfwGetWindowParam( GLFW_OPENGL_VERSION_MAJOR) <<"."<<glfwGetWindowParam( GLFW_OPENGL_VERSION_MINOR ) <<std::endl;
//	glClearColor( 0.73f, 0.73f, 0.73f, 1.0f );
//	glEnable(GL_DEPTH_TEST);
//	glfwDisable( GLFW_KEY_REPEAT );
//	glfwSetMousePos( WIDTH/2, HEIGHT/2 );
//	int xpos, ypos;
//	std::vector < cModel * > Actors;	
//	cCamera camera;
//	camera.InitPerspectiv();
//	cCamera* Ortho = new cCamera();
//	Ortho->InitOrtogonal( WIDTH, HEIGHT );
//	cCamera* Cam2 = new cCamera();
//	Cam2->InitPerspectiv();
//	bool run = true;
//	bool viewframe = false;
//	float SpecularPower = 2.5f;
//	ShaderManager.CreateProgramWithFile( "Shader/SpotPass.shad" );		
//	ShaderManager.CreateProgramWithFile( "Shader/Deffered.shad" );	
//	ShaderManager.CreateProgramWithFile( "Shader/Texture.shad" );
//	ShaderManager.CreateProgramWithFile( "Shader/DirPass.shad" );
//	ShaderManager.CreateProgramWithFile( "Shader/Null.shad" );
//		
//	////#################################        END        #######################################################
//	Fbo *Deffered = new Fbo( HEIGHT, WIDTH );
//	Texture2D *Normal = new Texture2D("",  WIDTH, HEIGHT, 0, RGBA32F );
//	Texture2D *Position = new Texture2D("",  WIDTH, HEIGHT, 0, RGB32F );
//	Texture2D *Specular = new Texture2D("",  WIDTH, HEIGHT, 0, RGB32F );		
//	Texture2D *Diffuse = new Texture2D("",  WIDTH, HEIGHT, 0, RGB32F );
//	Texture2D *Ambient = new Texture2D( "", WIDTH, HEIGHT, 0, RGB32F );
//	Texture2D *Deptht = new Texture2D( "", WIDTH, HEIGHT, 0, FORMAT::DEPTH_STENCIL32 );
//	Deffered->AddDepthAtachament( Deptht );
//	Deffered->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT0, Position );	
//	Deffered->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT1, Normal );		
//	Deffered->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT2, Ambient );
//	Deffered->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT3, Diffuse );
//	Deffered->AddTextureAtachament( BUFFERTARGET::COLOR_ATTACHMENT4, Specular );
//	// Wektor zawierajace bufory do aktywowania w FBO
//	std::vector < BUFFERTARGET > AttachamentBuff; 
//	AttachamentBuff.push_back( COLOR_ATTACHMENT0 );
//	AttachamentBuff.push_back( COLOR_ATTACHMENT1 );
//	AttachamentBuff.push_back( COLOR_ATTACHMENT2 );
//	AttachamentBuff.push_back( COLOR_ATTACHMENT3 );
//	AttachamentBuff.push_back( COLOR_ATTACHMENT4 );
//	Deffered->EnableDepth();	
//	Deffered->SetDrawBuffers( AttachamentBuff );
//
//	Texture2D *kostka = new Texture2D( "", "Data/tekstura.tga" );
//	Light *light = new Light();
//	glm::vec3 LightPos = glm::vec3( 0.0, 2.0, 0.0 );
//	light->SetPosition( glm::vec3( 0.0f, 2.f, 25.0f ) ); 
//	light->SetColor( glm::vec3( 1.0f, 1.0f, 1.0f ) );
//	light->SetRadius( 10.f );
//	
//	Light *light2 = new Light( glm::vec3( 0.f, 1.f, 1.f ), glm::vec3( 1.f, 1.f, 1.f), LightType::Dir );
//	light2->SetDiffuse( 0.5f );
//
//	// ###################         PRZYGOTOWANIE AKTORÓW             ####################
//	cMesh3d *cube = new cMesh3d( "Data/cube2.obj" );
//	Actors.push_back( new cModel );
//	Actors.back()->SetMesh( cube );
//	Actors.back()->SetTransform( new Transform );
//	Actors.back()->GetTransform()->Scale( 20.f, 0.5f, 20.f );
//	Actors.back()->GetTransform()->Translate( 0.0f, -5.f, 0.0f );
//	cModel* SphereM = new cModel();
//	SphereM->SetMesh( Sphere() );
//	SphereM->SetTransform( new Transform );
//	SphereM->GetTransform()->Translate( -12, 0.0, -30 );
//
//	cModel *Rec = new cModel();
//	Rec->SetTransform( new Transform );
//	Rec->SetMesh( Plane() );
//
//	cMesh3d *cube2 = Cube();
//	for( int a = 0; a < 5; ++a )
//	{
//		for( int b = 0; b < 5; ++b )
//		{
//			Actors.push_back( new cModel );
//			Actors.back()->SetMesh( cube  );		
//			Actors.back()->SetTransform( new Transform );
//			Actors.back()->GetTransform()->Translate( -10+(float)a*8.f, 0.0f, b*-8.f+20 );
//		}
//	}
//	Actors.push_back( new cModel );
//	Actors.back()->SetMesh( cube2 );
//	Actors.back()->SetTransform( new Transform );
//	Actors.back()->GetTransform()->Scale( 0.5f, 0.5f, 0.5f );
//	//############### koniec aktorow ####################################################	
//	GLuint tmp, Loc1, Loc2, Loc3, Loc4, Loc5, Loc6, Loc7, Loc8;
//	while( run )
//	{	
//		KeyUpdate();
//		glClearColor( 0.73f, 0.73f, 0.73f, 1.0f );
//		float DeltaTime = (float)Timer();
//		glfwGetMousePos(&xpos, &ypos);
//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
//		camera.Update();
//		// ***********************************************************************************	
//		//						FAZA GEOMETRI
//		// ***********************************************************************************
////		Deffered->SetDrawBuffers( AttachamentBuff );
////		Deffered->BindBuffer( FBOBIND::FB );
////		Deffered->BindDrawBuffers();	
////		//glDepthMask(GL_TRUE);
////		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////		glEnable(GL_DEPTH_TEST);
////		glDisable(GL_BLEND);
////		// ##################         WYŒWIETLA WSZYSTKIE MODELE  #################################
////		glViewport( 0, 0, WIDTH, HEIGHT );
////		ShaderManager.Use( "Deffered" );		
////		kostka->Bind( 0 );
////		for( std::vector< cModel*>::iterator it = Actors.begin(); it != Actors.end(); it++ )
////		{
////			(*it)->GetTransform()->CalculateWordlMatrix();			
////			glm::mat4 Model =  (*it)->GetTransform()->GetWordlMatrix();
////			glm::mat4 ModelView = camera.GetViewMatrix() * Model;
////			glm::mat3 NormalMatrix =  glm::inverseTranspose( glm::mat3( Model ) );
////			glm::mat4 MVP =  camera.GetProjectionMatrix() * ModelView;
////			float p = 128.f; int a = 0;
////
////			ShaderManager.GetActiveShader()->SetUniform( "Shininess", TFLOAT, &p);
////			ShaderManager.GetActiveShader()->SetUniform( "normalMatrix", MAT3, glm::value_ptr( NormalMatrix) );
////			ShaderManager.GetActiveShader()->SetUniform( "modelViewProjectionMatrix", MAT4, glm::value_ptr( MVP) );
////			ShaderManager.GetActiveShader()->SetUniform( "Texture1", TINT,  &a);
////			ShaderManager.GetActiveShader()->SetUniform( "mMatrix", MAT4, glm::value_ptr( Model ) );
////			/*Loc1 = ShaderManager.GetActiveShader()->GetUniformLocation("normalMatrix");
////			Loc2 = ShaderManager.GetActiveShader()->GetUniformLocation("modelViewProjectionMatrix");
////			Loc3 = ShaderManager.GetActiveShader()->GetUniformLocation( "mMatrix" );
////			Loc4 = ShaderManager.GetActiveShader()->GetUniformLocation( "Texture1" );
////			Loc5 = ShaderManager.GetActiveShader()->GetUniformLocation( "Shininess" ); 
////			glUniformMatrix3fv( Loc1, 1, GL_FALSE, glm::value_ptr( NormalMatrix) );
////			glUniformMatrix4fv( Loc2, 1, GL_FALSE, glm::value_ptr( camera.GetProjectionMatrix() * ModelView ) );
////			glUniformMatrix4fv( Loc3, 1, GL_FALSE, glm::value_ptr( (*it)->GetTransform()->GetWordlMatrix() ) ); */
////			Loc6 = ShaderManager.GetActiveShader()->GetUniformLocation( "AmbientIntensity");
////			Loc7 = ShaderManager.GetActiveShader()->GetUniformLocation( "DiffuseIntensity");
////			Loc8 = ShaderManager.GetActiveShader()->GetUniformLocation( "SpecularIntenisty");
////
////			glUniform3f( Loc6, 1.f, 1.f, 1.f );
////			glUniform3f( Loc7, 1.f, 1.f, 1.f );
////			glUniform3f( Loc8, 1.f, 1.f, 1.f );
////			pVao->Render();
////			//(*it)->Draw();
////		}	
////#pragma region STENCIL_PASS
////		// ***********************************************************************************	
////		//						 FAZA STENCIL
////		// ***********************************************************************************
////		//glDepthMask( GL_FALSE );	
////		//glEnable( GL_STENCIL_TEST );
////		//ShaderManager.Use( "Null" );
////		//Deffered->SetDrawBuffers( BUFFERTARGET::NONE );
////		//Deffered->BindDrawBuffers();
////		//glEnable( GL_DEPTH_TEST );
////		//glDisable( GL_CULL_FACE );
////		//glClear( GL_STENCIL_BUFFER_BIT );
////		//glStencilFunc( GL_ALWAYS, 0, 0 );
////		//glStencilOpSeparate( GL_BACK, GL_KEEP, GL_INCR, GL_KEEP );
////		//glStencilOpSeparate( GL_FRONT, GL_KEEP, GL_DECR, GL_KEEP );
////		//tmp = ShaderManager.GetActiveShader()->GetUniformLocation("modelViewProjectionMatrix");
////		glm::mat4 ModelView = Ortho->GetViewMatrix() * Rec->GetTransform()->GetWordlMatrix();
////		//glUniformMatrix4fv( tmp , 1, GL_FALSE, glm::value_ptr( Ortho->GetProjectionMatrix() *
////		//Ortho->GetViewMatrix()* Rec->GetTransform()->GetWordlMatrix() ) );
////		//Rec->Draw();		
////
////		//Deffered->SetDrawBuffers( BUFFERTARGET::COLOR_ATTACHMENT3 );
////		//Deffered->BindDrawBuffers();
////
////		// PRZYGOTOWANIE DO OSWIETLENIA :
////		//glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
////#pragma endregion STENCIL_PASS
////		glBindFramebuffer( GL_FRAMEBUFFER, 0 );
////		glEnable(GL_BLEND);
////		glDisable( GL_DEPTH_TEST );
////		glBlendEquation(GL_FUNC_ADD);
////		glBlendFunc(GL_ONE, GL_ONE);
////		//glEnable(GL_CULL_FACE);				//dodane stencil
////		//glCullFace(GL_BACK);				// dodane stencil
////		glClearColor( 0.0, 0.0, 0.0, 1.0 );
////		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////#pragma region POINT_LIGHT
////		// ***********************************************************************************	
////		//						OSWIETLENIE PUNKTOWE 
////		// ***********************************************************************************
////		Position->Bind( 0 );	
////		Normal->Bind( 1 );
////		Ambient->Bind( 2 );
////		ShaderManager.Use( "Texture" );
////		Rec->GetTransform()->CalculateWordlMatrix();
////		glm::mat4 MVP = Ortho->GetVPmatrix() * Rec->GetTransform()->GetWordlMatrix();
////		ShaderManager.GetActiveShader()->SetUniform( "modelViewProjectionMatrix", MAT4, glm::value_ptr( MVP ) );	
////		// ++++++++++++    SPHERA JAKO OPTYMALIZACJA 	
////		/*SphereM->GetTransform()->Translate(light->GetPosition() );
////		SphereM->GetTransform()->Scale( 10.5f, 10.5f, 10.5f );
////		SphereM->GetTransform()->CalculateWordlMatrix();
////		glm::mat4 MVP = camera.GetVPmatrix() * SphereM->GetTransform()->GetWordlMatrix();
////		ShaderManager.GetActiveShader()->SetUniform( "modelViewProjectionMatrix", MAT4, glm::value_ptr( MVP ) );
////		glEnable( GL_CULL_FACE );
////		glCullFace( GL_BACK ); 
////		/ +++++++++++++++ KONIEC SPHERY */
////		light->SetUniforms();
////		int location = 0;
////		ShaderManager.GetActiveShader()->SetUniform( "texPosition", TINT, &location );
////		GLint TexLoc1 = ShaderManager.GetActiveShader()->GetUniformLocation( "texPosition" );
////		GLint TexLoc2 = ShaderManager.GetActiveShader()->GetUniformLocation( "texNormal" );
////		GLint TexLoc3 = ShaderManager.GetActiveShader()->GetUniformLocation( "texColor" );
////		GLint SizeLoc = ShaderManager.GetActiveShader()->GetUniformLocation( "ScreenSize" );
////		glUniform1i( TexLoc1, 0 );
////		glUniform1i( TexLoc2, 1 );
////		glUniform1i( TexLoc3, 2 );
////		glUniform2f( SizeLoc, WIDTH, HEIGHT );		
////		Rec->Draw();	
////		//SphereM->Draw();
////#pragma endregion POINT_LIGHT
////#pragma region SPOT_LIGHT
////		// ***********************************************************************************	
////		//						ŒWIAT£O REFLEKTOROWE
////		// ***********************************************************************************
////		/*ShaderManager.Use( "SpotPass" );
////		Rec->GetTransform()->CalculateWordlMatrix();
////		MVP = Ortho->GetVPmatrix() * Rec->GetTransform()->GetWordlMatrix();
////		ShaderManager.GetActiveShader()->SetUniform( "modelViewProjectionMatrix", MAT4, glm::value_ptr( MVP ) );	
////		TexLoc1 = ShaderManager.GetActiveShader()->GetUniformLocation( "texPosition" );
////		TexLoc2 = ShaderManager.GetActiveShader()->GetUniformLocation( "texNormal" );
////		TexLoc3 = ShaderManager.GetActiveShader()->GetUniformLocation( "texColor" );
////		SizeLoc = ShaderManager.GetActiveShader()->GetUniformLocation( "ScreenSize" );
////		glUniform1i( TexLoc1, 0 );
////		glUniform1i( TexLoc2, 1 );
////		glUniform1i( TexLoc3, 2 );
////		glUniform2f( SizeLoc, WIDTH, HEIGHT );
////		//DODAC SWIATLO 
////		// np Lightxyz->SetUniforms();
////		Rec->Draw();*/
////#pragma endregion SPOT_LIGHT
////#pragma region DIRECT_LIGHT
////		// ***********************************************************************************	
////		//						ŒWIAT£O KIERUNKOWE
////		// ***********************************************************************************
////		//* >>>>> BLOKADA SWIATLA KIERUNKOWEGO USUNAC   <<<<<<
////		ShaderManager.Use( "DirPass" );
////		Rec->GetTransform()->CalculateWordlMatrix();
////		tmp = ShaderManager.GetActiveShader()->GetUniformLocation( "modelViewProjectionMatrix" );
////		ModelView = Ortho->GetViewMatrix() * Rec->GetTransform()->GetWordlMatrix();		
////		glUniformMatrix4fv( tmp , 1, GL_FALSE, glm::value_ptr( Ortho->GetProjectionMatrix() *
////		Ortho->GetViewMatrix()* Rec->GetTransform()->GetWordlMatrix() ) );
////		light2->SetUniforms();
////		TexLoc1 = ShaderManager.GetActiveShader()->GetUniformLocation( "texPosition" );
////		TexLoc2 = ShaderManager.GetActiveShader()->GetUniformLocation( "texNormal" );
////		TexLoc3 = ShaderManager.GetActiveShader()->GetUniformLocation( "texColor" );
////		SizeLoc = ShaderManager.GetActiveShader()->GetUniformLocation( "ScreenSize" );	
////		glUniform1i( TexLoc2, 1 );
////		glUniform1i( TexLoc3, 2 );
////		glUniform2f( SizeLoc, WIDTH, HEIGHT );
////		Rec->Draw();
////#pragma endregion DIRECT_LIGHT
////
////		// ***********************************************************************************	
////		//						FINAL - PRZEPISANIE BUFORU 4 NA EKRAN 
////		// ***********************************************************************************
////		Deffered->UnBind();
////		Deffered->BindBuffer( FBOBIND::READ );		
////		Deffered->SetReadBuffer( COLOR_ATTACHMENT1 );
////		glBlitFramebuffer( 0, 0, WIDTH, HEIGHT, 0, 0, WIDTH/4 , HEIGHT/4, GL_COLOR_BUFFER_BIT, GL_LINEAR );	
//
//		ShaderManager.Use( "Null" );
//		pVao->Render();
////Actors[0]->Draw();
//		
//		if( glfwGetKey( GLFW_KEY_F4) == GLFW_PRESS )	LightPos.y += DeltaTime * 5.f;
//		if( glfwGetKey( GLFW_KEY_F5) == GLFW_PRESS )	LightPos.y -= DeltaTime * 5.f;
//		if( glfwGetKey( GLFW_KEY_F6) == GLFW_PRESS )	LightPos.z += DeltaTime * 5.f;
//		if( glfwGetKey( GLFW_KEY_F7) == GLFW_PRESS )	LightPos.z -= DeltaTime * 5.f;
//		if( KeyEvent( GLFW_KEY_KP_ADD) )	SpecularPower+= 0.5;
//		if( KeyEvent( GLFW_KEY_KP_SUBTRACT ) )	SpecularPower-= 0.5;
//		light->SetPosition( LightPos );
//		light->SetSpecularPower( SpecularPower );
//		Actors.back()->GetTransform()->Translate( LightPos );
//		
//		if( viewframe ) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//			else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
//
//		//###########################################################################################################
//		//									KAMERA
//		//###########################################################################################################
//		if( glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ) camera.AddToYaw( MOUSE_SPEED * DeltaTime * float( WIDTH/2 - xpos ));
//		if( glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ) camera.AddToPitch( MOUSE_SPEED * DeltaTime * float( HEIGHT/2 - ypos )); 
//		if( glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS  ) camera.Move( glm::vec3( 10.f * DeltaTime, 0.0f, 0.f )); 
//		if( glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS  )  camera.Move( glm::vec3( -10.f * DeltaTime, 0.0f, 0.f ));
//		if( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS  )	camera.Move( glm::vec3( 0.0f, 0.f , -10.f * DeltaTime));
//		if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS  ) camera.Move( glm::vec3( 0.0f, 0.f, 10.f * DeltaTime ));		
//
//		if( Keyboard::GetSingleton().IsKeyPressed( GLFW_KEY_TAB ) ) std::cout << "LIGHT x: " << LightPos.x << " y: " << LightPos.y << " z: " << LightPos.z << std::endl;	
//
//		if( KeyEvent( GLFW_KEY_F1 ) == GLFW_PRESS ) 
//			viewframe = !viewframe;
//		glfwSwapBuffers();
//		run = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );		
//		Keyboard::GetSingleton().Update();
//	}
//
//	delete Deffered;
//
//	return 0;
//}	//         >>>> END OF MAIN FUNC <<<<


int main( int argc, char *argv[] )
{
	Application App( WIDTH, HEIGHT );
	App.Init();
	App.Run();
	App.CleanUp();
	
}


//VAO* CreateSimpleVAO()
//{
//	struct Vertex	
//	{
//		glm::vec3 Position;
//		glm::vec3 Normal;
//		glm::vec2 TexCoord;
//	};
//
//	std::vector< Vertex > m_Vertex;
//	std::vector< int > Indices;
//	m_Vertex.resize( 24 );
//	Indices.resize( 36 );	m_Vertex[0] .Position = glm::vec3(  1, -1, -1 );
//	Indices[0]  = 0 ;		m_Vertex[1] .Position = glm::vec3(  1, -1,  1 );
//	Indices[1]  = 1 ;		m_Vertex[2] .Position = glm::vec3( -1, -1,  1 );
//	Indices[2]  = 2 ;		m_Vertex[3] .Position = glm::vec3( -1, -1, -1 );
//	Indices[3]  = 0 ;		m_Vertex[4] .Position = glm::vec3(  1,  1, -1 );
//	Indices[4]  = 2 ;		m_Vertex[5] .Position = glm::vec3( -1,  1, -1 );
//	Indices[5]  = 3 ;		m_Vertex[6] .Position = glm::vec3( -1,  1, 1  );
//	Indices[6]  = 4 ;		m_Vertex[7] .Position = glm::vec3(  1,  1, 1  );
//	Indices[7]  = 5 ;		m_Vertex[8] .Position = glm::vec3(  1, -1, -1 );
//	Indices[8]  = 6 ;		m_Vertex[9] .Position = glm::vec3(  1,  1, -1 );
//	Indices[9]  = 4 ;		m_Vertex[10].Position  = glm::vec3(  1,  1, 1  );
//	Indices[10] = 6 ;		m_Vertex[11].Position  = glm::vec3(  1, -1, 1  );
//	Indices[11] = 7 ;		m_Vertex[12].Position  = glm::vec3(  1, -1, 1  );
//	Indices[12] = 8 ;		m_Vertex[13].Position  = glm::vec3(  1,  1, 1  );
//	Indices[13] = 9 ;		m_Vertex[14].Position  = glm::vec3( -1,  1, 1  );
//	Indices[14] = 10;		m_Vertex[15].Position  = glm::vec3( -1, -1, 1  );
//	Indices[15] = 8 ;		m_Vertex[16].Position  = glm::vec3( -1, -1, 1  );
//	Indices[16] = 10;		m_Vertex[17].Position  = glm::vec3( -1,  1, 1  );
//	Indices[17] = 11;		m_Vertex[18].Position  = glm::vec3( -1,  1, -1 );
//	Indices[18] = 12;		m_Vertex[19].Position  = glm::vec3( -1, -1, -1 );
//	Indices[19] = 13;		m_Vertex[20].Position  = glm::vec3(  1,  1, -1 );
//	Indices[20] = 14;		m_Vertex[21].Position  = glm::vec3(  1, -1, -1 );
//	Indices[21] = 12;		m_Vertex[22].Position  = glm::vec3( -1, -1, -1 );
//	Indices[22] = 14;		m_Vertex[23].Position  = glm::vec3( -1,  1, -1 );
//	Indices[23] = 15;		
//	Indices[24] = 16;	
//	Indices[25] = 17;	
//	Indices[26] = 18;	
//	Indices[27] = 16;	
//	Indices[28] = 18;
//	Indices[29] = 19;
//	Indices[30] = 20;
//	Indices[31] = 21;
//	Indices[32] = 22;
//	Indices[33] = 20;
//	Indices[34] = 22;
//	Indices[35] = 23;
//
//	m_Vertex[0] .TexCoord= glm::vec2( 0.25, 0.5 ); 
//	m_Vertex[1] .TexCoord= glm::vec2(0.25, 0.25 );
//	m_Vertex[2] .TexCoord= glm::vec2(0.5 , 0.25 );
//	m_Vertex[3] .TexCoord= glm::vec2(0.5 , 0.5  );
//	m_Vertex[4] .TexCoord= glm::vec2(1   , 0.5  );
//	m_Vertex[5] .TexCoord= glm::vec2(0.75, 0.5  );
//	m_Vertex[6] .TexCoord= glm::vec2(0.75, 0.25 );
//	m_Vertex[7] .TexCoord= glm::vec2(1   , 0.25 );
//	m_Vertex[8] .TexCoord= glm::vec2(0.25, 0.5  );
//	m_Vertex[9] .TexCoord= glm::vec2(1e-006, 0.5);
//	m_Vertex[10].TexCoord = glm::vec2(0   , 0.250);
//	m_Vertex[11].TexCoord = glm::vec2(0.25, 0.250);
//	m_Vertex[12].TexCoord = glm::vec2(0.25, 0.250);
//	m_Vertex[13].TexCoord = glm::vec2(0.25, 1e-006);
//	m_Vertex[14].TexCoord = glm::vec2(0.50, 0 );
//	m_Vertex[15].TexCoord = glm::vec2(0.5 , 0.25 );
//	m_Vertex[16].TexCoord = glm::vec2(0.5 , 0.25 );
//	m_Vertex[17].TexCoord = glm::vec2(0.75, 0.25 );
//	m_Vertex[18].TexCoord = glm::vec2(0.75, 0.5  );
//	m_Vertex[19].TexCoord = glm::vec2(0.5 , 0.5  );
//	m_Vertex[20].TexCoord = glm::vec2(0.25, 0.75 );
//	m_Vertex[21].TexCoord = glm::vec2(0.25, 0.5  );
//	m_Vertex[22].TexCoord = glm::vec2(0.5 , 0.5  );
//	m_Vertex[23].TexCoord = glm::vec2(0.50, 0.75 );
//
//	m_Vertex[0] .Normal = glm::vec3( 0, -1, 0  );
//	m_Vertex[1] .Normal = glm::vec3( 0, -1, 0  );
//	m_Vertex[2] .Normal = glm::vec3( 0, -1, 0  );
//	m_Vertex[3] .Normal = glm::vec3( 0, -1, 0  );
//	m_Vertex[4] .Normal = glm::vec3( 0, 1 ,0   );
//	m_Vertex[5] .Normal = glm::vec3( 0, 1 ,0   );
//	m_Vertex[6] .Normal = glm::vec3( 0, 1 ,0   );
//	m_Vertex[7] .Normal = glm::vec3( 0, 1 ,0   );
//	m_Vertex[8] .Normal = glm::vec3( 1, 0 ,0   );
//	m_Vertex[9] .Normal = glm::vec3( 1, 0 ,0   );
//	m_Vertex[10].Normal  = glm::vec3(1, 0 ,0   );
//	m_Vertex[11].Normal  = glm::vec3(1, 0 ,0   );
//	m_Vertex[12].Normal  = glm::vec3(0, -0, 1  );
//	m_Vertex[13].Normal  = glm::vec3(0, -0, 1  );
//	m_Vertex[14].Normal  = glm::vec3(0, -0, 1  );
//	m_Vertex[15].Normal  = glm::vec3(0, -0, 1  );
//	m_Vertex[16].Normal  = glm::vec3(1, -0, -0 );
//	m_Vertex[17].Normal  = glm::vec3(1, -0, -0 );
//	m_Vertex[18].Normal  = glm::vec3(1, -0, -0 );
//	m_Vertex[19].Normal  = glm::vec3(1, -0, -0 );
//	m_Vertex[20].Normal  = glm::vec3(0, 0 ,-1  );
//	m_Vertex[21].Normal  = glm::vec3(0, 0 ,-1  );
//	m_Vertex[22].Normal  = glm::vec3(0, 0 ,-1  );
//	m_Vertex[23].Normal  = glm::vec3(0, 0 ,-1  );  
//
//	VAOManager& Manager = VAOManager::GetSingleton();
//	VertexSettings set;
//	set.Declaration = Manager.GetVertexDeclaration( "Default" );
//	set.Indexed = true;
//	set.PrimitiveMode = PT_TRIANGLE;
//	set.UsageType = UT_STATIC_DRAW;
//	set.VertexCount = 36;
//	set.VertexSize = sizeof( float );
//	IndexSettings isett;
//	isett.IndexCount = 36;
//	isett.IndexTypeSize = sizeof( int );
//	isett.Type = UT_STATIC_DRAW;
//	VertexBuffer* pVertex = Manager.CreateVertexBuffer( set );
//	IndexBuffer* pIndex = Manager.CreateIndexBuffer( isett );
//	pIndex->SetIndexData( Indices );
//	pIndex->Prepare();
//	std::vector< float > Vec;
//	Vec.resize( 24 * sizeof( Vertex )/sizeof( float ) );
//
//	memcpy( &Vec[0], &m_Vertex[0], m_Vertex.size() * sizeof( Vertex ) );
//
//	pVertex->SetVertexData( Vec );
//	pVertex->Prepare();
//
//	VAO * Vao = Manager.CreateVertexArrayObject( pVertex, pIndex );
//	Vao->Prepare();
//	return Vao;
//}