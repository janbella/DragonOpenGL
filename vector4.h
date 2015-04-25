# ifndef VECTOR4_H_
# define VECTOR4_H_

struct Vector4
{
  union { float x, s, r; };
  union { float y, t, g; };
  union { float z, p, b; };
  union { float w, q, a; };

  const float* data() const;

  Vector4();

  Vector4( float x, float y, float z, float w );
};

# endif // VECTOR4_H_
