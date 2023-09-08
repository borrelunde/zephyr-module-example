# Only include header files and add source files if the module is enabled.
if (CONFIG_MODULE_EXAMPLE)

	# Include internal header files.
	zephyr_include_directories(include)
	zephyr_include_directories(drivers)

	# Add internal source files.
	add_subdirectory(lib)
	add_subdirectory(drivers)

endif()