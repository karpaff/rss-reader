cmake_minimum_required(VERSION 3.23)
project(RSS_Reader)


set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/opt/curl/include/)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)


add_executable(RSS_Reader main.cpp NewsItem.cpp NewsItem.h UserRequest.cpp UserRequest.h Menu.cpp Menu.h)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(RSS_Reader ${CURL_LIBRARIES})
