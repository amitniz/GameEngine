#include "include/window.h"
#include "include/events.h"
#include "include/logging.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

using namespace Odyssey;

Window::Window() : Window(DEFAULT_WIDTH, DEFAULT_HEIGHT) {} // default Window
Window::Window(GLint width, GLint height)
    : m_width(width), m_height(height){}

int Window::init() {
    if (!glfwInit()) {
        LOG_ERROR("error initializing GLFW");
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

    this->m_window =
        glfwCreateWindow(this->m_width, this->m_height, "GameEngine", NULL, NULL);
    if (!this->m_window) {
        LOG_ERROR("error creating a window");
        glfwTerminate();
        return 1;
    }

    // get buffer size
    glfwGetFramebufferSize(this->m_window, &this->m_width_buffer,
                           &this->m_height_buffer);

    // set current context
    glfwMakeContextCurrent(this->m_window);

    // set callback functions
    set_callbacks();
    // disable cursor
    glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // allow modern extension access
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        LOG_ERROR("%s", glewGetErrorString(err));
        glfwDestroyWindow(this->m_window);
        glfwTerminate();
        return 1;
    }
    GLCALL(glEnable(GL_DEPTH_TEST));
    // create viewport
    GLCALL(glViewport(0, 0, this->m_width_buffer, m_height_buffer));

    // create a connection between this Window instance to the glfw window
    glfwSetWindowUserPointer(this->m_window, this);
    LOG_DEBUG("window initialized successfully");
    return 0;
}

Window::~Window() {
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
}
void Window::keyboard_events_handler(GLFWwindow *window, int key, int code,
                                     int action, int mode) {
    // get instance
    TODO("get rid of the window pointer");
    // Window *win = (Window *)(glfwGetWindowUserPointer(window));

    // set keys behavior
    if ((key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key <= MAX_KEYS) {
        bool* m_keys = Events::getInstance()->m_keys;
        m_keys[key] = action == GLFW_RELEASE ? false : true;
    }
}

void Window::mouse_events_handler(GLFWwindow *window, double x_pos,
                                  double y_pos) {
    // get instance
    Events *events = Events::getInstance();
    // update mouse tracking
    if (!events->mouse_init) {
        events->mouse_init = true;
        return;
    }

    events->last_coords[0] = events->current_coords[0];
    events->last_coords[1] = events->current_coords[1];
    events->current_coords[0] = (int)x_pos;
    events->current_coords[1] = (int)y_pos;

    if (events->last_coords[0] || events->last_coords[1]) { // prevent the first change
        events->mouse_changes[0] = events->current_coords[0] - events->last_coords[0];
        events->mouse_changes[1] = events->current_coords[1] - events->last_coords[1];
    }
}

void Window::set_callbacks() {
    // set keyboard callback function
    glfwSetKeyCallback(this->m_window, Window::keyboard_events_handler);
    glfwSetCursorPosCallback(this->m_window, Window::mouse_events_handler);
}
