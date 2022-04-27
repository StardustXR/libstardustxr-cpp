if not get_option('client')
	client = dependency('stardustxr')
endif

install_headers(
	[
		'fusion.hpp',
		'sk_math_util.h',
		'sk_math.hpp',
	],
	subdir: 'stardustxr/fusion'
)
fusion_files = files(
	'fusion.cpp',
        'random.cpp',
        'messenger.cpp',
	'scenegraph.cpp',
)

subdir('types')
subdir('util')

lib_fusion = library(
	'stardustxr-fusion',
        [common_files, fusion_files],
        dependencies: [client, threads, flatbuffers],
	version: '0.1.1',
	soversion: '0',
	install: true
)
pkg.generate(lib_fusion, filebase: 'stardustxr-fusion', name: 'stardustxr-fusion', url: 'https://github.com/StardustXR/libstardustxr')

fusion = declare_dependency(
	include_directories: include_directories('.'),
	link_with: lib_fusion
)
