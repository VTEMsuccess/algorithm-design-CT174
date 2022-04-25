//buoi_1: thuc hanh sap xep
// 3 thuat toan sap xep don gian O(n^2) chon	xen	noi bot
//2 thuat toan sap xep phuc tap O(nlogn) quicksort	heapsort

#include<stdio.h>
#include<malloc.h>

typedef int keytype;
typedef float othertype;

typedef struct{
	keytype key;
	othertype otherfields;
} recordtype;

void Swap(recordtype *x,recordtype *y){
	recordtype t;
	t = *x;
	*x = *y;
	*y = t;
}

//sap xep chon
void SelectionSort(recordtype a[], int n){
	int i, j, lowindex;
	keytype lowkey;
	
	for( i=0; i<=n-2; i++){
		lowkey = a[i].key;
		lowindex = i;
		for (j=i+1; j<=n-1; j++)
			if(a[j].key < lowkey){
				lowkey = a[j].key;
				lowindex = j;
			}
		Swap(&a[i], &a[lowindex]);
	}
}

//sap xep xen
void InsertionSort( recordtype a[], int n){
	int i, j;
	
	for( i=0; i<=n-1; i++)
		for (j=i; (j>=1 && a[j].key < a[j-1].key); j-- )
			Swap(&a[j], &a[j-1]);
}

//sap xep noi bot
void BubbleSort( recordtype a[], int n) {
	int i, j;
	for( i=0; i<n-2; i++)
		for (j=n-1; j>=i+1; j--)
		if( a[j].key < a[j-1].key)
			Swap(&a[j], &a[j-1]);
}

	//sap xep nhanh QuickSort
//ham tim chot
int FindPivot(recordtype a[], int i, int j){
	keytype firstkey;
	int k;
	k = i+1;
	firstkey = a[i].key;
	while (k <= j && a[k].key == firstkey ) k++;
	if( k>j ) return -1;
	if( a[k].key > firstkey) return k;
	return i;
}
//ham phan hoach Partition
int Partition(recordtype a[], int i, int j, keytype pivot){
	int L, R;
	L = i;
	R = j;
	while ( L<=R ){
		while (a[L].key < pivot) L++;
		while (a[R].key >= pivot) R--;
		if( L<R ) Swap (&a[L],&a[R]);
	}
	return L;	//tra ve diem phan hoach
}
//ham QuickSort
void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivot(a,i,j);
	if (pivotindex != -1){
		pivot = a[pivotindex].key;
		k = Partition(a,i,j,pivot);
		QuickSort(a,i,k-1);
		QuickSort(a,k,j);
	}
}

	//sap xep vun dong HeapSort
//ham PushDown
void PushDown(recordtype a[], int first, int last){
	int r = first;
	while( r <= (last-1)/2)
	if(last == 2*r+1){
		if(a[r].key > a[last].key) Swap (&a[r], &a[last]);
		r = last;
	}else
	if( (a[r].key > a[2*r+1].key) && (a[2*r+1].key <= a[2*r+2].key)){
		Swap(&a[r], &a[2*r+1]);
		r = 2*r+1;
	}else
	if( (a[r].key > a[2*r+2].key) && (a[2*r+2].key < a[2*r+1].key)){
		Swap(&a[r], &a[2*r+2]);
		r = 2*r+2;
	}
	else
	r = last;
}

//ham HeapSort
void HeapSort(recordtype a[], int n){
	int i;
	//tao Heap
	for( i = (n-2)/2; i>=0; i--)
		PushDown(a,i,n-1);
	for (i = n-1; i>=2; i--){
		Swap(&a[0], &a[i]);
		PushDown(a,0,i-1);
	}
	Swap(&a[0],&a[1]);
}

//doc file
void Read_Data( recordtype a[], int *n){
	FILE *f;
	f=fopen("data.txt", "r");
	int i=0;
	if(f!=NULL)
	while (!feof(f)){
		fscanf(f,"%d%f",&a[i].key, &a[i].otherfields);
		i++ ;
	} else printf("Loi mo file\n");
	fclose(f);
	*n=i;
}

void Print_Data( recordtype a[], int n){
	int i;
	for( i=0; i<n; i++)
	printf("%3d%5d%8.2f\n",i+1, a[i].key, a[i].otherfields);
}

int main(){
	recordtype a[20];
	int n;
	Read_Data(a,&n);
	printf("Du lieu ban dau\n");
	Print_Data(a,n);
	
//	SelectionSort(a,n);			O(n^2)

//	InsertionSort(a,n);			O(n^2)
	
//	BubbleSort(a,n);			O(n^2)


//	QuickSort(a,0,n-1);			O(nlogn) truong hop tot nhat. com xau nhat la O(n^2)
	
	HeapSort(a,n); // O(nlogn)
	printf("\nsau khi sap xep: \n");
	Print_Data(a,n);
	return 0;
}
















