uniform sampler3D Noise;
uniform float glitterStrength;
uniform vec4 lightDir;
uniform vec4 color;
varying vec3 vNormal;
varying vec3 vViewVec;
varying vec3 vObjPos;


void main(void)
{
   
   float noisy = texture3D(Noise, vObjPos * 0.04).x;
   vec3 ldir = vec3(lightDir.x, lightDir.y, -lightDir.z);   // flip the z for OpenGL.

   vec3 normal = normalize(vNormal);

   // Basic lighting
   float diffuse = dot(ldir, vNormal);
   float specBase = clamp(dot(reflect(-normalize(vViewVec), vNormal), ldir), 0.0, 1.0);

   // Extract some random points to glitter.
   // This is done by perturbing a grid pattern with some noise and
   // with the view-vector to let the glittering change with view.
   vec3 fp = fract(0.7 * vObjPos + 9.0 * noisy + 0.1 * vViewVec);
   fp *= (1.0 - fp);
   float glitter = clamp(1.0 - 7.0 * (fp.x + fp.y + fp.z), 0.0, 1.0);

   float specular = pow(specBase, 24.0);
   // Only glitter around the specular highlight. We use a lower
   // exponent for the glitter to let it spread more.
   float glittering = glitter * pow(specBase, 1.5);

   // Get a little more interesting base color
   vec4 base = (0.5 * noisy + 0.5) * color;

   gl_FragColor = base * diffuse + 0.5 * specular + glitterStrength * glittering;
   
}