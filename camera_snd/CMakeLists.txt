# ========================= eCAL LICENSE =================================
#
# Copyright (C) 2022 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= eCAL LICENSE =================================

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

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION  ${CMAKE_INSTALL_PREFIX}/bin COMPONENT app
)
