project('libstardustxr','cpp', default_options : ['cpp_std=c++11'], version: '0.1.0')

pkg = import('pkgconfig')
threads = dependency('threads')

# Headers
incdir = include_directories('include')

commonheaders = ['include/message.hpp', 'include/messenger.hpp']
install_headers(commonheaders, subdir: 'stardustxr')

# Client library
clientheaders = ['include/client/connector.hpp', 'include/client/messenger.hpp', 'include/client/scenegraph.hpp', 'include/client/node.hpp', 'include/client/stardust_scenegraph.hpp']
clientsrc = ['src/client/stardust_scenegraph.cpp', 'src/messenger.cpp', 'src/client/messenger.cpp', 'src/client/connector.cpp']

clientlib = library('stardustxr', clientsrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(clientheaders, subdir: 'stardustxr/client')
pkg.generate(clientlib, filebase: 'stardustxr', name: 'stardustxr', url: 'https://github.com/technobaboo/libstardustxr')

# Server library
serverheaders = ['include/server/messengermanager.hpp', 'include/server/messenger.hpp', 'include/server/scenegraph.hpp', 'include/server/node.hpp', 'include/server/stardust_scenegraph.hpp']
serversrc = ['src/server/stardust_scenegraph.cpp', 'src/messenger.cpp', 'src/server/messenger.cpp', 'src/server/messengermanager.cpp']

serverlib = library('stardustxr-server', serversrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(serverheaders, subdir: 'stardustxr/server')
pkg.generate(serverlib, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/technobaboo/libstardustxr')

# Tests
executable('client', 'tests/serverclient/client.cpp', link_with: clientlib, include_directories: incdir)
executable('server', 'tests/serverclient/server.cpp', link_with: serverlib, include_directories: incdir)
