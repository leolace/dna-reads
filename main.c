#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_MAX_LENGTH 10000

typedef struct {
	int overlaps_count;
	size_t indexes_a[2];
	size_t indexes_b[2];
	char *read_a;
	char *read_b;
	size_t index_a;
	size_t index_b;
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

char* merge_overlap(Overlap overlap) {
	char *merged_string = (char*)malloc(sizeof(char) * READ_MAX_LENGTH);
	strcpy(merged_string, overlap.read_a);

	if (overlap.overlaps_count == strlen(overlap.read_b)) return merged_string;
	// printf("overlaps count: %d\n",overlap.overlaps_count);
	if (overlap.overlaps_count == 0) return strcat(merged_string, overlap.read_b);

	for (int i = overlap.indexes_b[0]; i < strlen(overlap.read_b); i++) {
		//		merged_string[i] = merged_string[i + 1];
		merged_string[i + overlap.indexes_a[0]] = overlap.read_b[i];
	}

	printf("string: %s\n", merged_string);

	return merged_string;
}

Overlap get_overlap(char **reads, int i, int j) {
	Overlap overlap;
	overlap.overlaps_count = 0;

	// prefixo vs. prefixo
	for (int si = 0; si < strlen(reads[i]); si++) {
		int temp_overlaps = 0;
		int temp_si = si;
				
		for (int sj = 0; sj < strlen(reads[j]); sj++) {
			
			if (reads[i][temp_si] == reads[j][sj]) {
				temp_si++;
				temp_overlaps++;

				if (temp_overlaps == strlen(reads[j])) {
					overlap.overlaps_count = temp_overlaps;
					overlap.indexes_a[0] = 0;
					overlap.indexes_a[1] = strlen(reads[i]) - 1;
					overlap.indexes_b[0] = 0;
					overlap.indexes_b[1] = strlen(reads[j]) - 1;
					overlap.read_a = reads[i];
					overlap.read_b = reads[j];
					overlap.index_a = i;
					overlap.index_b = j;
				}
			} else {
				if (temp_overlaps > overlap.overlaps_count) {
					overlap.overlaps_count = temp_overlaps;
					overlap.indexes_a[0] = si;
					overlap.indexes_a[1] = temp_si - 1;
					overlap.indexes_b[0] = sj - temp_overlaps;
					overlap.indexes_b[1] = sj - 1;
					overlap.read_a = reads[i];
					overlap.read_b = reads[j];
					overlap.index_a = i;
					overlap.index_b = j;
				};
				temp_si = si;
				temp_overlaps = 0;
			}
		}
	}

	return overlap;
}

char* overlapit(char **reads, int *size) {
	if (*size == 1) return reads[0];
	Overlap higher_overlaps;
	higher_overlaps.overlaps_count = 0;

	for (int i = 0; i < *size; i++) {
		for (int j = 0; j < *size; j++) {
			if (i == j) continue;
			int overlaps = 0;

			Overlap overlap = get_overlap(reads, i, j);

			if (overlap.overlaps_count > higher_overlaps.overlaps_count) {
				higher_overlaps = overlap;
			}
				
		}
	}

	for (int i = higher_overlaps.index_a; i < *size - 1; i++) {
		reads[i] = reads[i + 1];
	}
	(*size)--;

	for (int i = higher_overlaps.index_b; i < *size - 1; i++) {
		reads[i] = reads[i + 1];
	}
	(*size)--;

	for (int i = *size; i > 0; i--) {
		reads[i] = reads[i - 1];
	}
	(*size)++;

	reads[0] = merge_overlap(higher_overlaps);

	//	printf("merged: %s\n", reads[0]);


	return overlapit(reads, size);
}

int main () {
	int n = 0;

	scanf("%d", &n);

	char **reads = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		reads[i] = (char*)malloc(READ_MAX_LENGTH * sizeof(char)); // maybe causes overflow /:
		scanf("%99s", reads[i]);
	}
	
	char *test = overlapit(reads, &n);

	printf("%s", test);

	/* printf("sobreposicoes: %d\na: %d-%d\nb: %d-%d\n\n", higher_overlaps.overlaps_count, higher_overlaps.indexes_a[0], higher_overlaps.indexes_a[1], higher_overlaps.indexes_b[0], higher_overlaps.indexes_b[1]); */
	/* printf("a: \n"); */
	/* printcvec(higher_overlaps.read_a); */
	/* printf("b: \n"); */
	/* printcvec(higher_overlaps.read_b); */

	return 0;
}
