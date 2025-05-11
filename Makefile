build:
	gcc proiect.c task1.c task2.c task3.c -o test
run:
	./test ./InputData/data11.in ./out/data11.out
clean:
	rm -f test
