# Building/running:

build:
	# -Test
	echo "\n\n\n\n\n\n"
	gcc -o test "polarbear/polarbear.c" "polarbear/draw.c" "polarbear/font.c" "polarbear/surface.c" "test.c" -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

shared_test:
	gcc "polarbear/polarbear.c" "polarbear/draw.c" "polarbear/font.c" "polarbear/surface.c" test.c -fPIC -shared -o test.so -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

shared_obj:
	# -Shared Object
	gcc -fPIC -shared -o polarbear.so "polarbear/inc.c" "polarbear/polarbear.c" "polarbear/draw.c" "polarbear/surface.c" "polarbear/font.c" -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

btest:
	make build
	make run
	make cleanup

run:
	# -test
	./test

debug_build:
	gcc -o test "polarbear/polarbear.c" "polarbear/draw.c" "polarbear/surface.c" "polarbear/font.c" "test.c" -g -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

cleanup:
	# -cleanup
	rm polarbear.so
	rm test
