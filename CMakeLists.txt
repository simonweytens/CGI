cmake_minimum_required (VERSION 2.6)
project (CGI-Server)
add_executable(CGI-Server main.c)
target_link_libraries(CGI-Server json-c)
