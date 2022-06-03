#include "Client.hpp"

const std::string Client::user_key = "username";
const std::string Client::msg_key = "message";

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
  for (const auto& tmp : _messages) {
    std::cout << "From " << tmp.first << ": " << std::endl;
    for (const auto& message : tmp.second) {
      std::cout << "\t" << message << std::endl;
    }
  }
  _messages.clear();
}

void Client::update_messages()
{
  const auto messages_json = get_from_server().as_array();
  for (const auto& it : messages_json) {
    const auto user = it.at(user_key).as_string();
    const auto message = it.at(msg_key).as_string();
    _messages[user].emplace_back(message);
  }
}

json::value Client::get_from_server()
{
  _self.request(methods::GET).then([](const http_response& response) {
        if (response.status_code() == status_codes::OK) {
          response.extract_json();
        }
        return pplx::task_from_result(json::value());
      })
      .then([](const pplx::task<json::value>& prevTask) {
        return prevTask.get();
      }).wait();

  std::cerr << "Something went wrong ... can't get from server!!" << std::endl;
  return json::value::string("");
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
