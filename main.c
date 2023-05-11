#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM_SIZE 154
#define arquivo "exemplo02.txt"

unsigned short int PC = 0x0000;
unsigned int MBR = 0x0000000000000000;
unsigned short int MAR = 0x00000000;
unsigned char IR = 0x00;
unsigned short int IMM;
unsigned short int IBR = 0x0000;
unsigned short int AC = 0x0000;
unsigned char E, L, G;
unsigned char LR = 0x00;
unsigned char MEM[154];
unsigned short int A = 0x0000;
unsigned short int B = 0x0000;
unsigned short int T;


int exec = 1;

void zeraMemoria()
{
  for (int i = 0; i < 154; i++)
  {
    MEM[i] = 0;
  }
}

void printaMemoria()
{
  printf("\033[31mMaquina de Von Neumann\033[0m\n");
  for (int i = 0; i < MEM_SIZE; i++)
  {
    if (i % 7 == 0)
    {
      printf("\n");
    }
    printf("[ %x ] = 0x%.2x", i, MEM[i]);
    printf("\t");
  }
}

void cpu()
{
  printf("\n\nCPU:\n\n");
  printf("A:0x %02x        B:0x %x        T:0x %x\n", A, B, T);
  printf("MBR:0x %08x      MAR:0x %x      IMM:0x %x\n", MBR, MAR, IMM);
  printf("PC:0x %x       IR:0x %x       LR:0x %x\n", PC, IR, LR);
  printf("E:0x %x        L:0x %x        G:0x %x\n", E, L, G);
  printf("IBR:0x %x      \n", IBR);
}

void busca()
{
  MAR = PC;

  MBR = MEM[MAR];
  MBR = MBR << 8;
  MAR++;
  MBR = MEM[MAR] | MBR;
  MBR = MBR << 8;
  MAR++;
  MBR = MEM[MAR] | MBR;
  MBR = MBR << 8;
  MAR++;
  MBR = MEM[MAR] | MBR;
}

void decodifica()
{
  if (LR == 0) {
    IBR = MBR & 0xffff;
    MBR = MBR >> 16;
    IR = (MBR >> 11) & 0x1F;

    unsigned char chaves_imediatas[7] = {0b11001, 0b11010, 0b11011, 0b11100, 0b11101, 0b11110, 0b11111};
    for (int i = 0; i < 7; i++) {
      if (IR == chaves_imediatas[i]) {
        IMM = MBR & 0x7ff;
      }
      else{
        MAR = MBR &0x7FF;
      }
    }
        if (IR != 0b00000) {
          LR = 1;
        }
  }else if (LR == 1)  {

         IR = IBR >> 11;
        unsigned char chaves_imediatas[7] = {0b11001, 0b11010, 0b11011, 0b11100, 0b11101, 0b11110, 0b11111};
         for(int i = 0; i < 7; i++) {
         
          if(IR == chaves_imediatas[i]) {
              IMM = IBR & 0x7ff;
          }
          else{
              MAR = IBR & 0x7ff;
          }
      }

    if (IR != 0b00000)
    {
      LR = 0;
      //PC = PC + 4;
    }
  }
}
void executa()
{

  // hlt
  if (IR == 0b00000)
  {

  }


  // nop
  if (IR == 0b00001)
  {

    if (LR == 1)
    {
      PC += 4;
    }
  }
  // add
  if (IR == 0b00010)
  {
    A = A + B;

    if(LR== 1){
      PC += 4;
    }
  }

  // sub
  if (IR == 0b00011)
  {
    A = A - B;

    if(LR== 1){
      PC += 4;
    }

  }
  // mul
  if (IR == 0b00100)
  {
    A = A * B;

   if(LR== 1){
      PC += 4;
    }
  }
  // div
  if (IR == 0b00101)
  {
    A = A / B;

    if(LR== 1){
      PC += 4;
    }
  }
  // cmp
  if (IR == 0b00110)
  {
    if (A == B)
    {
      E = 1;
    }
    if (A != B)
    {
      E = 0;
    }
    if (A < B)
    {
      L = 1;
      G = 0;
    }
    if (A > B)
    {
      L = 0;
      G = 1;
    }
  
  if(LR== 1){
      PC += 4;
    }
  
  }

  // xchg
  if (IR == 0b00111)
  {
    T = A;
    A = B;
    B = T;

    if(LR== 1){
      PC += 4;
    }
  }

  // and
  if (IR == 0b01000)
  {
    A = A & B;

    if(LR== 1){
      PC += 4;
    }
  }

  //or
  if (IR == 0b01001)
  {
    A = A | B;

    if(LR== 1){
      PC += 4;
    }
  }


  // xor
  if (IR == 0b01010)
  {
    A = A ^ B;

    if(LR== 1){
      PC += 4;
    }
  }
  // not
  if (IR == 0b01011)
  {
    A = !A;

    if(LR== 1){
      PC += 4;
    }
  }

  // je
  if (IR == 0b01100)
  {
    if (E == 1)
    {
      PC = MAR;
      LR = 0;
    }
    else{
      PC += 4;
    }
  }
  // jne
  if (IR == 0b01101)
  {
    if (E == 0)
    {
      PC = MAR;
      LR = 0;
    }
    else{
      PC += 4;
    }
  }

  // jl
  if (IR == 0b01110)
  {

    if (L == 1)
    {
      PC = MAR;
      LR = 0;
    }
    else{

      PC +=4;

    }
  }

  // jle
  if (IR == 0b01111)
  {

    if (E == 1 || L == 1)
    {

      PC = MAR;
      LR = 0;
    }
    else{
      PC +=4;
    }
  }

  // jg
  if (IR == 0b10000)
  {
    if (G == 1)
    {
      PC = MAR;
      LR = 0;
    }

    else{
      PC +=4;
    }
  }

  // jge
  if (IR == 0b10001)
  {
    if (E == 1 || G == 1)
    {
      PC = MAR;
      LR = 0;
    }
    else{
      PC += 4;
    }
  }

  // jmp
  if (IR == 0b10010)
  {

    PC = MAR;
    LR = 0;
  }

  // loada
  if (IR == 0b10011)
  {
    MBR = MEM[MAR];
    MBR = MBR << 8;
    MAR++;
    MBR = MEM[MAR] | MBR;
    A = MBR & 0xffff;

    if(LR== 1){
      PC += 4;
    }
  }
  // loadb
  if (IR == 0b10100)
  {
    MBR = MEM[MAR];
    MBR = MBR << 8;
    MAR++;
    MBR = MEM[MAR] | MBR;
    B = MBR & 0xffff;

    if(LR== 1){
      PC += 4;
    }
  }
  // stora
  if (IR == 0b10101)
  {
    MEM[MAR] = A >> 8;
    MAR++;
    MEM[MAR] = A & 0x00ff;

    if(LR== 1){
      PC += 4;
    }
  }
  // storb
  if (IR == 0b10110)
  {
    MEM[MAR] = B >> 8;
    MAR++;
    MEM[MAR] = B & 0x00ff;

    if(LR== 1){
      PC += 4;
    }
  }
  // ldrb
  if (IR == 0b10111)
  {
    if (B <= 154)
    {
      MBR = MEM[B] << 8;
      MBR = MBR | MEM[B + 1];
      A = MBR;
    }
  if(LR== 1){
      PC += 4;
    }
  
  }
  /*movial imm
    zera o registrador A e move os oito bits menos significativos (0:7) do imediato
    para a parte inferior (0:7) do registrador A.*/
  if (IR == 0b11000)
  {
    A = 0;
    A = A | IMM & 0x00ff;

    if(LR== 1){
      PC += 4;
    }
  }
  /*moviah imm
    move os oito bits menos significativos (0:7) do imediato para a parte superior
    (8:15) do registrador A, enquanto os bits menos significativos do registrador A s�o mantidos intactos.*/
  if (IR == 0b11001)
  {
    A = (A & 0x00ff) | ((IMM & 0x00ff) << 8);
  
  if(LR== 1){
      PC += 4;
    }
  
  }
  // addia imm
  if (IR == 0b11010)
  {
 
    A = A + IMM;
    if(LR== 1){
      PC += 4;
    }
  
  }
  // subia imm
  if (IR == 0b11011)
  {
    A = A - IMM;
    if(LR== 1){
      PC += 4;
    }
  }
  // mulia imm
  if (IR == 0b11100)
  {
    A = A * IMM;
    if(LR== 1){
      PC += 4;
    }
  }
  // divia imm
  if (IR == 0b11101)
  {
    A = A / IMM;
    if(LR== 1){
      PC += 4;
    }
  }
  // lsh
  if (IR == 0b11110)
  {
    A = A << IMM;
    if(LR== 1){
      PC += 4;
    }
  }
  // rsh
  if (IR == 0b11111)
  {
    A = A >> IMM;
    if(LR== 1){
      PC += 4;
    }
  }
}

void separate(char *restante, char *opcode1, int *endereco1, char *opcode2, int *endereco2)
{
    char restante_copia[strlen(restante) + 1];
    strcpy(restante_copia, restante);

    *endereco1 = 0;
    *endereco2 = 0;

    char *simbolo = strtok(restante_copia, "/");
    int contador = 0;
    while (simbolo != NULL) {
        switch (contador) {
            case 0:

                sscanf(simbolo, "%s %x", opcode1, endereco1);
                break;
            case 1:

                sscanf(simbolo, "%s %x", opcode2, endereco2);
                break;
        }
        simbolo = strtok(NULL, "/");
        contador++;
    }


}
 short int  verificaInstrucao(char *opcode){

      if(strcmp(opcode,"hlt")==0){

        return 0b00000;

      }
      if(strcmp(opcode,"nop")==0){

        return 0b00001;

      }
      if(strcmp(opcode ,"add")==0){

        return 0b00010;

      }
      if(strcmp(opcode,"sub")==0){

        return 0b00011;
      }
      if(strcmp(opcode,"mul")==0){

        return 0b00100;

      }
       if(strcmp(opcode, "div")==0){

         return 0b00101;

      }
       if(strcmp(opcode,"cmp")==0){

        return 0b00110;

      }
       if(strcmp(opcode,"xchg")==0){

        return 0b00111;

      }
       if(strcmp(opcode,"and")==0){

        return 0b01000;

      }
       if(strcmp(opcode,"or")==0){

        return 0b01001;
      }
       if(strcmp(opcode,"xor")==0){
        return 0b01010;
      }
       if(strcmp(opcode,"not")==0){
        return 0b01011;
      }
       if(strcmp(opcode ,"je")==0){
        return 0b01100;
      }
       if(strcmp(opcode ,"jne")==0){
        return 0b01101;
      }
       if(strcmp(opcode,"jl")==0){
        return 0b01110;
      }
       if(strcmp(opcode ,"jle")==0){
        return 0b01111;
      }
       if(strcmp(opcode ,"jg")==0){

        return 0b10000;
      }
       if(strcmp(opcode,"jge")==0){

        return 0b10001;

      }
       if(strcmp(opcode,"jmp")==0){

        return 0b10010;

      }
       if(strcmp(opcode,"lda")==0){

        return 0b10011;

      }
       if(strcmp(opcode , "ldb")==0){

        return 0b10100;

      }
       if(strcmp(opcode,"sta")==0){

        return 0b10101;

      }
       if(strcmp(opcode,"stb")==0){

        return 0b10110;

      }
       if(strcmp(opcode,"ldrb")==0){

        return 0b10111;

      }
       if(strcmp(opcode,"movial")==0){

            return 0b11000;

      }
        if(strcmp(opcode,"moviah")==0){

            return 0b11001;
        }


       if(strcmp(opcode,"addia")==0){

        return 0b11010;

      }
       if(strcmp(opcode,"subia")==0){

        return 0b11011;

      }
       if(strcmp(opcode,"mulia")==0)
       {
          return 0b11100;
      }
       if(strcmp(opcode,"divia")==0){
          return 0b11101;
      }
      if(strcmp(opcode,"lsh")==0)
      {
        return 0b11110;
      }
      if(strcmp(opcode,"rsh")==0)
      {
        return 0b11111;
      }
      return 0;
}
void abrirArquivo(){
  FILE *file;
  char line[100];

  file = fopen(arquivo, "r");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }

while (fgets(line, 100, file) != NULL)
  {
    unsigned short int endereco;
    char simbolo;
    unsigned short int dado;
    sscanf(line, "%hx;%c;%*[^;]", &endereco, &simbolo);
    if(simbolo == 'i')
    {
      char restante[100];
      char opcode1[10];
      char opcode2[10];
      int endereco1,endereco2;
      sscanf(line,"%*[^;];%*[^;];%99[^;]",restante);
      separate(restante, opcode1, &endereco1, opcode2, &endereco2);

      short int op1 =  verificaInstrucao(opcode1) & ~(0b11111 << 11) ;
      short int op2 =  verificaInstrucao(opcode2) & ~(0b11111 << 11);
      short int end1 = endereco1 & 0x7FF;
      short int end2 = endereco2 & 0x7FF;
      MEM[endereco] = ((op1 & 0x1F) << 3) | ((end1 & 0x700) >> 8);
      MEM[endereco+1] = end1 & 0xFF;
      MEM[endereco+2] = ((op2 & 0x1F) << 3) | ((end2 & 0x700) >> 8);
      MEM[endereco+3] = end2 & 0xFF;

    }
    if(simbolo =='d')
    {

      sscanf(line,"%*[^;];%*[^;];%hx",&dado);
      MEM[endereco] = dado <<8;
      MEM[endereco+1] = dado &  0x00ff;

    }


  }

fclose(file);
}

int main()
{
  system("MODE con cols=168 lines=60");
  system("title Maquina de von Neumann");
  zeraMemoria();
  PC = 0;
  abrirArquivo();

  while (exec == 1) {
    printaMemoria();
    cpu();
    if (exec == 1) {
      printf("Quer continuar?\n1 para sim\n0 para nao\n");
      scanf("%d", & exec);
    } else if (exec == 0) {
      break;
    }
    busca();
    decodifica();
    executa();

    system("cls");
  }
  return 0;
}
