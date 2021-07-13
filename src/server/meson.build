server_includes = include_directories('.')

install_headers(
	[
		'messenger.hpp',
		'messengermanager.hpp',
		'scenegraph.hpp',
	],
	subdir: 'stardustxr/server'
)

lib_server = library(
	'stardustxr-server',
	files(
		'messenger.cpp',
		'messengermanager.cpp',
	),
	include_directories: [server_includes],
	dependencies: [common, threads],
	version: '0.1.0',
	soversion: '0',
	install: true
)

pkg.generate(lib_server, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/technobaboo/libstardustxr')

server = declare_dependency(
	include_directories: server_includes,
	link_with: lib_server
)
