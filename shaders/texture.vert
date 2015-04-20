# version 120

// texture coordinate attribute passed from OpenGL
attribute vec2 texcoord0;

attribute vec2 texcoord1;

// interpolated texture coordinate passed to fragment
varying vec2 frag_texcoord0;

varying vec2 frag_texcoord1;

void main(void)
{
  gl_Position = ftransform();
  frag_texcoord0 = texcoord0;

  frag_texcoord1 = texcoord1;
}
