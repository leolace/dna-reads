#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_MAX_LENGTH 100

typedef struct {
	int overlaps;
	size_t begin_a;
	size_t end_a;
	size_t begin_b;
	size_t end_b;
	size_t index_vec_a;
	size_t index_vec_b;
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
			} else {
				if (temp_overlaps > overlap.overlaps) {
					overlap.overlaps = temp_overlaps;
					overlap.begin_a = si;
					overlap.end_a = temp_si - 1;
					overlap.begin_b = sj - temp_overlaps;
					overlap.end_b = sj - 1;
					overlap.index_vec_a = i;
					overlap.index_vec_b = j;
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
	
	int higher_overlaps[3] = {0, -1, -1};

	for (int i = 0; i < n; i++) {
		char *readi = reads[i];
		
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			
			char *readj = reads[j];
			int overlaps = 0;

			Overlap overlap = get_overlap(reads, i, j);
			printcvec(reads[i]);
			printcvec(reads[j]);

			printf("sobreposicoes: %d\na: %d-%d\nb: %d-%d\n\n", overlap.overlaps, overlap.begin_a, overlap.end_a, overlap.begin_b, overlap.end_b);
		}
	}

	printf("maior overlap: %d\n", higher_overlaps[0]);
	printf("posicao 1: %d\n", higher_overlaps[1]);
	printf("posicao 2: %d\n", higher_overlaps[2]);
	
	return 0;
}
