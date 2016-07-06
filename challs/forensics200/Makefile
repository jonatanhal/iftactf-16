build:
	nasm -felf64 forensics200.nasm
	ld -o forensics200 forensics200.o
	rm forensics200.o
	strip forensics200
chall:
	base64 < forensics200 > forensics200.txt
