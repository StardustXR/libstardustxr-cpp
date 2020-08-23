project('libstardustxr','cpp', default_options : ['cpp_std=c++11'], version: '0.1.0')

pkg = import('pkgconfig')
threads = dependency('threads')

# Headers
incdir = include_directories('include')

commonheaders = ['include/message.hpp', 'include/messenger.hpp', 'include/scenegraph.hpp']
install_headers(commonheaders, subdir: 'stardustxr')

dummyheaders = ['include/dummy/blank_scenegraph.hpp']
install_headers(dummyheaders, subdir: 'stardustxr/dummy')

scenegraphheaders = ['include/stardust_scenegraph/stardust_scenegraph.hpp', 'include/stardust_scenegraph/node.hpp']
install_headers(scenegraphheaders, subdir: 'stardustxr/stardust_scenegraph')

# Client library
clientheaders = ['include/client/clientconnector.hpp']
clientsrc = ['src/stardust_scenegraph.cpp', 'src/messenger.cpp', 'src/clientconnector.cpp']

clientlib = library('stardustxr', clientsrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(clientheaders, subdir: 'stardustxr/client')
pkg.generate(clientlib, filebase: 'stardustxr', name: 'stardustxr', url: 'https://github.com/technobaboo/libstardustxr')

# Server library
serverheaders = ['include/server/messengermanager.hpp']
serversrc = ['src/stardust_scenegraph.cpp', 'src/messenger.cpp', 'src/messengermanager.cpp']

serverlib = library('stardustxr-server', serversrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(serverheaders, subdir: 'stardustxr/server')
pkg.generate(serverlib, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/technobaboo/libstardustxr')

# Tests
executable('messenger', 'tests/messenger.cpp', link_with: clientlib, include_directories: incdir)
executable('client', 'tests/serverclient/client.cpp', link_with: clientlib, include_directories: incdir)
executable('server', 'tests/serverclient/server.cpp', link_with: serverlib, include_directories: incdir)
