#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_MAX_LENGTH 100

typedef struct {
	int overlaps;
	size_t indexes_a[2];
	size_t indexes_b[2];
	char *vec_a;
	char *vec_b ;
} Overlap;

void printnvec(int *vec, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", vec[i]);
	}
	printf("\n");
}

void printcvec(char *vec) {
	for (int i = 0; i < strlen(vec); i++) {
		printf("%c ", vec[i]);
	}
	printf("\n");
	for (int i = 0; i < strlen(vec); i++) {
		printf("%d ", i);
	}
	printf("\n");
}

Overlap get_overlap(char **reads, int i, int j) {
	Overlap overlap;
	overlap.overlaps = 0;

	// prefixo vs. prefixo
	for (int si = 0; si < strlen(reads[i]); si++) {
		int temp_overlaps = 0;
		int temp_si = si;
				
		for (int sj = 0; sj < strlen(reads[j]); sj++) {
			
			if (reads[i][temp_si] == reads[j][sj]) {
				temp_si++;
				temp_overlaps++;

				if (temp_overlaps == strlen(reads[j])) {
					overlap.overlaps = temp_overlaps;
					overlap.indexes_a[0] = 0;
					overlap.indexes_a[1] = strlen(reads[i]) - 1;
					overlap.indexes_b[0] = 0;
					overlap.indexes_b[1] = strlen(reads[j]) - 1;
					overlap.vec_a = reads[i];
					overlap.vec_b = reads[j];
				}
			} else {
				if (temp_overlaps > overlap.overlaps) {
					overlap.overlaps = temp_overlaps;
					overlap.indexes_a[0] = si;
					overlap.indexes_a[1] = temp_si - 1;
					overlap.indexes_b[0] = sj - temp_overlaps;
					overlap.indexes_b[1] = sj - 1;
					overlap.vec_a = reads[i];
					overlap.vec_b = reads[j];
				};
				temp_si = si;
				temp_overlaps = 0;
			}
		}
	}

	return overlap;
}

int main () {
	int n = 0;

	scanf("%d", &n);

	char **reads = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		reads[i] = (char*)malloc(READ_MAX_LENGTH * sizeof(char)); // maybe causes overflow /:
		scanf("%99s", reads[i]);
	}
	
	Overlap higher_overlaps;
	higher_overlaps.overlaps = 0;

	for (int i = 0; i < n; i++) {
		char *readi = reads[i];
		
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			
			char *readj = reads[j];
			int overlaps = 0;

			Overlap overlap = get_overlap(reads, i, j);
			//			printcvec(reads[i]);
			//      printcvec(reads[j]);

			if (overlap.overlaps > higher_overlaps.overlaps) {
				higher_overlaps = overlap;
			}

		}
	}

	printf("sobreposicoes: %d\na: %d-%d\nb: %d-%d\n\n", higher_overlaps.overlaps, higher_overlaps.indexes_a[0], higher_overlaps.indexes_a[1], higher_overlaps.indexes_b[0], higher_overlaps.indexes_b[1]);
	printf("a: \n");
	printcvec(higher_overlaps.vec_a);
	printf("b: \n");
	printcvec(higher_overlaps.vec_b);
	
	return 0;
}
