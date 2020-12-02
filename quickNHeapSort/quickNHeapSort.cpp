#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <time.h>

using namespace std;


void createDataFiles(string name, int length, int choose);
void readData(int array[], int length, string name);

int partition(int array[], int low, int high, int& swap_count, int& compare_count);
void quickSort(int array[], int low, int high, int& swap_count, int& compare_count);
void medianOfThree(int array[], int low, int high);

void heapify(int array[], int n, int i, int& swap_count, int& compare_count);
void heapSort(int array[], int n, int& swap_count, int& compare_count);

void printArray(int array[], int size);
void printResults(int swap_count, int compare_count);


int main()
{
	cout << "Quick and Heap sort\n";

	int swap_count = 0, compare_count = 0;
	int length, choose;
	string name = "toSort.txt";
	cout << "Enter array length: ";
	cin >> length;
	cout << "1) Best 2) Random 3) Worst: ";
	cin >> choose;
	int *data = new int[length];

	createDataFiles("toSort.txt", length, choose);
	readData(data, length, "toSort.txt");

	cout << "1) Quicksort 2) Heapsort: ";
	cin >> choose;
	system("cls");

	auto start = chrono::high_resolution_clock::now();
	if (choose == 1)
		quickSort(data, 0, length - 1, swap_count, compare_count);
	else
		heapSort(data, length, swap_count, compare_count);

	printArray(data, length);
	cout << endl;

	printResults(swap_count, compare_count);
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() << " s" << endl;

}

void createDataFiles(string name, int length, int choose) {
	ofstream fr(name);
	unsigned int seed = chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine engine(seed);
	uniform_int_distribution<int> distr(1, 100000);
	int a;
	int *array = new int[length];

	for (int i = 0; i < length; i++) {
		a = distr(engine);
		array[i] = a;
	}

	if (choose == 1)
	{
		sort(array, array + length);
		swap(array[length - 2], array[length - 1]);
	}
	else if (choose == 3) 
		sort(array, array + length, greater<int>());



	for (int i = 0; i < length; i++)
		i != length - 1 ? fr << array[i] << " " : fr << array[i];

	fr.close();
}
void readData(int array[], int length, string name) {
	ifstream fd(name);
	for (int i = 0; i < length; i++)
		fd >> array[i];

	fd.close();
}

int partition(int array[], int low, int high, int& swap_count, int& compare_count) {

	//medianOfThree(array, low, high);

	int pivot = array[high];
	int leftwall = low - 1;
	for (int i = low; i < high; i++) {
		if (array[i] <= pivot) {
			leftwall++;
			swap(array[leftwall], array[i]);

			swap_count++;
			compare_count++;
		}
	}

	swap(array[leftwall + 1], array[high]);

	return (leftwall + 1);

}
void quickSort(int array[], int low, int high, int& swap_count, int& compare_count) {
	if (low < high) {
		int pivot_location = partition(array, low, high, swap_count, compare_count);

		quickSort(array, low, pivot_location - 1, swap_count, compare_count);
		quickSort(array, pivot_location + 1, high, swap_count, compare_count);
	}
}
void medianOfThree(int array[], int low, int high) {
	int middle = high + low / 2;
	if (array[middle] < array[low])
		swap(array[low], array[middle]);
	if (array[high] < array[low])
		swap(array[low], array[high]);
	if (array[middle] < array[high])
		swap(array[middle], array[high]);
}

void heapify(int array[], int n, int i, int& swap_count, int& compare_count) {
	int root = i;
	int left_child = 2 * i + 1;
	int right_child = 2 * i + 2;

	if (left_child < n && array[left_child] > array[root]) {
		root = left_child;
		compare_count++;
	}

	if (right_child < n && array[right_child] > array[root]) {
		root = right_child;
		compare_count++;
	}

	if (root != i) {
		swap(array[i], array[root]);

		compare_count++;
		swap_count++;
		heapify(array, n, root, swap_count, compare_count);
	}
}
void heapSort(int array[], int n, int& swap_count, int& compare_count) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(array, n, i, swap_count, compare_count);

	for (int i = n - 1; i > 0; i--) {
		swap(array[0], array[i]);
		swap_count++;

		heapify(array, i, 0, swap_count, compare_count);
	}

}

void printArray(int array[], int size) {
	ofstream fr("res.txt");
	int i;
	for (i = 0; i < size; i++)
		fr << array[i] << " ";
	fr << endl;

	fr.close();
}
void printResults(int swap_count, int compare_count) {
	cout << "Number of swaps: " << swap_count << endl;
	cout << "Number of compares: " << compare_count << endl;
}