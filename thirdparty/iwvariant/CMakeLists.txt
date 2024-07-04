add_library(iwvariant
    iwvariant.cpp
    iwvariant.h
)

target_include_directories(iwvariant PUBLIC
    ${PROJECT_SOURCE_DIR}/thirdparty/iwstring
)

target_link_libraries(iwvariant PRIVATE
    iwstring
)
