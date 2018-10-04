#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#define max 10000000
#define prime 10009

struct dogType{
    int id; //Posicion en la cual esta guardada el registro la cual se calcula con la funcion hash(Name)
    int next;//Posicion en la cual se guardaria otro registro si se tiene el mismo nombre (colision) calculado con la funcion reHash(Name)
    char Name[32];
    char Type[32];
    int Age;
    int height;
    char breed[16];
    float weight;
    char gender[1];

};

struct dogType *hash_table[max];

int hash_function(char a[32]){
    int hash = 0;
    for (int i = 0; i < 32; i++) {
        //printf("%i\t",a[i]);
        if(a[i]>=65&&a[i]<=90){
            a[i]+=32;
        }
        hash = (3 * hash + a[i])%prime;
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
   // printf("Registro: %i %i\n", dog->record->first,dog->record->second);
//    printf("Id: %i\n",dog->id);
    printf("Nombre: %s\n",dog->Name);
    printf("Tipo: %s\n", dog->Type);
    printf("Edad: %i años\n", dog->Age);
    printf("Raza: %s\n", dog->breed);
    printf("Estatura: %i cm\n", dog->height);
    printf("Peso: %3f Kg\n", dog->weight);
    printf("Sexo: %s\n", dog->gender);
    printf("------------------------\n");
}

int equals(char petName[], char petName2[]){
    printf("s1: %s\t s2: %s\n",petName,petName2);
	if(strlen(petName)!=strlen(petName2)){
		return 0;
	}else{
		int i=0;
		for(i;i<strlen(petName);i++){
			if(tolower(petName[i])!=tolower(petName2[i])){
				return 0;
			}
		}
	}
	return 1;
}

int hash_file(char n[32]){
    int found = 0,sol,temp=0;
    FILE *fp=fopen("dataDogs.dat","rb");
    struct dogType* pet=malloc(sizeof(struct dogType));
    if(fp==NULL){
		printf("Error abriendo archivo dataDogs.dat\n");
		return 0;
	}else{
        printf("entro al else\n");
		fread(pet,sizeof(struct dogType),1,fp);
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		sol=(size/sizeof(struct dogType)) + 1;
		while (!feof(fp)) {
			if(equals(pet->Name,n)==1){
				found=1;
				sol = temp;
				//printRecord(pet);
			}temp+=1;
			fread(pet,sizeof(struct dogType),1,fp);
		}
		fclose(fp);
	}
	free(pet);
	if(found==1) printf("Búsqueda concluida exitosamente.\n");
	if(found==0) printf("Mascota no encontrada.\n");
	preMenu();
	return sol;
}

//struct dogType *createDog(){
void writeTable(int pos, struct dogType *pet){
    FILE *files=fopen("dataDogs.dat","wb");
    if(files==NULL){
        printf("Error abriendo archivo dataDogs.dat.\n");
        return;
    }else{
        struct dogType *temp;
        fseek(files, 0L,SEEK_END);
        int tam = ftell(files)/sizeof(struct dogType);
        //printf("%i\n",tam);
        if(tam == 0){///va a ingresar un registro por primera vez
            ///recorremos el archivo hasta la posicion y lo llenamos de estructuras Null
            temp = malloc(sizeof(struct dogType));
            for(int rec = 1; rec < pos; rec++){
                temp->id = rec;
                temp->next = pos;
                fwrite(temp,sizeof(struct dogType),1,files);
            }
            fwrite(pet,sizeof(struct dogType),1,files);
            fclose(files);
            free(temp);
            free(pet);
        }else{
            if(pos>tam){///ingresa un registro dependiendo la poscion
                        ///en este caso mayor al tam del file actual
                ///Cerramos el archivo para escribirlo en un archivo nuevo
                fclose(files);
                files=fopen("dataDogs.dat","rb");
                fseek(files, 0L,SEEK_SET);
                FILE *filesNew = fopen("dataTemp.dat","wb");
                temp = malloc(sizeof(struct dogType));
                for(int rec = 1; rec < pos; rec++){//recorremos el archivo files escribiendo ahora en filesNew
                    if(rec<tam+1){//Dado que la posicion es menor reescribimos lo que ya teniamos previamente
                        fread(temp,sizeof(struct dogType),1,files);
                        fwrite(temp,sizeof(struct dogType),1,filesNew);
                    }else{//Escribimos los nulls nuevos
                        temp->id = rec;
                        temp->next = pos;
                        fwrite(temp,sizeof(struct dogType),1,filesNew);
                    }
                }
                //Escribimos en la posicion la mascota ingresada/borramos el archivo viejo y renombramos el nuevo
                fwrite(pet,sizeof(struct dogType),1,filesNew);
                fclose(files);
                remove(files);
                fclose(filesNew);
                rename("dataTemp.dat","dataDogs.dat");
                free(temp);
                free(pet);
            }else{///ingresa un registro en una poscion,en este caso mayor al tam del file actual
                ///Cerramos el archivo para escribirlo en un archivo nuevo
                fclose(files);
                files=fopen("dataDogs.dat","rb");
                fseek(files, 0L,SEEK_SET);
                FILE *filesNew = fopen("dataTemp.dat","wb");
                temp = malloc(sizeof(struct dogType));
                for(int rec = 1; rec <= tam; rec++){//recorremos el archivo files escribiendo ahora en filesNew
                    if(rec<pos){//actualiza hasta la poscion previa al cual vamos a ingresar el archivo
                        temp->id = rec;
                        temp->next = pos;
                        fwrite(temp,sizeof(struct dogType),1,filesNew);
                    }else if(rec>pos){//Dado que la posicion es menor al tam reescribimos lo que ya teniamos previamente
                        fread(temp,sizeof(struct dogType),1,files);
                        fwrite(temp,sizeof(struct dogType),1,filesNew);
                    }else{//Escribimos la mascota en la posicion
                        fwrite(pet,sizeof(struct dogType),1,filesNew);
                    }
                }
                //borramos el archivo viejo y renombramos el nuevo
                fclose(files);
                remove(files);
                fclose(filesNew);
                rename("dataTemp.dat","dataDogs.dat");
                free(temp);
                free(pet);
            }
        }
    }
}

void insertRecord(){
    //Se llenan los campos pedidos en la estructura NewDog
    struct dogType *newDog = malloc(sizeof(struct dogType));
    printf("Por favor ingrese los datos pedidos a continuación\n"
        "ingrese nombre:\n"
        "Cuando haya terminado presione enter\n");
    memset(newDog->Name,32,32);
    char n[32];
    scanf("%s", newDog->Name);
    printf("ingrese especie:\n"
        "Cuando haya terminado presione enter\n");
    // memcpy(n,newDog->Name,32);
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
    //Se llenan todos los campos menos id y Next
    int h = hash_function(newDog->Name);
    //En WriteTable si se llenan estos campos ya que se calculan
    writeTable(h,newDog);

    printf("registro hecho\n");

    preMenu();
}

void seeRecord(){
	FILE *files=fopen("dataDogs.dat","rb");
	struct dogType* dog=malloc(sizeof(struct dogType));
	if(files==NULL){
		printf("Error abriendo archivo dataDogs.dat.\n");
		return;
	}else{
        fread(dog,sizeof(struct dogType),1,files);
		fseek(files, 0L, SEEK_END);
		int size = ftell(files);
		fseek(files, 0L, SEEK_SET);
		int totalRecords=(size/sizeof(struct dogType));
		printf("Cantidad de registros:\t"
           "%i\n",totalRecords);

           int buscar=0;
           scanf("%i\n",&buscar);

           if (buscar>totalRecords) {
             printf("Posicion erronea\n");
           }
           fread(dog,sizeof(struct dogType),1,files);
           while (!feof(files)) {
             if (dog->id==buscar) {
               FILE * fh = fopen("history.txt","w");
               fprintf(fh, "ID: %i\nNombre: %s\nTipo: %s\nEdad: %i\nRaza: %s\nEstatura: %i\nPeso: %lf\nSexo: %c\n", dog->id, dog->Name, dog->Type, dog->Age, dog->breed, dog->height, dog->weight, dog->gender);
				fclose(fh);
        system("nano history.txt");
        return;
  }
  fread(dog,sizeof(struct dogType),1,files);
}
fclose(files);
}
free(dog);
printf("Información mostrada exitosamente.\n");

    preMenu();
}

void deleteRecord(){
/*
    printf("Cantidad de registros:\t"
           "%d\n",countRecords);*/
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
    int found = 0;
    FILE *fp=fopen("dataDogs.dat","rb");
    struct dogType* pet=malloc(sizeof(struct dogType));
    if(fp==NULL){
		printf("Error abriendo archivo dataDogs.dat\n");
		return;
	}else{
		fread(pet,sizeof(struct dogType),1,fp);
		while (!feof(fp)) {
			if(equals(pet->Name,n)==1){
				found=1;
				//printRecord(pet);
			}
			fread(pet,sizeof(struct dogType),1,fp);
		}
		fclose(fp);
	}
	free(pet);
	if(found==1) printf("Búsqueda concluida exitosamente.\n");
	if(found==0) printf("Mascota no encontrada.\n");
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
                //newPet = createDog();
                insertRecord();
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
            case 6:
                ;
                char nombre[32];
                printf("Ingrese el nombre de la mascota a calcular la hash Function\n");
                memset(nombre,32,32);
                scanf("%s",nombre);
                printf("%s\n",nombre);
                int h = hash_function(nombre);
                printf("%i\n", h);
                break;
        };
    }while(option!=5);

}

int main(){
    menu();
    return 0;
}
