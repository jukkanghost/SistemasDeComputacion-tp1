main:	
	nasm -f elf sumaDecimal.asm 
	nasm -f elf restaDecimal.asm
	nasm -f elf sumaBinaria.asm
	nasm -f elf restaBinaria.asm
	gcc -m32 -c -o calculadora.o calculadora.c
	gcc -m32 sumaDecimal.o restaDecimal.o restaBinaria.o sumaBinaria.o calculadora.o -o calc
clean: 
		rm -f calc *.o