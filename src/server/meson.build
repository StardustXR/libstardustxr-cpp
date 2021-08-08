install_headers(
	[
		'messengermanager.hpp',
	],
	subdir: 'stardustxr/server'
)
server_files = files(
	'messengermanager.cpp'
)
lib_server = library(
	'stardustxr-server',
	[common_files, server_files],
	dependencies: [threads],
	version: '0.1.1',
	soversion: '0',
	install: true
)
pkg.generate(lib_server, filebase: 'stardustxr-server', name: 'stardustxr-server', url: 'https://github.com/technobaboo/libstardustxr')