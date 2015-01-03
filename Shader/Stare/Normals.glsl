#version 410

layout (triangles) in;
layout (line_strip) out;

layout( max_vertices = 8) out;

in Vertex
{
	vec3 normal;
} vertex[];

uniform mat4 modelViewProjectionMatrix;
