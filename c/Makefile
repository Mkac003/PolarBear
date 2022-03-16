# Building/running:

build:
	# -Test
	echo "\n\n\n\n\n\n"
	gcc -o test "polarbear.c" "test.c" -Iinclude -lpthread -Llib -lSDL2 -lSDL2main

shared_obj:
	# -Shared Object
	gcc -fPIC -shared -o polarbear.so polarbear.c -Iinclude -lpthread -Llib -lSDL2 -lSDL2main

btest:
	make build
	make run
	make cleanup

run:
	# -test
	./test

debug_build:
	gcc -o test "polarbear.c" "test.c" -g -Iinclude -lpthread -Llib -lSDL2 -lSDL2main

cleanup:
	# -cleanup
	rm polarbear.so
	rm test
