#include "Client.hpp"

Client::Client(const utility::string_t& address, std::string username)
    :_username(std::move(username)),
     _self(address, http_client_config()),
     _messages{} { }

void Client::start_chat(int duration)
{
  std::cout << "You just started a chat, your username is " << _username << std::endl;
  for (int i = 0; i < duration; ++i) {
    update_messages();
    std::cout << "Type to send(1), read(2), exit(0): ";
    char choice = get_choice();
    if (choice == '0') {
      break;
    }
    if (choice == '1') {
      send();
    }
    else {
      show_messages();
    }
  }
  std::cout << "End of chat!" << std::endl;
}

void Client::send()
{
  std::string partner;
  std::string msg;
  std::cout << "partner's username: ";
  std::cin >> partner;
  std::cout << "message: ";
  std::cin >> msg;
  send(partner, msg);
}

void Client::send(const std::string& partner, const std::string& msg)
{

}

void Client::show_messages()
{
  if (_messages.empty()) {
    std::cout << "You have no unread messages right now!" << std::endl;
    return;
  }
  for (const auto& tmp: _messages) {
    std::cout << "From " << tmp.first << ": " << std::endl;
    for (const auto& message: tmp.second) {
      std::cout << "\t" << message << std::endl;
    }
  }
  _messages.clear();
}

void Client::update_messages()
{

}

char Client::get_choice()
{
  char c;
  std::cin >> c;
  if (c < '0' || c > '2') {
    return '0';
  }
  return c;
}
