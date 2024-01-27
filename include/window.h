#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Window{

public:
  Window();
  Window(int width, int height);
  
  int init();
 
  inline int get_width_buffer() const {return this->m_width_buffer;}
  inline int get_height_buffer() const {return this->m_height_buffer;}
  inline float get_ratio() const {return (float)((float)this->m_width_buffer/(float)this->m_height_buffer);}

  inline bool should_close() const { return glfwWindowShouldClose(this->m_window);}
  inline void swap_buffers() {glfwSwapBuffers(this->m_window);}

  ~Window();

private:
  GLFWwindow* m_window;
  int m_width,m_height;
  int m_width_buffer, m_height_buffer;

};
