/* Created on: Jan 30, 2015
 *     Author: T.Delame (tdelame@gmail.com)
 */
# ifndef PROJECT_MATERIAL_H_
# define PROJECT_MATERIAL_H_

# include "vector4.h"

/**
 * @brief The Material struct is a class encapsulating material properties
 */
struct Material
{
    Vector4 ambient;   // ambient property of the material
    Vector4 diffuse;   // diffuse property of the material
    Vector4 specular;  // specular property of the material
    float shininess;// shininess property of the material

    /**
     * @brief Material constructor. Sets attributes to the default material
     */
    Material() : ambient( 0.19225 , 0.19225 , 0.19225  , 1),
                 diffuse( 0.50754 , 0.50754 , 0.50754  , 1),
                 specular(0.508273, 0.508273, 0.508273 , 1),
                 shininess(51.2f)
    { }

    /**
     * @brief Material constructor
     * @param ambient   ambient property of the material
     * @param diffuse   diffuse property of the material
     * @param specular  specular property of the material
     * @param shininess shininess property of the material
     */
    Material( const Vector4& ambient, const Vector4& diffuse, const Vector4& specular, float shininess ) :
        ambient( ambient ), diffuse( diffuse ), specular( specular ), shininess( shininess )
    { }
};

# endif
