project('libstardustxr','cpp',default_options : ['cpp_std=c++11'])

threads = dependency('threads')
incdir = include_directories('include')
src = ['src/messenger.cpp']

serversrc = ['src/messenger.cpp', 'src/messengermanager.cpp']

executable('messenger', 'tests/messenger.cpp', link_with: lib, include_directories: incdir)
serverlib = library('stardustxr-server', serversrc, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0')
