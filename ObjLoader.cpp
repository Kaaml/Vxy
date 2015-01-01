#include "ObjLoader.h"

ObjLoader::ObjLoader(void)
	: mTriangulated( true )
{
}

void ObjLoader::LoadAssimp( const std::string &FileName )
{
	Assimp::Importer Importer;
	const aiScene *scene = Importer.ReadFile( FileName, 
		aiProcessPreset_TargetRealtime_Quality );
	if( !scene )
	{
		std::cout << "ASSIMP cos poszlo nie tak\n";
	}

	//w petli przez wszystkie meshe
	const aiMesh * mesh = scene->mMeshes[0];
	for( uint t = 0; t < mesh->mNumFaces ; t++ )
	{
		const aiFace *face = &mesh->mFaces[ t ] ;
		mGpuIndices.push_back( face->mIndices[ 0 ] );
		mGpuIndices.push_back( face->mIndices[ 1 ] );
		mGpuIndices.push_back( face->mIndices[ 2 ] );
	}
	
	// verteksy
	if( mesh->HasPositions() )
	{
		mVertex.resize( mesh->mNumVertices );
		memcpy( &mVertex[0], mesh->mVertices, 3*4* mesh->mNumVertices );
	}
	if( mesh->HasNormals() )
	{
		mNormals.resize( mesh->mNumVertices  );
		memcpy(  &mNormals[0], mesh->mNormals, 3*4* mesh->mNumVertices );
	}
	if( mesh->HasTextureCoords(0) )
	{
		for( uint k = 0; k < mesh->mNumVertices; ++k )
		{
			glm::vec2 tmp;
			tmp.x =	mesh->mTextureCoords[0][k].x;
			tmp.y = mesh->mTextureCoords[0][k].y;
			mTexcoords.push_back( tmp );
		}		
	}
	mGpuBuffer.resize( mesh->mNumVertices*8);

	for( uint i = 0; i < mesh->mNumVertices; ++i )
	{
		mGpuBuffer[ i*8 ] = mVertex[ i ].x;
		mGpuBuffer[ i*8 +1 ] = mVertex[ i ].y;
		mGpuBuffer[ i*8 +2] = mVertex[ i ].z;
		mGpuBuffer[ i*8 +3] = mNormals[ i ].x;
		mGpuBuffer[ i*8 +4] = mNormals[ i ].y;
		mGpuBuffer[ i*8 +5] = mNormals[ i ].z;
		mGpuBuffer[ i*8 +6] = mTexcoords[ i ].s;
		mGpuBuffer[ i*8 +7] = mTexcoords[ i ].t;
	}
	Surface *pSurface = new Surface();
	VertexBufferManager &VBOMan = VertexBufferManager::GetSingleton();
	IndexBuffer *pIndex = VBOMan.CreateIndexBuffer();
	pIndex->SetIndexData( mGpuIndices );
	pIndex->Prepare();
	VertexDeclaration *pDecl = VBOMan.GetVertexDeclaration( "Default" );
	VertexSettings( PT_TRIANGLE, UT_STATIC_DRAW, pIndex, pDecl );	
	VertexBuffer *pVertex = VBOMan.CreateVertexBuffer(
		VertexSettings( PT_TRIANGLE, UT_STATIC_DRAW, pIndex, pDecl ) );	
	pVertex->SetVertexData( mGpuBuffer );
	pVertex->Prepare();
	pSurface->SetVertexBuffer( pVertex );
	mSurfaces.push_back( pSurface );


}
void ObjLoader::Load( const std::string &FileName )
{
	std::fstream File( FileName.c_str(), std::ios::in | std::ios::binary );
	if( !File.is_open() )
	{
		std::cerr <<"EROR: Nie mozna otworzyc pliku: " << FileName << std::endl;
		return;
	}
	std::string line;
	std::stringstream ssbuffer;
	glm::vec3 tmp;
	glm::vec2 vec2tmp;
	while( !File.eof() )
	{
		line.clear();
		ssbuffer.clear();
		std::getline( File, line );
		if( !line.compare( 0, 2, "v " ) )
		{
			// ########## VERTEX ##########			
			ssbuffer << line.substr(2, line.length()-2 );
			ssbuffer >> tmp.x >> tmp.y >> tmp.z ;
			mVertex.push_back( tmp );
		}
		else if( !line.compare( 0, 2, "vt") )
		{
			// ########## TEXT COORDS ##########			
			ssbuffer << line.substr(2, line.length()-2 );
			ssbuffer >> vec2tmp.x >> vec2tmp.y ;
			mTexcoords.push_back( vec2tmp );
		}
		else if( !line.compare( 0, 2, "vn") )
		{
			// ########## NORMALS ##########			
			ssbuffer << line.substr(2, line.length()-2 );
			ssbuffer >> tmp.x >> tmp.y >> tmp.z ;
			mNormals.push_back( tmp );	
		}
		else if( line[0] == 'f' )
		{
			// ########## FACE ##########
			//GetFace( line );
			GetFace_t( line );
		}
		else if( line[0] == 's' )
		{
			// ########## group number ##########
		}
		else if( line[0] ==  'g' )
		{
			// ########## group name ##########
		}
		else if( line[0] == 'o' )
		{
			// ########## object name ##########
		}
		else if( line[0] == 'u' )
		{
			// ########## material desc ##########
		}
		else if( line[0] ==  'm' )
		{
			// ########## material library ##########
		}

	}
	this->Prepare();
}

void ObjLoader::GetFace( const std::string &line )
{
	std::string buffer (line.substr(2));
	const bool vn = !mNormals.empty();
	const bool vt = !mTexcoords.empty();
	
	glm::ivec3 tmp[4];
	//short iStep = 0, iPos = 0, face = 0;
	//auto it = buffer.begin();
	/*while( it != buffer.end() )
	{
		iStep = 1;
		if( it == line.end() )
			break;
		if( *it == '/' )
		{
			if( iPos == 0 )
			{
				if( !vt && vn )
				{
					iPos = 1;
					iStep++;
				}
			}
			iPos++;
		}
		else if( *it == ' ' )
		{
			iPos = 0;
			++face;
		}
		else
		{
			const unsigned short Value = atoi( &(*it) );
			int tmp = Value;
			while( ( tmp = tmp/ 10 )!= 0 )
			++iStep;
			if( Value > 0 )
			{
					
				switch( iPos )
				{
				case 0:
					{
						mVertexIndices.push_back( Value -1 );
						
					}
					break;
				case 1:
					{

						mTexIndices.push_back( Value -1 );
					}
					break;
				case 2:
					{
						mNormalIndices.push_back( Value -1 );
					}
					break;
				default:
					std::cerr << "ERROR: cos poszlo nie tak z wczytywaniem pliku\n";
				}

		}

		}
		it+=iStep;		
	}*/
	if( std::count( buffer.begin(), buffer.end(), ' ' ) == 2 )
	{
		char space;
		// trujkat nic nie robic tylko wczytac
		if( vn & vt)
		{
			// NORMALNE I TEKSTURY
			std::stringstream ssbuf( buffer );
			ssbuf >> tmp[0].x >> space >> tmp[0].y >> space >> tmp[0].z  /*space*/
				>> tmp[1].x >> space >> tmp[1].y >> space >> tmp[1].z  /*space*/
				>>  tmp[2].x >> space >> tmp[2].y >> space >> tmp[2].z;
				mFaces.push_back( tmp[0] );
				mFaces.push_back( tmp[1] );
				mFaces.push_back( tmp[2] );
			
		}else if( vn && !vt )
		{
			// SAME NORMALNE
			std::stringstream ssbuf( buffer );			
			ssbuf >> tmp[0].x >> space >> space >> tmp[0].z /*>> space*/
				>> tmp[1].x >> space >> space >> tmp[1].z  /*>>space*/
				>> tmp[2].x >> space >> space >> tmp[2].z;
			tmp[0].y = tmp[1].y = tmp[2].y = 1;
			mFaces.push_back( tmp[0] );
			mFaces.push_back( tmp[1] );
			mFaces.push_back( tmp[2] );
			
		}else if( !vn && !vt)
		{
			// BRAK NORMALNYCH I TEKSTUR
			std::stringstream ssbuf( buffer );			
			ssbuf >> tmp[0].x /*>> space*/
				>> tmp[1].x /*>> space*/
				>> tmp[2].x /*>> space*/;
			tmp[0].y = tmp[1].y = tmp[2].y = 1;
			tmp[0].z = tmp[1].z = tmp[2].z = 1;
			mFaces.push_back( tmp[0] );
			mFaces.push_back( tmp[1] );
			mFaces.push_back( tmp[2] );
			
		}else
		{
			// SAME TEXCOORDY
			std::stringstream ssbuf( buffer );
			ssbuf >> tmp[0].x >> space >> tmp[0].y >> space
				>> tmp[1].x >> space >> tmp[1].y >> space
				>> tmp[2].x >> space >> tmp[2].y;
			tmp[0].z = tmp[1].z = tmp[2].z = 1;
			mFaces.push_back( tmp[0] );
			mFaces.push_back( tmp[1] );
			mFaces.push_back( tmp[2] );
		}
	}else
	{
		//DLA CZWOROKATOW
		std::vector< glm::ivec3 > Indices;
		char space;
		// trujkat nic nie robic tylko wczytac
		if( vn & vt)
		{
			// NORMALNE I TEKSTURY
			std::stringstream ssbuf( buffer );
			ssbuf >> tmp[0].x >> space >> tmp[0].y >> space >> tmp[0].z >> space
				>> tmp[1].x >> space >> tmp[1].y >> space >> tmp[1].z >> space
				>>  tmp[2].x >> space >> tmp[2].y >> space >> tmp[2].z>> space
				>> tmp[3].x >> space >> tmp[3].y >> space >> tmp[3].z ;
			Indices.push_back( tmp[0] );
			Indices.push_back( tmp[1] );
			Indices.push_back( tmp[2] );
			Indices.push_back( tmp[3] );
		}else if( vn && !vt )
		{
			// SAME NORMALNE
			std::stringstream ssbuf( buffer );			
			ssbuf >> tmp[0].x >> space >> space >> tmp[0].z /*>> space*/
				>> tmp[1].x >> space >> space >> tmp[1].z  /*>>space*/
				>> tmp[2].x >> space >> space >> tmp[2].z
				>> tmp[3].x >> space >> space >> tmp[3].z;
			tmp[0].y = tmp[1].y = tmp[2].y = tmp[3].y = 1;
			Indices.push_back( tmp[0] );
			Indices.push_back( tmp[1] );
			Indices.push_back( tmp[2] );
			Indices.push_back( tmp[3] );

		}else if( !vn && !vt)
		{
			// BRAK NORMALNYCH I TEKSTUR
			std::stringstream ssbuf( buffer );			
			ssbuf >> tmp[0].x /*>> space*/
				>> tmp[1].x /*>> space*/
				>> tmp[2].x /*>> space*/
				>> tmp[3].x /*> space*/;
			tmp[0].y = tmp[1].y = tmp[2].y = tmp[3].y = 1;
			tmp[0].z = tmp[1].z = tmp[2].z = tmp[3].z = 1;
			Indices.push_back( tmp[0] );
			Indices.push_back( tmp[1] );
			Indices.push_back( tmp[2] );
			Indices.push_back( tmp[3] );
		}else
		{
			// SAME TEXCOORDY
			std::stringstream ssbuf( buffer );			
				ssbuf >> tmp[0].x >> space >> tmp[0].y >> space
					>> tmp[1].x >> space >> tmp[1].y >> space
					>> tmp[2].x >> space >> tmp[2].y >> space 
					>> tmp[3].x >> space >> tmp[3].y;
				tmp[0].z = tmp[1].z = tmp[2].z = tmp[3].z = 1;
				Indices.push_back( tmp[0] );
				Indices.push_back( tmp[1] );
				Indices.push_back( tmp[2] );
				Indices.push_back( tmp[3] );			
		}
		// indices od 1 do 4				   0________1
		mFaces.push_back( Indices[0] );		//	|\     /|
		mFaces.push_back( Indices[1] );		//	| \   / |
		mFaces.push_back( Indices[2] );		//	|  \ /  |
		mFaces.push_back( Indices[0] );		//	|   X   |
		mFaces.push_back( Indices[2] );		//	|  / \  |
		mFaces.push_back( Indices[3] );		// 3|_/___\_|2

	}
}

void ObjLoader::Prepare()
{
	mGpuBuffer.reserve( mVertexMap.size() * 8 );
	mGpuBuffer.resize( mVertexMap.size() * 8  );
	for( auto &it : mVertexMap )
	{
		mGpuBuffer[ it.second*8 ] = mVertex[ it.first.x ].x;
		mGpuBuffer.at( it.second*8+1 ) = mVertex[ it.first.x ].y;
		mGpuBuffer.at( it.second*8+2 ) = mVertex[ it.first.x ].z;
		//NORMALNE
		if( (it.first.y != -1) && ( mNormals.size() > 0 ) )
		{
			mGpuBuffer.at( it.second*8+3 ) = mNormals[ it.first.z ].x;
			mGpuBuffer.at( it.second*8+4 ) = mNormals[ it.first.z ].y;
			mGpuBuffer.at( it.second*8+5 ) = mNormals[ it.first.z ].z;
		}else
		{
			mGpuBuffer.at( it.second*8+3 ) = 0.f;
			mGpuBuffer.at( it.second*8+4 ) = 0.f;
			mGpuBuffer.at( it.second*8+5 ) = 0.f;
		}
		//texcoord
		if( it.first.z != -1 && ( mTexcoords.size() > 0 ) )
		{
			mGpuBuffer.at( it.second*8+6 ) = mTexcoords[ it.first.y ].s;
			mGpuBuffer.at( it.second*8+7 ) = mTexcoords[ it.first.y ].t;
			/*float tmpa =  mTexcoords[ it.first.y ].s;
			float tmpb =  mTexcoords[ it.first.y ].t;;*/
		}
		else
		{
			mGpuBuffer.at( it.second*8+6 ) = -1.f;
			mGpuBuffer.at( it.second*8+7 ) = -1.f;
		}
	}
	Surface *pSurface = new Surface();
	VertexBufferManager &VBOMan = VertexBufferManager::GetSingleton();
	IndexBuffer *pIndex = VBOMan.CreateIndexBuffer();
	pIndex->SetIndexData( mGpuIndices );
	pIndex->Prepare();
	VertexDeclaration *pDecl = VBOMan.GetVertexDeclaration( "Default" );
	VertexSettings( PT_TRIANGLE, UT_STATIC_DRAW, pIndex, pDecl );	
	VertexBuffer *pVertex = VBOMan.CreateVertexBuffer(
		VertexSettings( PT_TRIANGLE, UT_STATIC_DRAW, pIndex, pDecl ) );	
	pVertex->SetVertexData( mGpuBuffer );
	pVertex->Prepare();
	pSurface->SetVertexBuffer( pVertex );
	mSurfaces.push_back( pSurface );
	

}

ObjLoader::~ObjLoader(void)
{
}

void ObjLoader::GetFace_t( std::string &line )
{
	line = line.substr(2);
	std::vector<int> FaceCorners; // rogi œcian
	size_t it = line.find_first_of( ' ' );
	glm::ivec3 tmp( -1 );
	//fVertex tmp;
	while( std::string::npos != it )
	{
		std::string word = line.substr( 0, it );
		// wyciagnij dane z word
		//std::cout << word << std::endl;
		GetDataFromFaceWord( &word[0],(int*) &tmp, &word[ word.length() ]+1 );
		auto s = mVertexMap.find( tmp );
		
		if( s != mVertexMap.end() )
		{
			FaceCorners.push_back(s->second );
			// je¿eli taki wierzcho³ek ju¿ jest wrzuæ indeks do tmp buffora
		}else
		{
			/*currMtl->Meshbuffer->Vertices.push_back(v);
			vertLocation = currMtl->Meshbuffer->Vertices.size() -1;
			currMtl->VertMap.insert(v, vertLocation*/
			// wrzuc unikalny wierzcholek do mapy
			int Size = mVertexMap.size();
			mVertexMap.insert( std::pair<glm::ivec3, int >( tmp,Size ) );
			// wrzuc jego wartosc do tmp bufora 
			FaceCorners.push_back( Size );
		}

		line = line.substr( it+1, line.length() );
		it = line.find_first_of(' ');
	};		// END of WHILE
	GetDataFromFaceWord( &line[0], (int*)&tmp, &line[ line.length() ]+1 );
		auto s = mVertexMap.find( tmp );
		if( s != mVertexMap.end() )
		{
			FaceCorners.push_back(s->second );
			// je¿eli taki wierzcho³ek ju¿ jest wrzuæ indeks do tmp buffora
		}else
		{
			/*currMtl->Meshbuffer->Vertices.push_back(v);
			vertLocation = currMtl->Meshbuffer->Vertices.size() -1;
			currMtl->VertMap.insert(v, vertLocation*/
			// wrzuc unikalny wierzcholek do mapy
			int Size = mVertexMap.size();
			mVertexMap.insert( std::pair<glm::ivec3, int >( tmp,Size ) );
			// wrzuc jego wartosc do tmp bufora 
			FaceCorners.push_back( Size );
		};
	// poprawic warunek petli jakby cos bo jest zly dlatego to ^ tu jest
	//triangulacja polygonów
	for( unsigned int i = 1; i < FaceCorners.size() - 1; ++i )
	{
		mGpuIndices.push_back( FaceCorners[0] );
		mGpuIndices.push_back( FaceCorners[1] );
		mGpuIndices.push_back( FaceCorners[2] );

	}
	
	
}

char* ObjLoader::GetNextWorld( char* startPtr, char* endPtr )
{
	char* before = startPtr;
	while( (before != endPtr ) &&  (*before != ' ') )
	{
		++before;
	}
	return before;
}

short ObjLoader::WordsSize( char* startPtr, char* endPtr )
{
	char* c = startPtr;
	while( *c != ' ' )
	{
		if( c == endPtr )
			return 0;
		++c;
	}
	return c-startPtr;

}
//vertex data -> pointer na s³owo, index -> bufer indeksow, buffEnd -> ptr na koniec s³owa
bool ObjLoader::GetDataFromFaceWord( char* vertexData, int* index, const char* buffEnd )
{
	// pobieranie indeksów dla jednego wierzcho³ka
	char word[16] = "";
	const char* p = vertexData;
	short indexType = 0; 
	int i = 0;

	while( p != buffEnd)
	{
		if( ((*p >= '0') && (*p <= '9') ) || (*p =='-') )
		{
			//dla cyfr
			word[ i++ ]= *p;
		}
		else if( *p == '/' || *p ==' ' || *p == '\0' )
		{
			// koniec numeru w buforze word
			word[i] = '\0';
			index[ indexType ] = atoi( word );
			if( index[ indexType] < 0 )
			{
				switch( indexType )
				{
				case 0:
					index[ indexType ] = mVertex.size();
					break;
				case 1:
					index[ indexType ] = mTexcoords.size();
					break;
				case 2:
					index[ indexType ] = mNormals.size();
					break;
				}
			}
			else
			{
				// dla dobrych indeksów numeruj od zera
				index[ indexType ] -=1;
			}
			// przygotuj do nastepnej liczby
			word[0] = '\0';
			i = 0;
			if( *p =='/' )
			{
				if( ++indexType > 2 )
				{
					// cos zle z plikiem 
					indexType = 0;
				}
			}
			else
			{
				while( ++indexType < 3 )
					index[ indexType ] = -1;
				++p;
				break;		//wyjscie z petli
			}
		}

		// go to next char
		++p;

	}
	return true;
}

std::vector< Surface* >& ObjLoader::GetSurfaces()
{
	return mSurfaces;
}
