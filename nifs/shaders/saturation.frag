uniform sampler2D texture;
uniform float alpha;
const vec3 coef= vec3(0.2125, 0.7154, 0.0721);
void main()
{
  vec4 color = texture2D(texture,gl_TexCoord[0].st);  
  vec4 intensity = vec4(dot(color.rgb,coef));  
  gl_FragColor  =  mix(intensity, color,alpha);
}
