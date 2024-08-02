cmake_minimum_required(VERSION 3.28)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(commands)
include_directories(compile)
include_directories(data_structures)
include_directories(errors)
include_directories(precompile)
include_directories(utils)

add_executable(src
        commands/addressing.c
        commands/addressing.h
        commands/directives.c
        commands/directives.h
        commands/encoding.c
        commands/encoding.h
        commands/instructions.c
        commands/instructions.h
        commands/opcodes.c
        commands/opcodes.h
        commands/registers.c
        commands/registers.h
        compile/segments.c
        compile/segments.h
        compile/symbols.c
        compile/symbols.h
        compile/transactions.c
        compile/transactions.h
        data_structures/table.c
        data_structures/table.h
        errors/errors.c
        errors/errors.h
        errors/errors_handling.c
        errors/errors_handling.h
        precompile/comments.c
        precompile/comments.h
        precompile/macros.c
        precompile/macros.h
        utils/args_utils.c
        utils/args_utils.h
        utils/array_utils.c
        utils/array_utils.h
        utils/file_utils.c
        utils/file_utils.h
        utils/strings_utils.c
        utils/strings_utils.h
        assembler.c
        assembler.h)
