#include "core/application.hpp"

#include <ctime>

int main(int argc, char *argv[])
{
  Application::init();
  Application::run();
  Application::shutdown();
  return 0;
}