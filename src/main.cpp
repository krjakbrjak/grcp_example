#include "server.h"
#include "client.h"

#include <iostream>

#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

int main(int argc, char **argv)
{
    CLI::App app{"gRPC example"};

    std::string address = "0.0.0.0:50074";
    app.add_option("-a,--address", address, "A server address");

    auto is_server = true;
    app.add_option("-s,--server_mode", is_server, "Shoud the app run as the server or the client");

    CLI11_PARSE(app, argc, argv);

    if (is_server)
    {
        Server impl{address};
        impl.wait();
    }
    else
    {
        Client client{address};
        std::cout << client.get() << std::endl;
    }
}
