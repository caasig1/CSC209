#include <stdio.h>

/* stats.c
 * The program takes inputs from the standard input.
 * It returns the minimum, maximum and average of a given list of size 10.
 * The number is arbitrary and can be changed easily by changing the below variable.
 * The minimum, maximum and average of the first and second halves of the list are also printed.
 * Any number input after the first 10 will be ignored,
 */

int fillarray(int array[], int size);
int stats(int array[], int size);

/* main()
 * The main function just activates the appropriate function calls to:
 * a) fill the array
 * b) get the statistics from it
 */
int main() {
	int size_of_array = 10;
	int array[size_of_array];
	fillarray(array, size_of_array);

	// Call the stats on the entire array
	printf("Full array:\n");
       	stats(array, size_of_array);

	// Call the stats on the first half of the array
	printf("First half of the array:\n");
        stats(array, size_of_array/2);

	// Call the stats on the second half of the array
	printf("Second half of the array:\n");
        stats(array + 5, size_of_array/2);
}

/* fillarray(array[], size)
 * Fill the array that is given.
 * Any extra numbers given (more than the size of the array) are ignored.
 */
int fillarray(int array[], int size){
	for (int i = 0; i < size; i++){
		scanf("%d", &array[i]);
	}
	return 0;
}

/* stats(array[], size)
 * Find the statistics of a given array of a given size.
 * The stats are min, max, and average.
 */
int stats(int array[], int size){
	int min = array[0];
	int max = 0;
	int mean = 0;

	for (int i = 0; i < size; i++){
		// Check the minimum with the current value.
		if (array[i] < min){
			min = array[i];
		}
		// Check the maximum with the current value.
		if (array[i] > max){
			max = array[i];
		}
		mean += array[i];
	}
	mean = mean / size;
	printf("min: %d\n", min);
        printf("max: %d\n", max);
        printf("mean: %d\n", mean);
	return 0;
}
