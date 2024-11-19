#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>


//---------------------------------------------------------------------------------------------------------------
// Manipua��o das Informa��es da pessoa a ser cadastrada --------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------


//n�mero m�ximo de cadastros permitidos
#define NUM_MAX_CAD 1024


typedef struct Pessoa {
    int ocupado;
	char nome[256];
	char cpf[13];	//o cpf tem 11 caracteres, mas eu leio at� 12 e tem o espaco do '\0'
	int idade;
	char sexo;
	float salario;

} Pessoa;


//--------------------------------------------------------------------------------------------------------------
//Vari�veis Globais --------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

/*
   Essas vari�veis precisam ser globais para
   poderem ser acessadas pelas fun��es:
   * tela_cadastrar();
   * tela_pesquisar();
   * tela_remover();
   * tela_relatorio();
*/

//cria um vetor com capacidade de armazenar os dados de 2048 pessoas !!!
Pessoa vetor_pessoas[NUM_MAX_CAD];
int total_pessoas = 0; //guarda o total de pessoas cadastradas


//--------------------------------------------------------------------------------------------------------------
//Prot�tipo das Fun��es com as Telas / Funcionalidades (Cadastrar/Pesquisar... ---------------------------------
//--------------------------------------------------------------------------------------------------------------

//mostra a tela com o menu de op��es
//retorna a op��o (um valor de 1 a 5) escolhida
//retorna -1 caso o usu�rio escolha uma op��o inv�lida
int tela_menu_opcoes();

//mostra a tela de cadastro
void tela_cadastrar();

//mostra a tela de pesquisa pelo cpf
void tela_pesquisar();

//mostra a tela remover pessoa do cadastro
void tela_remover();

//mostra a tela de relat�rio
void tela_relatorio();

//mostra a tela sair
//retorna 1 caso o usu�rio escolha encerrar a aplica��o
//e 0 caso contr�rio
int tela_sair();


//---------------------------------------------------------------------------------------------------------------
//Programa ------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------


int main()
{
    //muda a localiza��o para Portugu�s do Brasil
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    //variaveis utilizadas para controlar o loop de execu��o do programa
    int sair = 0;   //controla quando o program deve ser encerrao
    int opcao;      //guarda a op��o escolhida pelo usu�rio no menu de op��o


    //inicializa o vetor de pessoas
    //cada elemento do vetor pode guardar o dado de uma pessoa
    //marca os elementos do vetor colo livres / desocupados
    for(int i=0; i < NUM_MAX_CAD; i++)
    {
        //marca a posi��o como livre/desocupada
        //ou seja, pode receber os dados de uma pessoa!
        vetor_pessoas[i].ocupado = 0;
    }


    //loop de execu��o do programa
    do
    {
        //-------------------------------------------------------------------
        //- TELA DE OP��ES --------------------------------------------------
        //-------------------------------------------------------------------

        //mostra a tela com o menu de op��es;
        opcao = tela_menu_opcoes();

        //verifica qual op��o foi escolhida!
        switch(opcao)
        {
            case 1:
                //chama/executa a tela de cadastro
                tela_cadastrar();

            break;

            case 2:
                //chama/executa a tela de pesquisa pelo cpf
                tela_pesquisar();

            break;

            case 3:
                //chama/executa a tela remover pessoa do cadastro
                tela_remover();

            break;

            case 4:

                //mostra a tela de relat�rio
                tela_relatorio();

            break;


            //-------------------------------------------------------------------
            //- TELA ENCERRAR APLICA��O -----------------------------------------
            //-------------------------------------------------------------------

            case 5:

                //mostra a tela sair
                //retorna 1 caso o usu�rio escolha encerrar a aplica��o
                //e 0 caso contr�rio
                sair = tela_sair();

            break;


            //-------------------------------------------------------------------
            //- TRATAMENTO DE OP��O INV�LIDA ------------------------------------
            //-------------------------------------------------------------------


            default:
                //Mostra uma mensagem informando que a op��o
                //escolhida do "Menu de Op��es" � inv�lida!!!
                printf("\nOp��o Inv�lida !!! \n");
                system("pause");
        }

    }while(sair == 0);

    system("cls");
    printf("\nFim da execu��o do programa!\n");

    return 0;
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

//mostra a tela com o menu de op��es
//retorna a op��o (um valor de 1 a 5) escolhida
//retorna -1 caso o usu�rio escolha uma op��o inv�lida
int tela_menu_opcoes()
{
    //guarda a op��o escolhida pelo usu�rio
    int opcao;

     //mostra a Tela com o "Menu de Op��es"
    system("cls");
    printf("Menu de Op��es \n");
    printf("1 - Cadastrar \n");
    printf("2 - Pesquisar \n");
    printf("3 - Remover \n");
    printf("4 - Relat�rio \n");
    printf("5 - Sair \n\n");

    //faz a leitura da op��o escolhida
    printf("Escolha uma op��o: ");
    int erro = scanf("%d", &opcao);

    //verifica se houve uma falha na leitura do scanf
    if(erro != 1) {
        //limpa o buffer do tecaldo (windows)
        fflush(stdin);
        //como teve uma falha na leitura, marca uma op��o inv�lida
        opcao = -1;
    }

    //retorna a op��o escolhida
    return opcao;
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

//mostra a tela de cadastro
void tela_cadastrar()
{
    //controla se o usu�rio quer cadastrar uma nova pessoa;
    int continuar;

    //usado no controle de op��es "sim" ou "n�o"
    char ch;

    //utilizado para verificar erros na leituras/entradas
    //dos dados (nome, idade...) pelo teclado
    int erro;

    //guarda o indice de uma pessoa j� cadastrada com o mesmo cpf
    //da pessoa que ir� ser cadastrada (tela cadastrar)
    int idxPesquisa = -1;

    //vari�veis utilizadas para fazer a leitura dos dados da pessoa do teclado!
    char nome[256];
    //o cpf tem 11 caracteres numericos !!!
    //Gero um vetor com 13 o caractere para:
    //Saber se o usu�rio entrou mais de 11 caracteres;
    //Ter o espa�o do caractere null;
    char cpf[13];
	int idade;
	char sexo, strSexo[3]; //utilizo strSexo para validar a entrada do caractere que representa o sexo
    float salario;

    do {
        system("cls");
        printf("1 - Cadastrar \n");


        //verifica se o cadastro chegou na capacidade m�xima
        if(total_pessoas >= NUM_MAX_CAD)
        {
            //indica que o cadastro j� est� cheio
            printf("\nErro: O cadastro j� atingiu sua capacidade m�xima!\n");
            system("pause");
            break; //encerra o la�o do-while
        }

        //FAZ A ENTRADA DO NOME
        //o nome deve ter pelo menos 3 caracteres
        do
        {
            erro = 0; //marca que ainda n�o ocorreu um erro

            printf("\nDigite o nome: ");
            scanf(" %255[^\n]", nome);

            //Caso o usu�rio entre mais de 255 caracteres, o scanf n�o falha !!!
            //Neste caso ele l� apenas os 255 caracteres, e deixa os caracteres restantes
            //como lixo no buffer do teclado!!!
            //por isso eu limpo o buffer do teclado ap�s a leitura
            fflush(stdin);


            //o nome pode ter no m�ximo 254 caracteres
            if(strlen(nome) > 254)
            {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O nome pode possuir no m�ximo 254 carracteres!\n");
            }
            if(strlen(nome) < 3) {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O nome deve possuir pelo menos 3 (tr�s) carracteres!\n");
            }

        } while(erro == 1); //FIM DA ENTRADA DO NOME


        //FAZ A ENTRADA DO CPF
        //o cpf deve ter 11 digitos num�ricos (testei apenas a quantidade de digitos)
        do
        {
            erro = 0; //marca que por enquanto n�o houve erro

            printf("\nDigite o CPF: ");

            //posso ler no m�ximo 12 caracteres
            scanf(" %12[^\n]", cpf);

            //Caso o usu�rio digite mais de 12 caracteres, o scanf n�o falha !!!
            //Neste caso ele l� apenas os 12 caracteres, e deixa os caracteres restantes
            //como lixo no buffer do teclado!!!
            //por isso eu limpo o buffer do teclado ap�s a leitura
            fflush(stdin);

            //o cpf deve ter 11 digitos/caracteres
            if(strlen(cpf) != 11)
            {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O CPF deve possuir 11 (onze) d�gitos!\n");
            }

        }while(erro == 1); //FIM DA ENTRADA DO CPF


        //FAZ A ENTRADA DA IDADE
        //a idade deve estar entre 1 e 130
        do
        {
            printf("\nDigite a idade: ");
            //caso n�o consiga ler um inteiro retorna um valor diferente de 1
            erro = scanf("%d", &idade);

            //limpa o buffer do teclado para o caso do scanf falhar
            //ou o usu�rio digitar alguma coisa ap�s o n�mero inteiro
            fflush(stdin);

            //verifica se houve um erro de leitua do scanf
            if(erro != 1)
            {
                printf("ERRO: Digite um valor inteiro v�lido!\n");
            }
            //verifica se a idade est� dentro do intervalo
            else if(idade < 1 || idade > 120)
            {
                erro = -1; //considero idade fora do intervalo como um erro
                printf("ERRO: A idade deve estar entre 1 e 120 anos!\n");
            }

        }while(erro != 1); //FIM DA ENTRADA DA IDADE


        //FAZ A ENTRADA DO SEXO
        //Aceita apenas os caracteres (mai�sculo e min�sculo) 'M' ou 'F'
        do
        {
            erro = 0; //marca que por enquanto n�o houve erro

            printf("\nDigite o sexo (M / F): ");

            //l� at� dois caracteres do teclado
            scanf(" %2[^\n]", strSexo);

            //limpa o buffer do tecaldo (windows)
            //se o usu�rio digitar mais de dois caracteres o buffer
            //ficar� com lixo
            fflush(stdin);

            //caso o usu�rio tenha digitado apenas um caracteres
            if(strlen(strSexo) == 1)
            {
                //converte o caractere digitado para mai�sculo e
                //salva ele na vari�vel sexo
                sexo = toupper(strSexo[0]);
            }
            else //o usu�rio digitou mais de um caractere !!!
            {
                erro = 1; //indica que houve um erro
            }

            //caso n�o tenha digitado 'M' ou 'F'
            //ou caso tenha digitado mais de 1 caractere
            if( !(sexo == 'M' || sexo == 'F') || erro == 1 )
            {
                erro = 1; //india que houve erro
                printf("ERRO: S�o aceitos apenas os valores 'M' ou 'F'!\n");
            }

        }while(erro == 1); //FIM DA ENTRADA DO SEXO


        //FAZ A ENTRADA DO SAL�RIO
        //o sal�rio deve ser maior ou igual � R$ 1320,00
        do
        {
            printf("\nDigite o sal�rio: R$ ");
            //caso n�o consiga ler um float retorna um valor diferente de 1 (um)
            erro = scanf("%f", &salario);

            //limpa o buffer do tecaldo (windows)
            //se o usu�rio digitar um valor num�rico inv�lido
            fflush(stdin);

            //se o sal�rio n�o for maior ou igual � R$1.320,00
            //ou se houve um erro na leitura do scanf
            if(salario < 1320.0 || erro != 1)
            {
                erro = -1; //considero salario < 1320.0 como um erro !!!
                printf("ERRO: o sal�rio n�o pode ser menor que R$ 1320,00 !\n");
            }

        }while(erro != 1);  //FIM DA ENTRADA DO SAL�RIO


        //indica que por enquanto n�o encontrou ninguem com o mesmo cpf
        idxPesquisa = -1;

        //verifica se j� existe uma pessoa cadastrada com o mesmo cpf
        for(int i=0; i < NUM_MAX_CAD; i++)
        {
            //verifica se est� ocupado com os dados de uma pessoa
            if(vetor_pessoas[i].ocupado == 1) {

                //compara as strings
                //se encontrar alguem com o mesmo cpf
                if( strcmp(vetor_pessoas[i].cpf, cpf) == 0)
                {
                    //indice da pessoa com o mesmo cpf no vetor de cadastro
                    idxPesquisa = i;
                    break;
                }
            }
        }


        //Caso o idxPesquisa seja diferente de -1, quer dizer que encontrou uma
        //pessoa com o cpf igual no cadastro.
        if(idxPesquisa != -1)
        {
            //indica que j� existe uma pessoa com o mesmo cpf no cadastro
            printf("\nErro: N�o foi poss�vel inserir os dados pois j� existe uma pessoa com o mesmo cpf no cadastro:\v");

            printf("\nPessoa com o mesmo CPF: \n");
            printf("CPF:     %s\n", vetor_pessoas[idxPesquisa].cpf);
            printf("Nome:    %s\n", vetor_pessoas[idxPesquisa].nome);
            printf("Idade:   %d\n", vetor_pessoas[idxPesquisa].idade);
            printf("Sexo:    %c\n", vetor_pessoas[idxPesquisa].sexo);
            printf("Salario: R$ %.2f\n\n",vetor_pessoas[idxPesquisa].salario);
            system("pause");
        }
        else //N�o encontrou uma pessoa j� cadastrada com o mesmo cpf !!!
        {
            //procura um elemento livre (n�o ocupado) no vetor de pessoas!
            for(int i=0; i < NUM_MAX_CAD; i++)
            {
                //encontrou uma posi��o livre
                if(vetor_pessoas[i].ocupado == 0)
                {
                    //marca a posi��o do vetor como ocupada
                    vetor_pessoas[i].ocupado = 1;

                    //insere os dados da pessoa no vetor !!!
                    strcpy(vetor_pessoas[i].nome, nome);
                    strcpy(vetor_pessoas[i].cpf, cpf);
                    vetor_pessoas[i].idade = idade;
                    vetor_pessoas[i].sexo = sexo;
                    vetor_pessoas[i].salario = salario;

                    //incrementa a variavel global que contem o total de pessoas cadastradas
                    total_pessoas = total_pessoas + 1;

                    printf("\nDados cadastrados com sucesso! \n");
                    system("pause");

                    //termina o la�o do for
                    break;
                }
            }
        }

        //Mostra uma mensagem na tela perguntando se o usu�rio deseja
        //pesquisar outra pessoa
        do{

            //faz a leitura da op��o (caractere) escolhida
            printf("\nGostaria de cadastrar outra pessoa? (s/n): ");
            scanf(" %c", &ch);

            //limpa o buffer do tecaldo (windows)
            //se o usu�rio digitar mais de um caracteres o buffer
            //ficar� com lixo (por isso eu limpo)
            fflush(stdin);

            //converte o caractere lido para maiusculo
            ch = toupper(ch);

        //caso o usu�rio n�o digite 's' ou 'n'
        }while(!(ch == 'S' || ch == 'N'));

        //o usu�rio decidiu cadastrar outra pessoa
        if(ch == 'S')
        {
            continuar = 1;
        }
        //o us�rio n�o quer cadastrar outra pessoa
        else{
            continuar = 0;
        }

    } while(continuar == 1);
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

//mostra a tela de pesquisa pelo cpf
void tela_pesquisar()
{
    //controla se o usu�rio quer pesquisar/procurar uma nova pessoa;
    int continuar;

    //usado no controle de op��es "sim" ou "n�o"
    char ch;

    //utilizado para verificar erro na leitura/entrada
    //dos cpf pelo teclado
    int erro;

    //guarda o indice da pessoa que foi pesquisada
    int idxPesquisa = -1;

    //o cpf tem 11 caracteres numericos !!!
    //Gero um vetor com 13 o caractere para:
    //Saber se o usu�rio entrou mais de 11 caracteres;
    //Ter o espa�o do caractere null;
    char cpf[13];

    do{

        system("cls");
        printf("2 - Pesquisar \n");

        //ENTRADA DO CPF
        //o cpf deve ter 11 digitos num�ricos (testei apenas a quantidade de digitos)
        do
        {
            erro = 0; //marca que por enquanto n�o houve erro

            printf("\nDigite o CPF: ");
            //posso ler no m�ximo 12 caracteres
            scanf(" %12[^\n]", cpf);

            //Caso o usu�rio digite mais de 12 caracteres, o scanf n�o falha !!!
            //Neste caso ele l� apenas os 12 caracteres, e deixa os caracteres restantes
            //como lixo no buffer do teclado!!!
            fflush(stdin);

            //o cpf deve ter 11 digitos/caracteres
            if(strlen(cpf) != 11)
            {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O CPF deve possuir 11 (onze) d�gitos!\n");
            }

        }while(erro == 1); // FIM ENTRADA DO CPF


        //indica que por enquanto n�o encontrou ninguem com o cpf pesquisado
        idxPesquisa = -1;

        //pesquisa uma pessoa no cadastro a partir do cpf.
        //percorre todo o vetor com o cadastro das pessoas
        for(int i=0; i<NUM_MAX_CAD; i++){

            //verifica se est� ocupado com os dados de uma pessoa
            if(vetor_pessoas[i].ocupado == 1)
            {
                //verifica se o cpf da pessoa � igual ao cpf pesquisado
                if(strcmp(vetor_pessoas[i].cpf, cpf) == 0){

                    //guarda o indice da pessoa que tem o cpf igual ao cpf pesquisado
                    idxPesquisa = i;

                    //encontrou a pessoa, encerra o la�o de busca
                    break;
                }
            }
        }

        //Caso o indice seja diferente de -1, quer dizer que encontrou uma
        //pessoa com o cpf igual ao cpf pesquisado.
        if(idxPesquisa != -1)
        {
            printf("\nPessoa Encontrada: \n");
            printf("CPF:     %s\n", vetor_pessoas[idxPesquisa].cpf);
            printf("Nome:    %s\n", vetor_pessoas[idxPesquisa].nome);
            printf("Idade:   %d\n", vetor_pessoas[idxPesquisa].idade);
            printf("Sexo:    %c\n", vetor_pessoas[idxPesquisa].sexo);
            printf("Salario: R$ %.2f\n\n",vetor_pessoas[idxPesquisa].salario);
            system("pause");
        }
        else //N�o encontrou uma pessoa
        {
            printf("\nN�o foi encontrada uma pessoa com o cpf informado!\n\n");
            system("pause");
        }


        //Mostra uma mensagem na tela perguntando se o usu�rio deseja
        //pesquisar outra pessoa
        do{

            //faz a leitura da op��o (caractere) escolhida
            printf("\nGostaria de pesquisar outra pessoa?  (s/n): ");
            scanf(" %c", &ch);

            //limpa o buffer do tecaldo (windows)
            //se o usu�rio digitar mais de um caracteres o buffer
            //ficar� com lixo (por isso eu limpo)
            fflush(stdin);

            //converte o caractere lido para maiusculo
            ch = toupper(ch);

        //caso o usu�rio n�o digite 's' ou 'n'
        }while(!(ch == 'S' || ch == 'N'));

        //o usu�rio decidiu pesquisar outra pessoa
        if(ch == 'S')
        {
            continuar = 1;
        }
        //o us�rio n�o quer pesquisar outra pessoa
        else{
            continuar = 0;
        }

    } while(continuar == 1);
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

//mostra a tela remover pessoa do cadastro
void tela_remover()
{
    //controla se o usu�rio quer remover uma outra pessoa;
    int continuar;

    //usado no controle de op��es "sim" ou "n�o"
    char ch;

    //utilizado para verificar erro na leitura/entrada
    //dos cpf pelo teclado
    int erro;

    //guarda o indice da pessoa que ser� removida
    int idxPesquisa = -1;

    //o cpf tem 11 caracteres numericos !!!
    //Gero um vetor com 13 o caractere para:
    //Saber se o usu�rio entrou mais de 11 caracteres;
    //Ter o espa�o do caractere null;
    char cpf[13];

    do
    {
        system("cls");
        printf("3 - Remover \n\n");

        //ENTRADA DO CPF
        //o cpf deve ter 11 digitos num�ricos (testei apenas a quantidade de digitos)
        do
        {
            erro = 0; //marca que por enquanto n�o houve erro

            printf("\nDigite o CPF: ");

            //posso ler no m�ximo 12 caracteres
            scanf(" %12[^\n]", cpf);

            //Caso o usu�rio digite mais de 12 caracteres, o scanf n�o falha !!!
            //Neste caso ele l� apenas os 12 caracteres, e deixa os caracteres restantes
            //como lixo no buffer do teclado!!!
            fflush(stdin);

            //o cpf deve ter 11 digitos/caracteres
            if(strlen(cpf) != 11)
            {
                erro = 1; //marca a ocorr�ncia de um erro
                printf("ERRO: O CPF deve possuir 11 (onze) d�gitos!\n");
            }

        }while(erro == 1); // FIM ENTRADA DO CPF


        //indica que por enquanto n�o encontrou ninguem com o cpf pesquisado
        idxPesquisa = -1;

        //percorre todo o vetor com as pessoas cadastradas
        for(int i = 0; i < NUM_MAX_CAD; i++) {

            //verifica apenas elementos do vetor de pessoas que realmente est�o ocupados
            //ocupados/guardado os dados de uma pessoa !!!
            if(vetor_pessoas[i].ocupado == 1)
            {
                //verifica se o cpf da pessoa � igual ao cpf passado como par�mentro
                if(strcmp(vetor_pessoas[i].cpf, cpf) == 0){

                    //encontrou a pessoa, ent�o tem que decrementar o contador de pessoas
                    total_pessoas = total_pessoas - 1;

                    //marca o espa�o/elemento do vetor como livre, ou seja
                    //pode ser reutilizado para guardar os dados de outra pessoa!!!
                    vetor_pessoas[i].ocupado = 0;

                    //guarda o indice da pessoa que tem o cpf igual ao cpf pesquisado
                    idxPesquisa = i;

                    //encontrou a pessoa, encerra o la�o de busca
                    break;
                }
            }
        }

        //Caso o indice seja diferente de -1, quer dizer que encontrou uma
        //pessoa com o cpf igual ao cpf pesquisado.
        if(idxPesquisa != -1)
        {
            printf("\nPessoa removida com sucesso!\n");
        }
        else
        {
            printf("\nN�o foi poss�vel remover a pessoa do cadastro!\n");
        }

        system("pause");



        //Mostra uma mensagem na tela perguntando se o usu�rio deseja
        //remover outra pessoa
        do{

            //faz a leitura da op��o (caractere) escolhida
            printf("\nGostaria de remover outra pessoa?  (s/n): ");
            scanf(" %c", &ch);

            //limpa o buffer do tecaldo (windows)
            //se o usu�rio digitar mais de um caracteres o buffer
            //ficar� com lixo (por isso eu limpo)
            fflush(stdin);

            //converte o caractere lido para maiusculo
            ch = toupper(ch);

        //caso o usu�rio n�o digite 's' ou 'n'
        }while(!(ch == 'S' || ch == 'N'));

        //o usu�rio decidiu pesquisar outra pessoa
        if(ch == 'S')
        {
            continuar = 1;
        }
        //o us�rio n�o quer pesquisar outra pessoa
        else{
            continuar = 0;
        }

    }while(continuar);
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

//mostra a tela de relat�rio
void tela_relatorio()
{
    system("cls");
    printf("4 - Relat�rio \n\n");

    printf("Total de Pessoas Cadastradas: %d\n\n", total_pessoas);

    //percorre todo o vetor com o cadastro das pessoas
    for(int i=0; i<NUM_MAX_CAD; i++){

        if(vetor_pessoas[i].ocupado == 1)
        {
            printf("CPF:     %s\n", vetor_pessoas[i].cpf);
            printf("Nome:    %s\n", vetor_pessoas[i].nome);
            printf("Idade:   %d\n", vetor_pessoas[i].idade);
            printf("Sexo:    %c\n", vetor_pessoas[i].sexo);
            printf("Salario: R$ %.2f\n\n",vetor_pessoas[i].salario);
        }
    }

    system("pause");
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------

//mostra a tela sair
//retorna 1 caso o usu�rio escolha encerrar a aplica��o
//e 0 caso contr�rio
int tela_sair()
{
    //guarda o caractere ('s' ou 'n') digitado
    char ch;

    //recebe 1 indicando que a aplica��o deve ser encerrada e 0 caso contr�rio
    int sair;
    system("cls");
    printf("5 - Sair \n\n");

    do{
        //faz a leitura da op��o (caractere) escolhida
        printf("\nDeseja mesmo sair?  (s/n): ");
        scanf(" %c", &ch);

        //limpa o buffer do tecaldo (windows)
        //se o usu�rio digitar mais de um caracteres o buffer
        //ficar� com lixo (por isso eu limpo)
        fflush(stdin);

        //converte o caractere lido para maiusculo
        ch = toupper(ch);

        //caso o usu�rio escolha 'S', isto � sair
        if(ch == 'S')
        {
            //recebe 1 indicando que a aplica��o deve ser encerrada
            sair = 1;
        }
        else if(ch == 'N')
        {
            //recebe 0 indicando que a aplica��o n�o deve ser encerrada
            sair = 0;
        }

    //caso o usu�rio n�o digite 's' ou 'n'
    }while(!(ch == 'S' || ch == 'N'));

    //retorna 1 (sair) ou 0 (n�o sair)
    return sair;
}

//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
