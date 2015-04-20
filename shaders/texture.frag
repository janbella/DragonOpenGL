# version 120

// texture unit used
uniform sampler2D texture0;

uniform sampler2D texture1;

// interpolated texture coordinate passed to fragment
varying vec2 frag_texcoord0;

varying vec2 frag_texcoord1;

void main()
{
  vec4 texel0 = texture2D( texture0, frag_texcoord0 );
  gl_FragColor = texel0;

  vec4 texel1 = texture2D( texture1, frag_texcoord1);
  gl_FragColor += texel1;
}
