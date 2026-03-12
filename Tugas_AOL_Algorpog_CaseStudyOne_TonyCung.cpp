// Nama : Tony Cung 
// NIM 	: 2902645255
// Dosen : Fidelson Tanzil, S.Kom., M.TI

// Hasil AOL Studi Kasus Pertama 

#include <stdio.h>
#include <string.h>

int main(){
	char katasatu[110], katadua[110];
	gets(katasatu);
	gets(katadua);
	int lenA= strlen(katasatu);
	int lenB= strlen(katadua);
	
	
	// Fungsi untuk menentukan panjang minimum dari kedua kata
	// Jika panjang kata satu lebih kecil dari kata dua maka minimal panjang kata ditentukan sesuai panjang kata satu dan sebaliknya
	int minLen=(lenA<lenB? lenA:lenB);

	// Fungsi untuk mencari prefix (awalan) yang sama
	int prefixKata=0;
	for(int i=0;i<minLen;i++){
		if(katasatu[i]==katadua[i]){
			prefixKata++; 
	}else{
		break; 
	}
}

	// Fungsi untuk mencari suffix (akhiran) yang sama 
	int suffixKata=0;
	for(int i=0;i<minLen;i++){
		if(katasatu[lenA-1-i]==katadua[lenB-1-i]){
			suffixKata++;  
	}else{
		break;
	}
}

	// Fungsi ini menandakan tidak ada prefix dan suffix yang sama 
	if(prefixKata==0 && suffixKata==0){
		printf("No Output\n");
		return 0;
	}
	
	char hasil[110];
	int gabungan=0;
	
	// Fungsi untuk menyimpan prefix dan suffix ke dalam hasil 
	for(int i=0;i<prefixKata;i++){
		hasil[gabungan++]=katasatu[i];
	}
	
	for(int i=suffixKata;i>0;i--){
		hasil[gabungan++]=katasatu[lenA-i];
	}
	
	hasil[gabungan]='\0';
	
	// Fungsi untuk mengubah huruf: huruf besar -> kecil, huruf kecil -> besar
	for(int i=0;i<gabungan;i++){
		if(hasil[i]>='a'&& hasil[i]<='z'){
			hasil[i]-=32;
		}else if(hasil[i]>='A'&& hasil[i]<='Z'){
			hasil[i]+=32;
		}
	}
	
	printf("%s", hasil);
	
	return 0;
}
