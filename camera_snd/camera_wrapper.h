#pragma once

#include <QCamera>
#include <QCameraImageCapture>
#include <QObject>
#include <QScopedPointer>

#include <ecal/msg/protobuf/publisher.h>

#include "compressed_image.pb.h"

class CameraWrapper : public QObject {
  Q_OBJECT
public:
  CameraWrapper(
      eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
      std::string &camera_name, uint16_t width, uint16_t height);
  ~CameraWrapper();
  bool isReadyForCapture();

protected:
  virtual void capture();

private slots:
  void setCamera(const QCameraInfo &cameraInfo);

private:
  bool isGivenResolutionSupported();
  std::string supportedResolutionsList();

  QScopedPointer<QCamera> camera_;
  QScopedPointer<QCameraImageCapture> imageCapture_;

  eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher_;

  std::string cameraName_;
  uint16_t width_;
  uint16_t height_;
  size_t photosTaken_;

signals:
  void photoSentSignal();
};
