
include_directories(include)

add_executable(SimC
        ast.c
        lexer.c
        main.c
        pp.c
        stack.c
        visitor.c
        ${PROJECT_SOURCE_DIR}/include/ast.h
        ${PROJECT_SOURCE_DIR}/include/lexer.h
        ${PROJECT_SOURCE_DIR}/include/pp.h
        ${PROJECT_SOURCE_DIR}/include/stack.h
        ${PROJECT_SOURCE_DIR}/include/utils.h
        ${PROJECT_SOURCE_DIR}/include/visitor.h)
