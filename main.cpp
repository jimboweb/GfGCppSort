#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void testInputArrayAndSize(void (*f)(int arr[], int n), string  filename);
void testInputArrayAndSizeAndParam(void (*f)(int arr[], int n, int m), const string & filename);
int testInputArrayAndSizeAndParamWithIntReturn(int (*f)(int arr[], int n, int m), const string & filename);
void testInputArrayAndSizeWithBoolReturn(bool (*f)(int arr[], int n), string filename);
void printArr(int a[], int s){
    for(int i=0;i<s;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}


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

int lomutoPartition(int arr[], int l, int h){
    int pivot = arr[h];
    int i=l-1;
    for(int j=l;j<=h-1;j++){
        if(arr[j]<pivot){
            i++;
            std::swap(arr[i],arr[j]);
        }
    }
    std::swap(arr[i+1],arr[h]);
    return i+1;
}


int kthSmallest(int arr[], int n, int k){
    int l=0,r=n-1;
    while(l<=r){
        int p = lomutoPartition(arr,l,r);
        if(p==k-1){
            return  arr[p];
        }
        else if (p>k-1){
            r = p-1;
        } else {
            l = p+1;
        }
    }
    return -1;
}

void testKthSmallest(){
    testInputArrayAndSizeAndParamWithIntReturn(kthSmallest,"kthSmallestInput.txt");
}

void quicksortLomutoRec(int arr[],int l, int h){
    if(l<h){
        int p = lomutoPartition(arr,l,h);
        quicksortLomutoRec(arr,l,p-1);
        quicksortLomutoRec(arr,p+1,h);
    }
}

void quicksortLomuto(int arr[], int s){
    quicksortLomutoRec(arr,0,s);
}

void testLomutoPartition(){
    int arr[] = {40,10,80,30,90,50,70};
    int l = 0;
    int h = 6;
    lomutoPartition(arr,l,h);
    for(int i=0;i<7;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

void testQuicksortLomuto(){
    int arr[] = {40,10,80,30,90,50,70,30,100,10,25};
    int s = sizeof(arr)/ sizeof(arr[0]);
    quicksortLomuto(arr,s-1);
    for(int i=0;i<s;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

int hoarePartition(int arr[], int l, int h){
    int pivot = arr[l];
    int i=l-1, j = h + 1;
    while(true){
        do{
            i++;
        } while (arr[i]<pivot);
        do{
            j--;
        } while (arr[j]>pivot);
        if(i>=j) return j;
        swap(arr[i],arr[j]);
    }
}

void quickSortHoareRec(int arr[], int l, int h){
    if(l<h){
        int p = hoarePartition(arr,l,h);
        quickSortHoareRec(arr,l,p);
        quickSortHoareRec(arr,p+1,h);
    }
}

void quickSortHoare(int arr[], int s){
    quickSortHoareRec(arr,0,s-1);
}

void testHoarePartition(){
    int arr[] = {40,10,80,30,90,50,70};
    int l = 0;
    int h = 6;
    hoarePartition(arr,l,h);
    for(int i=0;i<7;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

}

void testQuicksortHoare(){
    int arr[] = {40,10,80,30,90,50,70,30,100,10,25};
    int s = sizeof(arr)/ sizeof(arr[0]);
    quickSortHoare(arr,s);
    for(int i=0;i<s;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

}

bool findTripletsNaive(int arr[], int n){
    for(int i=0;i<n;i++){
        int first = arr[i];
        for(int j=0;j<n;j++){
            if(j==i)
                continue;
            int second = arr[j];
            for(int k=0;k<n;k++){
                if(k==i||k==j)
                    continue;
                int third = arr[k];
                if(first+second+third==0){
                    printf("%d + %d + %d = 0",arr[i],arr[j],arr[k]);
                    return true;
                }
            }
        }
    }
    return false;
}

/* You are required to complete the function below
*  arr[]: input array
*  n: size of array
*/
bool findTriplets(int arr[], int n)
{
    sort(arr, arr+n);
    if(arr[0]>0||arr[n-1]<0)
        return false;
    for(int i=0;i<n;i++){
        int l = i+1, r=n-1, x = arr[i];
        while(l<r){
            int sum = x + arr[l] + arr[r];
            if(sum==0)
                return true;
            if(sum > 0)
                r--;
            else
                l++;
        }
    }
    return false;
}

void testFindTriplets(){
    testInputArrayAndSizeWithBoolReturn(findTriplets,"tripletsinput.txt");
}

vector<int> threeWayPartition(vector<int> A, int a, int b){
    int lo=0, mid = 0, hi = A.size()-1,
    while(mid<hi){
        if(A[mid]<a){
            std::swap(A[lo],A[mid]);
            lo++;
            mid++;
        } else if (A[mid]<b){
            mid++;
        } else {
            std::swap(A[mid],A[hi]);
            hi--;
        }
    }
    return A;
}

//todo: test this
void testThreeWayPartition(string  filename){
    int T,n,m;
    ifstream myfile;
    myfile.open ("/Users/jimstewart/Git/GfGCppSort/"+filename);
    if(!myfile.is_open()){
        cout<<"couldn't open file"<<endl;
        return;
    }
    myfile >> T;
    while(T--){
        myfile>>n;
        myfile>>m;
        vector<int> vctr;
        for(int i=0;i<n;i++){
            myfile>>vctr[i];
        }
        vector<int> rslt = threeWayPartition(vctr,n,m);
        for(int i:rslt)
            cout<<i<<" ";
        cout<<endl;
    }
    myfile.close();
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

int testInputArrayAndSizeAndParamWithIntReturn(int (*f)(int arr[], int n, int m), const string & filename){
    int T,n,m;
    ifstream myfile;
    myfile.open ("/Users/jimstewart/Git/GfGCppSort/"+filename);
    if(!myfile.is_open()){
        cout<<"couldn't ope file"<<endl;
        return -1;
    }
    myfile >> T;
    while(T--){
        myfile>>n;
        myfile>>m;
        int arr[n];
        for(int i=0;i<n;i++){
            myfile>>arr[i];
        }
        cout<<f(arr,n,m)<<endl;
    }
    myfile.close();
    return 0;
}

void testInputArrayAndSizeWithBoolReturn(bool (*f)(int arr[], int n), string filename){
    int T,n;
    ifstream myfile;
    myfile.open ("/Users/jimstewart/Git/GfGCppSort/"+filename);
    if(!myfile.is_open()){
        cout<<"couldn't open file"<<endl;
    }
    myfile >> T;
    while(T--){
        myfile>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            myfile>>arr[i];
        }
        string output = f(arr,n)?"True":"False";
        cout<<output<<endl;
    }
    myfile.close();
}

int main() {
    //testInputArrayAndSize(countInversions,"countInversionsInput.txt");
    testFindTriplets();
    return 0;
}
