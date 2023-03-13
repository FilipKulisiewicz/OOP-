# opcje kompilacji

CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17
LIBS= -lglut -lGLU -lGL

__start__: Flight
	./Flight

Flight: obj obj/main.o obj/Scena.o obj/Dron.o obj/Dron2.o obj/UkladW.o obj/PlaskowyzProsty.o obj/PlaskowyzRand.o obj/Wzgorze.o obj/Graniastoslup6.o obj/Prostopadloscian.o obj/Powierzchnia.o obj/Macierz.o obj/Wektor.o obj/OpenGL_API.o
	g++ -Wall -pedantic -o Flight obj/main.o obj/Scena.o obj/Dron.o obj/Dron2.o obj/UkladW.o obj/PlaskowyzProsty.o obj/PlaskowyzRand.o obj/Wzgorze.o obj/Prostopadloscian.o obj/Graniastoslup6.o obj/Powierzchnia.o\
						obj/Macierz.o obj/Wektor.o obj/OpenGL_API.o ${LIBS} -lpthread

obj:
	mkdir obj

obj/main.o: src/main.cpp inc/InterfejsDrona.hh inc/InterfejsElementuKrajobrazu.hh inc/InterfejsRysowanie.hh 
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh 
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh 
	g++ -c ${CXXFLAGS} -o obj/Dron.o src/Dron.cpp

obj/Dron2.o: src/Dron2.cpp inc/Dron2.hh 
	g++ -c ${CXXFLAGS} -o obj/Dron2.o src/Dron2.cpp

#obj/Dron3.o: src/Dron3.cpp inc/Dron3.hh 
#	g++ -c ${CXXFLAGS} -o obj/Dron3.o src/Dron3.cpp

obj/PlaskowyzProsty.o: src/PlaskowyzProsty.cpp inc/PlaskowyzProsty.hh 
	g++ -c ${CXXFLAGS} -o obj/PlaskowyzProsty.o src/PlaskowyzProsty.cpp

obj/PlaskowyzRand.o: src/PlaskowyzRand.cpp inc/PlaskowyzRand.hh 
	g++ -c ${CXXFLAGS} -o obj/PlaskowyzRand.o src/PlaskowyzRand.cpp

obj/Wzgorze.o: src/Wzgorze.cpp inc/Wzgorze.hh 
	g++ -c ${CXXFLAGS} -o obj/Wzgorze.o src/Wzgorze.cpp

obj/Graniastoslup6.o: src/Graniastoslup6.cpp inc/Graniastoslup6.hh 
	g++ -c ${CXXFLAGS} -o obj/Graniastoslup6.o src/Graniastoslup6.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh 
	g++ -c ${CXXFLAGS} -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/Powierzchnia.o: src/Powierzchnia.cpp inc/Powierzchnia.hh 
	g++ -c ${CXXFLAGS} -o obj/Powierzchnia.o src/Powierzchnia.cpp

obj/UkladW.o: src/UkladW.cpp inc/UkladW.hh 
	g++ -c ${CXXFLAGS} -o obj/UkladW.o src/UkladW.cpp

obj/Macierz.o: src/Macierz.cpp inc/Macierz.hh 
	g++ -c ${CXXFLAGS} -o obj/Macierz.o src/Macierz.cpp

obj/Wektor.o: src/Wektor.cpp inc/Wektor.hh 
	g++ -c ${CXXFLAGS} -o obj/Wektor.o src/Wektor.cpp

obj/OpenGL_API.o: src/OpenGL_API.cpp inc/OpenGL_API.hh
	g++ -c ${CXXFLAGS} -o obj/OpenGL_API.o src/OpenGL_API.cpp ${LIBS}

clear:
	rm -f obj/*.o obroty_2D
	rmdir obj
	rm Flight
