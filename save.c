//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void print_photo(photo_struct a, FILE *filename, int ascii)
{
	int nr_pixels = 1;
	if (a.rgb == 2)
		nr_pixels = 3;
	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.columns; j++) {
			unsigned char tmp;
			for (int k = 0; k < nr_pixels; k++)
				if (ascii == 1) {
					tmp = (unsigned char)round(a.photo_matrix[i][j].pixel[k]);
					fprintf(filename, "%hhu ", tmp);
				} else {
					tmp = (unsigned char)round(a.photo_matrix[i][j].pixel[k]);
					fwrite(&tmp, sizeof(unsigned char), 1, filename);
				}
		}
		if (ascii == 1)
			fprintf(filename, "\n");
	}
}

void save_photo(photo_struct photo, char *details)
{
	if (!photo.photo_matrix) {
		printf("No image loaded\n");
		return;
	}
	int ascii = 0;
	char *parse;
	parse = strtok(details, " ");
	char *name_string = parse;
	parse = strtok(NULL, " ");
	if (parse) {
		if (strcmp(parse, "ascii") != 0) {
			printf("Invalid command\n");
			return;
		}
		ascii = 1;
		FILE *filename = fopen(name_string, "wt");
		if (photo.rgb == 0)
			fprintf(filename, "P1\n");
		else
			if (photo.rgb == 1)
				fprintf(filename, "P2\n");
			else
				fprintf(filename, "P3\n");
		fprintf(filename, "%d %d\n", photo.columns, photo.rows);
		if (photo.max_value != -1)
			fprintf(filename, "%d\n", photo.max_value);
		// AICI:!!!!!!
		print_photo(photo, filename, ascii);
		fclose(filename);
		printf("Saved %s\n", name_string);
	} else {
		FILE *filename = fopen(name_string, "wt");
		if (photo.rgb == 0)
			fprintf(filename, "P4\n");
		else
			if (photo.rgb == 1)
				fprintf(filename, "P5\n");
			else
				fprintf(filename, "P6\n");
		fprintf(filename, "%d %d\n", photo.columns, photo.rows);
		if (photo.max_value != -1)
			fprintf(filename, "%d\n", photo.max_value);
		fclose(filename);

		filename = fopen(name_string, "ab");
		print_photo(photo, filename, ascii);
		fclose(filename);
		printf("Saved %s\n", name_string);
	}
}
