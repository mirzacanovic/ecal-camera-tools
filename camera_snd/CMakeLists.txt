cmake_minimum_required(VERSION 3.0)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

project(camera_snd)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

set(source_files
  main.cpp
  camera_wrapper.h
  camera_wrapper.cpp
  camera_wrapper_with_fps_control.h
  camera_wrapper_with_fps_control.cpp
)

set(protobuf_files
    ${CMAKE_SOURCE_DIR}/proto_messages/compressed_image.proto
)

add_executable(${PROJECT_NAME} ${source_files})

PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/proto_messages/ ${protobuf_files})

target_link_libraries(${PROJECT_NAME}
  eCAL::core
  protobuf::libprotobuf
  Qt5::Widgets
  Qt5::MultimediaWidgets
)