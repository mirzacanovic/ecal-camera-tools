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
    std::cout << "Example usage: ./camera_snd compressed_image_protobuf "
                 "/dev/video0 640 480 10 \n\n";
    std::cout << "Command Line Arguments: \n\n";
    std::cout << "Topic: To be able to read the image with the eCAL monitor "
                 "plugin, set this to \"compressed_image_protobuf\". \n";
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
    std::cerr << "Invalid parameters, usage: ./protobuf_snd [topicName] "
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