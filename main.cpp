#include <iostream>
using namespace std;

void printIntersection(int *arr1, int *arr2, int N, int M){
    int i = 0, j = 0, lastPrinted = -1;
    while(i < N && j < M){
        if(arr1[i]>arr2[j])
            j++;
        else if (arr1[i]<arr2[j])
            i++;
        else if (arr1[i]!=lastPrinted){
            cout<<arr1[i]<<" ";
            lastPrinted=arr1[i];
        } else {
            i++;
            j++;
        }

    }
}


void testIntersectionOfSortedArrays(){
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {2, 4, 6, 7, 8};
    int n1 = sizeof(arr1)/ sizeof(arr1[0]);
    int n2 = sizeof(arr2)/ sizeof(arr2[0]);
    printIntersection(arr1, arr2, n1, n2);
}

void findUnion(int arr1[], int arr2[], int n, int m) {
    int i = 0, j = 0, lastPrinted = -1;
    while (i < n || j < m) {
        if (i<n&&arr1[i] != lastPrinted) {
            cout << arr1[i] << " ";
            lastPrinted = arr1[i];

        } else if(arr2[j]!=lastPrinted){
            cout << arr2[j] << " ";
            lastPrinted = arr2[j];
        }
        if (arr1[i] > arr2[j])
            j++;
        else if (arr1[i] < arr2[j])
            i++;
        else {
            i++;
            j++;
        }
        while(arr1[i]<=lastPrinted)
            i++;
        while(arr2[j]<=lastPrinted)
            j++;
    }

}

void testFindUnion(){
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {2, 4, 6, 7, 8};
    int n1 = sizeof(arr1)/ sizeof(arr1[0]);
    int n2 = sizeof(arr2)/ sizeof(arr2[0]);
    findUnion(arr1, arr2, n1, n2);
}


int main() {
    testFindUnion();
    return 0;
}
