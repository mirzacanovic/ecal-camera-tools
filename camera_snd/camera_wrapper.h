#pragma once

#include <QObject>
#include <QCamera>
#include <QCameraImageCapture>
#include <QScopedPointer>

#include <ecal/msg/protobuf/publisher.h>

#include "compressed_image.pb.h"

class CameraWrapper : public QObject
{
  Q_OBJECT
public:
  CameraWrapper(eCAL::protobuf::CPublisher<foxglove::CompressedImage>& publisher, std::string& camera_name, uint16_t width, uint16_t height, uint16_t maxFps);
  ~CameraWrapper();
  bool isReadyForCapture();

private slots:
  void setCamera(const QCameraInfo& cameraInfo);
private:
  void capture();
  bool isGivenResolutionSupported();
  std::string supportedResolutionsList();

  QScopedPointer<QCamera> camera_;
  QScopedPointer<QCameraImageCapture> imageCapture_;

  eCAL::protobuf::CPublisher<foxglove::CompressedImage>& publisher_;

  std::string cameraName_;
  uint16_t width_;
  uint16_t height_;
  size_t photosTaken_;

  qint64 frameIntervalInMs = 0;
  qint64 lastFrameTimestamp;

signals:
  void photoSentSignal();
};
