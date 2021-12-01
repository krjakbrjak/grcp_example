#pragma once

#include <string>

class Server final
{
public:
    Server(const std::string &address);
    ~Server();
    void wait();

private:
    class Pimpl;
    std::unique_ptr<Pimpl> m_pimpl;
};
