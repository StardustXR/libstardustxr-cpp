fusion_tests_includes = include_directories('../../src/')

glm = dependency('glm')

test_basic = executable(
	'basic',
	'basic.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('basic', test_basic)


test_data = executable(
	'data',
	'data.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion, flatbuffers],
)
test('data', test_data)


test_environment = executable(
	'environment',
	'environment.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('environment', test_environment)


test_fields = executable(
	'fields',
	'fields.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('fields', test_fields)


test_input = executable(
	'input',
	'input.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('input', test_input)


test_launch = executable(
	'launch',
	'launch.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('launch', test_launch)


test_lifecycle = executable(
	'lifecycle',
	'lifecycle.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('lifecycle', test_lifecycle)


test_materials = executable(
	'materials',
	'materials.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('materials', test_materials)


test_model = executable(
	'model',
	'model.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('model', test_model)


if glm.found()
	test_spatial = executable(
		'spatial',
		'spatial.cpp',
		include_directories: [fusion_tests_includes],
		dependencies: [fusion, glm],
	)
	test('spatial', test_spatial)
endif


test_spatial_loop = executable(
	'spatialloop',
	'spatialloop.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('spatialloop', test_spatial_loop)


if glm.found()
	test_text = executable(
		'text',
		'text.cpp',
		include_directories: [fusion_tests_includes],
		dependencies: [fusion, glm],
	)
	test('text', test_text)
endif


test_zone = executable(
	'zone',
	'zone.cpp',
	include_directories: [fusion_tests_includes],
	dependencies: [fusion],
)
test('zone', test_zone)
