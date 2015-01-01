#pragma once
#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <vector>
#include <map>
#include <cmath>
#include <deque>
#include <iostream>
#include <hash_map>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#	define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <IL/il.h>
#include <il/ilu.h>
#include <il/ilut.h>
#include <GLFW/glfw3.h>

// XML PARSER
#include <pugixml.hpp>

// DEFINICJA WSZYSTKICH KLASS
class Application;
class Fbo;
class VAO;
class VertexBufferManager;
class VertexBuffer;
class IndexBuffer;
class Material;
class MaterialManager;
class Surface;
class cProgramShader;
class cShaderManager;
class Renderer;
class RenderPass;
class cCamera;
class cShaderManager;
class Light;
class TextureManager;
class Node;


typedef unsigned int uint;
#endif