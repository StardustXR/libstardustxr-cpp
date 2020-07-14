#include "../blank_scenegraph.hpp"
#include "clientconnector.hpp"
#include "messenger.hpp"

int main(int argc, char *argv[]) {
  printf("Client starting...\n");
  int readFD, writeFD;
  if (!StardustXR::ConnectClient("/tmp/stardust.sock", readFD, writeFD)) {
    perror("Client failed to connect to server");
    return 1;
  }

  StardustXR::BlankScenegraph scenegraph;
  StardustXR::Messenger messenger(readFD, writeFD, &scenegraph);

  std::vector<uint8_t> blankVector;

  messenger.sendSignal("/test", "echo", blankVector);

  std::this_thread::sleep_for(std::chrono::seconds(300));

  return 0;
}
