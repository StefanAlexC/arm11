cmake_minimum_required(VERSION 3.6)
project(arm11_37)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_ASSEMBLE
        src/assemble/assemble.c
        src/assemble/assemble.h
        src/assemble/encode.c
        src/assemble/encode.h
        src/assemble/assembleBranch.c
        src/assemble/assembleBranch.h
        src/assemble/assembleSDT.c
        src/assemble/assembleSDT.h
        src/arm11_utils.h
        src/arm11_utils.c)


set(SOURCE_FILES_EMULATE
        src/emulate/emulate.c
        src/emulate/emulate.h
        src/emulate/ARM11.h
        src/emulate/decode/decode.c
        src/emulate/decode/decode.h
        src/emulate/decode/decode_utils.c
        src/emulate/decode/decode_utils.h
        src/emulate/decode/masks.h
        src/emulate/execute/barrel_shifter.c
        src/emulate/execute/barrel_shifter.h
        src/emulate/execute/branch_instruction.c
        src/emulate/execute/branch_instruction.h
        src/emulate/execute/execute.c
        src/emulate/execute/execute.h
        src/emulate/execute/execute_dp.c
        src/emulate/execute/execute_dp.h
        src/emulate/execute/execute_mul.c
        src/emulate/execute/execute_mul.h
        src/emulate/execute/execute_SDT.c
        src/emulate/execute/execute_SDT.h
        src/emulate/execute/execute_utils.c
        src/emulate/execute/execute_utils.h
        src/arm11_utils.c
        src/arm11_utils.h)

add_executable(assemble ${SOURCE_FILES_ASSEMBLE})
add_executable(emulate ${SOURCE_FILES_EMULATE})