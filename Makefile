all: compile link

compile: 
	g++ -c ShootingGame.cpp -I"C:\Users\abhis\OneDrive\Documents\libraries\SFML-2.6.2\include" -DSFML_STATIC
	g++ -c Game.cpp -I"C:\Users\abhis\OneDrive\Documents\libraries\SFML-2.6.2\include" -DSFML_STATIC

link:
	g++ ShootingGame.o Game.o -o main -L"C:\Users\abhis\OneDrive\Documents\libraries\SFML-2.6.2\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-graphics -lsfml-window -lsfml-system

run:
	./main.exe

clear:
	rm -f main *.o