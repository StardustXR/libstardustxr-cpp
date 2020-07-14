project('libstardustxr','cpp',default_options : ['cpp_std=c++11'])

threads = dependency('threads')
incdir = include_directories('include')
clientsrc = ['src/messenger.cpp', 'src/clientconnector.cpp']

serversrc = ['src/messenger.cpp', 'src/messengermanager.cpp']

clientlib = library('stardustxr', clientsrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0')
serverlib = library('stardustxr-server', serversrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0')

executable('messenger', 'tests/messenger.cpp', link_with: clientlib, include_directories: incdir)
