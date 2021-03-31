fusion_fields_includes = include_directories('.')

install_headers(
	[
		'boxfield.hpp',
		'field.hpp',
		'roundedboxfield.hpp',
		'spherefield.hpp',
	],
	subdir: 'stardustxr/fusion/types/fields'
)

lib_fusion_fields = static_library(
	'fusion_fields',
	files(
		'boxfield.cpp',
		'field.cpp',
		'roundedboxfield.cpp',
		'spherefield.cpp',
	),
	include_directories: [fusion_fields_includes],
	link_args: '-lflatbuffers',
	dependencies: [client],
)

fusion_static_libs += lib_fusion_fields
