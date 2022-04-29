
/*	VO THANH EM B2012081	*/ 

// Bai toan Cai ba lo 1
// Moi do vat co so luong khong gioi han
// Du lieu cho trong file QHD_CaiBalo1.txt
// Giai bai toan bang thuat toan Quy Hoach Dong

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char TenDV[20];
	float  GT;
	int  TL, PA; //PA la so do vat duoc chon
} DoVat;

DoVat * ReadFromFile(int *W, int *n){
     FILE *f;
     f = fopen("QHD_CaiBalo1.txt", "r");
     
     fscanf(f, "%d",W); // Xac dinh trong luong Ba lo
     
	 DoVat *dsdv;
	 dsdv=(DoVat*)malloc(sizeof(DoVat));
	 int i=0;
 	 while (!feof(f)){
	   fscanf(f, "%d%f%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
	   
	   dsdv[i].PA=0;
	   i++;
	//   dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));  
	 }
	 *n=i;
     fclose(f);
     return dsdv;
}

void InDSDV(DoVat *dsdv ,int n, int W){
	int i, TongTL=0;
	float  TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri | Phuong an |\n");
	printf("|---|--------------------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-20s|%5d    |%9.2f|%8d   |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT, dsdv[i].PA);
		
		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|--------------------|---------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %d\n",W);
	
	printf("Tong trong luong = %d\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
}

void TaoBang(DoVat *dsdv, int n, int W, float F[][W+1], int X[][W+1]){
	int xk, yk, k;
	int Xmax, V;
	float Fmax;


//dien vao hang dau tien cua bang

	for(V=0; V<=W; V++){
		X[0][V] = V/dsdv[0].TL;	// X la trong luong
		F[0][V] = X[0][V] * dsdv[0].GT;	// F la gia tri
	}

// dien cac dong con lai
	for(k=1; k<n; k++)
		for(V=0; V<=W; V++){
			Fmax = F[k-1][V];
			Xmax = 0;
			yk = V/dsdv[k].TL; // ba lo 1	QHD
			
			// ba lo 2 QHD: yk = min(dsdv[k].SL, V/dsdv[k].TL);
			
			// ba lo 3 QHD: yk = min(1, V/dsdv[k].TL);
			
			for(xk=1; xk <= yk; xk++)
				if(F[k-1][V-xk*dsdv[k].TL] + xk*dsdv[k].GT > Fmax){
					Fmax = F[k-1][V-xk*dsdv[k].TL] + xk*dsdv[k].GT;
					Xmax = xk;		
				}
			F[k][V] = Fmax;
			X[k][V] = Xmax;
		}
}

void InBang(int n, int W, float F[][W+1], int X[][W+1]){
	int V,k;
	printf("\n\nBang F va X: \n\n");
	
	for(k=0; k<n; k++){
		for(V=0; V<= W; V++)
		printf("%c%4.1f|%2d", 186, F[k][V],X[k][V]);
	printf("%c\n",186);
	}	
}

void TraBang(DoVat *dsdv, int n, int W, int X[][W+1]){
	int k, V;
	V = W;
	for(k=n-1; k>=0; k--){
		dsdv[k].PA = X[k][V];
		V = V - X[k][V] * dsdv[k].TL;
	}
}




	
int main(){
	DoVat * dsdv;	// Danh sach cac do vat (mang dong cua cac do vat)
	int n,W; 			

	dsdv=ReadFromFile(&W, &n);
	
	
	
	float F[n][W+1];
	int X[n][W+1];
	
	TaoBang(dsdv, n, W, F, X);
	
	InBang(n, W, F, X);
	TraBang(dsdv, n,W,X);
	InDSDV(dsdv, n, W);
	
	free(dsdv);
	return 0;
}
