/* ========================= eCAL LICENSE =================================
*
* Copyright (C) 2022 Continental Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* ========================= eCAL LICENSE =================================
*/

#include <iostream>
#include <string>

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include <QCoreApplication>
#include <QtWidgets>

#include "camera_wrapper.h"
#include "camera_wrapper_with_fps_control.h"
#include "compressed_image.pb.h"

int main(int argc, char **argv) {
  if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    std::cout << "eCAL Camera Sender \n\n";
    std::cout << "Example usage: argv[0] compressed_image_protobuf "
                 "/dev/video0 640 480 10 \n\n";
    std::cout << "Command Line Arguments: \n\n";
    std::cout << "Topic: Name of the topic";
    std::cout << "Camera: Path to camera. \n";
    std::cout << "Width: Image width (optional) \n";
    std::cout << "Height: Image height (optional) \n";
    std::cout << "Framerate: Maximal framerate (optional)\n";

    return 0;
  }

  std::string cameraName;
  std::string topicName;
  uint16_t width = 0;
  uint16_t height = 0;
  uint16_t maxFps = 0;

  std::shared_ptr<CameraWrapper> camera;

  if (argc < 3) {
    std::cerr << "Invalid parameters, usage: argv[0] [topicName] "
                 "[cameraName] [OPTIONAL_resolutionWidth] "
                 "[OPTIONAL_resolutionHeight] [OPTIONAL_maxFps]"
              << std::endl;
    return 0;
  } else {
    if (argc > 4) {
      width = std::stoi(argv[3]);
      height = std::stoi(argv[4]);
    }

    if (argc == 6) {
      maxFps = std::stoi(argv[5]);
    }

    topicName = argv[1];
    cameraName = argv[2];
  }

  QApplication app(argc, argv);

  // Initialize eCAL and create a protobuf publisher
  eCAL::Initialize(argc, argv, "Image Sender");
  eCAL::protobuf::CPublisher<foxglove::CompressedImage> publisher(topicName);

  if (maxFps > 0) {
    camera = std::make_shared<CameraWrapperWithFpsControl>(
        publisher, cameraName, width, height, maxFps);
  } else {
    camera =
        std::make_shared<CameraWrapper>(publisher, cameraName, width, height);
  }

  return app.exec();
}