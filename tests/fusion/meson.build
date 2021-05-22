fusion_tests_includes = include_directories('../../src/')

executable(
	'basic',
	'basic.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)

executable(
	'environment',
	'environment.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)

executable(
	'fields',
	'fields.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)

executable(
	'input',
	'input.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
	link_args: '-lflatbuffers',
)


executable(
	'lifecycle',
	'lifecycle.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)

executable(
	'model',
	'model.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)

executable(
	'spatial',
	'spatial.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
