#ifndef STARDUSTXR_MESSENGER_MANAGER_H
#define STARDUSTXR_MESSENGER_MANAGER_H

#include "../messenger.hpp"
#include "../scenegraph.hpp"

#include <fcntl.h>
#include <list>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <thread>

#include <iostream>
#include <time.h>
#include <unistd.h>
#define SD_SOCK_PATH "/tmp/stardust.sock"

namespace StardustXR {

class MessengerManager {
public:
  explicit MessengerManager(Scenegraph *scenegraph);
  std::list<ServerMessenger> messengers;
  Scenegraph *scenegraph;

private:
  typedef struct {
    int fd;
    char buf[256];
  } RecieveFDReturn;

  std::thread socketThread;

  RecieveFDReturn recieveFD(int socket);
  void socketLoop();
};

} // namespace StardustXR

#endif
