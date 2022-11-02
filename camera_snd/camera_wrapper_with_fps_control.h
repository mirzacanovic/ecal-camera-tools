#pragma once

#include "camera_wrapper.h"

class CameraWrapperWithFpsControl : public CameraWrapper {
  Q_OBJECT
public:
  CameraWrapperWithFpsControl(
      eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
      std::string &camera_name, uint16_t width, uint16_t height,
      uint16_t maxFps);

  ~CameraWrapperWithFpsControl();

  void capture();

private:
  qint64 frameIntervalInMs;
  qint64 lastFrameTimestamp;
};