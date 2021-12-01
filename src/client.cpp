#include "client.h"

#include <worker.grpc.pb.h>

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/create_channel.h>

struct Client::Pimpl
{
    auto create_stub(const std::string &address)
    {
        auto channel = ::grpc::CreateChannel(address, ::grpc::InsecureChannelCredentials());
        return Worker::NewStub(channel);
    }

    Pimpl(const std::string &address)
        : stub{create_stub(address)}
    {
    }

    std::unique_ptr<Worker::Stub> stub;
};

Client::Client(const std::string &address)
    : m_pimpl{std::make_unique<Pimpl>(address)}
{
}

Client::~Client() = default;

int Client::get()
{
    ::grpc::ClientContext context;
    Request request;
    Response response;
    request.set_number(123);
    m_pimpl->stub->Get(&context, request, &response);
    return response.number();
}
