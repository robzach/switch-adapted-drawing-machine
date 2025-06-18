// struct code from Claude
// Define a structure for x,y coordinate pairs
typedef struct {
  int x;
  int y;
} Point;

// Main structure with char array, integer, and list of coordinates
typedef struct {
  char name[50];           // Character array (adjust size as needed)
  int count;               // Integer (could be used for number of coordinates)
  Point coordinates[100];  // Array of Point structures (adjust size as needed)
} Shape;



Shape shapes[5] = {
  { "square",  // name
    5,         // count
    {
      { -50, -50 },  // coordinates
      { 50, -50 },
      { 50, 50 },
      { -50, 50 },
      { -50, -50 } } },
  { "triangle",  //name
    4,           // count
    {
      { 20, -20 },  //coordinates
      { -20, -20 },
      { 0, 20 },
      { 20, -20 },
    } },
  { "dumb dipper",  //name
    6,              // count
    {
      { 80, 80 },  //coordinates
      { 40, 60 },
      { -50, 50 },
      { -30, -40 },
      { 30, -30 },
      { 20, 20 } } },
  { "square spiral",  //name
    8,                // count
    {
      { 20, -20 },  //coordinates
      { -20, -20 },
      { -20, 20 },
      { 10, 20 },
      { 10, -10 },
      { -10, -10 },
      { -10, 10 },
      { 0, 10 } } },
  { "pulse",  //name
    9,        // count
    {
      { -50, 70 },  //coordinates
      { -30, 70 },
      { -20, 80 },
      { -10, 60 },
      { 0, 90 },
      { 10, 60 },
      { 20, 80 },
      { 30, 70 },
      { 80, 70 } } }

};
