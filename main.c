#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_MAX_LENGTH 100

void printnvec(int *vec, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", vec[i]);
	}
	printf("\n");
}

void printcvec(char *vec, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c ", vec[i]);
	}
	printf("\n");
}

int main () {
	int n = 0;

	scanf("%d", &n);

	char **reads = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		reads[i] = (char*)malloc(READ_MAX_LENGTH * sizeof(char)); // maybe causes overflow /:
		scanf("%99s", reads[i]);
	}

	int **decimal_reads = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		decimal_reads[i] = (int*)malloc(READ_MAX_LENGTH * sizeof(int));

		for (int j = 0; j < strlen(reads[i]); j++) {
			decimal_reads[i][j] = (int)reads[i][j];
		}
	}
	
	int higher_overlaps[3] = {0, -1, -1};

	for (int i = 0; i < n; i++) {
		int *readi = decimal_reads[i];
		
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			
			int *readj = decimal_reads[j];
			int overlaps = 0;

			// prefixo vs. prefixo
			for (int si = 0; si < strlen(reads[i]); si++) {
				int temp_overlaps = 0;
				int temp_si = si;
				
				for (int sj = 0; sj < strlen(reads[j]); sj++) {
					if (readi[temp_si] == readj[sj]) {
						temp_si++;
						temp_overlaps++;
					} else {
						temp_si = si;
						temp_overlaps = 0;
					}
				}
				if (temp_overlaps > overlaps) overlaps = temp_overlaps;
			}

			// sufixo vs. sufixo
			for (int si = strlen(reads[i]) - 1; si >= 0; si--) {
				int temp_overlaps = 0;
				int temp_si = si;
				
				for (int sj = strlen(reads[j]) - 1; sj >= 0; sj--) {
					if (readi[temp_si] == readj[sj]) {
						temp_si++;
						temp_overlaps++;
					} else {
						temp_si = si;
						temp_overlaps = 0;
					}
				}
				if (temp_overlaps > overlaps) overlaps = temp_overlaps;
			}

			// prefixo vs. sufixo
			for (int si = 0; si < strlen(reads[i]); si++) {
				int temp_overlaps = 0;
				int temp_si = si;
				
				for (int sj = strlen(reads[j]) - 1; sj >= 0; sj--) {
					if (readi[temp_si] == readj[sj]) {
						temp_si++;
						temp_overlaps++;
					} else {
						temp_si = si;
						temp_overlaps = 0;
					}
				}
				if (temp_overlaps > overlaps) overlaps = temp_overlaps;
			}

			// sufixo vs. prefixo
			for (int si = strlen(reads[i]) - 1; si >= 0; si--) {
				int temp_overlaps = 0;
				int temp_si = si;
				
				for (int sj = 0; sj < strlen(reads[j]); sj++) {
					if (readi[temp_si] == readj[sj]) {
						temp_si++;
						temp_overlaps++;
					} else {
						temp_si = si;
						temp_overlaps = 0;
					}
				}
				if (temp_overlaps > overlaps) overlaps = temp_overlaps;
			}

			if (overlaps > higher_overlaps[0]) {
				higher_overlaps[0] = overlaps;
				higher_overlaps[1] = j;
				higher_overlaps[2] = i;
			}
		}
	}

	printf("maior overlap: %d\n", higher_overlaps[0]);
	printf("posicao 1: %d\n", higher_overlaps[1]);
	printf("posicao 2: %d\n", higher_overlaps[2]);
	
	return 0;
}