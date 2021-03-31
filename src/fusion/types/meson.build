fusion_types_includes = include_directories('.')

install_headers(
	[
		 'node.hpp',
		 'spatial.cpp',
	],
	subdir: 'stardustxr/fusion/types'
)

lib_fusion_types = static_library(
	'fusion_types',
	files(
		 'node.cpp',
		 'spatial.cpp',
	),
	include_directories: [fusion_types_includes],
	dependencies: [client],
)

fusion_static_libs += lib_fusion_types

subdir('fields')
