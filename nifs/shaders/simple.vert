
//
// simple.vert: Extremely simple OGL2 vertex shader
//
// author: Steve Koren
//
// Copyright (c) 2002: 3Dlabs, Inc.
//

uniform vec3 triangleColor;
varying vec3 tc;

void main(void)
{
	tc = triangleColor;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
