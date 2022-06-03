#ifndef SERVER_SERVER_HPP_
#define SERVER_SERVER_HPP_

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "ThreadPool.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class Server {
private:
  http_listener _listener;

public:
  explicit Server(const std::string& listening_port);
  ~Server();
  void start();

private:
  void handle_get(const http_request& request);
  void handle_post(const http_request& request);
  static json::value construct_reply(const std::string& msg);
  static void handle_unknown_request(const http_request& request);
};

#endif //SERVER_SERVER_HPP_
