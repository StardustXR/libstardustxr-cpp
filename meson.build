project('libstardustxr','cpp', default_options : ['cpp_std=c++11'], version: '0.1.0')

pkg = import('pkgconfig')
threads = dependency('threads')

# Headers
incdir = include_directories('src')

commonheaders = ['src/message.hpp', 'src/messenger.hpp', 'src/util.hpp']
install_headers(commonheaders, subdir: 'stardustxr')

# Client library
clientheaders = ['src/client/connector.hpp', 'src/client/messenger.hpp', 'src/client/scenegraph.hpp', 'src/client/node.hpp', 'src/client/stardust_scenegraph.hpp']
clientsrc = ['src/client/stardust_scenegraph.cpp', 'src/messenger.cpp', 'src/client/messenger.cpp', 'src/client/connector.cpp']

clientlib = library('stardustxr', clientsrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(clientheaders, subdir: 'stardustxr/client')
pkg.generate(clientlib, filebase: 'stardustxr', name: 'stardustxr', url: 'https://github.com/technobaboo/libstardustxr')

# Server library
serverheaders = ['src/server/messengermanager.hpp', 'src/server/messenger.hpp', 'src/server/scenegraph.hpp', 'src/server/node.hpp']
serversrc = ['src/messenger.cpp', 'src/server/messenger.cpp', 'src/server/messengermanager.cpp']

serverlib = library('stardustxr-server', serversrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(serverheaders, subdir: 'stardustxr/server')
pkg.generate(serverlib, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/technobaboo/libstardustxr')

# Tests
executable('client', 'tests/serverclient/client.cpp', link_with: clientlib, include_directories: incdir)
