//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int get_type_of_file(char *type)
{
	char ascii_types[3][3] = {"P1", "P2", "P3"};
	char binary_types[3][3] = {"P4", "P5", "P6"};

	for (int i = 0; i < 3; i++)
		if (strcmp(type, ascii_types[i]) == 0)
			return 1;

	for (int i = 0; i < 3; i++)
		if (strcmp(type, binary_types[i]) == 0)
			return 2;

	return -1;
}

int get_type_of_photo(char *type)
{
	//Photo is black and white:
	int rgb = 0;

	//Photo is in grayscale:
	if (strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0)
		rgb = 1;

	//Photo is coloured:
	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0)
		rgb = 2;

	return rgb;
}

void read_comment(FILE *filename)
{
	char garbage;
	do {
		fscanf(filename, "%c", &garbage);
	} while (garbage != '\n');
}

void check_comments(FILE *filename, int *verify)
{
	char letter;
	fscanf(filename, "%c", &letter);

	if (letter == '#') {
		read_comment(filename);
	} else {
		fseek(filename, -1, SEEK_CUR);
		*verify = 0;
	}
}

void load_image(photo_struct *photo, char *name_string)
{
	FILE *filename = fopen(name_string, "rb");

	if (!filename) {
		if ((*photo).photo_matrix)
			free_matrix((*photo).rows, (*photo).columns,
						(*photo).photo_matrix);

		(*photo).photo_matrix = NULL;
		(*photo).x1 = -1;
		(*photo).y1 = -1;
		(*photo).x2 = -1;
		(*photo).y2 = -1;

		printf("Failed to load %s\n", name_string);
		return;
	}

	if ((*photo).photo_matrix)
		free_matrix((*photo).rows, (*photo).columns, (*photo).photo_matrix);

	int verify = 1;
	while (verify == 1)
		check_comments(filename, &verify);
		
	char *type;
	type = malloc(3 * sizeof(char));
	fscanf(filename, "%s\n", type);

	verify = 1;
	while (verify == 1)
		check_comments(filename, &verify);

	fscanf(filename, "%d%d\n", &(*photo).columns, &(*photo).rows);

	verify = 1;
	while (verify == 1)
		check_comments(filename, &verify);

	(*photo).ok = get_type_of_file(type);
	(*photo).rgb = get_type_of_photo(type);
	(*photo).max_value = -1;
	if ((*photo).rgb > 0)
		fscanf(filename, "%d\n", &(*photo).max_value);

	verify = 1;
	while (verify == 1)
		check_comments(filename, &verify);

	(*photo).photo_matrix = read_matrix((*photo).rows, (*photo).columns,
										(*photo).rgb, (*photo).ok, filename);

	(*photo).x1 = 0;
	(*photo).y1 = 0;
	(*photo).x2 = (*photo).columns;
	(*photo).y2 = (*photo).rows;

	free(type);
	printf("Loaded %s\n", name_string);

	fclose(filename);
}
