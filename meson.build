project('libstardustxr','cpp',default_options : ['cpp_std=c++11'])

threads = dependency('threads')

# Headers
incdir = include_directories('include')

commonheaders = ['include/message.hpp', 'include/messenger.hpp', 'include/scenegraph.hpp']
install_headers(commonheaders, subdir: 'stardustxr')


# install_headers(

# Client library
clientheaders = ['include/client/clientconnector.hpp']
clientsrc = ['src/messenger.cpp', 'src/clientconnector.cpp']

clientlib = library('stardustxr', clientsrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(clientheaders, subdir: 'stardustxr/client')

# Server library
serverheaders = ['include/server/messengermanager.hpp']
serversrc = ['src/messenger.cpp', 'src/messengermanager.cpp']

serverlib = library('stardustxr-server', serversrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0', install: true)

install_headers(serverheaders, subdir: 'stardustxr/server')

# Tests
executable('messenger', 'tests/messenger.cpp', link_with: clientlib, include_directories: incdir)
executable('client', 'tests/serverclient/client.cpp', link_with: clientlib, include_directories: incdir)
executable('server', 'tests/serverclient/server.cpp', link_with: serverlib, include_directories: incdir)
