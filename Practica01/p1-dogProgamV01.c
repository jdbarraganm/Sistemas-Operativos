#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define max 1000

struct dogType{
    struct pair_int *record;
    int id;
    char Name[32];
    char Type[32];
    int Age;
    char breed[16];
    int height;
    float weight;
    char gender[1];
    struct dogType *next;
};

struct pair_int{
    int first;
    int second;
};

int countRecords = 0;
struct dogType *hash_table[max];
struct dogType *next=NULL;
char prueba[32];

// int hash_file(char n[32]){
//     FILE *fp=fopen("dataDogs.dat","rb");
//     struct dogType* dog=malloc(sizeof(struct dogType));
//     if(fp==NULL){
// 		printf("Error abriendo archivo dataDogs.dat\n");
// 		return;
// 	}else{
// 		fread(dog,sizeof(struct dogType),1,fp);
// 		while (!feof(fp)) {
// 			if(equals(dog->Name)==1){
// 				found=1;
//         printf("------------------------\n");
//         printf("Registro: %i %i\n", dog->record->first,dog->record->second);
//         printf("Nombre: %s\n",dog->Name);
//         printf("Tipo: %s\n", dog->Type);
//         printf("Edad: %i años\n", dog->Age);
//         printf("Raza: %s\n", dog->breed);
//         printf("Estatura: %i cm\n", dog->height);
//         printf("Peso: %3f Kg\n", dog->weight);
//         printf("Sexo: %s\n", dog->gender);
//         printf("------------------------\n");
// 			}
// 			fread(pet,sizeof(struct dogType),1,fp);
// 		}
// 		fclose(fp);
// 	}
// 	free(pet);
// 	if(found==1) printf("Búsqueda concluida exitosamente.\n");
// 	if(found==0) printf("Mascota no encontrada.\n");
// 	mypause();
// }

int hash_function(char a[32]){
  int hash = 0;
  for (int i = 0; i < 32; i++) {
    //printf("%i\t",a[i]);
    if(a[i]>=65&&a[i]<=90){
        a[i]+=32;
    }
    hash = (31 * hash + a[i])%max;
  }
  printf("\n");
  return hash;
}

void preMenu(){
    printf("Oprima [Enter] para volver al menu\n");
    fflush(stdin);
	getchar();
	getchar();
}

void printRecord(struct dogType *dog){
    printf("------------------------\n");
    printf("Registro: %i %i\n", dog->record->first,dog->record->second);
    printf("Nombre: %s\n",dog->Name);
    printf("Tipo: %s\n", dog->Type);
    printf("Edad: %i años\n", dog->Age);
    printf("Raza: %s\n", dog->breed);
    printf("Estatura: %i cm\n", dog->height);
    printf("Peso: %3f Kg\n", dog->weight);
    printf("Sexo: %s\n", dog->gender);
    printf("------------------------\n");
}

void loadDog(){
    FILE *files=fopen("dataDogs.dat","ab");
    if(files==NULL){
        printf("Error abriendo archivo dataDogs.dat.\n");
        return;
    }else{
        struct dogType *newDog = malloc(sizeof(struct dogType));
        printf("Por favor ingrese los datos pedidos a continuación\n"
            "ingrese nombre:\n"
            "Cuando haya terminado presione enter\n");
        memset(newDog->Name,32,32);
        char n[32];
        scanf("%s", newDog->Name);
        printf("ingrese especie:\n"
            "Cuando haya terminado presione enter\n");
        memcpy(n,newDog->Name,32);
        scanf("%s", newDog->Type);
        printf("ingrese edad:\n"
            "Cuando haya terminado presione enter\n");
        scanf("%i", &newDog->Age);
        printf("ingrese raza:\n"
            "Cuando haya terminado presione enter\n");
        scanf("%s", newDog->breed);
        printf("Ingrese estatura:\n"
            "Cuando haya terminado presione enter\n");
        scanf("%i", &newDog->height);
        printf("Ingrese peso:\n"
            "Cuando haya terminado presione enter\n");
        scanf("%f", &newDog->weight);
        printf("ingrese genero:\n"
            "Cuando haya terminado presione enter\n");
        scanf("%s", newDog->gender);
        newDog->next=NULL;

        int address = hash_function(n);
        struct dogType *pointer = hash_table[address];
        int addressSec = 0;
        if(pointer==NULL){
            printf("entro al null\n");
            hash_table[address] = newDog;
            newDog->record = malloc(sizeof(struct pair_int));
            newDog->record->first = address;
            newDog->record->second = addressSec;
        }else {
            printf("no es null\n");
            pointer=hash_table[address];
            addressSec+=1;
            while (pointer->next != NULL) {
                pointer = pointer->next;
                addressSec+=1;
            }
            pointer->next = malloc (sizeof(struct dogType));
            pointer->next = newDog;
            newDog->record = malloc(sizeof(struct pair_int));
            newDog->record->first = address;
            newDog->record->second = addressSec;
        }
        fseek(files, 0L,SEEK_END);
        int tam = ftell(files);
        fseek(files, 0L,SEEK_SET);
        newDog->id= tam/sizeof(struct dogType)+1;
        printf("%s\n", );
        fwrite(newDog,sizeof(struct dogType),1,files);
        fclose(files);
        free(newDog);
        printf("registro hecho\n");
        countRecords++;
        preMenu();
    }


    //return newDog;
}

void seeRecord(){
	FILE *fp=fopen("dataDogs.dat","rb");
	struct dogType* pet=malloc(sizeof(struct dogType));
	if(fp==NULL){
		printf("Error abriendo archivo dataDogs.dat.\n");
		return;
	}else{
        fread(pet,sizeof(struct dogType),1,fp);
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		int totalRecords=(size/sizeof(struct dogType));
		printf("Cantidad de registros:\t"
           "%i\n",totalRecords);

           int buscar=0;
           scanf("%i\n",&buscar);

           if (buscar>totalRecords) {
             printf("Posicion erronea\n", );
           }
           fread(pet,sizeof(struct dogType),1,fp);
           while (!feop(fp)) {
             /* code */
           }
	}

    preMenu();
}

void deleteRecord(){
    printf("Cantidad de registros:\t"
           "%d\n",countRecords);
    printf("Por favor ingrese el numero de registro a borrar\n");
    int record;
    scanf("%i",&record);
    preMenu();
}

void searchRecord(){
    char n[32];
    printf("Por favor digite el nombre de su mascota\n"
           "Seguida la tecla ENTER\n");
    memset(n,32,32);
    scanf("%s",n);
    int addres = hash_function(n);
    printf("%i\n",addres);
    struct dogType *pointer = hash_table[addres];
    printRecord(pointer);
    while (pointer->next != NULL) {
        pointer = pointer->next;
        printRecord(pointer);
    }
    preMenu();
}

//Menu principal
void menu(){
    int option;
    do{
        printf("Por favor seleciona un numero de las sgtes opciones seguido de la tecla enter\n"
           "1. Ingresar registro\n"
           "2. Ver registro\n"
           "3. Borrar registro\n"
           "4. Buscar registro\n"
           "5. Salir\n");
        scanf("%i",&option);

        struct dogType *newPet;
        switch(option){
            case 1:
                loadDog();
                break;
            case 2:
                seeRecord();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                searchRecord();
                break;
        };
    }while(option!=5);

}

int main(){
    menu();
    return 0;
}
