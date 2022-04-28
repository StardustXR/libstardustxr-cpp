fusion_tests_includes = include_directories('../../src/')

glm = dependency('glm')

executable(
	'basic',
	'basic.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)


executable(
	'data',
	'data.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion, flatbuffers],
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
)


executable(
	'launch',
	'launch.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)


executable(
	'lifecycle',
	'lifecycle.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)


executable(
	'materials',
	'materials.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)


executable(
	'model',
	'model.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)


if glm.found()
	executable(
		'spatial',
		'spatial.cpp',
		include_directories: [fusion_tests_includes],
		dependencies: [fusion, glm],
	)
endif


executable(
	'spatialloop',
	'spatialloop.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)


if glm.found()
	executable(
		'text',
		'text.cpp',
		include_directories: [fusion_tests_includes],
		dependencies: [fusion, glm],
	)
endif


executable(
	'zone',
	'zone.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
