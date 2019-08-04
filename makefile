#SOURCES = $(wildcard Sources/*.cpp)
#OBJECTS = $(patsubst Sources/%.cpp,Objects/%.o,$(SOURCES))
TARGETS = Bin/matrix_generator.out Bin/main.out

.PHONY : generate run gprof clean

START : $(TARGETS)
	@echo "_________for matrix files generation: make generate"
	@echo "_________for matrices multiplication: make run"
	@echo "_________for gprof file generation: make gprof"

Bin/matrix_generator.out : Objects/matrix_generator.o
	mkdir -vp Bin
	g++ $< -o $@

Bin/main.out : Objects/main.o Objects/utility.o
	mkdir -vp Bin
	g++ -O3 -pg $^ -g -o $@

Objects/%.o : Sources/%.cpp
	mkdir -vp Objects
	g++ -O3 -c -pg $< -I./Headers -o $@

generate :
	./Bin/matrix_generator.out

run:
	./Bin/main.out

gprof :
	gprof -b Bin/main.out gmon.out > Data/gprof_analysis.txt


clean :
	rm -rf Bin Objects gmon.out Data/*.txt
