/* 

	VO THANH EM b2012081

*/

/* buoi_2 Thuc Hanh 	*/

// bai toan cai ba lo 3
// moi do vat co so luong 1 duy nhat
// du lieu cho trong file "CaiBaLo3.txt"
// su dung pp tham an

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct{
	char TenDV[20];
	float TL, GT, DG;
	int SL, So_DV_Duoc_Chon;
} DoVat;

void Swap(DoVat *X, DoVat*Y){
	DoVat temp;
	temp = *X;
	*X = *Y;
	*Y = temp;
}

DoVat * ReadFromFile( float *W, int *n){
	FILE *f;
	f = fopen("CaiBalo3.txt", "r");
	fscanf(f, "%f",W); 	// xac dinh trong luong cai ba lo
	DoVat *dsdv;
	dsdv = (DoVat*) malloc( sizeof(DoVat));
	int i=0;
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]",&dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].So_DV_Duoc_Chon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1)); 
		// c++ thi dung realloc(dsdv, sizeof(DoVat)*(i+1)
	}
	*n=i; 	//so luong do vat
	fclose(f);
	return dsdv; //mang cac do vat
}

void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for (i=0; i<=n-2; i++)
		for( j=n-1; j>=i+1; j--){
			if(dsdv[j].DG > dsdv[j-1].DG)	// de sap xep giam dan thi doi dau < thanh dau lon >
				Swap(&dsdv[j], &dsdv[j-1]);
		}
}

void InDSDV( DoVat *dsdv, int n, float W){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an thu duoc tu ky thuat THAM AN nhu sau: \n");
	printf("|---|--------------------|----------|---------|----------|-----------|-----------------|\n");
	printf("|STT|     Ten Do Vat     | T. Luong | Gia Tri | So Luong |  Don Gia  | So DV duoc chon |\n");
	printf("|---|--------------------|----------|---------|----------|-----------|-----------------|\n");
	for( i=0; i<n; i++){	//dau - trong |%-3d| co nghia la canh trai
		printf("|%-3d|%-20s| %9.2f|%9.2f|%5d     |%9.2f  |%8d	       |\n", (i+1), dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT,dsdv[i].SL, dsdv[i].DG, dsdv[i].So_DV_Duoc_Chon);
		TongTL = TongTL + dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].So_DV_Duoc_Chon *dsdv[i].GT;
	}
	printf("|---|--------------------|----------|---------|----------|-----------|-----------------|\n");
	printf("\nTrong luong cua ba lo = %-9.2f\n",W);
	printf("\nTong trong luong cac do vat duoc chon = %-9.2f\n\nTong gia tri = %-9.2f\n",TongTL, TongGT);
}

int min(int a, int b){
	return a<b? a:b;
}

void Greedy(DoVat *dsdv, int n, float W){
	int i;
	for( i=0; i<n; i++){
		
		dsdv[i].So_DV_Duoc_Chon= min(1, W/dsdv[i].TL); //CaiBaLo3
		
	//	dsdv[i].So_DV_Duoc_Chon= min(dsdv[i].SL, W/dsdv[i].TL); cai ba lo 2
	
	//	dsdv[i].So_DV_Duoc_Chon = ( W / dsdv[i].TL ); cai balo1
	
		W = W - dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
	}
}

int main(){
	
	int n;
	float W;
	DoVat *dsdv;
	dsdv = ReadFromFile(&W, &n);
	BubbleSort(dsdv,n);
	Greedy(dsdv,n,W);
	InDSDV(dsdv,n,W);
	free(dsdv);
	
	return 0;
}





















