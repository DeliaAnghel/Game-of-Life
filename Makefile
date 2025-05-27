build:
	gcc proiect.c task1.c task2.c task3.c task4.c -o test
run:
	./test ./InputData/data16.in ./out/data16.out
clean:
	rm -f test
