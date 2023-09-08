set(HEADER_LIST "${Raupeka_SOURCE_DIR}/include/lrc_lib/lib.hpp")

add_library(lrc_lib STATIC
	parser.cpp
)

target_link_libraries(lrc_lib ${llvm_libs})

# All users of this library will need at least C++11
target_compile_features(lrc_lib PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST})
