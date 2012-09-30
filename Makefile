OBJS = main.o lib/star.o lib/galaxy.o
CXXFLAGS += `gosu-config --cxxflags`
OPENFLAGS = -fopenmp
LIBS = `gosu-config --libs`

my_game: $(OBJS) libgosu.a
	g++ -fopenmp main.cpp libgosu.a `gosu-config --libs` -o my_game

# my_game: $(OBJS) libgosu.a
# 	g++ $(OPENFLAGS) $(OBJS) libgosu.a $(LIBS) -o my_game -fopenmp

# g++ -fopenmp main.cpp

# g++ -fopenmp openmp.cpp -o openmp

# g++ -fopenmp main.cpp libgosu.a `gosu-config --libs` -o my_game