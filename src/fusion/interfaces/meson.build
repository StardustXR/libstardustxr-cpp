fusion_interfaces_includes = include_directories('.')

install_headers(
	[
		'lifecycleinterface.hpp',
	],
	subdir: 'stardustxr/fusion/interfaces'
)

lib_fusion_interfaces = static_library(
	'fusion_interfaces',
	files(
		'lifecycleinterface.cpp',
	),
	include_directories: [fusion_interfaces_includes],
	dependencies: [client],
)

fusion_static_libs += lib_fusion_interfaces
