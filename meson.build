project('libstardustxr','cpp', default_options : ['cpp_std=c++11'], version: '0.9.0')

pkg = import('pkgconfig')
threads = dependency('threads')
flatbuffers = dependency('flatbuffers', version:'>=2.0.6')

common_files = []

subdir('src')

if get_option('tests')
	subdir('tests')
endif
