install_headers(
	[
		'connector.hpp',
	],
	subdir: 'stardustxr/client'
)
client_files = files(
	'connector.cpp'
)
lib_client = library(
	'stardustxr',
	[common_files, client_files],
	dependencies: [threads],
	version: '0.9.0',
	soversion: '0',
	install: true
)
pkg.generate(lib_client, filebase: 'stardustxr', name: 'stardustxr', url: 'https://github.com/StardustXR/libstardustxr')

client = declare_dependency(
	include_directories: include_directories('.'),
	link_with: lib_client,
)
