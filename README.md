# ecal-camera-tools

Contains a sample program that captures webcam video and sends it via [eCAL](https://eclipse-ecal.github.io/ecal/), as well as an eCAL Monitor plugin that displays the images.

## Prerequisites (Ubuntu)

Besides *eCAL 5*, the following packages need to be installed:

* qtmultimedia5-dev
* libqt5multimedia5-plugins
* qtwayland5
* protobuf-compiler

## eCAL Monitor Plugin

After running cmake --install on the monitor plugin, you can view the published camera image in the eCAL Monitor GUI in the detailed view under the Camera Receiver tab. If you don't see anything, please make sure you published under the topic name "compressed_image_protobuf".
