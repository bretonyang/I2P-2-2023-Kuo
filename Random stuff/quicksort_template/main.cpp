#include <iostream>

using namespace std;

int arr[100005];

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int arr[], int left_index, int right_index) {
    int pivot = arr[left_index]; // choose leftmost element as pivot
    int index_to_store = left_index + 1;
    for (int i = left_index + 1; i <= right_index; i++) {
        if (arr[i] < pivot) {
            swap(&arr[i], &arr[index_to_store]);
            index_to_store++;
        }
    }
    swap(&arr[left_index], &arr[index_to_store - 1]);
    return index_to_store - 1;
}

void quicksort(int arr[], int left_index, int right_index) {
    if (left_index > right_index) return;

    int pivot_index = partition(arr, left_index, right_index);
    quicksort(arr, left_index, pivot_index - 1);
    quicksort(arr, pivot_index + 1, right_index);
}

int main() {
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        quicksort(arr, 0, n - 1);

        for (int i = 0; i < n; i++)
            cout << arr[i] << ' ';
        cout << endl;
    }
    return 0;
}
