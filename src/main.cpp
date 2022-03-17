#include "core/application.hpp"

int main(int argc, char *argv[])
{
  Application::init();
  Application::run();
  Application::shutdown();
  return 0;
}