client_includes = include_directories('.')

install_headers(
	[
		'connector.hpp',
		'messenger.hpp',
	],
	subdir: 'stardustxr/client'
)

lib_client = library(
	'stardustxr',
	files(
		'connector.cpp',
		'messenger.cpp',
	),
	include_directories: [client_includes],
	dependencies: [common, threads],
	version: '0.1.0',
	soversion: '0',
	install: true
)

pkg.generate(lib_client, filebase: 'stardustxr', name: 'stardustxr', url: 'https://github.com/technobaboo/libstardustxr')

client = declare_dependency(
	include_directories: client_includes,
	link_with: lib_client
)
