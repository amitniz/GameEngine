#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define MAX_KEYS 1024

class Window {

public:
  Window();
  ~Window();
  Window(int width, int height);

  int init();

  inline void poll_events() const { glfwPollEvents(); }
  inline int get_width_buffer() const { return this->m_width_buffer; }
  inline int get_height_buffer() const { return this->m_height_buffer; }
  inline float get_ratio() const {
    return (float)((float)this->m_width_buffer / (float)this->m_height_buffer);
  }

  inline bool should_close() const {
    return glfwWindowShouldClose(this->m_window);
  }
  inline void swap_buffers() const { glfwSwapBuffers(this->m_window); }
  inline const bool *get_keys_state() const { return this->m_keys; }
  inline const int *get_mouse_changes() const { return this->mouse_changes; }

private:
  void set_callbacks();
  static void keyboard_events_handler(GLFWwindow *window, int key, int code,
                                      int action, int mode);
  static void mouse_events_handler(GLFWwindow *window, double x_pos,
                                   double y_pos);

  GLFWwindow *m_window;
  int m_width, m_height;
  int m_width_buffer, m_height_buffer;
  // keyboard
  bool m_keys[MAX_KEYS];
  // mouse
  int current_coords[2];
  int mouse_changes[2];
  int last_coords[2];
  bool mouse_init; // prevents inital read before user moved the mouse
};
