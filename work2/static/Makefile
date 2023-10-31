a.out: main1.c
	gcc -rdynamic main1.c -ldl
../sub/libtest.so: ../sub/calc.c
	gcc -shared -o ../sub/libtest.so ../sub/calc.c
clean:
	rm -rf a.out