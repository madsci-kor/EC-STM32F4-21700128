#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	int x;
	int y;
	int z;
} POSITION_TypeDef;

//
void addPos(POSITION_TypeDef pos0, POSITION_TypeDef pos1, POSITION_TypeDef* posOut);
void subDist(POSITION_TypeDef pos0, POSITION_TypeDef pos1, POSITION_TypeDef* posOut);
void printPos(POSITION_TypeDef Pos);

int main()
{
	// Exercise 3 ***********************************************
	printf("\nExercise 3\n");
	POSITION_TypeDef Pos[2];
	POSITION_TypeDef PosOut = { 0, 0, 0};

	Pos[0].x = 2; Pos[0].y = 2; Pos[0].z = 2;
	Pos[1].x = 5; Pos[1].y = 5; Pos[1].z = 5;

	printf("Result output of 'addPos'\n");
	addPos(Pos[0], Pos[1], &PosOut);
	printPos(PosOut);

	printf("Result output of 'getDist'\n");
	subDist(Pos[0], Pos[1], &PosOut);
	printPos(PosOut);

	system("pause");
	return 0;
}

void addPos(POSITION_TypeDef pos0, POSITION_TypeDef pos1, POSITION_TypeDef* posOut)
{ 
	// YOUR CODE GOES HERE
	posOut->x = pos0.x + pos1.x;
	posOut->y = pos0.y + pos1.y;
	posOut->z = pos0.z + pos1.z;
}
void subDist(POSITION_TypeDef pos0, POSITION_TypeDef pos1, POSITION_TypeDef* posOut)
{
	// YOUR CODE GOES HERE
	posOut->x = abs(pos0.x - pos1.x);
	posOut->y = abs(pos0.y - pos1.y);
	posOut->z = abs(pos0.z - pos1.z);
}
void printPos(POSITION_TypeDef Pos)
{
	// YOUR CODE GOES HERE	
    printf("PosOut : (x, y, z) = (%d, %d, %d)\n",Pos.x, Pos.y, Pos.z);
	
}