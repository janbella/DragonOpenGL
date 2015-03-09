# version 120

struct material_info {
    vec4 ka;
    vec4 kd;
    vec4 ks;
    vec4 emission;
    float shininess;
};

struct light_info {
    vec4 position;
    vec4 la      ;
    vec4 ld      ;
    vec4 ls      ;
};

uniform material_info material;
uniform light_info light_1;
uniform light_info light_2;

varying vec4 color;

vec4 phongWithMaterial( vec4 position, vec3 norm , light_info light)
{
    vec3 L = normalize( light.position.xyz - position.xyz );
    vec3 E = normalize( -position.xyz );
    vec3 R = normalize( -reflect( L, norm ) );

    vec4 i_emission = material.emission; 
    vec4 i_ambient  = light.la * material.ka;
    vec4 i_diffuse  = light.ld * material.kd * max( dot( norm, L ), 0.0 );
    vec4 i_specular = light.ls * material.ks * pow( max( dot(R, E ), 0.0 ), material.shininess );

    return i_emission + i_ambient + clamp( i_diffuse, 0, 1 ) + clamp( i_specular, 0, 1 );
}

void main( void )
{
    vec4 position = gl_ModelViewMatrix * gl_Vertex; // camera coordinate system
    vec3 normal   = mat3(gl_ModelViewMatrixInverseTranspose) * gl_Normal;
    //color = phongWithMaterial( position, normal );    // computing light in the camera coordinate frame -> light cosidered local
    color = phongWithMaterial( gl_Vertex, gl_Normal, light_1 );  // computing light in the world coordinate frame -> considered global

    //color += phongWithMaterial( position, normal, light_2 );

    //color /= 2.0f;

    gl_Position = gl_ProjectionMatrix * position;
}
