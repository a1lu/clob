add_executable(clob-cli
    clob_cli.c
    )

target_link_libraries(clob-cli PRIVATE clob:clob)
