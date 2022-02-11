cmake_minimum_required(VERSION 2.8.11)
Project(modshot)

## Setup options ##

# Note this option only adds steamshim_child into oneshot.
# It's outside this repo's responsibility to compile the parent.
# Contact rkevin for details.
option(STEAM "Build for Steam" OFF)
option(DEBUG "Debug mode" OFF)

## Misc setup ##

set(CMAKE_INCLUDE_CURRENT_DIR ON)

## Setup main source ##

set(SRC_AUDIO_HEADER_PATH src/audio/headers)
set(SRC_GRAPHICS_HEADER_PATH src/graphics/headers)
set(SRC_OPENGL_HEADER_PATH src/opengl/headers)
set(SRC_INPUT_HEADER_PATH src/input/headers)
set(SRC_FS_HEADER_PATH src/filesystem/headers)

set(SRC_AUDIO_SOURCE_PATH src/audio/source)
set(SRC_GRAPHICS_SOURCE_PATH src/graphics/source)
set(SRC_OPENGL_SOURCE_PATH src/opengl/source)
set(SRC_INPUT_SOURCE_PATH src/input/source)
set(SRC_FS_SOURCE_PATH src/filesystem/source)

set(SRC_STEAM_PATH src/steam)

set(MAIN_HEADERS
	# Audio
	${SRC_AUDIO_HEADER_PATH}/audio.h
	${SRC_AUDIO_HEADER_PATH}/al-util.h
	${SRC_AUDIO_HEADER_PATH}/aldatasource.h
	${SRC_AUDIO_HEADER_PATH}/alstream.h
	${SRC_AUDIO_HEADER_PATH}/audiostream.h
	${SRC_AUDIO_HEADER_PATH}/audiochannels.h
	${SRC_AUDIO_HEADER_PATH}/soundemitter.h

	# Graphics
	${SRC_GRAPHICS_HEADER_PATH}/bitmap.h
	${SRC_GRAPHICS_HEADER_PATH}/graphics.h
	${SRC_GRAPHICS_HEADER_PATH}/disposable.h
	${SRC_GRAPHICS_HEADER_PATH}/font.h
	${SRC_GRAPHICS_HEADER_PATH}/sprite.h
	${SRC_GRAPHICS_HEADER_PATH}/scene.h
	${SRC_GRAPHICS_HEADER_PATH}/tilemap.h
	${SRC_GRAPHICS_HEADER_PATH}/tilemap-common.h
	${SRC_GRAPHICS_HEADER_PATH}/tileatlas.h
	${SRC_GRAPHICS_HEADER_PATH}/flashable.h

	# OpenGL
	${SRC_OPENGL_HEADER_PATH}/glstate.h
	${SRC_OPENGL_HEADER_PATH}/gl-debug.h
	${SRC_OPENGL_HEADER_PATH}/gl-util.h
	${SRC_OPENGL_HEADER_PATH}/gl-fun.h
	${SRC_OPENGL_HEADER_PATH}/gl-meta.h
	${SRC_OPENGL_HEADER_PATH}/quadarray.h
	${SRC_OPENGL_HEADER_PATH}/plane.h
	${SRC_OPENGL_HEADER_PATH}/shader.h
	${SRC_OPENGL_HEADER_PATH}/quad.h
	${SRC_OPENGL_HEADER_PATH}/texpool.h
	${SRC_OPENGL_HEADER_PATH}/tilequad.h
	${SRC_OPENGL_HEADER_PATH}/vertex.h
	${SRC_OPENGL_HEADER_PATH}/window.h
	${SRC_OPENGL_HEADER_PATH}/sdl-util.h
	${SRC_OPENGL_HEADER_PATH}/viewport.h
	${SRC_OPENGL_HEADER_PATH}/table.h
	${SRC_OPENGL_HEADER_PATH}/transform.h

	# Input
	${SRC_INPUT_HEADER_PATH}/input.h
	${SRC_INPUT_HEADER_PATH}/keybindings.h

	# Filesystem
	${SRC_FS_HEADER_PATH}/filesystem.h
	${SRC_FS_HEADER_PATH}/rgssad.h

	src/binding.h
	src/etc.h
	src/etc-internal.h
	src/eventthread.h
	src/serializable.h
	src/global-ibo.h
	src/exception.h
	src/serial-util.h
	src/intrulist.h
	src/binding.h
	src/util.h
	src/config.h
	src/settingsmenu.h
	src/sharedstate.h
	src/boost-hash.h
	src/debugwriter.h
	src/oneshot.h
	src/pipe.h
	chromasdk/RzChromaSDKDefines.h
	chromasdk/RzChromaSDKTypes.h
	chromasdk/RzErrors.h
	chromasdk/ChromaApi.h
	src/i18n.h
	src/otherview-message.h
	src/crash-handler.h
)

set(MAIN_SOURCE
	# Audio
	${SRC_AUDIO_SOURCE_PATH}/alstream.cpp
	${SRC_AUDIO_SOURCE_PATH}/audiostream.cpp
	${SRC_AUDIO_SOURCE_PATH}/audiochannels.cpp
	${SRC_AUDIO_SOURCE_PATH}/audio.cpp
	${SRC_AUDIO_SOURCE_PATH}/soundemitter.cpp
	${SRC_AUDIO_SOURCE_PATH}/sdlsoundsource.cpp
	${SRC_AUDIO_SOURCE_PATH}/vorbissource.cpp

	# Graphics
	${SRC_GRAPHICS_SOURCE_PATH}/autotiles.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/bitmap.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/graphics.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/font.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/sprite.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/scene.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/tilemap.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/tileatlas.cpp

	# OpenGL
	${SRC_OPENGL_SOURCE_PATH}/glstate.cpp
	${SRC_OPENGL_SOURCE_PATH}/gl-debug.cpp
	${SRC_OPENGL_SOURCE_PATH}/gl-fun.cpp
	${SRC_OPENGL_SOURCE_PATH}/gl-meta.cpp
	${SRC_OPENGL_SOURCE_PATH}/plane.cpp
	${SRC_OPENGL_SOURCE_PATH}/shader.cpp
	${SRC_OPENGL_SOURCE_PATH}/texpool.cpp
	${SRC_OPENGL_SOURCE_PATH}/vertex.cpp
	${SRC_OPENGL_SOURCE_PATH}/tilequad.cpp
	${SRC_OPENGL_SOURCE_PATH}/window.cpp
	${SRC_OPENGL_SOURCE_PATH}/screen.cpp
	${SRC_OPENGL_SOURCE_PATH}/viewport.cpp
	${SRC_OPENGL_SOURCE_PATH}/table.cpp

	# Input
	${SRC_INPUT_SOURCE_PATH}/input.cpp
	${SRC_INPUT_SOURCE_PATH}/keybindings.cpp

	# Filesystem
	${SRC_FS_SOURCE_PATH}/filesystem.cpp
	${SRC_FS_SOURCE_PATH}/rgssad.cpp

	src/main.cpp
	src/eventthread.cpp
	src/etc.cpp
	src/config.cpp
	src/settingsmenu.cpp
	src/sharedstate.cpp
	src/oneshot.cpp
	src/i18n.cpp
	src/otherview-message.cpp
	src/crash-handler.cpp
)

if(WIN32)
	list(APPEND MAIN_SOURCE assets/resources.rc)
	list(APPEND DEFINES UNICODE)
	list(APPEND PLATFORM_LIBRARIES Secur32 Shlwapi)
	include_directories(
		${CMAKE_CURRENT_BINARY_DIR}/windows
	)
elseif(APPLE)
	list(APPEND MAIN_HEADERS src/mac-desktop.h)
	list(APPEND MAIN_SOURCE src/mac-desktop.mm)
else()
	find_package(PkgConfig REQUIRED)
	if(NOT MSYS2)
        pkg_check_modules(LINUXPKGS REQUIRED gtk+-2.0 libxfconf-0)
    endif()
	include_directories(${LINUXPKGS_INCLUDE_DIRS})
	add_compile_options(${LINUXPKGS_CFLAGS_OTHER} -g)
	list(APPEND PLATFORM_LIBRARIES ${LINUXPKGS_LDFLAGS})
	list(APPEND MAIN_SOURCE src/xdg-user-dir-lookup.c)
	list(APPEND MAIN_HEADERS src/xdg-user-dir-lookup.h)
endif()

if (STEAM)
	list(APPEND MAIN_HEADERS
		${SRC_STEAM_PATH}/steam.h
		steamshim/steamshim_child.h
	)
	list(APPEND MAIN_SOURCE
		${SRC_STEAM_PATH}/steam.cpp
		steamshim/steamshim_child.c
	)
	list(APPEND DEFINES
		STEAM
	)
endif()

source_group("MKXP Source" FILES ${MAIN_SOURCE} ${MAIN_HEADERS})

## Setup embedded source ##

set(EMBEDDED_INPUT
	shader/common.h
	shader/transSimple.frag
	shader/trans.frag
	shader/hue.frag
	shader/sprite.frag
	shader/plane.frag
	shader/gray.frag
	shader/bitmapBlit.frag
	shader/flatColor.frag
	shader/simple.frag
	shader/simpleColor.frag
	shader/simpleAlpha.frag
	shader/simpleAlphaUni.frag
	shader/flashMap.frag
	shader/obscured.frag
	shader/minimal.vert
	shader/simple.vert
	shader/simpleColor.vert
	shader/sprite.vert
	shader/tilemap.vert
	shader/blur.frag
	shader/blurH.vert
	shader/blurV.vert
	shader/mask.frag
	shader/mask.vert
	shader/crt.frag
	shader/crt_sprite.frag
	shader/simpleMatrix.vert
	shader/chronos.frag
	shader/cubic_lens.frag
	shader/water.frag
	shader/zoom.vert
	assets/icon.png
	assets/gamecontrollerdb.txt
)

if (RGSS2)
	list(APPEND DEFINES
		RGSS2
	)
endif()

if (MSVC)
	list(APPEND DEFINES
		_CRT_SECURE_NO_WARNINGS
		NOMINMAX
	)
endif()

## Process Embeddeds ##

find_program(XXD_EXE xxd
	DOC "Location of the xxd executable"
)

macro(ProcessWithXXD outvar inputfile outdir)
	get_filename_component(basefile ${inputfile} NAME)
	set(outputfile ${outdir}/${basefile}.xxd)
	set_source_files_properties(${outputfile} PROPERTIES HEADER_ONLY TRUE)
	add_custom_command(
		OUTPUT ${outputfile}
		COMMAND ${XXD_EXE} -i ${inputfile} ${outputfile}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${inputfile}
		COMMENT "Generating XXD for ${inputfile}"
	)
	list(APPEND ${outvar}
		${outputfile}
	)
endmacro()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/xxdhack)
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}/xxdhack
)

foreach(item ${EMBEDDED_INPUT})
	ProcessWithXXD(EMBEDDED_SOURCE ${item} ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

source_group("Embedded Source" FILES ${EMBEDDED_INPUT} ${EMBEDDED_SOURCE})

## Setup binding source ##

list(APPEND DEFINES
	BINDING_MRI
)
set(BINDING_HEADERS
	binding-mri/binding-util.h
	binding-mri/binding-types.h
	binding-mri/serializable-binding.h
	binding-mri/disposable-binding.h
	binding-mri/sceneelement-binding.h
	binding-mri/viewportelement-binding.h
	binding-mri/flashable-binding.h
)
set(BINDING_SOURCE
	binding-mri/binding-mri.cpp
	binding-mri/binding-util.cpp
	binding-mri/table-binding.cpp
	binding-mri/etc-binding.cpp
	binding-mri/bitmap-binding.cpp
	binding-mri/font-binding.cpp
	binding-mri/graphics-binding.cpp
	binding-mri/input-binding.cpp
	binding-mri/sprite-binding.cpp
	binding-mri/viewport-binding.cpp
	binding-mri/plane-binding.cpp
	binding-mri/window-binding.cpp
	binding-mri/tilemap-binding.cpp
	binding-mri/audio-binding.cpp
	binding-mri/module_rpg.cpp
	binding-mri/filesystem-binding.cpp
	binding-mri/oneshot-binding.cpp
	binding-mri/steam-binding.cpp
	binding-mri/wallpaper-binding.cpp
	binding-mri/journal-binding.cpp
	binding-mri/chroma-binding.cpp
	binding-mri/niko-binding.cpp
	binding-mri/modshot-window-binding.cpp
	binding-mri/aleffect-binding.cpp
	binding-mri/otherview-binding.cpp
)

source_group("Binding Source" FILES ${BINDING_SOURCE} ${BINDING_HEADERS})

## Setup main executable ##

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
	${MAIN_HEADERS}
	${MAIN_SOURCE}
	${BINDING_HEADERS}
	${BINDING_SOURCE}
	${EMBEDDED_SOURCE}
)
if(WIN32)
target_link_libraries(${PROJECT_NAME}
	wsock32 ws2_32 winmm.lib

	${CMAKE_CURRENT_BINARY_DIR}/exlibs/ruby_dest/ucrt64/lib/libx64-ucrt-ruby310.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_ttf_dest/lib/libSDL2_ttf.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_image_dest/lib/libSDL2_image.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl_sound_dest/lib/libSDL2_sound.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_dest/lib/libSDL2.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_dest/lib/libSDL2main.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_dest/lib/libSDL2_test.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/zlib_dest/lib/libzlib.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/pixman_dest/lib/libpixman-1.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/physfs_dest/lib/libphysfs.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/vorbis_dest/lib/libvorbis.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/vorbis_dest/lib/libvorbisfile.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/vorbis_dest/lib/libvorbisenc.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/sigcpp_dest/lib/libsigc-2.0.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/openal_dest/lib/libOpenAL32.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/libpng_dest/lib/libpng.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/libogg_dest/lib/libogg.dll.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/libnsgif_dest/lib/libnsgif.dll.a

	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_atomic-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_chrono-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_container-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_context-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_contract-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_coroutine-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_date_time-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_exception-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_filesystem-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_graph-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_iostreams-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_json-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_locale-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_log-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_log_setup-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_c99-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_c99f-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_c99l-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_tr1-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_tr1f-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_tr1l-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_nowide-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_program_options-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_random-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_regex-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_serialization-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_system-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_thread-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_timer-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_type_erasure-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_wave-mgw11-mt-x64-1_78.a
	${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_wserialization-mgw11-mt-x64-1_78.a

	${PLATFORM_LIBRARIES}
)
else()
target_link_libraries(${PROJECT_NAME}    
    -lpthread
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/ruby_dest/usr/local/lib/libruby.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/zlib_dest/lib/libz.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/pixman_dest/lib/libpixman-1.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/openal_dest/lib/libopenal.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_dest/lib/libSDL2.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_ttf_dest/lib/libSDL2_ttf.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl2_image_dest/lib/libSDL2_image.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/sdl_sound_dest/lib/libSDL2_sound.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/physfs_dest/lib/libphysfs.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/sigcpp_dest/lib/libsigc-2.0.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/vorbis_dest/lib/libvorbis.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/vorbis_dest/lib/libvorbisenc.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/vorbis_dest/lib/libvorbisfile.so
    
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_atomic.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_chrono.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_container.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_context.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_contract.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_coroutine.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_date_time.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_exception.a
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_filesystem.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_graph.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_iostreams.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_json.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_locale.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_log.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_log_setup.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_c99.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_c99f.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_c99l.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_tr1.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_tr1f.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_math_tr1l.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_nowide.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_prg_exec_monitor.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_program_options.so
    # ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_python27.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_random.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_regex.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_serialization.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_test_exec_monitor.a
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_thread.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_timer.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_type_erasure.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_unit_test_framework.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_wave.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_wserialization.so
    ${CMAKE_CURRENT_BINARY_DIR}/exlibs/boost_dest/lib/libboost_system.so
    
    ${PLATFORM_LIBRARIES}
)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFINES})
target_include_directories(${PROJECT_NAME} PRIVATE src ${SRC_STEAM_PATH} ${SRC_AUDIO_HEADER_PATH} ${SRC_GRAPHICS_HEADER_PATH} ${SRC_OPENGL_HEADER_PATH} ${SRC_INPUT_HEADER_PATH} ${SRC_FS_HEADER_PATH})

target_include_directories(${PROJECT_NAME} PRIVATE 
	build/exlibs/boost_dest/include/boost-1_78
	build/bzip2_dest/include
	build/exlibs/libnsgif_dest/include
	build/exlibs/sigcpp_dest/include/sigc++-2.0
	build/exlibs/libsigcplusplus-2.10.7/libsigcplusplus-2.10.7
	build/exlibs/openal-soft/include/AL
	build/exlibs/sdl2_dest/include
	build/exlibs/sdl2_dest/include/SDL2
	build/exlibs/vorbis_dest/include
	build/exlibs/libogg_dest/include
	build/exlibs/sdl2_image_dest/include/
	build/exlibs/sdl2_image_dest/include/SDL2
	build/exlibs/sdl2_ttf_dest/include/
	build/exlibs/sdl2_ttf_dest/include/SDL2
	build/exlibs/sdl_sound_dest/include/
	build/exlibs/sdl_sound_dest/include/SDL2
	build/exlibs/pixman_dest/include/pixman-1
	build/exlibs/physfs_dest/include
	build/exlibs/ruby_dest/ucrt64/include/ruby-3.1.0
	build/exlibs/ruby_dest/ucrt64/include/ruby-3.1.0/x64-mingw-ucrt
	build/exlibs/ruby_dest/usr/local/include/ruby-3.1.0
	build/exlibs/ruby_dest/usr/local/include/ruby-3.1.0/x86_64-linux
)

if(WIN32 AND NOT STEAM)
	add_executable("oneshot-shim" WIN32
	"${CMAKE_SOURCE_DIR}/windows/shim.c"
	"${CMAKE_SOURCE_DIR}/assets/resources.rc")
endif()

#add_subdirectory(scripts)
