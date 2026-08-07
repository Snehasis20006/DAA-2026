#include<stdio.h>
#include<stdlib.h>
void merge(int a[], int n1, int b[], int n2, int c[]){
     int i=0,j=0,k=0;
     while(i<n1 && j<n2){
         if(a[i]<b[j]){
             c[k++]=a[i++];
         }
         else{
             c[k++]=b[j++];
         }
     }
     while(i<n1){
         c[k++]=a[i++];
     }
     while(j<n2){
         c[k++]=b[j++];
     }
}
int main(){
    int k,a;//k=no of array ,a=no of elements in an array.
    printf("entrer the number of arrays : ");
    scanf("%d",&k);
    int **arr=malloc(k*sizeof(int*));
    printf("\nenter the numberof elements in each array : ");
    scanf("%d",&a);
    for(int i=0;i<k;i++){
        arr[i]=malloc(a*sizeof(int));
        printf("\nenter %d shorted  elements of array %d : ",a,i+1);
        for(int j=0;j<a;j++){
            scanf("%d",&arr[i][j]);
        }
    }
   
   int *result=malloc(2*a*sizeof(int));
    merge(arr[0],a,arr[1],a,result);
    int size=2*a;
    for(int i=2;i<k;i++){
        int *temp=malloc((size+a)*sizeof(int));
        merge(result,size,arr[i],a,temp);
        free(result);
        result=temp;
        size+=a;
    }

    printf("\nmerged array is : ");
    for(int i=0;i<size;i++){
        printf("%d ",result[i]);
    }
    free(result);

}