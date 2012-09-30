OBJS = main.o lib/star.o lib/galaxy.o
CXXFLAGS += `gosu-config --cxxflags `
LIBS = `gosu-config --libs `

my_game: $(OBJS) libgosu.a
	g++ -o my_game $(OBJS) libgosu.a $(LIBS)