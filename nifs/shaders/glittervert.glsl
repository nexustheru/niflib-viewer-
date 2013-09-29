
varying vec3 vNormal;
varying vec3 vViewVec;
varying vec3 vObjPos;

void main(void)
{


   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
 
   

   // Eye-space lighting
   vNormal = gl_NormalMatrix * gl_Normal;

   // dont flip the sign here like we do in d3d b/c its differnt handedness.   
   vViewVec = gl_NormalMatrix *  vec3(gl_Vertex);
   
   // Pass position to the fragment shader
   vObjPos = gl_Vertex.xyz;

   
}