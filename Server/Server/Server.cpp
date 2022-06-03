#include "Server.hpp"

void Server::print(const std::string& tmp)
{
  ThreadPool b{};
  std::cout << b.foo(tmp) << std::endl;
}
