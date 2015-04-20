# version 120

/**
 * Holds material properties
 */
struct material_info
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emission;
    float shininess;
};

/**
 * Holds light properties
 */
struct light_info
{
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

// a material assigned to the object
uniform material_info material;

// light applied to the object
uniform light_info light_1;

uniform bool enabled_light2;
// second light applied to the object
uniform light_info light_2;


varying vec4 color;

vec4 phongWithMaterial( vec4 position, vec3 N , light_info light)
{
    vec3 L = normalize( light.position.xyz - position.xyz ); // light vector
    vec3 E = normalize( -position.xyz );                     // eye vector
    vec3 R = normalize( -reflect( L, N ) );                  // reflected light vector

    vec4 i_emission = material.emission;
    vec4 i_ambient  = light.ambient  * material.ambient;
    vec4 i_diffuse  = light.diffuse  * material.diffuse  *      max( dot(N, L ), 0.0 );
    vec4 i_specular = light.specular * material.specular * pow( max( dot(R, E ), 0.0 ), material.shininess );

    return i_emission + i_ambient + clamp( i_diffuse, 0, 1 ) + clamp( i_specular, 0, 1 );

}

// i_received = i_source / (c0 + c1 * d + c2 * d)
light_info attenuate(light_info light, float distance, float c0, float c1, float c2)
{
    light.ambient  /= (c0 + c1*distance + c2 * pow(distance,2.0f));
    light.diffuse  /= (c0 + c1*distance + c2 * pow(distance,2.0f));
    light.specular /= (c0 + c1*distance + c2 * pow(distance,2.0f));
    return light;
}

float vec4_size(vec4 vector)
{
    vector.xyz/=vector.w;
    return sqrt(pow(vector.x,2) + pow(vector.y,2) + pow(vector.z,2));
}

void main( void )
{
    vec4 position = gl_ModelViewMatrix * gl_Vertex; // position in camera coordinate system
    vec3 normal   = mat3(gl_ModelViewMatrixInverseTranspose) * gl_Normal;

    //color = phongWithMaterial( position, normal, light_1 );    // computing light in the camera coordinate frame -> light cosidered local



    color = phongWithMaterial( gl_Vertex, gl_Normal, light_1 );  // computing light in the world coordinate frame -> considered global

    if(enabled_light2)
    {
        color = (color + phongWithMaterial( position, normal, attenuate(light_2, vec4_size(gl_ProjectionMatrixInverse * light_2.position), 0.75f,0.25f,0.11f ) ));
        color /= 2.0f;
    }

    gl_Position = gl_ProjectionMatrix * position;
}
