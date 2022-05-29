cmake_minimum_required(VERSION 3.11)
project(gRPC_Example)

find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(CLI11 REQUIRED)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/protos_out/worker.pb.h
                          ${CMAKE_CURRENT_BINARY_DIR}/protos_out/worker.pb.cc
                          ${CMAKE_CURRENT_BINARY_DIR}/protos_out/worker.grpc.pb.cc
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/protos_out
                   COMMAND protobuf::protoc ARGS -I ${CMAKE_CURRENT_SOURCE_DIR}/protos --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin> --grpc_out=${CMAKE_CURRENT_BINARY_DIR}/protos_out --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/protos_out ${CMAKE_CURRENT_SOURCE_DIR}/protos/worker.proto
                   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/protos/worker.proto
                   DEPENDS protobuf::protoc
                   COMMENT Generate worker stubs
                   VERBATIM)

add_executable(gRPCExample
    main.cpp
    server.cpp
    client.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/protos_out/worker.pb.cc
    ${CMAKE_CURRENT_BINARY_DIR}/protos_out/worker.grpc.pb.cc
)

target_link_libraries(gRPCExample gRPC::grpc++ CLI11::CLI11)
target_include_directories(gRPCExample PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/protos_out)
target_compile_features(gRPCExample PRIVATE cxx_std_17)

install(TARGETS gRPCExample EXPORT gRPCExampleTargets
  RUNTIME DESTINATION bin
)
install(EXPORT gRPCExampleTargets DESTINATION lib/gRPCExample)
