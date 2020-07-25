# libstardustxr
Stardust C++ library for server implementations and clients

## Prerequisites
1. Flatbuffers v1.12.0
2. Meson

## Build
```bash
meson build
cd build
ninja
```

## Install
```bash
ninja install
```

## Client
- Include directory `/usr/local/include/stardustxr`
- Link to `/usr/local/lib/x86_64-linux-gnu/libstardustxr.so`

### Example
```cpp
#include "stardustxr/messenger.hpp"
#include "stardustxr/dummy/blank_scenegraph.hpp"
#include "stardustxr/client/clientconnector.hpp"

int main(int argc, char *argv[]) {
  printf("Client starting...\n");
  int readFD, writeFD;
  if (!StardustXR::ConnectClient("/tmp/stardust.sock", readFD, writeFD)) {
    perror("Client failed to connect to server");
    return 1;
  }

  StardustXR::BlankScenegraph scenegraph;
  StardustXR::Messenger messenger(readFD, writeFD, &scenegraph);

  std::this_thread::sleep_for(std::chrono::seconds(300));

  return 0;
}
```

## Server
- Include directory `/usr/local/include/stardustxr`
- Link to `/usr/local/lib/x86_64-linux-gnu/libstardustxr-server.so`

### Example
```cpp
#include "stardustxr/messenger.hpp"
#include "stardustxr/dummy/blank_scenegraph.hpp"
#include "stardustxr/server/messengermanager.hpp"

int main(int argc, char *argv[]) {
  printf("Server starting...\n");

  StardustXR::BlankScenegraph scenegraph;
  StardustXR::MessengerManager messengerManager(&scenegraph);

  std::this_thread::sleep_for(std::chrono::seconds(300));

  return 0;
}
```
z
