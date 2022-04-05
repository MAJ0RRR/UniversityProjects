#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct file {
	int size;
	int id;
}file;

file* create_disk(int n);
file* create_pendrive();
void qsort_size(file* disk, int l, int r);
int partition_size(file* disk, int l, int r);
void qsort_id(file* disk, int l, int r);
int partition_id(file* disk, int l, int r);
void swap(file* first, file* second);
void file_transfer(file** pendrive, file* disk, int size,int* copied);

int main(){ 
	file* disk = NULL;
	file* p1 = NULL;
	file* p2 = NULL;
	int n, p,cap1,cap2, copied = 0;
	//INPUT
	scanf("%i %i", &n,&p);
	//CREATING DISK
	disk = create_disk(n);
	//CREATING PENDRIVES
	p1 = create_pendrive();
	p2 = create_pendrive();
	//SORT DISK BY SIZE
	qsort_size(disk, 0, n - 1);
	//TRANSFER FILES TO PENDRIVES
	file_transfer(&p1, disk, p,&copied);
	cap1 = copied;
	file_transfer(&p2, disk, p,&copied);
	cap2 = copied - cap1;
	//SORTING BY ID
	qsort_id(p1, 0, cap1 - 1);
	qsort_id(p2, 0, cap2 - 1);
	//OUTPUT
	printf("%i\n", copied);
	printf("1: ");
	for (int i = 0; i < cap1; i++) {
		printf("%i ", p1[i].id);
	}
	printf("\n");
	printf("2: ");
	for (int i = 0; i < cap2; i++) {
		printf("%i ", p2[i].id);
	}
	//FREE MEMORY
	free(disk);
	free(p1);
	free(p2);
	return 0;
}


file* create_disk(int n) {
	file* disk = (file*)malloc(sizeof(file) * n);
	if (disk == NULL) exit(-1);
	for (int i = 0; i < n; i++) {
		scanf("%i %i", &disk[i].id, &disk[i].size);
	}
	return disk;
}

file* create_pendrive() {
	file* pendrive = (file*)malloc(sizeof(file));
	if (pendrive == NULL) exit(-1);
	return pendrive;
}

void qsort_size(file* disk, int l, int r) {
	if (l < r) {
		int index = partition_size(disk, l, r);
		qsort_size(disk, l, index - 1);
		qsort_size(disk, index + 1, r);
	}
}

int partition_size(file* disk, int l, int r) {
	int pivot = disk[r].size;
	int s = l - 1;
	for (int i = l; i < r; i++) {
		if (disk[i].size < pivot) {
			s++;
			swap(&disk[s], &disk[i]);
		}
	}
	swap(&disk[s + 1], &disk[r]);
	return (s + 1);
}

void swap(file* first, file* second) {
	file temp = *first;
	*first = *second;
	*second = temp;
}

void file_transfer(file** pendrive,file* disk,int size,int* copied) {
	int index = 0;
	int current_cap = 1;
	while (size > 0) {
		if ((size - disk[*copied].size) >= 0) {
			(*pendrive)[index].id = disk[*copied].id;
			(*pendrive)[index].size = disk[*copied].size;
			size -= disk[*copied].size;
			*copied += 1;
			index++;
			if (current_cap == index) {
				current_cap *= 2;
				*pendrive = (file*)realloc(*pendrive, (current_cap * sizeof(file))+1);
				if (pendrive == NULL)
					exit(-1);
			}
	}
		else break;
	}
}

void qsort_id(file* disk, int l, int r) {
	if (l < r) {
		int index = partition_id(disk, l, r);
		qsort_id(disk, l, index - 1);
		qsort_id(disk, index + 1, r);
	}
}

int partition_id(file* disk, int l, int r) {
	int pivot = disk[r].id;
	int s = l - 1;
	for (int i = l; i < r; i++) {
		if (disk[i].id > pivot) {
			s++;
			swap(&disk[s], &disk[i]);
		}
	}
	swap(&disk[s + 1], &disk[r]);
	return (s + 1);
}