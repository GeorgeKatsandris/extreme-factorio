SRC := $(wildcard src/*.cpp)
OBJ := $(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
TGT=main

all: $(TGT)

main: $(OBJ)
	g++ -o $@ $^

obj/%.o: src/%.cpp
	g++ -c -o $@ $< -Ihead

clean:
	@rm obj/*
	@rm $(TGT)
