#include "ThreadPool.hpp"

std::string ThreadPool::foo(const std::string& tmp)
{
  return std::string(tmp.rbegin(), tmp.rend());
}