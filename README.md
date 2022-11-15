# ecal-camera-tools

Contains a sample program that captures webcam video and sends it via [eCAL](https://eclipse-ecal.github.io/ecal/), as well as an eCAL Monitor plugin that displays the images.

## Prerequisites (Ubuntu)

Besides *eCAL 5*, the following packages need to be installed:

* qtmultimedia5-dev
* libqt5multimedia5-plugins
* qtwayland5
* protobuf-compiler
* libprotoc-dev
* libhdf5-dev

## eCAL Camera Sender

This application captures the stream from a specified camera and publishes it via Protobuf. Optionally, the resolution of the image as well as a maximal framerate can be specified.

Example usage: ./camera_snd compressed_image_protobuf /dev/video0 640 480 10

Command Line Arguments:
* Topic: Name of the topic.
* Camera: Path to camera. Usually, this is "/dev/video0" unless there are multiple cameras
* Width: Image width (optional)
* Height: Image height (optional)
* Framerate: Maximal framerate (optional)

## eCAL Monitor Plugin

After running cmake --install on the monitor plugin, you can view the published camera image in the eCAL Monitor GUI in the detailed view under the Camera Receiver tab.