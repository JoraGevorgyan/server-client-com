#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Client {
private:
  std::string _username;
  http_client _self;
  std::unordered_map<std::string, std::vector<std::string>> _messages;

public:
  Client(const utility::string_t& address, std::string username);
  void start_chat(int duration);

private:
  void send();
  void show_messages();
  void send(const std::string& partner, const std::string& msg);
  void update_messages();
  json::value get_from_server();
  static char get_choice();
};

#endif //CLIENT_CLIENT_HPP
