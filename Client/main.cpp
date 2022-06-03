#include "Client.hpp"

int main()
{
  constexpr int chat_duration = 40;
  std::string username;
  std::cout << "Enter your username: ";
  std::cin >> username;
  Client client(uri_builder(U("http://localhost")).to_uri().to_string(), username);
  client.start_chat(chat_duration);
  return 0;
}
