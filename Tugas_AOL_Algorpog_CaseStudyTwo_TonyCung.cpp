// Nama : Tony Cung 
// NIM 	: 2902645255
// Dosen : Fidelson Tanzil, S.Kom., M.TI

// Hasil AOL Studi Kasus 2 

#include <stdio.h>
#include <string.h>

struct List{
    char restaurant[100];
    char city[100];
    long int cost;
    char currency[100];
    int price_range;
    float rating;
    char rating_text[100];
    long int votes;
};

FILE *fp;
int total = 0;

// Fungsi untuk membawa dan membaca data yang telah disiapkan, yaitu data restoran.csv ke dalam program
void readFile(struct List data[]){
    fp = fopen("restaurant.csv", "r");   
    if(fp == NULL){
        printf("File not found!\n");
        return;
    }
	
    char header[10000];
    fgets(header, sizeof(header), fp);  // Fungsi agar baris bagian judul (header) tidak terbaca

    while(fscanf(fp, "%[^,],%[^,],%ld,%[^,],%d,%f,%[^,],%ld\n",  // Baca semua huruf selama bukan koma dan baca angka dari data restoran.csv
                 data[total].restaurant,
                 data[total].city,
                 &data[total].cost,
                 data[total].currency,
                 &data[total].price_range,
                 &data[total].rating,
                 data[total].rating_text,
                 &data[total].votes) != EOF)
    {
        total++;
    }

    fclose(fp);
}

// Fungsi untuk menampilkan header tabel data restoran dan supaya output terlihat rapi 
void printHeader(){
    printf("%-25s %-15s %-10s %-10s %-12s %-8s %-20s %-10s\n",
           "Restaurant Name", "City", "Cost", "Currency",
           "Price Range", "Rating", "Rating Text", "Votes");
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

// Fungsi untuk menampilkan (display) data sesuai jumlah baris yang diinginkan
void displayData(struct List data[], int k){
    if(k <= 0) return;

    for(int i = 0; i < k; i++){
        printf("%-25.25s %-15.15s %-10ld %-10.10s %-12d %-8.1f %-20.20s %-10ld\n",
            data[i].restaurant,
            data[i].city,
            data[i].cost,
            data[i].currency,
            data[i].price_range,
            data[i].rating,
            data[i].rating_text,
            data[i].votes
        );
    }
}

// Fungsi agar input user tidak case-sensitive saat sorting atau input kolum yang dicari dengan mengubah huruf kapital menjadi huruf kecil
void toLowerCase(char str[]){
	for(int i=0; i<strlen(str); i++){
		if(str[i]>='A'&& str[i]<='Z'){
			str[i]+=32;
		}
	}
}


// Fungsi untuk mencari (searching) data sesuai keinginan pengguna

// Fungsi untuk mencari (searching) data dengan kata kunci berupa kata (string)
int linearSearchString(struct List data[], char column[], char key_string[]){
    int found = 0;

    for(int i = 0; i < total; i++){
        if(
            (strcmp(column, "restaurant") == 0 && strcmp(data[i].restaurant, key_string) == 0) ||
            (strcmp(column, "city") == 0 && strcmp(data[i].city, key_string) == 0) ||
            (strcmp(column, "currency") == 0 && strcmp(data[i].currency, key_string) == 0) ||
            (strcmp(column, "rating text") == 0 && strcmp(data[i].rating_text, key_string) == 0)
        ){
            if(found == 0){
                printHeader();   //kalau data ditemukan, header diprint satu kali saja 
            }
            displayData(&data[i], 1);
            found = 1;
        }
    }

    if(!found){
        printf("Sorry, the data you want is not found. Please try again\n");
    }

    return found;
}

// Fungsi untuk mencari (searching) data dengan kata kunci berupa angka (integer)
int linearSearchNumber(struct List data[], char column[], int key_number){
    int found = 0;

    for(int i = 0; i < total; i++){
        if(
            (strcmp(column, "cost") == 0 && data[i].cost == key_number) ||
            (strcmp(column, "price range") == 0 && data[i].price_range == key_number) ||
            (strcmp(column, "votes") == 0 && data[i].votes == key_number)
        ){
            if(found == 0){
                printHeader();   
            }
            displayData(&data[i], 1);
            found = 1;
        }
    }

    if(!found){
        printf("Sorry, the data you want is not found. Please try again\n");
    }

    return found;
}

// Fungsi untuk mencari (searching) data dengan kata kunci berupa angka (float)
int linearSearchFloat(struct List data[], char column[], float key_float){
	int found =0;
	
	for(int i=0; i< total; i++){
		if(strcmp(column, "rating") == 0 && data[i].rating == key_float){
			if(found == 0){
				printHeader();
			}
			displayData(&data[i], 1);
			found = 1;
		}
	}
	if(!found){
		printf("Sorry, the data you want is not found. Please try again\n");
	}
	
	return found;
}

// Fungsi untuk sorting data dengan ascending atau diurutkan naik

// Sorting untuk kolum berupa kata (string) dengan ascending atau diurutkan naik
void sortStringAsc(struct List data[], char column[]){
	for(int i=0; i<total-1; i++){
		for(int j=0; j<total-1-i; j++){
			int cmp=0;
			
			if(strcmp(column, "restaurant")==0)
				cmp=strcmp(data[j].restaurant,data[j+1].restaurant);
			else if(strcmp(column, "city")==0)
				cmp=strcmp(data[j].city,data[j+1].city);
			else if(strcmp(column, "currency")==0)
				cmp=strcmp(data[j].currency,data[j+1].currency);
			else if(strcmp(column, "rating text")==0)
				cmp=strcmp(data[j].rating_text,data[j+1].rating_text);
			
			if(cmp>0){
				struct List temp=data[j];
				data[j]=data[j+1];
				data[j+1]=temp;
			}
		}
	}
}

// Sorting untuk kolum berupa angka (integer dan float) dengan ascending atau diurutkan naik
void sortNumberAsc(struct List data[], char column[]){
    for(int i=0;i<total-1;i++){
        for(int j=0;j<total-1-i;j++){
        	int swap=0;
        	
           	if(strcmp(column, "cost")==0 && data[j].cost>data[j+1].cost)
				swap=1;
			else if(strcmp(column, "price range")==0 && data[j].price_range>data[j+1].price_range)
				swap=1;
			else if(strcmp(column, "rating")==0 && data[j].rating>data[j+1].rating)
				swap=1;
			else if(strcmp(column, "votes")==0 && data[j].votes>data[j+1].votes)
				swap=1;
			 
			if(swap){
				struct List temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
			}
            
        }
    }
}

// Fungsi untuk sorting data dengan descending atau diurutkan turun

// Sorting untuk kolum berupa kata (string) dengan descending atau diurutkan turun
void sortStringDesc(struct List data[], char column[]){
	for(int i=0; i<total-1; i++){
		for(int j=0; j<total-1-i; j++){
			int cmp=0;
			
			if(strcmp(column, "restaurant")==0)
				cmp=strcmp(data[j].restaurant,data[j+1].restaurant);
			else if(strcmp(column, "city")==0)
				cmp=strcmp(data[j].city,data[j+1].city);
			else if(strcmp(column, "currency")==0)
				cmp=strcmp(data[j].currency,data[j+1].currency);
			else if(strcmp(column, "rating text")==0)
				cmp=strcmp(data[j].rating_text,data[j+1].rating_text);
			
			if(cmp<0){
				struct List temp=data[j];
				data[j]=data[j+1];
				data[j+1]=temp;
			}
		}
	}
}

// Sorting untuk kolum berupa angka (integer dan float) dengan descending atau diurutkan turun
void sortNumberDesc(struct List data[], char column[]){
    for(int i=0;i<total-1;i++){
        for(int j=0;j<total-1-i;j++){
        	int swap=0;
        	
           	if(strcmp(column, "cost")==0 && data[j].cost<data[j+1].cost)
				swap=1;
			else if(strcmp(column, "price range")==0 && data[j].price_range<data[j+1].price_range)
				swap=1;
			else if(strcmp(column, "rating")==0 && data[j].rating<data[j+1].rating)
				swap=1;
			else if(strcmp(column, "votes")==0 && data[j].votes<data[j+1].votes)
				swap=1;
			 
			if(swap){
				struct List temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
			}
            
        }
    }
}

// Fungsi untuk mengekspor atau menulis data restoran ke file CSV 
int exportData(struct List data[], char file_name[]){
    fp = fopen(file_name, "w");
    if(fp == NULL){
        printf("Failed to export file\n");
        return 0;
    }
    
    for(int i = 0; i < total; i++){
        fprintf(fp, "%s,%s,%ld,%s,%d,%.1f,%s,%ld\n",
         	data[i].restaurant,
            data[i].city,
            data[i].cost,
            data[i].currency,
            data[i].price_range,
            data[i].rating,
            data[i].rating_text,
            data[i].votes);
    }
    
    fclose(fp);
    return 1;
}

struct List data[10000];

int main(){
	
	readFile(data);
	
	printf("What Do You Want To Do?\n");
	printf("Please Select Your Choice\n");
	printf("1. Display Data\n");
	printf("2. Search Data\n");
	printf("3. Sort Data\n");
	printf("4. Export Data\n");
	printf("5. Exit\n");
	
	int number;
	printf("Your Choice Number: ");
	scanf("%d", &number);
	
	switch(number){
		case 1:{
			int k;
			printf("Number of rows:");
			scanf("%d", &k);
			
			if(k>total){
				k=total;
			}
			
			printHeader();
			displayData(data, k);
			break;
		}
		
		case 2:{
			char column[100];
			char key_string[100];
			long int key_number;
			float key_float;
			
			printf("Choose Column: ");
			scanf(" %[^\n]", column);
			toLowerCase(column);
		
    		if(strcmp(column, "restaurant")==0 ||
				strcmp(column, "city")==0 ||
				strcmp(column, "currency")==0 ||
				strcmp(column, "rating text")==0){
					printf("What Data Do You Want to Find: ");
					scanf(" %[^\n]", key_string);
				   	linearSearchString(data, column, key_string);
			 	}
			else if(strcmp(column, "cost")==0 ||
					strcmp(column, "price range")==0 ||
					strcmp(column, "votes")==0){
						printf("What Data Do You Want to Find: ");
						scanf(" %ld", &key_number);
				   		linearSearchNumber(data, column, key_number);
				}
			else{
				printf("What Data Do You Want To Find: ");
				scanf(" %f", &key_float);
				linearSearchFloat(data, column, key_float);
			}
			break;
		}
		
		case 3:{
		 	char column[100];
    		char order[10];

    		printf("Choose Column: ");
    		scanf(" %[^\n]", column);
    		toLowerCase(column);

    		printf("Sort Ascending (asc) or Descending (desc): ");
    		scanf("%s", order);
    		toLowerCase(order);
    		
    		if(strcmp(order,"asc")==0){
    			if(strcmp(column, "restaurant")==0 ||
				   strcmp(column, "city")==0 ||
				   strcmp(column, "currency")==0 ||
				   strcmp(column, "rating text")==0){
				   	sortStringAsc(data, column);
				   }
				else{
					sortNumberAsc(data, column);
					}
			}
			
			if(strcmp(order,"desc")==0){
    			if(strcmp(column, "restaurant")==0 ||
				   strcmp(column, "city")==0 ||
				   strcmp(column, "currency")==0 ||
				   strcmp(column, "rating text")==0){
				   	sortStringDesc(data, column);
				   }
				else{
					sortNumberDesc(data, column);
					}
			}
			printHeader();
    		displayData(data, 10);
			break;
		}
		
		case 4:{
			char file_name[100];
			printf("File Name: ");
			scanf("%s", file_name);
			
			strcat(file_name, ".csv");
			
			if(exportData(data, file_name)){
				printf("Data successfully written to file %s!\n", file_name);
			}
			break;
		}
		
		case 5:{
			printf("You have exit from the program. Thank you\n");
			break;
		}
	
		default:{
			printf("Sorry, invalid choice. Please try again\n");
			break;
		}
	}
	return 0;
}

