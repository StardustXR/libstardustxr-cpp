subdir('fields')

fusion_types_includes = include_directories('.')

install_headers(
	[
		 'node.hpp',
	],
	subdir: 'stardustxr/fusion/types'
)

lib_fusion_types = static_library(
	'fusion_types',
	files(
		 'node.cpp',
	),
	include_directories: [fusion_types_includes],
	dependencies: [fusion_fields, client]
)

fusion_types = declare_dependency(
	include_directories: fusion_types_includes,
	link_with: lib_fusion_types
)
