#include <iostream>
#include <fstream>

using namespace std;

void testInputArrayAndSize(void (*f)(int arr[], int n), string  filename);
void testInputArrayAndSizeAndParam(void (*f)(int arr[], int n, int m), const string & filename);

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
    int i = 0, j = 0;
    while (i < n && j < m) {
        if(i>0 && arr1[i]==arr1[i-1]){
            i++;
            continue;
        }
        if(j>0&&arr2[j]==arr2[j-1]){
            j++;
            continue;
        }
        if(arr1[i]<arr2[j]){
            cout << arr1[i] << " ";
            i++;
        } else if (arr2[j]<arr1[i]){
            cout << arr2[j] << " ";
            j++;
        } else {
            cout << arr1[i]<<" ";
            i++;
            j++;
        }
    }
    while(i<n){
        if(i==0||arr1[i]!=arr1[i-1]){
            cout<<arr1[i]<<" ";
        }
        i++;
    }
    while(j<m){
        if(j==0||arr2[j]!=arr2[j-1]){
            cout<<arr2[j]<<" ";
        }
        j++;
    }

}

void testFindUnion(){
    int arr1[] = {1,1,1,1,1};
    int arr2[] = {2,2,2,2,2};
    int n1 = sizeof(arr1)/ sizeof(arr1[0]);
    int n2 = sizeof(arr2)/ sizeof(arr2[0]);
    findUnion(arr1, arr2, n1, n2);
}

int merge(int arr[], int start, int mid, int end){
    int arr3[end-start];
    int i=0,j=0;
    int count = 0;
    int n1 = mid-start;
    while((i+start<mid)&&(j+mid<end)){
        if(arr[mid+j] < arr[start+i]) {
            arr3[i + j] = arr[mid+j];
            count+=n1-i;
            j++;
        } else {
            arr3[i+j]=arr[start+i];
            i++;
        }
    }
    while(i+start<mid){
        arr3[i+j]=arr[start+i];
        i++;
    }
    while(j+mid<end){
        arr3[i+j]=arr[mid+j];
        j++;
    }
    for(i=0;i<end-start;i++){
        arr[start+i]=arr3[i];
    }
    return count;
}

int countInversionsRec(int arr[], int start, int end){
    int mid = (start+end)/2;
    int count = 0;
    if(start<end){
        count += countInversionsRec(arr,start,mid);
        count += countInversionsRec(arr,mid+1,end);
        count += merge(arr,start,mid,end);
    }

    return count;
}

void countInversions(int arr[], int n){
    cout<< countInversionsRec(arr,0,n)<<endl;
}

void testCountInversions(){
    int arr[] = {3,5,8,11,3,6,9,13};
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

void naivePartition(int arr[], int n, int m){
    int res[n],i,c=0;
    for(i=0;i<n;i++){
        if(arr[i]<arr[m]){
            res[c]=arr[i];
            c++;
        }
    }
    res[c]=arr[m];
    for(i=0;i<n;i++){
        if(arr[i]>=arr[m]&&i!=m){
            c++;
            res[c]=arr[i];
        }
    }
    for(i=0;i<n;i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
}

int main() {
    //testInputArrayAndSize(countInversions,"countInversionsInput.txt");
    testInputArrayAndSizeAndParam(naivePartition,"partitionInput.txt");
    return 0;
}

void testInputArrayAndSize(void (*f)(int arr[], int n), string  filename){
    int T,n;
    ifstream myfile;
    myfile.open ("/Users/jimstewart/Git/GfGCppSort/"+filename);
    if(!myfile.is_open()){
        cout<<"couldn't open file"<<endl;
        return;
    }
    myfile >> T;
    while(T--){
        myfile>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            myfile>>arr[i];
        }
        f(arr,n);
    }
    myfile.close();
}

void testInputArrayAndSizeAndParam(void (*f)(int arr[], int n, int m), const string & filename){
    int T,n,m;
    ifstream myfile;
    myfile.open ("/Users/jimstewart/Git/GfGCppSort/"+filename);
    if(!myfile.is_open()){
        cout<<"couldn't ope file"<<endl;
        return;
    }
    myfile >> T;
    while(T--){
        myfile>>n;
        myfile>>m;
        int arr[n];
        for(int i=0;i<n;i++){
            myfile>>arr[i];
        }
        f(arr,n,m);
    }
    myfile.close();
}