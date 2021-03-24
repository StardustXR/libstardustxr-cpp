fusion_includes = include_directories('.')

install_headers(
	[
		# 'messenger.hpp',
	],
	subdir: 'stardustxr/fusion'
)

lib_fusion = library(
	'stardustxr-fusion',
	files(
		# 'messenger.cpp',
	),
	include_directories: [fusion_includes],
	dependencies: [client],
	version: '0.1.0',
	soversion: '0',
	install: true
)

pkg.generate(lib_fusion, filebase: 'stardustxr-fusion', name: 'stardustxr-fusion', url: 'https://github.com/technobaboo/libstardustxr')

fusion = declare_dependency(
	include_directories: fusion_includes,
	link_with: lib_fusion
)
