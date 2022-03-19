//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "utilities.h"
#include "utilities.c"
#include "load.h"
#include "load.c"
#include "crop.h"
#include "crop.c"
#include "apply.h"
#include "apply.c"
#include "rotate.h"
#include "rotate.c"
#include "select.h"
#include "select.c"
#include "save.h"
#include "save.c"

// Function to return a number for each command
int return_command(char *s)
{
	if (strcmp(s, "LOAD") == 0)
		return 1;
	if (strcmp(s, "SELECT") == 0)
		return 2;
	if (strcmp(s, "ROTATE") == 0)
		return 3;
	if (strcmp(s, "CROP") == 0)
		return 4;
	if (strcmp(s, "APPLY") == 0)
		return 5;
	if (strcmp(s, "SAVE") == 0)
		return 6;
	return 7;
}

int main(void)
{
	photo_struct photo;
	photo.photo_matrix = NULL;
	photo.x1 = -1;
	photo.x2 = -1;
	photo.y1 = -1;
	photo.y2 = -1;

	char *input, *input_aux, error[6] = "ERROR";
	input = malloc(50 * sizeof(char));
	input_aux = malloc(50 * sizeof(char));
	fgets(input, 50, stdin);
	input[strlen(input) - 1] = '\0';

	while (strcmp(input, "EXIT") != 0) {
		int ok = 0;
		char *command;
		strcpy(input_aux, input);

		if (strcmp(input_aux, "CROP") == 0) {
			command = input_aux;
		} else {
			if (strchr(input_aux, ' ')) {
				command = strtok(input_aux, " ");
			} else {
				if (strcmp(input_aux, "APPLY") == 0) {
					ok = 1;
					command = input_aux;
				} else {
					command = error;
				}
			}
		}

			switch (return_command(command)) {
			case 1:
				command = strtok(NULL, input_aux);
				load_image(&photo, command);
				break;
			case 2:
				command = strtok(NULL, input_aux);
				select_photo(&photo, strstr(input, command));
				break;
			case 3:
				command = strtok(NULL, input_aux);
				rotate_photo(&photo, strstr(input, command));
				break;
			case 4:
				crop_photo(&photo);
				break;
			case 5:
				if (ok == 1) {
					if (!photo.photo_matrix)
						printf("No image loaded\n");
					else
						printf("Invalid command\n");
					break;
				}
				command = strtok(NULL, input_aux);
				apply_photo(&photo, strstr(input, command));
				break;
			case 6:
				command = strtok(NULL, input_aux);
				save_photo(photo, strstr(input, command));
				break;
			default:
				printf("Invalid command\n");
				break;
		}

		fgets(input, 50, stdin);
		if (strcmp(input, "EXIT") != 0)
			input[strlen(input) - 1] = '\0';
	}

	free(input);
	free(input_aux);
	
	if (photo.photo_matrix)
		free_matrix(photo.rows, photo.columns, photo.photo_matrix);
	else
		printf("No image loaded\n");
}
