#include "ThreadPool.hpp"

std::string foo(const std::string& tmp)
{
  return std::string(tmp.rbegin(), tmp.rend());
}