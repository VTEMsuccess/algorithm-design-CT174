/* 

	VO THANH EM b2012081

*/

/* Thuat toan THAM AN
- Sap xep cac canh theo thu tu tang dan do dai
- Uu tien chon cac canh co do dai nho nhat dua vao phuong an
- Mot canh duoc dua vao phuong an neu no khong tao thanh dinh cap 3 va khong tao thanh chu trinh thieu

Du Lieu trong file TSP.txt

*/

#include <stdio.h>
#define size 30

typedef struct{
	float do_dai;
	int dau, cuoi;
} canh;

void read_file(char File_Name[], canh a[], int *n){
	int i, j, t;
	float temp;
	FILE *f;
	f = fopen(File_Name, "r");
	if( f==NULL){
		printf("Loi mo file!!");
		return ;
	}
	fscanf(f,"%d",n); // n so dinh cua do thi
	int k = 0;
	for (i=0; i<*n; i++)
		for( j=i; j<*n; j++)
			if(i==j) for (t=0; t<=j; t++) fscanf(f,"%f",&temp);  //doc bo qua cac so duoi duong cheo dinh
			else{
				fscanf(f,"%f",&a[k].do_dai);  // Doc luu tru cac so tren duong cheo chinh
				a[k].dau=i;
				a[k].cuoi=j;
				k++;
			}
			
	fclose(f);
}

void in_ds_canh(canh a[], int m, int la_PA){
	int i;
	float tong=0.0;
	for( i=0; i<m; i++){
		printf("%3d %C%c=%8.2f\n",(i+1), a[i].dau+65, a[i].cuoi+65, a[i].do_dai);
		if(la_PA)
		tong=tong+a[i].do_dai;
	}
	if(la_PA)
		printf("Tong do dai cac canh = %8.2f\n",tong);
}

void Swap( canh *x, canh *y){
	canh temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(canh a[], int m){
	int i, j;
	for(i=0; i<= m-2; i++)
		for( j=m-1; j>=i+1; j--)
			if(a[j].do_dai < a[j-1].do_dai)
			Swap(&a[j], &a[j-1]);
}

int dinh_cap3( canh PA[], int k, canh moi){
	int i, dem;
	i=0;
	dem=1;
	while( i<k && dem <3){
		if( moi.dau==PA[i].dau || moi.dau==PA[i].cuoi)
		dem++;
		i++;
	}
	if( dem == 3)  return 1;
	
	i=0;
	dem= 1;
	while(i<k && dem<3){
		if(moi.cuoi==PA[i].dau || moi.cuoi==PA[i].cuoi)
			dem++;
		i++;	
	}
	return dem==3;
}

void init_forest(int parent[], int n){
	int i;
	for( i=0; i<n; i++)
		parent[i]=i;
}

int find_root(int parent[], int u){
	while( u != parent[u])
		u = parent[u];
	return u;
}

int chu_trinh(int r_dau, int r_cuoi){
	return (r_dau == r_cuoi);
}

void update_forest(int parent[], int r1, int r2){
	parent[r2] = r1; // Hop nhat hai cay voi nhau
}

void Greedy(canh ds_canh[], int n, canh PA[]){
	int i,j;
	int parent[n];
	init_forest(parent, n);
	int r_dau, r_cuoi;
// chon cac canh nho nhat khong tao thanh dinh cap 3 va khong tao thanh chu trinh thieu de dua vao PA

	j=0;
	for(i=0; i<n*(n-1)/2 && j<n-1; i++){
		r_dau = find_root(parent, ds_canh[i].dau);
		r_cuoi = find_root(parent, ds_canh[i].cuoi);
		if( !dinh_cap3( PA, j, ds_canh[i]) && !chu_trinh(r_dau, r_cuoi)){
			PA[j]=ds_canh[i]; //ds_canh[i] khong tao thanh dinh cap 3 , khong tao thanh chu trinh thieu khi dua vao PA
			j++;
			update_forest(parent, r_dau, r_cuoi);	//Hop nhat 2 cay: Dat cha cua nut goc cuoi bang goc dau
		}
	}
	
// den day PA da co n-1 canh
//Tim mot canh trong so cac canh chua xet dua vao PA neu no khong tao thanh dinh cap 3 Nhungw phai tao thanh CHU TRINH

	for( ; i<n*(n-1)/2; i++){
		r_dau = find_root(parent, ds_canh[i].dau);
		r_cuoi = find_root(parent, ds_canh[i].cuoi);
		if( (!dinh_cap3( PA, n-1, ds_canh[i]) && !chu_trinh(r_dau, r_cuoi)) ){
			PA[n-1]=ds_canh[i];
			break;		//ket thuc vi PA da co du n canh, tao thanh chu trinh
		}
	}

}

int main(){
	canh ds_canh[size];
	int n;
	read_file("TSP.txt",ds_canh, &n);
	printf("Danh sach cac canh cua do thi\n");
	in_ds_canh(ds_canh, n*(n-1)/2, 0);
	
	BubbleSort(ds_canh, n*(n-1)/2);
	printf("Danh sach cac canh cua do thi da duoc SAP XEP\n");
	in_ds_canh(ds_canh, n*(n-1)/2, 0);
	canh PA[n];
	Greedy(ds_canh, n, PA);
	printf("PHUONG AN\n");
	
	in_ds_canh(PA, n, 1);
	
	return 0;
}
































