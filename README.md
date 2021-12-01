# gRPC C++ example

This is a simple [CMake](https://cmake.org) project that can be used as an example of how to use [gRPC](https://grpc.io) library.
The wonderful [CLI11](https://github.com/CLIUtils/CLI11) library is used to parse command-line arguments.

## Build and Run instructions

```sh
cmake -DCMAKE_INSTALL_PREFIX=install_dir -B build -S .
cmake --build build --parallel
./install_dir/bin/gRPCExample # this will start the server
./install_dir/bin/gRPCExample -s false # this will start the client
```

To print help message:
```sh
./install_dir/bin/gRPCExample --help
```

This will produce the following output:
```sh
gRPC example
Usage: ./install_dir/bin/gRPCExample [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -a,--address TEXT           A server address
  -s,--server_mode BOOLEAN    Shoud the app run as the server or the client
```