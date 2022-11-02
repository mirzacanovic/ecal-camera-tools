#include "camera_wrapper_with_fps_control.h"

#include <QDateTime>
#include <thread>

CameraWrapperWithFpsControl::CameraWrapperWithFpsControl(
    eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
    std::string &camera_name, uint16_t width, uint16_t height, uint16_t maxFps)
    : CameraWrapper(publisher, camera_name, width, height),
      frameIntervalInMs(1000 / maxFps),
      lastFrameTimestamp(QDateTime::currentMSecsSinceEpoch()) {}

CameraWrapperWithFpsControl::~CameraWrapperWithFpsControl() {}

void CameraWrapperWithFpsControl::capture() {
  qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
  std::cout << "Time: " << currentTime << std::endl;
  // limit the number of photos captured
  qint64 sleepingTime =
      currentTime - lastFrameTimestamp < frameIntervalInMs
          ? frameIntervalInMs - (currentTime - lastFrameTimestamp)
          : 0;

  std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));

  CameraWrapper::capture();

  lastFrameTimestamp = QDateTime::currentMSecsSinceEpoch();
}
