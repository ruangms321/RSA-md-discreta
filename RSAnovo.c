#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
int loop_funcao = TRUE;
//******inicializacao de funcoes*******
void pega_P_Q();
int menu();
int teste_primo(long long int numero);
int test_coprimo(long long int e, long long int tp);
void manipular_pasta(long long int n, long long int e);
int criptografar();

//******CALCULOS******

int menu() {
    while(loop_funcao == TRUE)
    {
        loop_funcao = FALSE;

        printf("1. Gerar chave publica;\n");
        printf("2. Criptografar uma mensagem;\n");
        printf("3. Descriptografar uma mensagem.\n");
        printf("4. SAIR\n");
        printf("Digite o numero da opcao: ");
        
        int escolha;
        scanf("%d", &escolha);

        switch(escolha)
        {
            case 1://gerar e salvar a chave publica
                pega_P_Q();
                break;

            case 2:
                //printf("\nCriptografar.\n\n");
               // int m;
                criptografar();
               // if(m == 1) pega_P_Q();
                break;
        
            case 3:
                printf("\nVocê escolheu: Descriptografar.\n\n");
                //descriptografar();                              // Ir à função Descriptografar.
                break;

            case 4:
                return 4;
                break;

            default:
                printf("\nOpção inválida!\n\n");    // Caso o usuário escolha uma opção inválida.

                if((escolha > 10) || (escolha < 0)) {   // Opções inválidas são: dígtos > 10 | digitos < 0
                   return 0;// exit(EXIT_FAILURE);                 // Finaliza o programa.
                }

                //sleep(2);       // Espera 2 segundos para mostrar a mensagem de opção inválida.
                loop_funcao = TRUE; // Se a escolha estiver dentro do intervalo [0, 10], mas não for {1, 2, 3}...
                break;              // então o programa lista novamente as opções e pergunta novamente.
        }
    }
    return 0;
}

int criptografar()
{   printf("entrou");
    char mensagem[5000];
    long long int mensagem_encriptada[5000];
    long long int n, e;
    int tamanhostr;
    printf("\nDigite uma mensagem para ser criptografada:\n ");
    getchar();
    fgets(mensagem, 5000, stdin);//ler do teclado(stdin) a mensagem ate 500.000digitos contando com os espacos, o scanf armazena so ate um espaco em branco
    

    printf("\ndigite a chave publica. se nao tiver digite 0)\n");
    printf("Digite 'n'");
    scanf("%lld", &n);
    if(n == 0) return 1;
    
    printf("Digite o expoente e ");
    scanf("%lld", &e);
    if(e == 0) return 1;

    FILE *mensagem_encriptadax;
    mensagem_encriptadax = fopen("mensagem_criptografada.txt", "w+");
    if(mensagem_encriptadax == NULL){
        printf("Nao foi possivel criar o arquivo.\n");
        return 0;}
    printf("%cchegouaki", mensagem[1]);
    //Observação 1: A mensagem deve ser encriptada usando o alfabeto de letras A - Z, codi-
    //ficado com inteiros de 2 a 28, onde 2 = A, 3 = B,..., 27 = Z, 28 = espaço.
    tamanhostr = strlen(mensagem);
    int i;
    for( i = 0; i < tamanhostr; i++){
        if(isspace(mensagem[i]) || isalpha(mensagem[i]))
        {
             // se der ~0 é verdade
             //isspace verifica se é espaco
             //isalpha verifica se é letra
            if(mensagem[i] == 32){
                //32 é o espaco na tabela ascii
                //32-4 = 28 como pede na questao
                mensagem_encriptada[i] = mensagem[i] - 4;
                continue;
                }
            
            else{
            int check_lower = islower(mensagem[i]);
            if(check_lower == 512)
            {
                mensagem[i] = toupper(mensagem[i]);
            }
                mensagem_encriptada[i] = mensagem[i] - 63;
                printf("%c", mensagem[i]);
        }}
    }




    unsigned long long int potencia_criptografar;
    int k;
    for(k = 0; k < tamanhostr - 1; k++) {
        potencia_criptografar = pow(mensagem_encriptada[k], e);   // Loop -> Texto criptografado = (Texto puro^e) mod(n)
        mensagem_encriptada[k] = potencia_criptografar % n;       // e depois escreve o valor criptografado no documento.
        fprintf(mensagem_encriptadax, "%i", mensagem_encriptada[k]);//escreve o digito escriptado
        if(k != tamanhostr - 2) {
            fprintf(mensagem_encriptadax, " ");//escreve espaco
        }
    

    fclose(mensagem_encriptadax); //fecha o txt
    return 0;
    }}

int escolha_e(long long int tp, long long int* f){//scanea E e avalia o E, E é umas das chaves publicas
    int a;
    long long int e;
    printf("digite um numero e que seja 1 < e < tp, sendo que sejam coprimos");
    scanf("%lld", &e);
    if(e > tp && e <= 1)
    {
        escolha_e(tp, f);
    }
    else
    {
        a = test_coprimo(e, tp);
        if(a != 1)
        {
            //se nao forem coprimos, ou ~(1<e<tp), vai repetir a funcao
            printf("errotestedigite um numero e que seja 1 < e < tp, sendo que sejam coprimos");
            escolha_e(tp, f);
        }
        else if(a == 1)
        {
            *f = e;
            return 0;
        }
    }
}
void pega_P_Q(){
    long long int p, q, n, tp, h;
    int b, c;
    long long int e = 0;
    
    printf("digite P, de preferencia um numero muito grande e que seja primo.\n");
    scanf("%lld", &p);

    printf("digite Q, de preferencia um numero muito grande e que seja primo.\n");
    scanf("%lld", &q);

    b = teste_primo(p);
    c = teste_primo(q);

    if(b != 0)
    {
        printf("p nao é primo\n");
        pega_P_Q();
    }
    else if(c != 0)
    {
        printf("q nao é primo");
        pega_P_Q();
    }
    else if(p < 100 && q < 100){
        printf("esse(s) primo(s) é(sao) pequeno(s)\n");
    }
    else if(p == q){
        printf("P e Q sao iguais");
        pega_P_Q();
    }
    else
    {
        n = p * q; //uma das chaves publica
        tp = ((p - 1) * (q - 1));
        escolha_e(tp, &e);
        printf("\nN e Tp sao \n%lld\n%lld\n", n, tp);
        manipular_pasta(n, e); //guarda as chaves em um arquivo
        printf("\nchaves publicas salvas no arquivo .txt\n");
        printf("\nescolha do 'E' finalizada\n");
        menu();//volta para o menu de opcoes
    }
}
int main(){
    printf("    ####    ######    ####    ######   ######    #####     ####   ######     ##     #######   ####      ##\n");
    printf("   ##   ##  ##  ##    ##      ##  ##  # ## #   ##   ##   ##  ##   ##  ##   ####     ##   #    ##      ####\n");
    printf("  ##        ##  ##    ##      ##  ##    ##     ##   ##  ##        ##  ##  ##  ##    ## #      ##     ##  ##            ######    #####    ####\n");
    printf("  ##        #####     ##      #####     ##     ##   ##  ##        #####   ##  ##    ####      ##     ##  ##             ##  ##  ##           ##\n");
    printf("  ##        ## ##     ##      ##        ##     ##   ##  ##  ###   ## ##   ######    ## #      ##     ######             ##       #####    #####\n");
    printf("  ##  ##    ##  ##    ##      ##        ##     ##   ##   ##  ##   ##  ##  ##  ##    ##        ##     ##  ##             ##           ##  ##  ##\n");
    printf("   ####    #### ##   ####    ####      ####     #####     #####  #### ##  ##  ##   ####      ####    ##  ##            ####     ######    #####\n");
    while(menu() != 4){ // loop para sair do programa so quando digitar 4 
        loop_funcao = TRUE;
    }
}


//funcoes auxiliares
int test_coprimo(long long int e, long long int tp){//se forem coprimos o ultimo resutado é 1, se nao for coprimo do qualque um outro valor
    if (tp == 0) return e;
    else test_coprimo(tp, e % tp);
}
int teste_primo(long long int num){//entra um numero, se primo retorna 0 se nao retorna 1 
 int i, resultado = 0;
 for (i = 2; i <= num /2; i++) {
    if (num % i == 0) {
       resultado++;
    }}
    if (resultado == 0) return 0;   
    else return 1;
        
}
void manipular_pasta(long long int n, long long int e){
    FILE *chave_p_pasta;
    chave_p_pasta = fopen("CHAVE_RSA.txt", "w+");
    if(chave_p_pasta == NULL)
    {
      printf("Erro na abertura do arquivo!");
      return;
     }
     fprintf(chave_p_pasta, "n = %lld, e = %lli", n, e);
     fclose(chave_p_pasta);
     printf("Dados gravados com sucesso!");
     return;

}
