add_executable(lrc main.cpp)
target_compile_features(lrc PRIVATE cxx_std_20)

# use lrc_lib headers from ../include/lib
target_include_directories(lrc PRIVATE ../include/lib)

install(TARGETS lrc DESTINATION bin)

# link against LLVM and Boost
target_link_libraries(lrc ${llvm_libs} ${Boost_LIBRARIES})
# Link against liblrc
target_link_libraries(lrc lrc_lib)