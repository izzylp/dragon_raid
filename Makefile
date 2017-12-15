.PHONY: all src test clean

test=./test
src=./src

test_file=${test}/main
test_file_1=${test}/Player
test_file_2=${test}/Monster
test_file_3=${test}/Shot
test_file_4=${test}/Life
test_file_5=${test}/Score
test_file_6=${test}/Wall

src_file=${src}/main_7
src_additional_files=${src}/Game.cpp ${src}/Player.cpp ${src}/Monster.cpp ${src}/Shot.cpp ${src}/Object.cpp ${src}/Font.cpp ${src}/Map.cpp ${src}/Controller.cpp ${src}/Score.cpp ${src}/Life.cpp ${src}/Wall.cpp ${src}/CircularArray.cpp

src_flags=-std=c++11 -W -O3
src_linker_flags=-lsfml-graphics -lsfml-window -lsfml-system -lboost_system -lboost_date_time -lboost_thread
test_flags=-std=c++11 -W -O3
test_linker_flags=-lsfml-graphics -lsfml-window -lsfml-system -lboost_system -lboost_date_time -lboost_thread

all:
	g++ ${src_flags} -o ${src_file} ${src_file}.cpp ${src_additional_files} ${src_linker_flags}
	g++ ${test_flags} -o ${test_file} ${test_file}.cpp ${src_additional_files} ${test_linker_flags}

src:
	g++ ${src_flags} -o ${src_file} ${src_file}.cpp ${src_additional_files} ${src_linker_flags}

test_main:
	g++ -o ${test_file}.o -c ${test_file}.cpp

test:
	g++ ${test_file}.o ${test_file_1}.cpp ${test_file_2}.cpp ${test_file_3}.cpp ${test_file_4}.cpp ${test_file_5}.cpp ${test_file_6}.cpp ${src_additional_files} -o ${test_file} ${test_flags} ${test_linker_flags}

run_src:
	${src_file}

run_test:
	${test_file}

clean:
	rm ${test_file} ${src_file}
