/*  Created on: Feb 27, 2015
 *      Author: T.Delame (tdelame@gmail.com)
 */
# ifndef PROJECT_SHADER_H_
# define PROJECT_SHADER_H_

# include "glCheck.h"
# include <string>

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  void load(
    const std::string& vertexShaderSourceFile,
    const std::string& fragmentShaderSourceFile );

  inline
  operator GLint() const
  {
    return id;
  }
private:
  ShaderProgram( const ShaderProgram& other );
  ShaderProgram&
  operator=( const ShaderProgram& other );
public:
  GLint id;
};

# endif /* PROJECT_SHADER_H_ */
