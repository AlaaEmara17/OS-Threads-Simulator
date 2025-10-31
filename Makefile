all: mergesort
mergesort: Merge_sort.c
	chmod +x Merge_sort.c
	gcc Merge_sort.c -o mergesort

mult: Matrix_Multiplication.c
	chmod +x Matrix_Multiplication.c
	gcc Matrix_Multiplication.c -o mult

#run: mergesort
#	./mergesort

#run: mult
#	./mult

clear:
	rm -f mergesort
	rm -f mult