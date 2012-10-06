gosu c++ tutorial:
https://github.com/jlnr/gosu/wiki/C---Tutorial

compile with:
g++ -fopenmp -02 main.cpp libgosu.a `gosu-config --libs` -o my_game


to profile, make loop stop after n rounds

g++ -fopenmp -pg main.cpp libgosu.a `gosu-config --libs` -o my_game
./my_game
gprof my_game > gprof.output
