/*
Created by Fatih ECEV�T
19011093
M.Ama� G�vensan
*/

#include <stdio.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100


// Fonksiyonda herhangi bi ilerleme olmad��� / txt dosyas�ndan ilk okundu�u halini yazd�rmak i�i kullan�l�r
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
  //Mevcut h�crenin hedefimiz olup olmad���n� kontrol eder.E�er mevcut konum ��k�� ise hedefe ba�ar� ile ula�m���z demektir.
  if (x == cikis_satir && y == cikis_sutun)
  {
    //E�er mevcut h�cre hedefimiz ise bir yol olarak i�aretler
    cikis[x][y] = 1;
    gidilen[x][y] = 1;
    return 1;
  }
  // Mevcut h�crenin matrisimizin s�n�rlar� i�inde olup olmad���n� kontrol eder,
  // Ayr�ca bir duvar olmad���ndan ve duvar�n yolumuza ��kmad���ndan emin olur.
  else if (x >= 0 && y >= 0 && y < N && x < M && labirent[x][y] != 1 && labirent[x][y] != 2 && cikis[x][y] == 0) 
  {
    //H�creye gidi� g�venliyse h�creyi ziyaret eder. Hem t�m ziyatret edilen hem de yaln�zca ��k��a giden yolu g�steren matrislerimizde mevcut konumu gidildi(1) olarak i�aretler
    cikis[x][y] = 1;
    gidilen[x][y] = 1;
      if(labirent[x][y]==6){
    	*puan=*puan+10;
    	labirent[x][y]=0;
	}
     system("cls");
     gecikme(25);
    yazdir2(M,N,labirent,gidilen);
    //yazdir2(M,N,labirent,cikis);// U�ran�lan t�m yollar� anl�k g�rmek i�in �stteki yazdir �a�r�s� yorum sat�r�na al�n�p bu �al��t�r�labilir.
    printf("Anlik puaniniz : %d \n",*puan);
    
	
    //Sa� y�nde ilerler
    if (yol_bulma(labirent, cikis,gidilen, N,M, x, y + 1,puan,cikis_satir,cikis_sutun)){
    	return 1;
	}
    //A�a�� y�nde ilerler
   else if (yol_bulma(labirent, cikis,gidilen, N ,M,x + 1, y,puan,cikis_satir,cikis_sutun)){
   		return 1;
   }
    //Sol gy�nde ilerler
   else if (yol_bulma(labirent, cikis,gidilen, N ,M,x, y - 1,puan,cikis_satir,cikis_sutun)){
   		return 1;
   }
      
    //Yukar� y�nde ilerler
   else  if (yol_bulma(labirent, cikis,gidilen, N , M,x - 1, y,puan,cikis_satir,cikis_sutun)){
  	 	return 1; 
   }
    //BACKTRACK�NG (��k�� yolunu bulamad��� - sa� a�a�� sol yukar� y�nlerini deneyerek ��k��a ula�amad��� i�in son ba�ar�l� ilerleme kaydetti�i yere d�n�� yapar
    cikis[x][y] = 3; //Gidildi fakat ��k��a ula��lamad� mesaj�n� yazd�r�rken verebilmek i�in
    tmp=0;
    if( cikis[x][y] == 3){
    	//Yol geni�li�i 1 olan ��kmaz sokakta olup olmad��� kontrol�. Etraf�n�n 3 taraf�n�n duvarla kapl� oldu�una bak�l�r.
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
			/*printf("Tek C�k�sl� C�kmaz Sokak !!! \n");	
    		yazdir2(M,N,labirent,cikis);
    		printf("Anlik puaniniz : %d \n",*puan);*/
    		
		}else{
			//Yol geni�li�i 2 olan ��kmaz sokakta olup olmad��� kontrol�. 8 farkl� ihtimal de�erlendirilir
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
	
	//Sat�r ve s�tun say�s� bulunur
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
	// Txt dosyas�ndaki labirent format� matrisde 0-1'ler ile ifade edilir.
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
    printf("CIKIS YOLU YOK, LAB�RENTTE KISILI KALDI \n");
    

  	
  	return 0;
  	
} 
