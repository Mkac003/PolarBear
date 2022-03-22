from polarbear import cload

lib = cload.load("test.so")

lib.call("main", types=["int", "pint"], 123, 132)
