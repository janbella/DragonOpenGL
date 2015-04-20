/* Created on: Jan 30, 2015
 *     Author: T.Delame (tdelame@gmail.com)
 */
# ifndef PROJECT_LIGHT_H_
# define PROJECT_LIGHT_H_

# include "vector4.h"

/**
 * @brief The Light struct is a class encapsulating light properties
 */
struct Light
{
    Vector4 position;    // light position
    Vector4 ambient;          // ambience vector
    Vector4 diffuse;          // diffusion
    Vector4 specular;          // specular

    /**
     * @brief Light constructor.
     * @param position position of the light
     * @param ambient ambient part of the light
     * @param diffuse diffuse part of the light
     * @param specular specular part of the light
     */
    Light( const Vector4& position, const Vector4& ambient, const Vector4& diffuse, const Vector4& specular ) :
        position(position),
        ambient(ambient),
        diffuse(diffuse),
        specular(specular)
    {  }

    /**
     * @brief Light non parametric constructor. Sets default values for attributes.
     */
    Light() : position(0.0, 0.0, 0.0, 1.0 ),
        ambient( 0,   0,   0,   1 ),
        diffuse( 1,   1,   1,   1 ),
        specular(1,   1,   1,   1 )
    {  }

};

# endif
