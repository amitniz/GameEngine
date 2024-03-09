#pragma once

#include <stdio.h>
#include <chrono>
#include <GL/glew.h>
#include <signal.h>

namespace Odyssey{
#define TIME []() -> const char* {\
    auto now = std::chrono::system_clock::now();\
    std::time_t time = std::chrono::system_clock::to_time_t(now);\
    std::tm tm = *std::localtime(&time);\
    static char buffer[9];\
    std::strftime(buffer, sizeof(buffer), "%T", &tm);\
    return buffer;\
}()

#define ASSERT(x) if (!(x)) __asm__ volatile("int $0x03");

#define GLCALL(x) clear_error();\
  x;\
  ASSERT(log_call(#x, __FILE__,__LINE__))


#define LOG(level,...)  printf("[%s]::[%s]: ",TIME,level);\
                        printf(__VA_ARGS__);\
                        printf("\n")


#define LOG_DEBUG(...)  LOG("DEBUG",__VA_ARGS__)
#define LOG_INFO(...) LOG("INFO",__VA_ARGS__)
#define LOG_WARNING(...) LOG("WARNING",__VA_ARGS__)
#define LOG_ERROR(...) LOG("ERROR",__VA_ARGS__)
#define LOG_CRITICAL(...) LOG("CRITICAL",__VA_ARGS__)
#define UNFINISHED LOG("UNFINISHED", "called unfinished function: %s", __func__)
#define TODO(...) printf("[TODO]::[%s]: ",TIME);\
                  printf(__VA_ARGS__);\
                  printf(": %s\n",__func__);
void clear_error();
bool log_call(const char* function, const char* file, int line);
};
