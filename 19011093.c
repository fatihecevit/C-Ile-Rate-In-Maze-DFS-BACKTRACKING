/*
Created by Fatih ECEVÝT
19011093
M.Amaç Güvensan
*/

#include <stdio.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100


// Fonksiyonda herhangi bi ilerleme olmadýðý / txt dosyasýndan ilk okunduðu halini yazdýrmak içi kullanýlýr
void yazdir(int N, int M,int A[][MAX]) 
{ 
	int i=0,j=0;
    for (i = 0; i < N; i++) { 
        for (j = 0; j < M; j++) {
        	if(A[i][j]==1){
        		if(j % 3==0){
        			printf("+ ");	
				}else{
					printf("- ");
				}
        		
			}
			else if(A[i][j]==2){
				printf("l ");
			}
			else if(A[i][j]==0){
				printf("  ");
			}
			else if(A[i][j]==6){
				printf("O ");
			}
			else{
				printf("%d ", A[i][j]); 
			}
       		
		}
		  printf("\n");
    }
}
void yazdir2(int N, int M,int A[][MAX],int B [][MAX]) 
{ 
	int i=0,j=0;
    for (i = 0; i < N; i++) { 
        for (j = 0; j < M; j++) {
        	if(A[i][j]==1){
        		if(j % 3==0){
        			printf("+ ");	
				}else{
					printf("- ");
				}
			}
			else if(A[i][j]==2){
				printf("l ");
			}
			else if(A[i][j]==0){
				if(B[i][j]==1){
					printf("* ");
				}
				else if(B[i][j]==3){
					printf("' ");
				}else{
					printf("  ");	
				}
				
			}
			else if(A[i][j]==6){
				printf("O ");
			}
			else{
				printf("%d ", A[i][j]); 
			}
       		
		}
		  printf("\n");
    }
}

void gecikme(int salise)
{
    long dur;
    clock_t simdi,sonra;

    dur = salise*(CLOCKS_PER_SEC/1000);
    simdi = sonra = clock();
    while( (simdi-sonra) < dur )
        simdi = clock();
}

int yol_bulma(int labirent[MAX][MAX], int cikis[MAX][MAX],int gidilen[MAX][MAX] ,int N,int M, int x, int y,int *puan,int cikis_satir,int cikis_sutun)
{	

	int tmp=0;
  //Mevcut hücrenin hedefimiz olup olmadýðýný kontrol eder.Eðer mevcut konum çýkýþ ise hedefe baþarý ile ulaþmýþýz demektir.
  if (x == cikis_satir && y == cikis_sutun)
  {
    //Eðer mevcut hücre hedefimiz ise bir yol olarak iþaretler
    cikis[x][y] = 1;
    gidilen[x][y] = 1;
    return 1;
  }
  // Mevcut hücrenin matrisimizin sýnýrlarý içinde olup olmadýðýný kontrol eder,
  // Ayrýca bir duvar olmadýðýndan ve duvarýn yolumuza çýkmadýðýndan emin olur.
  else if (x >= 0 && y >= 0 && y < N && x < M && labirent[x][y] != 1 && labirent[x][y] != 2 && cikis[x][y] == 0) 
  {
    //Hücreye gidiþ güvenliyse hücreyi ziyaret eder. Hem tüm ziyatret edilen hem de yalnýzca çýkýþa giden yolu gösteren matrislerimizde mevcut konumu gidildi(1) olarak iþaretler
    cikis[x][y] = 1;
    gidilen[x][y] = 1;
      if(labirent[x][y]==6){
    	*puan=*puan+10;
    	labirent[x][y]=0;
	}
     system("cls");
     gecikme(25);
    yazdir2(M,N,labirent,gidilen);
    //yazdir2(M,N,labirent,cikis);// Uðranýlan tüm yollarý anlýk görmek için üstteki yazdir çaðrýsý yorum satýrýna alýnýp bu çalýþtýrýlabilir.
    printf("Anlik puaniniz : %d \n",*puan);
    
	
    //Sað yönde ilerler
    if (yol_bulma(labirent, cikis,gidilen, N,M, x, y + 1,puan,cikis_satir,cikis_sutun)){
    	return 1;
	}
    //Aþaðý yönde ilerler
   else if (yol_bulma(labirent, cikis,gidilen, N ,M,x + 1, y,puan,cikis_satir,cikis_sutun)){
   		return 1;
   }
    //Sol gyönde ilerler
   else if (yol_bulma(labirent, cikis,gidilen, N ,M,x, y - 1,puan,cikis_satir,cikis_sutun)){
   		return 1;
   }
      
    //Yukarý yönde ilerler
   else  if (yol_bulma(labirent, cikis,gidilen, N , M,x - 1, y,puan,cikis_satir,cikis_sutun)){
  	 	return 1; 
   }
    //BACKTRACKÝNG (Çýkýþ yolunu bulamadýðý - sað aþaðý sol yukarý yönlerini deneyerek çýkýþa ulaþamadýðý için son baþarýlý ilerleme kaydettiði yere dönüþ yapar
    cikis[x][y] = 3; //Gidildi fakat çýkýþa ulaþýlamadý mesajýný yazdýrýrken verebilmek için
    tmp=0;
    if( cikis[x][y] == 3){
    	//Yol geniþliði 1 olan çýkmaz sokakta olup olmadýðý kontrolü. Etrafýnýn 3 tarafýnýn duvarla kaplý olduðuna bakýlýr.
    	if((labirent[x][y+1] == 1) || (labirent[x][y+1] == 2)){
    		tmp++;
		}
		if((labirent[x+1][y] == 1) || (labirent[x+1][y] == 2)){
    		tmp++;
		}
		if((labirent[x][y-1] == 1) || (labirent[x][y-1] == 2)){
    		tmp++;
		}
		if((labirent[x-1][y] == 1) || (labirent[x-1][y] == 2)){
    		tmp++;
		}
		if(tmp==3){
			*puan=*puan-5;
			/*printf("Tek Cýkýslý Cýkmaz Sokak !!! \n");	
    		yazdir2(M,N,labirent,cikis);
    		printf("Anlik puaniniz : %d \n",*puan);*/
    		
		}else{
			//Yol geniþliði 2 olan çýkmaz sokakta olup olmadýðý kontrolü. 8 farklý ihtimal deðerlendirilir
		tmp=0;
		if((labirent[x][y-1] == 1) || (labirent[x][y-1] == 2)){
			if((labirent[x+1][y] == 1) || (labirent[x+1][y] == 2)){
				if((labirent[x][y+2] == 1) || (labirent[x][y+2] == 2)){
					tmp++;
				}
			}
		}
		
		if((labirent[x][y+1] == 1) || (labirent[x][y+1] == 2)){
			if((labirent[x+1][y] == 1) || (labirent[x+1][y] == 2)){
				if((labirent[x][y-2] == 1) || (labirent[x][y-2] == 2)){
					tmp++;
				}
			}
		}
		if((labirent[x][y+1] == 1) || (labirent[x][y+1] == 2)){
			if((labirent[x-1][y] == 1) || (labirent[x-1][y] == 2)){
				if((labirent[x+2][y] == 1) || (labirent[x+2][y] == 2)){
					tmp++;
				}
			}
		}
		if((labirent[x][y+1] == 1) || (labirent[x][y+1] == 2)){
			if((labirent[x+1][y] == 1) || (labirent[x+1][y] == 2)){
				if((labirent[x-2][y] == 1) || (labirent[x-2][y] == 2)){
					tmp++;
				}
			}
		}
		if((labirent[x][y+1] == 1) || (labirent[x][y+1] == 2)){
			if((labirent[x-1][y] == 1) || (labirent[x-1][y] == 2)){
				if((labirent[x][y-2] == 1) || (labirent[x][y-2] == 2)){
					tmp++;
				}
			}
		}
		if((labirent[x][y-1] == 1) || (labirent[x][y-1] == 2)){
			if((labirent[x-1][y] == 1) || (labirent[x-1][y] == 2)){
				if((labirent[x][y+2] == 1) || (labirent[x][y+2] == 2)){
					tmp++;
				}
			}
		}
		if((labirent[x][y-1] == 1) || (labirent[x][y-1] == 2)){
			if((labirent[x-1][y] == 1) || (labirent[x-1][y] == 2)){
				if((labirent[x+2][y] == 1) || (labirent[x+2][y] == 2)){
					tmp++;
				}
			}
		}
		if((labirent[x][y-1] == 1) || (labirent[x][y-1] == 2)){
			if((labirent[x+1][y] == 1) || (labirent[x+1][y] == 2)){
				if((labirent[x-2][y] == 1) || (labirent[x-2][y] == 2)){
					tmp++;
				}
			}
		}
		if(tmp==1){
			*puan=*puan-5;
			/*printf("Cift Cikisli Cikmaz Sokak !!! \n");	
    		yazdir2(M,N,labirent,cikis);
    		printf("Anlik puaniniz : %d \n",*puan);*/
    		
		}
		
	}
    	
	}
    
    gidilen[x][y] = 0;
    
    return 0;
  }
  return 0;
}

// ANA FONKSIYON 
int main() 
{ 
	FILE *dosya;
	FILE *f;
	dosya=fopen("maze.txt","r");
	char lab[1000],dosya_adi[20];  
	int labirent[MAX][MAX],alinan_yol[MAX][MAX],gidis[MAX][MAX];
	int i,j,N,M,bas_satir,bas_sutun,cikis_satir,cikis_sutun;
	int line=0,puan=0,satir=0,sutun=0,tmp=0;
	char a='*',sonraki;
	
	//Satýr ve sütun sayýsý bulunur
	f=fopen("maze.txt","r");
	if(f==NULL)
	{
		puts("Dosya ACMA ISLEMI BASARISIZ OLDU");
		getch();
	}
	while(a!=EOF) 
	{
		a=fgetc(f); 
		sutun++;
		if(a=='\n'){
			sutun--;
			tmp=sutun;
			sutun=0;
			satir++;
			sonraki=fgetc(f);
		}
	
	}		
	
		sutun=tmp;
	// Txt dosyasýndaki labirent formatý matrisde 0-1'ler ile ifade edilir.
	if((dosya!= NULL)){
		while(fgets(lab,sizeof(lab),dosya)){
				
			for(i=0;i<sutun;i++){
				if(lab[i]=='+' || lab[i]=='-'){
					labirent[line][i]=1;
				}else if( lab[i]=='|' ){
					labirent[line][i]=2;
				}else if(lab[i]=='0' ){
					labirent[line][i]=6;
				}else{
					labirent[line][i]=0;
					if(lab[i]=='b'){
						bas_sutun=i;
						bas_satir=line;
					}
					if(lab[i]=='c'){
						cikis_sutun=i;
						cikis_satir=line;
					}
					
				}
				
			}
			line++;
		}
	
	}
	i=0;
    for(i=0;i<satir;i++){
    	for(j=0;j<sutun;j++){
    		alinan_yol[i][j]=0;
    		gidis[i][j]=0;
		}
	}
	
    
    printf("LABIRENTIN ILK DURUMU :\n\n");
    yazdir(satir,sutun,labirent);
    printf("Anlik puaniniz : %d \n",puan);
	
	 if (yol_bulma(labirent,alinan_yol,gidis, sutun,satir ,bas_satir, bas_sutun,&puan,cikis_satir,cikis_sutun)==1){
	 	printf("\n\n----------------------\n");
	 	printf ("\n LABIRENTTEN BASARILI SEKILDE CIKIS YAPILDI\n");
	 	printf("\n----------------------\n");
	 	printf (" \n UGRANILAN TUM YOLLAR:\n\n");
   		yazdir2(satir,sutun,labirent,alinan_yol);
   		printf("TOPLAM PUANINIZ : %d \n",puan);
   		printf("\n\n----------------------\n");
   		printf("\nCIKISA GIDEN YOL:\n\n");
     	yazdir2(satir,sutun,labirent,gidis);
     	printf("TOPLAM PUANINIZ  : %d \n",puan);
	 }
	 
  else
    printf("CIKIS YOLU YOK, LABÝRENTTE KISILI KALDI \n");
    

  	
  	return 0;
  	
} 
