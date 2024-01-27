#include "include/window.h"
#include "include/logging.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

Window::Window() : m_width(DEFAULT_WIDTH), m_height(DEFAULT_HEIGHT) {}
Window::Window(GLint width, GLint height) : m_width(width), m_height(height) {}

int Window::init() {
  if (!glfwInit()) {
    printf("error initializing GLFW");
    glfwTerminate();
    return 1;
  }

  // setup glfw windows properties
  // openGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // core profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  this->m_window = glfwCreateWindow(this->m_width, this->m_height, "GameEngine", NULL, NULL);
  if(!this->m_window){
    printf("error creating a window");
    glfwTerminate();
    return 1;
  }

  //get buffer size
  glfwGetFramebufferSize(this->m_window, &this->m_width_buffer, &this->m_height_buffer);

  //set current context
  glfwMakeContextCurrent(this->m_window);

  //allow modern extension access
  glewExperimental = GL_TRUE;

  GLenum err = glewInit();
  if(err != GLEW_OK){
    printf("error: %s",glewGetErrorString(err));
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
    return 1;
  }
  GLCALL(glEnable(GL_DEPTH_TEST));
  //create viewport
  GLCALL(glViewport(0,0,this->m_width_buffer,m_height_buffer));

  return 0;
}

Window::~Window(){
  glfwDestroyWindow(this->m_window);
  glfwTerminate();
}
