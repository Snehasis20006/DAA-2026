#include<stdio.h>
void sort(int a[],int n);
void mean(int a[],int n);
void median(int a[],int n);
void reverse (int a[],int n);
void mode(int a[],int n);
void largest_element(int a[],int n){
    int max=a[0];
    for(int i=0;i<n;i++){
        if(a[i]>max){
            max=a[i];
        }
    }
    printf("largest element : %d \n",max);
}
void second_largest_element(int a[],int n){
    int max=a[0];
    int second_max=a[0];
    for(int i=0;i<n;i++){
        if(a[i]>max){
            second_max=max;
            max=a[i];
        }
        else if(a[i]>second_max && a[i]!=max){
            second_max=a[i];
        }
    }
    printf("second largest element : %d \n",second_max);
}
int main(){
    int a[1000];
    int n,i;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter element : ");
        scanf("%d",&a[i]);
    }
    printf("Before sort the originsal array : \n");
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    reverse(a,n);
    sort(a,n);
    
    printf("After sort : \n");
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    mean(a,n);
    median(a,n);
    mode(a,n);
    largest_element(a,n);
    second_largest_element(a,n);
    return 0;
}
void median(int a[],int n){
    int l=n/2;
    if(n%2==1){
        printf("Median: %d\n",a[l]);
    }
    else{
        printf("Median: %d , %d\n",a[l-1] ,a[l]);
}
}
void mean(int a[],int n){
int sum=0;
for(int i=0;i<n;i++){
    sum+=a[i];
}
printf("\nMean: %.2f\n",(float)sum/n);
}
void reverse (int a[],int n){
    printf("reverse of the original array : \n");
    for(int i=n-1;i>=0;i--){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void sort(int a[],int n){
   for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
        if(a[i]>a[j]){
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }
   }
}
void mode(int a[],int  n){
    int maxcount=0;
    int modvalue=a[0];
    for(int i=0;i<n;i++){
        int count=0;
        for(int j=i+1;j<n;j++){
            if(a[i]==a[j]) count++;
        }
        if(count>maxcount){
            maxcount=count;
            modvalue=a[i];
        }
    }
    printf("Mode: %d\n",modvalue);
}