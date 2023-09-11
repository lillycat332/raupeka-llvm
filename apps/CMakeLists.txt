add_executable(lrc main.cpp)
target_compile_features(lrc PRIVATE cxx_std_20)

install(TARGETS lrc DESTINATION bin)

target_link_libraries(lrc ${llvm_libs})
