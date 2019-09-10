using namespace std;

#include <iostream>

void printArray(int *nums, int size);
int insertion_sort(int* nums, int size);


int main() {
	const int size = 10;
	int nums[size] = {-9, 2, 2, 9, 31, 12, 3, 5, -4, -3};

	printArray(nums, size);
	insertion_sort(nums, size);
	printArray(nums, size);
}


int insertion_sort(int* nums, int size) {
	for (int i = 1; i < size; i++) {

		int j, curr = nums[i];

		for (j = i-1; j >= 0; j--) {
			if (nums[j] > curr)
				nums[j+1] = nums[j];
			else
				break;

			nums[j] = curr;
		}
	}
}


void printArray(int* nums, int size) {
	cout << "Array: ";

	for (int i = 0; i < size; i++)
		if (i < size - 1)
			cout << nums[i] << ", ";
		else
			cout << nums[i] << endl;
}
