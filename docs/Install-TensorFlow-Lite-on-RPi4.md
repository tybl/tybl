Source: https://qengineering.eu/install-tensorflow-2-lite-on-raspberry-pi-4.html

The following installation steps appear to be deprecated after TensorFlow 2.6.

```shell
# the tools needed
$ sudo apt update
$ sudo apt upgrade
$ sudo apt install cmake

# download the latest TensorFlow version (2.6.0)
$ wget -O tensorflow.zip https://github.com/tensorflow/tensorflow/archive/v2.6.0.zip

# unpack
$ unzip tensorflow.zip
$ cd tensorflow-2.6.2

# get the dependencies
$ ./tensorflow/lite/tools/make/download_dependencies.sh

# run the C++ installation (± 25 min)
$ ./tensorflow/lite/tools/make/build_rpi_lib.sh

# install the flatbuffers
$ cd ~/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers
$ mkdir build
$ cd build
$ cmake ..
```
Everything up to this point seems to work. However, the following step fails with 2.6.0 and 2.6.1. It looks like flatbuffers are configured with `-Werror` which causes the `flattest` target to fail when an object's memory is written with `memset()`. 
```shell
$ make -j4
$ sudo make install
$ sudo ldconfig

# clean up
$ cd ~
$ rm tensorflow.zip
```