#pragma once

#include <stdio.h>
#include <ctime>
#include <GL/glew.h>
#include <signal.h>

#define TIME []{ std::time_t cur_time = std::time(nullptr); return std::ctime(&cur_time); }()
#define ASSERT(x) if (!(x)) __asm__ volatile("int $0x03");

#define GLCALL(x) clear_error();\
  x;\
  ASSERT(log_call(#x, __FILE__,__LINE__))

#define LOG_DEBUG(msg) (printf("[DEBUG]: %s : %s",msg,TIME))
#define LOG_ERROR(msg) (printf("[ERROR]: %s : %s",msg,TIME))

void clear_error();
bool log_call(const char* function, const char* file, int line);
