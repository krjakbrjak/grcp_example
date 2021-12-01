#include "server.h"

#include <worker.grpc.pb.h>

#include <iostream>

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>

namespace
{
    std::unique_ptr<::grpc::Server> create_server(const std::string &address, Worker::Service *service)
    {
        ::grpc::ServerBuilder builder;
        builder.AddListeningPort(address, ::grpc::InsecureServerCredentials());
        builder.RegisterService(service);
        return builder.BuildAndStart();
    }
}

struct Server::Pimpl : public Worker::Service
{
    std::unique_ptr<::grpc::Server> server;

    Pimpl(const std::string &address)
        : server{create_server(address, this)}
    {
    }

    virtual ::grpc::Status Get(::grpc::ServerContext *context, const ::Request *request, ::Response *response) override
    {
        std::cout << request->number() << std::endl;
        response->set_number(request->number() + 1);
        return ::grpc::Status::OK;
    }
};

Server::~Server() = default;

Server::Server(const std::string &address)
    : m_pimpl{std::make_unique<Pimpl>(address)}
{
}

void Server::wait()
{
    m_pimpl->server->Wait();
}
