main:	
	nasm -f elf sumaDecimal.asm 
	nasm -f elf restaDecimal.asm
	gcc -m32  -c -o calculadora.o calculadora.c
	gcc -m32  sumaDecimal.o  restaDecimal.o calculadora.o  -o calc
clean: 
		rm -f calc *.o