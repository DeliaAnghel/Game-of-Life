build:
	gcc proiect.c task1.c task2.c -o test
run:
	./test ./InputData/data1.in ./out/data1.out
clean:
	rm -f test
