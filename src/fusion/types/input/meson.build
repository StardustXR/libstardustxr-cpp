fusion_input_includes = include_directories('.')

install_headers(
	[
		'inputhandler.hpp',
	],
	subdir: 'stardustxr/fusion/types/input'
)

lib_fusion_input = static_library(
	'fusion_input',
	files(
		'inputhandler.cpp',
	),
	include_directories: [fusion_input_includes],
	link_args: '-lflatbuffers',
	dependencies: [client],
)

fusion_static_libs += lib_fusion_input
