# libstardustxr
Stardust XR C++ library for server implementations and clients

## Prerequisites
1. Meson
2. Ninja
3. Flatbuffers >= 1.12.0

## Build
```bash
meson build --prefix=/usr
cd build
ninja
```

## Install
```bash
ninja install
```

## Server
- Include directory `/usr/local/include/stardustxr`
- Link to `/usr/local/lib/x86_64-linux-gnu/libstardustxr-server.so`
- pkgconfig name is `stardustxr-server`

## Client
- Include directory `/usr/local/include/stardustxr`
- Link to `/usr/local/lib/x86_64-linux-gnu/libstardustxr.so`
- pkgconfig name is `stardustxr`

## Fusion
- Include directory `/usr/local/include/stardustxr`
- Link to `/usr/local/lib/x86_64-linux-gnu/libstardustxr-server.so`
- pkgconfig name is `stardustxr-fusion`
