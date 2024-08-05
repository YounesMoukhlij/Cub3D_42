#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum dimensions for convenience
#define MAX_ROWS 27
#define MAX_COLS 27

char *map[] = {
    "111111111111111111111111",
    "100000000000000000000001",
    "110000000000000000000001   11111111111111111",
    "110000000000000000000001   11000000000000001",
    "110000000000000000000001   110000000000N0001",
    "110000000000000000000001   11000000000000001",
    "110000000000000000000001   11111111111111111",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "110000000000000000000001",
    "100000000000000000000001",
    "100000000000000000000001",
    "111111111111111111111111",
    "111111        1111111111",
    "111111"
};

void find_bounds(int n_row, int n_col, int *top, int *bottom, int *left, int *right) {
    // Initialize boundaries
    *top = n_row;
    *bottom = n_row;
    *left = n_col;
    *right = n_col;

    // Expand upwards
    while (*top > 0 && map[*top - 1][n_col] != '1') {
        (*top)--;
    }
    // Expand downwards
    while (*bottom < MAX_ROWS - 1 && map[*bottom + 1][n_col] != '1') {
        (*bottom)++;
    }
    // Expand leftwards
    while (*left > 0 && map[n_row][*left - 1] != '1') {
        (*left)--;
    }
    // Expand rightwards
    while (*right < MAX_COLS - 1 && map[n_row][*right + 1] != '1') {
        (*right)++;
    }
}

int main() {
    int n_row = -1, n_col = -1;

    // Find the coordinates of 'N'
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            if (map[i][j] == 'N')
            {
                n_row = i;
                n_col = j;
                break;
            }
        }
        if (n_row != -1) break;
    }

    if (n_row == -1 || n_col == -1) {
        printf("Player 'N' not found in the map.\n");
        return 1;
    }

    // Find the boundaries
    int top, bottom, left, right;
    find_bounds(n_row, n_col, &top, &bottom, &left, &right);

    // Calculate dimensions of the new map
    int new_rows = bottom - top + 1;
    int new_cols = right - left + 1;

    // Allocate memory for the new map
    char **new_map = (char **)malloc(new_rows * sizeof(char *));
    for (int i = 0; i < new_rows; i++) {
        new_map[i] = (char *)malloc((new_cols + 1) * sizeof(char)); // +1 for null terminator
    }

    // Copy the area into the new map
    for (int i = 0; i < new_rows; i++) {
        strncpy(new_map[i], &map[top + i][left], new_cols);
        new_map[i][new_cols] = '\0'; // Null terminate the string
    }

    // Print the extracted area
    printf("Extracted area:\n");
    for (int i = 0; i < new_rows; i++) {
        printf("%s\n", new_map[i]);
    }

    // Free allocated memory
    for (int i = 0; i < new_rows; i++) {
        free(new_map[i]);
    }
    free(new_map);

    return 0;
}