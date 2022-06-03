#include "Server.hpp"

Server::Server(const std::string& listening_port)
{
  uri_builder uri(U("http://*:") + listening_port);
  const auto uri_address = uri.to_uri().to_string();
  _listener = http_listener(uri_address, http_listener_config());
}

Server::~Server()
{
  _listener.close().wait();
}

void Server::start()
{
  _listener.support(methods::GET,
      [this](auto&& arg) { handle_get(std::forward<decltype(arg)>(arg)); });
  _listener.support(methods::POST, &Server::handle_unknown_request);
  _listener.support(methods::PUT, &Server::handle_unknown_request);
  _listener.support(methods::DEL, &Server::handle_unknown_request);
  _listener.open().wait();
}

void Server::handle_get(const http_request& request)
{
  std::cout << "SERVER: got a request" << std::endl;
}

json::value Server::construct_reply(const std::string& msg)
{
  return {};
}

void Server::handle_unknown_request(const http_request& request)
{
  request.reply(status_codes::MethodNotAllowed);
}
