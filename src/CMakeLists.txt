set(HEADER_LIST "${Raupeka_SOURCE_DIR}/include/lrc_lib/lib.hpp")

add_library(lrc_lib STATIC
	parser.cpp

	# parser.hpp
)

set_target_properties(${TARGET_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

target_compile_features(lrc_lib PUBLIC cxx_std_20)
target_compile_features(lrc_lib PRIVATE cxx_std_20)

target_compile_options(lrc_lib PRIVATE -std=c++20 -stdlib=libc++ -fno-exceptions -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Wl,-search_paths_first -Wl,-headerpad_max_install_names)

target_link_libraries(lrc_lib ${llvm_libs})

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST})
