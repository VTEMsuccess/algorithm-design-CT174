
/*	VO THANH EM B2012081	*/ 

// Bai toan tam giac so i dong va j cot

// Du lieu cho trong file QHD_tam_giac_so.txt
// Giai bai toan bang thuat toan Quy Hoach Dong

#include <stdio.h>
#define size 50


void ReadData(int a[][size], int *n){
     FILE *f;
     f = fopen("QHD_tam_giac_so.txt", "r");
     if( f==NULL){
     	printf("Loi mo file");
		 return;
	 }
   
	 int i=0, j;
 	 while (!feof(f)){
 	 	for (j=0; j<=i; j++)
	   		fscanf(f, "%d", &a[i][j]);
	   i++;
	   
	 }
	 *n=i;
     fclose(f);
}

void PrintData(int a[][size], int n){
	int i, j;
	printf("\nTam giac so da cho\n");
	for(i=0; i<n; i++){
		for( j=0; j<=i; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
}

int cs_max(int n, int F[][n], int i, int j){
	if( j==0)
		return (F[i-1][0] > F[i-1][1]) ? 0:1;
	if(j==i)
		return i-1;
	if(j==i-1)
		return (F[i-1][i-2] > F[i-1][i-1]) ? i-2 : i-1;
		
	if (F[i-1][j-1] > F[i-1][j] && F[i-1][j-1] > F[i-1][j+1] ) 
		return j-1;
	if (F[i-1][j] > F[i-1][j-1] && F[i-1][j] > F[i-1][j+1] ) 
		return j;
	if (F[i-1][j+1] > F[i-1][j] && F[i-1][j+1] > F[i-1][j-1] ) 
		return j+1;
		
}

void TaoBang(int a[][size], int n, int F[][n]){
	int i,j;
	//2 dong dau tien cua bang F duoc xac dinh cu the
	
	F[0][0] = a[0][0];
	F[1][0] = a[1][0] + F[0][0];
	F[1][1] = a[1][1] + F[0][0];
	
	//tu dong thu 3 (i=2) tro ve sau
	//moi phan tu cua bang F duoc xac dinh vao dong truoc do (Truy Hoi)
	
	for(i=2; i<n; i++)
		for(j=0; j<=n; j++){
			int k=cs_max(n, F,i,j);
			F[i][j] = a[i][j] + F[i-1][k];
		}
		
}

void InBang(int n, int  F[][n]){
	int i,j;
	printf("\n\nBang F \n\n");
	
	for(i=0; i<n; i++){
		for(j=0; j<= i; j++)
		printf("%5d", F[i][j]);
	printf("\n");
	}	
}

int cs_max_dong_cuoi(int F[], int j){
	int somax=F[0];
	int maxindex = 0;
	int k;
	for(k=1; k<=j; k++)
		if(F[k]>somax){
			somax = F[k];
			maxindex=k;
		}
	return maxindex;
	
}

void TraBang(int a[][size], int n, int F[][n], int PA[]){
	int i,j;
	//xac dinh chi so j cua phan tu lon nhat trong dong cuoi cua bang F
	j=cs_max_dong_cuoi(F[n-1],n-1);
	
	//phan tu cuoi cung cua duong di tuc la PA[n-1]
	//la phan tu cua dong cuoi cung cua bang a, ung voi cot j vua tim thay o tren 
	PA[n-1]= a[n-1][j];
	
	//xet cac dong cua bang F , tu dong n-1 den dong 1
	//de xac dinh cac phan tu cua PA tu PA[n-2] den PA[o]
	
	for( i=n-1; i>=1; i--){
		
		//can cu vao chi so cot j cua dong duoi (dong i) cua bang F
		// ma xac dinh chi so cot j cua dong tren (dong n-1) cua bang F
		
		j=cs_max(n,F,i,j);
		
		//PA[i-1] 	la phan tu cua dong i-1 cua tam giac so a
		//ung voi cot j vua tim thay
		
		PA[i-1]= a[i-1][j];	
		
	}
}

int GiaPA(int PA[], int n){
	int i;
	int sum =0;
	for(i=0; i<n; i++)	sum = PA[i];
	return sum;
}

void PrintPA(int PA[], int n){
	int i;
	printf("\n Phuong Phap QHD \n");
	printf("\nPA la duong di qua cac so: \n\n");
	printf("%d", PA[0]);
	for(i=1; i<n; i++ )printf(" => %d", PA[i]);
	printf("\n\nTong cac so tren duong di la: %d\n", GiaPA(PA,n));
}



	
int main(){
	int a[size][size]; //luu team giac so
	int n; 			

	ReadData(a, &n);
	PrintData(a,n);

	
	
	int PA;	// phuong an toi uu: mang co n phan tu
	int F[n][n];	//Bnag F: mang 2 chieu co n dong, n cot.
	
	TaoBang(a, n, F);
	InBang(n, F);
	
	TraBang(a, n, F,PA);
	PrintData(PA, n);

	

	return 0;
}
