#pragma once

#include <string>
#include <memory>

class Client final
{
public:
    Client(const std::string &address);
    ~Client();

    int get();

private:
    class Pimpl;
    std::unique_ptr<Pimpl> m_pimpl;
};
