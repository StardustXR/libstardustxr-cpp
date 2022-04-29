resources = [
	'gyro_gem.glb',
	'gyro_inside.glb',
	'gyro_middle.glb',
	'gyro_outside.glb',
	'stardust_icon.glb',
	'wide_street_01_1k.hdr',
	'zhengyang_gate_4k.hdr',
]

custom_target(
	'cp_resources',
	input : resources,
	output : resources,
	command : ['cp', '@INPUT@', '@OUTDIR@'],
	install : false,
	build_by_default : true
)