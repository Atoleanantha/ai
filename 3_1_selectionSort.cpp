#include<iostream>
using namespace std;

void selectionSort(int arr[], int size){
    int minIdx=0;
    for(int i=0;i<size;i++){
        minIdx=i;
        for(int j=i+1;j<size;j++){
            if(arr[minIdx]>arr[j]){
                minIdx=j;
            }
        }
        int temp=arr[minIdx];
        arr[minIdx]=arr[i];
        arr[i]=temp;
    }
    
    for(int i=0;i<size;i++){
        cout<<arr[i]<<"\t";
    }
}

int main(){
    int arr[]={1,3,7,1,0};
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array
    selectionSort(arr, size);
    return 0;
}
