#include "../blank_scenegraph.hpp"
#include "messengermanager.hpp"

int main(int argc, char *argv[]) {
  printf("Server starting...\n");

  StardustXR::BlankScenegraph scenegraph;
  StardustXR::MessengerManager messengerManager(&scenegraph);

  std::this_thread::sleep_for(std::chrono::seconds(300));

  return 0;
}
