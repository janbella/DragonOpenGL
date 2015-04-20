/*  Created on: Feb 27, 2015
 *      Author: T.Delame (tdelame@gmail.com)
 */
# ifndef PROJECT_SHADER_H_
# define PROJECT_SHADER_H_

# include "glCheck.h"
# include <string>

class ShaderProgram
{
public:
    GLint id;   // identifyer of the program

public:
    /**
     * @brief ShaderProgram constructor
     */
    ShaderProgram();
    /**
     *
     */
    virtual ~ShaderProgram();

    /**
     * @brief load loads shader program to the memory
     * @param vertexShaderSourceFile    vertex shader file path
     * @param fragmentShaderSourceFile  fragment shader file path
     */
    void load( const std::string& vertexShaderSourceFile,
               const std::string& fragmentShaderSourceFile );

    /**
     * @brief operator GLint
     */
    inline operator GLint() const
    {
        return id;
    }

private:
    /**
     * @brief ShaderProgram standard copy constructor
     * @param other
     */
    ShaderProgram( const ShaderProgram& other );

    /**
     * @brief operator = standard assignment operator
     * @param other
     * @return other
     */
    ShaderProgram& operator= (const ShaderProgram& other );
};

# endif /* PROJECT_SHADER_H_ */
