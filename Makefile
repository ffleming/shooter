CPP=c++
CFLAGS=-std=c++11 -g3
LIBS=
GLFW_CFLAGS=`pkg-config --cflags glfw3,assimp,glew`
GLFW_LIBS= `pkg-config --static --libs glfw3,assimp,glew`
BUILDDIR=build
SOURCEDIR=src

all: object.o player.o enemy.o star.o player_bullet.o board.o main.o game.o mesh.o shader.o
	c++ $(GLFW_CFLAGS) $(CFLAGS) -o shooter $(BUILDDIR)/main.o $(BUILDDIR)/mesh.o $(BUILDDIR)/game.o $(BUILDDIR)/object.o $(BUILDDIR)/player.o $(BUILDDIR)/enemy.o $(BUILDDIR)/star.o $(BUILDDIR)/board.o $(BUILDDIR)/player_bullet.o $(BUILDDIR)/shader.o $(GLFW_LIBS) $(LIBS)

shader.o:
	c++ $(CFLAGS) -w -c -o $(BUILDDIR)/shader.o $(SOURCEDIR)/common/shader.cpp $(LIBS)

mesh.o:
	c++ $(CFLAGS) -w -c -o $(BUILDDIR)/mesh.o $(SOURCEDIR)/common/mesh.cpp $(LIBS)

object.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/object.o $(SOURCEDIR)/object.cpp $(LIBS)

player.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/player.o $(SOURCEDIR)/player.cpp $(LIBS)

enemy.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/enemy.o $(SOURCEDIR)/enemy.cpp $(LIBS)

star.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/star.o $(SOURCEDIR)/star.cpp $(LIBS)

player_bullet.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/player_bullet.o $(SOURCEDIR)/player_bullet.cpp $(LIBS)

board.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/board.o $(SOURCEDIR)/board.cpp $(LIBS)

game.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/game.o $(SOURCEDIR)/game.cpp $(LIBS)

main.o:
	c++ $(CFLAGS) -c -o $(BUILDDIR)/main.o $(SOURCEDIR)/main.cpp $(LIBS)

clean:
	-rm $(BULDDIR)/*.o shooter
