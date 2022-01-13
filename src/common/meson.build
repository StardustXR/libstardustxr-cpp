if get_option('client') or get_option('server')
	install_headers(
		[
			'flex.hpp',
			'messenger.hpp',
			'scenegraph.hpp',
		],
		subdir: 'stardustxr/common'
	)
        subdir('flatbuffers')
endif
common_files += files('messenger.cpp')
