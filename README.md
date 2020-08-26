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

## Server
- Include directory `/usr/local/include/stardustxr`
- Link to `/usr/local/lib/x86_64-linux-gnu/libstardustxr-server.so`
