project('libstardustxr','cpp')

threads = dependency('threads')
incdir = include_directories('include')
src = ['src/messenger.cpp']

lib = library('stardustxr', src, include_directories: incdir, dependencies: [threads], version: '0.1.0', soversion: '0')

executable('messenger', 'tests/messenger.cpp', link_with: lib, include_directories: incdir)
