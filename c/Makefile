# Building/running:

build:
	# -Test
	echo "\n\n\n\n\n\n"
	gcc -o test "polarbear/polarbear.c" "polarbear/draw.c" "test.c" -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image

shared_test:
	gcc "polarbear/polarbear.c" "polarbear/draw.c" test.c -fPIC -shared -o test.so -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image

shared_obj:
	# -Shared Object
	gcc -fPIC -shared -o polarbear.so "polarbear/polarbear.c" "polarbear/draw.c" -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image

btest:
	make build
	make run
	make cleanup

run:
	# -test
	./test

debug_build:
	gcc -o test "polarbear/polarbear.c" "polarbear/draw.c" "test.c" -g -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lSDL2_image

cleanup:
	# -cleanup
	rm polarbear.so
	rm test
