#include "include/logging.h"

void clear_error(){
  while (glGetError() != GL_NO_ERROR);
}

bool log_call(const char* function, const char* file, int line){
  while (GLenum error = glGetError()){
    printf("[OpenGL Error] %u %s %s %d\n",error,function, file,line);
    return false;
  }
  return true;
}

