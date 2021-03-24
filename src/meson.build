common_includes = include_directories('.')

install_headers(
	[
		'message.hpp',
		'messenger.hpp',
		'util.hpp'
	],
	subdir: 'stardustxr'
)

lib_common = static_library(
	'common',
	files(
		'messenger.cpp',
	),
	include_directories: [common_includes]
)

common = declare_dependency(
	include_directories: common_includes,
	link_with: lib_common
)

subdir('client')
subdir('server')
subdir('fusion')
