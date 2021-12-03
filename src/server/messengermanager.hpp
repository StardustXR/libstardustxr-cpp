#pragma once

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

namespace StardustXR {

class MessengerManager {
public:
  explicit MessengerManager();
  virtual ~MessengerManager();

protected:
  virtual void clientConnected(int inFD, int outFD) = 0;
  std::string socketPath;

private:
  typedef struct {
	int fd;
	char buf[256];
  } RecieveFDReturn;

  std::thread socketThread;
  void socketLoop();
};

} // namespace StardustXR
