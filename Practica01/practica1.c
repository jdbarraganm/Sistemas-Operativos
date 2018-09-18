#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct dogType{
    char Name[32];
    char Type[32];
    int Age;
    char breed[16];
    int height;
    float weight;
    char gender[1];
    struct dogType *next;
};
struct dogType *hash_table[1000];
struct dogType *next=NULL;

int hash_function(char a[32]){
  int hash = 0;
  for (int i = 0; i < 32; i++) {
    hash = 31 * hash + a[i];
  }
  return hash;
}

void loadDog(void *dog){
    bool flag = 0;
    struct dogType *newDog;
    //malloc(sizeof(struct dogType));
    newDog = dog;
    printf("Por favor ingrese los datos pedidos a continuación\n");
    printf("ingrese nombre:\n");
    scanf("%s", newDog->Name);
    char a[32];
    memcpy(a,newDog->Name,32);
    printf("%s\n",a);
    printf("Cuando haya terminado presione enter\n");
    printf("ingrese especie:\n");
    printf("Cuando haya terminado presione enter\n");
    scanf("%s", newDog->Type);
    printf("ingrese edad:\n");
    printf("Cuando haya terminado presione enter\n");
    scanf("%i", &newDog->Age);
    printf("ingrese raza:\n");
    printf("Cuando haya terminado presione enter\n");
    scanf("%s", newDog->breed);
    printf("ingrese estatura:\n");
    printf("Cuando haya terminado presione enter\n");
    scanf("%i", &newDog->height);
    printf("ingrese peso:\n");
    printf("Cuando haya terminado presione enter\n");
    scanf("%f", &newDog->weight);
    printf("ingrese genero:\n");
    printf("Cuando haya terminado presione enter\n");
    scanf("%s", newDog->gender);

    char n[32];
    memcpy(n,newDog->Name,32);
    struct dogType *start;
    struct dogType *pointer;
    int adress = hash_function(n);

    if(hash_table[adress]==NULL){
      hash_table[adress] = malloc(sizeof(struct dogType));
      hash_table[adress] =newDog;
      hash_table[adress]->next=NULL;
    } else {
      pointer=hash_table[adress];
      while (pointer->next != NULL) {
        pointer = pointer->next;
      }
      pointer->next = malloc (sizeof(struct dogType));
      pointer = newDog;
      pointer = pointer->next;
      pointer->next = NULL;
    }
}

void menu(int option){
    printf("Please ");
    switch(option){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;

    }

}

int main(){

  FILE *fileap;
  int r;
    struct dogType *perri;
    //perri = malloc(sizeof(struct dogType));
    perri=(struct dogType*) malloc(sizeof(struct dogType));

    if(perri==NULL){
        perror("Error en el malloc");
        exit(-1);
    }

    loadDog(perri);
    /*printf("Por favor ingrese los datos pedidos a continuación\n");
    printf("ingrese nombre:\n");
    scanf("%s", perri->Name);
    //printf("%s\n",perri->Name );
    char a[32];
    printf("%s\n",a);
    memcpy(a,perri->Name,32);
    //a = &perri->Name;
    printf("%s\n",a);
    */
    //FILE *fileap = fopen("data.dat","w+");
    fileap = fopen("dataDogs.dat", "w");
   if(fileap == NULL){
       perror("error fopen");
       exit(-1);
   }

    r = fwrite(perri, sizeof(struct dogType), 1,fileap);
   if(r==0){
       perror("Error en fwrite");
       exit(-1);
   }
   int c = fclose(fileap);
   if(c != 0){
       perror("Error en fclose");
       exit(-1);
   }



}
