#include "messenger.hpp"
#include "blank_scenegraph.hpp"
#include <chrono>
#include <iostream>

std::chrono::duration<double> benchmark_time(void *(*function)()) {
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  (*function)();
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

int s2cpipe[2];
int c2spipe[2];

void client() {
  printf("Client Started\n");

  StardustXR::BlankScenegraph blankScenegraph;
  StardustXR::Messenger messenger(s2cpipe[0], c2spipe[1], &blankScenegraph);

  flexbuffers::Builder fbb;
  fbb.String("Echo test");
  fbb.Finish();
  std::vector<uint8_t> flexbuffer = fbb.GetBuffer();

  messenger.sendSignal("/test", "echo", flexbuffer);
}
void server() {
  printf("Server Started\n");

  StardustXR::BlankScenegraph blankScenegraph;
  StardustXR::Messenger messenger(s2cpipe[0], c2spipe[1], &blankScenegraph);
}

int main(int argc, char **argv) {
  if (pipe(s2cpipe) == -1) {
    perror("s2cpipe");
    exit(EXIT_FAILURE);
  }
  if (pipe(c2spipe) == -1) {
    perror("c2spipe");
    exit(EXIT_FAILURE);
  }

  pid_t cpid;
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) {
    close(s2cpipe[1]);
    close(c2spipe[0]);
    client();
  } else {
    close(s2cpipe[0]);
    close(c2spipe[1]);
    server();
  }

  return 0;
}
