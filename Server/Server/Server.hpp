#ifndef SERVER_SERVER_SERVER_HPP_
#define SERVER_SERVER_SERVER_HPP_

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "ThreadPool.hpp"

namespace http = web::http;
namespace listener = http::experimental::listener;

class Server {
private:

public:
  void print(const std::string& tmp);
};

#endif //SERVER_SERVER_SERVER_HPP_
