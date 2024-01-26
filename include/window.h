#pragma once 

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{

public:
  Window();
  Window(GLint width, GLint height);
  
  int init();
 
  GLint get_width_buffer() {return this->m_width_buffer;}
  GLint get_height_buffer() {return this->m_height_buffer;}

  inline bool should_close() { return glfwWindowShouldClose(this->m_window);}
  inline void swap_buffers() {glfwSwapBuffers(this->m_window);}

  ~Window();

private:
  GLFWwindow* m_window;
  GLint m_width,m_height;
  GLint m_width_buffer, m_height_buffer;

};
