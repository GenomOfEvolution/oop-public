#pragma once
#include <string>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);