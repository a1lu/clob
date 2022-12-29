target_sources(${PROJECT_NAME}
    PRIVATE
    clob.c
    brz.c
    brz.h
    )

target_include_directories(${PROJECT_NAME} PUBLIC ../include)

if(CLOB_DEBUG_BRZ)
target_sources(${PROJECT_NAME}
    PRIVATE
    debug_brz.c
    debug_brz.h
    )
endif()
