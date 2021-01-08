// c does not have sizeof for arrays sinze they are of unknown size, unless directly specified
// for instance, a list a = [1,2,3] would not have a[3] be an error, rather it would point to something else that was perhaps previously assigned/created in the program
// We need size, and obviously the array, in order to sum all the elements in the array
int function(int *array, int size){
	int sum = 0;
	for (int i=0; i<size; i++){
		sum = sum + array[i];
	}
	return sum;
}
