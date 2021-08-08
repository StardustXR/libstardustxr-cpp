if get_option('client') or get_option('server')
	install_headers(
		[
			'flex.hpp',
			'message.hpp',
			'messenger.hpp',
			'scenegraph.hpp',
		],
		subdir: 'stardustxr/common'
	)
endif
common_files += files('messenger.cpp')