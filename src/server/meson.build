server_includes = include_directories('.')

install_headers(
	[
		'messengermanager.hpp',
	],
	subdir: 'stardustxr/server'
)

lib_server = library(
	'stardustxr-server',
	files(
		'messengermanager.cpp',
	),
	include_directories: [common_includes, server_includes],
	dependencies: [threads],
	link_whole: [lib_common],
	version: '0.1.0',
	soversion: '0',
	install: true
)

pkg.generate(lib_server, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/technobaboo/libstardustxr')

server = declare_dependency(
	include_directories: server_includes,
	link_with: lib_server
)
