function(add_compute_shaders target)
	cmake_parse_arguments(PARSE_ARGV 1 arg "" "" "SOURCES")

	set(spvfiles "")

	foreach(source ${arg_SOURCES})
		get_filename_component(base ${source} NAME_WE)

		set(outfile ${CMAKE_CURRENT_BINARY_DIR}/${base}.spv)
		set(spvfiles ${spvfiles} ${outfile})

		add_custom_command(
			OUTPUT ${outfile}
			DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${source}
			COMMENT "Compile shader ${base}"
			COMMAND ${Vulkan_GLSLC_EXECUTABLE} --target-env=vulkan1.0 -c ${CMAKE_CURRENT_SOURCE_DIR}/${source} -g -o ${outfile})

		install(FILES ${outfile} DESTINATION share/glscopeclient/shaders)

	endforeach()

	add_custom_target(${target}
		COMMAND ${CMAKE_COMMAND} -E true
		SOURCES ${spvfiles}
	)

endfunction()

add_compute_shaders(
	protocolshaders
	SOURCES
		AddFilter.glsl
		BlackmanHarrisWindow.glsl
		ComplexToLogMagnitude.glsl
		ComplexToMagnitude.glsl
		Convert8BitSamples.glsl
		Convert16BitSamples.glsl
		CosineSumWindow.glsl
		DeEmbedFilter.glsl
		DeEmbedNormalization.glsl
		FIRFilter.glsl
		RectangularWindow.glsl
		SubtractFilter.glsl
		UpsampleFilter.glsl
		WaterfallFilter.glsl
	)

add_dependencies(scopeprotocols protocolshaders)
