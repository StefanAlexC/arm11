CC = gcc
CFLAGS = -Wall -pedantic -std=c99
SRC = src/
SRC_EXECUTE = src/execute/
SRC_DECODE = src/decode/

#all : assemble emulate
all: emulate

# Build rule for emulate executable
emulate: emulate.o execute decode
	$(CC) $(SRC)emulate.o $(SRC_EXECUTE)execute.o $(SRC_DECODE)decode.o -o emulate

execute: execute.o execute_dp.o execute_mul.o execute_SDT.o branch_instruction.o barrel_shifter.o execute_utils.o
	$(CC) $(FLAGS) $(SRC_EXECUTE)execute_dp.o $(SRC_EXECUTE)execute_mul.o $(SRC_EXECUTE)execute_SDT.o $(SRC_EXECUTE)branch_instruction.o $(SRC_EXECUTE)execute.o $(SRC_EXECUTE)barrel_shifter.o $(SRC_EXECUTE)execute_utils.o

decode: decode.o decode_utils.o
	$(CC) $(FLAGS) $(SRC_DECODE)decode.o $(SRC_DECODE)decode_utils.o -o decode

# Build rules for the .o files
emulate.o: $(SRC)emulate.c $(SRC)emulate.h $(SRC_EXECUTE)execute.c $(SRC_EXECUTE)execute.h $(SRC_DECODE)decode.c $(SRC_DECODE)decode.h
	$(CC) $(FLAGS) $(SRC)emulate.c -c -o $(SRC)emulate.o

execute.o: $(SRC_EXECUTE)execute.c $(SRC_EXECUTE)execute.h $(SRC_EXECUTE)execute_mul.c $(SRC_EXECUTE)execute_mul.h $(SRC_EXECUTE)execute_dp.c $(SRC_EXECUTE)execute_dp.h $(SRC_EXECUTE)execute_SDT.c $(SRC_EXECUTE)execute_SDT.h $(SRC_EXECUTE)branch_instruction.c $(SRC_EXECUTE)branch_instruction.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)execute.c -c -o $(SRC_EXECUTE)execute.o

decode.o: $(SRC_DECODE)decode.c $(SRC_DECODE)decode.h $(SRC_DECODE)decode_utils.c $(SRC_DECODE)decode_utils.h
	$(CC) $(FLAGS) $(SRC_DECODE)decode.c -c -o $(SRC_DECODE)decode.o

execute_mul.o: $(SRC_EXECUTE)execute_mul.c $(SRC_EXECUTE)execute_mul.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)execute_mul.c -c -o $(SRC_EXECUTE)execute_mul.o

execute_dp.o: $(SRC_EXECUTE)execute_dp.c $(SRC_EXECUTE)execute_dp.h $(SRC_EXECUTE)execute_utils.c $(SRC_EXECUTE)execute_utils.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)execute_dp.c -c -o $(SRC_EXECUTE)execute_dp.o

execute_SDT.o: $(SRC_EXECUTE)execute_SDT.c $(SRC_EXECUTE)execute_SDT.h $(SRC_EXECUTE)barrel_shifter.c $(SRC_EXECUTE)barrel_shifter.h $(SRC)ARM11.h $(SRC_DECODE)decode_utils.c $(SRC_DECODE)decode_utils.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)execute_SDT.c -c -o $(SRC_EXECUTE)execute_SDT.o

branch_instruction.o: $(SRC_EXECUTE)branch_instruction.c $(SRC_EXECUTE)branch_instruction.h $(SRC_DECODE)decode_utils.c $(SRC_DECODE)decode_utils.h $(SRC)ARM11.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)branch_instruction.c -c -o $(SRC_EXECUTE)branch_instruction.o

barrel_shifter.o: $(SRC_EXECUTE)barrel_shifter.c $(SRC_EXECUTE)barrel_shifter.h $(SRC_DECODE)decode_utils.c $(SRC_DECODE)decode_utils.h $(SRC_DECODE)masks.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)barrel_shifter.c -c -o $(SRC_EXECUTE)barrel_shifter.o

execute_utils.o: $(SRC_EXECUTE)execute_utils.c $(SRC_EXECUTE)execute_utils.h $(SRC_DECODE)decode_utils.c $(SRC_DECODE)decode_utils.h
	$(CC) $(FLAGS) $(SRC_EXECUTE)execute_utils.c -c -o $(SRC_EXECUTE)execute_utils.o
