#include "Server.hpp"

const std::string Server::user_key = "username";
const std::string Server::msg_key = "message";

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
  _listener.support(methods::POST,
      [this](auto&& arg) { handle_post(std::forward<decltype(arg)>(arg)); });
  _listener.support(methods::PUT, &Server::handle_unknown_request);
  _listener.support(methods::DEL, &Server::handle_unknown_request);
  _listener.open().wait();
}

void Server::handle_get(const http_request& request)
{
  request.reply(status_codes::OK, construct_reply());
}

void Server::handle_post(const http_request& request)
{
  std::cout << "SERVER: got 'post' request" << std::endl;
}

json::value Server::construct_reply()
{
  json::value message;
  message[user_key] = json::value::string("partner");
  message[msg_key] = json::value::string("msg_content");
  json::value res;
  res[0] = message;
  message[user_key] = json::value::string("partner_1111");
  message[msg_key] = json::value::string("msg_content_1111");
  res[1] = message;
  return res;
}

void Server::handle_unknown_request(const http_request& request)
{
  request.reply(status_codes::MethodNotAllowed);
}
