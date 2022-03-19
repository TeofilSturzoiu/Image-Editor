//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int check_any_letters(char *coordinates)
{
	long curr = 0;
	for (unsigned long i = 0; i < strlen(coordinates); i++)
		if (isdigit(coordinates[i]) == 0 && coordinates[i] != '-')
			curr++;

	if (curr > 0)
		return 0;
	else
		return 1;
}

void select_photo(photo_struct *photo, char *coordinates)
{
	if (!(*photo).photo_matrix) {
		printf("No image loaded\n");
		return;
	}
	if (strcmp(coordinates, "ALL") == 0 || strcmp(coordinates, "ALL ") == 0) {
		(*photo).x1 = (*photo).y1 = 0;
		(*photo).y2 = (*photo).rows;
		(*photo).x2 = (*photo).columns;
		printf("Selected ALL\n");
		return;
	}
	int x1, x2, y1, y2;
	char *parse;
	parse = strtok(coordinates, " ");
	if (check_any_letters(parse) == 0) {
		printf("Invalid command\n");
		return;
	}
	x1 = atoi(parse);
	parse = strtok(NULL, " ");
	if (!parse) {
		printf("Invalid command\n");
		return;
	}
	if (check_any_letters(parse) == 0) {
		printf("Invalid command\n");
		return;
	}
	y1 = atoi(parse);
	parse = strtok(NULL, " ");
	if (!parse) {
		printf("Invalid command\n");
		return;
	}
	if (check_any_letters(parse) == 0) {
		printf("Invalid command\n");
		return;
	}
	x2 = atoi(parse);
	parse = strtok(NULL, " ");
	if (!parse) {
		printf("Invalid command\n");
		return;
	}
	if (check_any_letters(parse) == 0) {
		printf("Invalid command\n");
		return;
	}
	y2 = atoi(parse);
	parse = strtok(NULL, " ");
	if (parse) {
		printf("Invalid command\n");
		return;
	}
	if (x1 > x2) {
		int aux = x1;
		x1 = x2;
		x2 = aux;
	}
	if (y1 > y2) {
		int aux = y1;
		y1 = y2;
		y2 = aux;
	}
	if (x2 > (*photo).columns || y2 > (*photo).rows || x2 == x1 ||
		y2 == y1 || x1 == -1 || x2 == -1 || y1 == -1 || y2 == -1) {
		printf("Invalid set of coordinates\n");
		return;
	}
	(*photo).x1 = x1;
	(*photo).x2 = x2;
	(*photo).y1 = y1;
	(*photo).y2 = y2;
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

