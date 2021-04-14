fusion_includes = include_directories('.')

fusion_static_libs = []

subdir('DirectXMath')
subdir('interfaces')
subdir('types')

install_headers(
	[
		'fusion.hpp',
		'sk_math.hpp',
	],
	subdir: 'stardustxr/fusion'
)

lib_fusion = library(
	'stardustxr-fusion',
	files(
		 'fusion.cpp',
		 'scenegraph.cpp',
	),
	include_directories: [fusion_includes],
	link_whole: fusion_static_libs,
	link_args: '-lflatbuffers',
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
