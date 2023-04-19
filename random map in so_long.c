// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// #define ROWS 10
// #define COLS 10

// int main(void) {
//     char map[ROWS][COLS];
//     int i, j;

//     srand(time(NULL)); // Initialize random seed

//     // Fill the map with empty spaces
//     for (i = 0; i < ROWS; i++) {
//         for (j = 0; j < COLS; j++) {
//             map[i][j] = '0';
//         }
//     }

//     // Add random walls to the map
//     for (i = 0; i < ROWS; i++) {
//         for (j = 0; j < COLS; j++) {
//             if (rand() % 5 == 0) {
//                 map[i][j] = '1';
//             }
//         }
//     }

//     // Add random collectibles to the map
//     for (i = 0; i < ROWS; i++) {
//         for (j = 0; j < COLS; j++) {
//             if (rand() % 8 == 0 && map[i][j] == '0') {
//                 map[i][j] = 'C';
//             }
//         }
//     }

//     // Add random exit to the map
//     int exit_row = rand() % ROWS;
//     int exit_col = rand() % COLS;
//     while (map[exit_row][exit_col] != '0') {
//         exit_row = rand() % ROWS;
//         exit_col = rand() % COLS;
//     }
//     map[exit_row][exit_col] = 'E';

//     // Add random player position to the map
//     int player_row = rand() % ROWS;
//     int player_col = rand() % COLS;
//     while (map[player_row][player_col] != '0') {
//         player_row = rand() % ROWS;
//         player_col = rand() % COLS;
//     }
//     map[player_row][player_col] = 'P';

//     // Print the generated map
//     for (i = 0; i < ROWS; i++) {
//         for (j = 0; j < COLS; j++) {
//             printf("%c", map[i][j]);
//         }
//         printf("\n");
//     }

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// void generateMap(int width, int height) {
//   char map[height][width];
//   int i, j;
  
//   // Initialize the map with empty spaces
//   for (i = 0; i < height; i++) {
//     for (j = 0; j < width; j++) {
//       map[i][j] = '0';
//     }
//   }
  
//   // Set the borders of the map to walls
//   for (i = 0; i < height; i++) {
//     map[i][0] = '1';       // left wall
//     map[i][width-1] = '1'; // right wall
//   }
//   for (j = 0; j < width; j++) {
//     map[0][j] = '1';         // top wall
//     map[height-1][j] = '1';  // bottom wall
//   }
  
//   // Add random walls inside the map
//   srand(time(NULL)); // Initialize the random number generator
//   int numWalls = (width * height) / 3; // Adjust this value as needed
//   int x, y;
//   for (i = 0; i < numWalls; i++) {
//     x = rand() % (width - 2) + 1; // Random x-coordinate (excluding border)
//     y = rand() % (height - 2) + 1; // Random y-coordinate (excluding border)
//     map[y][x] = '1'; // Set the position to a wall
//   }
  
//   // Add the player and the exit
//   x = rand() % (width - 2) + 1;
//   y = rand() % (height - 2) + 1;
//   map[y][x] = 'P'; // Set the player's position
  
//   do {
//     x = rand() % (width - 2) + 1;
//     y = rand() % (height - 2) + 1;
//   } while (map[y][x] != '0'); // Ensure the exit is not on a wall or player position
//   map[y][x] = 'E'; // Set the exit position
  
//   // Print the map
//   for (i = 0; i < height; i++) {
//     for (j = 0; j < width; j++) {
//       printf("%c", map[i][j]);
//     }
//     printf("\n");
//   }
// }

// int main() {
//   generateMap(30, 10); // Adjust the width and height as needed
//   return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateMap(int width, int height)
{
  char map[height][width];
  int i, j;
  
  // Initialize the map with empty spaces
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      map[i][j] = '0';
    }
  }
  
  // Set the borders of the map to walls
  for (i = 0; i < height; i++) {
    map[i][0] = '1';       // left wall
    map[i][width-1] = '1'; // right wall
  }
  for (j = 0; j < width; j++) {
    map[0][j] = '1';         // top wall
    map[height-1][j] = '1';  // bottom wall
  }
  
  // Add random walls inside the map
  srand(time(NULL)); // Initialize the random number generator
  int numWalls = (width * height) / 3; // Adjust this value as needed
  int x, y;
  for (i = 0; i < numWalls; i++) {
    x = rand() % (width - 2) + 1; // Random x-coordinate (excluding border)
    y = rand() % (height - 2) + 1; // Random y-coordinate (excluding border)
    map[y][x] = '1'; // Set the position to a wall
  }
  
  // Add the player and the exit
  x = rand() % (width - 2) + 1;
  y = rand() % (height - 2) + 1;
  map[y][x] = 'P'; // Set the player's position
  
  do {
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
  } while (map[y][x] != '0'); // Ensure the exit is not on a wall or player position
  map[y][x] = 'E'; // Set the exit position
  
  // Add the collectibles
  int numCollectibles = numWalls / 2; // Adjust this value as needed
  int numCollected = 0;
  while (numCollected < numCollectibles) {
    x = rand() % (width - 2) + 1;
    y = rand() % (height - 2) + 1;
    if (map[y][x] == '0') { // Only add collectibles on empty spaces
      map[y][x] = 'C';
      numCollected++;
    }
  }
  
// Check if the map is valid
  int numPlayers = 0;
  int numExits = 0;
  int numCollectedCheck = 0;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (map[i][j] == 'P') {
        numPlayers++;
      }
      else if (map[i][j] == 'E') {
        numExits++;
      }
      else if (map[i][j] == 'C') {
        numCollectedCheck++;
      }
      else if (map[i][j] == '1') { // Check if there are walls around the map
        if (i == 0 || i == height-1 || j == 0 || j == width-1) {
          printf("Invalid map: Walls should not be on the border of the map.\n");
          return;
        }
        if (i > 0 && map[i-1][j] != '1' && map[i-1][j] != 'P' && map[i-1][j] != 'E') {
          printf("Invalid map: Walls should be connected.\n");
          return;
        }
        if (j > 0 && map[i][j-1] != '1' && map[i][j-1] != 'P' && map[i][j-1] != 'E') {
          printf("Invalid map: Walls should be connected.\n");
          return;
        }
        if (i < height-1 && map[i+1][j] != '1' && map[i+1][j] != 'P' && map[i+1][j] != 'E') {
          printf("Invalid map: Walls should be connected.\n");
          return;
        }
        if (j < width-1 && map[i][j+1] != '1' && map[i][j+1] != 'P' && map[i][j+1] != 'E') {
          printf("Invalid map: Walls should be connected.\n");
          return;
        }
      }
    }
  }
  if (numPlayers != 1) {
    printf("Invalid map: There should be exactly one player.\n");
    return;
  }
  if (numExits != 1) {
    printf("Invalid map: There should be exactly one exit.\n");
    return;
  }
  if (numCollected != numCollectedCheck) {
    printf("Invalid map: The number of collectibles is incorrect.\n");
    return;
  }
  printf("Valid map!\n");
}
int main()
{
  generateMap(20,20);
}