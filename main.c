#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>



//vou iniciar o programa com a função para poder usar acentos e outros caracteres como : Ç ^ ~.
//depois é só chama-lá no main.

int caracteresEspeciais(){
   setlocale(LC_ALL, "Portuguese_Brazil.1252");

return 0;
}

//AQUI COLOCO UMA STRUCT PARA LIDAR MELHOR COM OS DADOS DO CLIENTE, VISTO QUE É IMPORTANTE QUE TANTO O NOME COMO TELEFONE ESTEJAM ALINHADOS PARA..
//TRABALHAR MELHOR!
//TAMBÉM USAREMOS STRUCT PARA LIDAR COM O GERENCIAMENTO DE AGENDAMENTOS.

struct Paciente {
    char nome[50];
    char telefone[15];
};

struct Agendamento {
    int pacienteIndex; //ÍNDICE
    char dia[20];
    char hora[20];
    char especialidade[50];
};

int buscarPacientePorTelefone(struct Paciente pacientes[], int totalPacientes, char telefone[]) {
    for (int i = 0; i < totalPacientes; i++) {
        if (strcmp(pacientes[i].telefone, telefone) == 0) {
            return i;
        }
    }
    return -1;
}

int verificarDisponibilidadeConsulta(struct Agendamento agendamentos[], int totalAgendamentos, char dia[], char hora[]) {
    for (int i = 0; i < totalAgendamentos; i++) {
        if (strcmp(agendamentos[i].dia, dia) == 0 && strcmp(agendamentos[i].hora, hora) == 0) {
            return 0;
        }
    }
    return 1;
}


void exibirListaPacientes(struct Paciente pacientes[], int totalPacientes) {
    printf("\n===+++ LISTA DE PACIENTES CADASTRADOS +++===\n");
    for (int i = 0; i < totalPacientes; i++) {
        printf("%d. NOME: %s | TELEFONE: %s\n", i + 1, pacientes[i].nome, pacientes[i].telefone);
    }
    printf("\n ======================================\n");
}

void exibirListaAgendamentos(struct Paciente pacientes[], struct Agendamento agendamentos[], int totalAgendamentos) {
    printf("\n=== Lista de Agendamentos ===\n");
    for (int i = 0; i < totalAgendamentos; i++) {
        printf("%d. P A C I E N T E : %s | D I A: %s | H O R A: %s | E S P E C I A L I D A D E: %s\n",
               i + 1,
               pacientes[agendamentos[i].pacienteIndex].nome,
               agendamentos[i].dia,
               agendamentos[i].hora,
               agendamentos[i].especialidade);
    }
    printf("================================\n");
}

void remarcarOuCancelarConsulta(struct Paciente pacientes[], struct Agendamento agendamentos[], int *totalAgendamentos) {
    exibirListaAgendamentos(pacientes, agendamentos, *totalAgendamentos);

    if (*totalAgendamentos > 0) {
        printf("\n ==== ESCOLHA O NÚMERO DO AGENDAMENTO PARA REMARCAR OU CANCELAR.....->");
        int escolhaAgendamento;
        scanf("%d", &escolhaAgendamento);

        if (escolhaAgendamento > 0 && escolhaAgendamento <= *totalAgendamentos) {
            int agendamentoIndex = escolhaAgendamento - 1;


            printf("\n--- Informações do Agendamento ---\n");
            printf("\n PACIENTE.....: %s\n", pacientes[agendamentos[agendamentoIndex].pacienteIndex].nome);
            printf("\n DIA...: %s\n", agendamentos[agendamentoIndex].dia);
            printf("\n HORA...: %s\n", agendamentos[agendamentoIndex].hora);
            printf("\n ESPECIALIDADE....: %s\n", agendamentos[agendamentoIndex].especialidade);
            printf("\n---------------------------------\n");


            printf("\n ----- VOCÊ DESEJA REMARCAR (1) OU CANCELAR (2) ESTE AGENDAMENTO?(1 - REMARCAR / 2 - CANCELAR)...-> ");
            int confirmacao;
            scanf("%d", &confirmacao);

            if (confirmacao == 1) {

                printf("....DIGITE O NOVO DIA : ");
                scanf(" %[^\n]s", agendamentos[agendamentoIndex].dia);

                printf(".....DIGITE A NOVA HORA : ");
                scanf(" %[^\n]s", agendamentos[agendamentoIndex].hora);

                printf("\n =============...AGENDAMENTO REMARCADO COM SUCESSO ! ! ! ============\n");
            } else if (confirmacao == 2) {
                // Cancelar agendamento
                for (int i = agendamentoIndex; i < *totalAgendamentos - 1; i++) {
                    agendamentos[i] = agendamentos[i + 1];
                }
                (*totalAgendamentos)--;

                printf("\n =============...AGENDAMENTO CANCELADO COM SUCESSO ! ! ! ============\n");
            } else {
                printf("\n ============ ...OPÇÃO INVÁLIDA ==============\n");
            }
        } else {
            printf("\n------- NÚMERO DE AGENDAMENTO INVÁLIDO.-.-.-.-.-.-.-.-.-.-.-.\n");
        }
    } else {
        printf("\n----------- NÃO EXISTE AGENDAMENTOS PARA CANCELAR OU REMARCAR --------------\n");
    }
}

void exibirMenu() {


    printf("\n _-_-_-_-_-_-_-_-_-_-_-_:::: BEM VINDO AO CADASTRO NA CLÍNICA DE CONSULTAS ÁGIL ! ! !  ::::_-_-_-_-_-_-_-_-_-_-_-_-_\n");
    printf("\n....DIGITE 1 PARA FAZER O CADASTRO DO CLIENTE.... \n");
    printf("\n....DIGITE 2 PARA AGENDAR UMA CONSULTA.... \n");
    printf("\n....DIGITE 3 PARA EXIBIR LISTA DE PACIENTES.... \n");
    printf("\n....DIGITE 4 PARA REMARCAR OU CANCELAR UMA CONSULTA.... \n");
    printf("\n ....DIGITE 0 PARA SAIR DO PROGRAMA.... \n");
    printf("\n++++++++++++++==================================================+++++++++++++\n");
}

int main() {
    caracteresEspeciais();
    //aqui que começa nosso """banco de dados""", pois cada struct de 'paciente', será armazenada em 'pacientes[100]'.
    //nós podemos armazenas até 100 pacientes diferentes, ok? por favor, não quebrem meu código kkkkkkkkkk;
    struct Paciente pacientes[100];
    // funciona de forma análoga a de cima;
    struct Agendamento agendamentos[100];
    // essa variável é importante para o controle da quantidade de pacientes inscritos, ela será usada dentro do switch, e incrementada até o limite de 1000;
    int totalPacientes = 0;
    // nossa variável abaixo é a da escolha do menu;
    int opcao;
    int totalAgendamentos = 0;

    do {

        exibirMenu();
        printf(">>>>>DIGITE SUA OPÇÃO....-> ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 0:
                // para deixar mais bunitin, vamos limpar o menu
                system("cls");
                printf("\n ------- SAINDO DO PROGRAMA ! ATÉ MAIS ! ---------\n");
                break;

            case 1:
                // DENOVO, para deixar mais bunitin, vamos limpar o menu
                system("cls");
                printf("\n=== C A D A S T R O   DE   P A C I E N T E ===\n");


                if (totalPacientes < 100) {

                    printf("++++++++Nome....: ");
                    scanf(" %[^\n]s", pacientes[totalPacientes].nome);

                    printf("\n +++++++Telefone....: ");
                    scanf(" %[^\n]s", pacientes[totalPacientes].telefone);

                    totalPacientes++;

                    printf("\n PACIENTE CADASTRADO ! ! !\n");
                    system("pause");
                    system("cls");
                } else {
                    printf("\n------- INFELIZMENTE A LISTA DE PACIENTES ESTÁ TOTALMENTE CHEIA.\n");
                           printf("\n------- SOLICITE A ÀREA DE TI PARA RESOLVER O PROBLEMA....\n");
                           system("pause");
                           system("cls");
                }

                int indicePacienteExistente = buscarPacientePorTelefone(pacientes, totalPacientes, pacientes[totalPacientes].telefone);
                if (indicePacienteExistente != -1) {
                    printf("\n------- Paciente já cadastrado! -------\n");
                    system("pause");
                    system("cls");
                    totalPacientes--;
                }
                break;

         case 2:

    system("cls");
    exibirListaPacientes(pacientes, totalPacientes);

    if (totalPacientes > 0) {
        printf("... DIGITE O NÚMERO DO PACIENTE PARA AGENDAR CONSULTA----->... ");
        int escolhaPaciente;
        scanf("%d", &escolhaPaciente);

        if (escolhaPaciente > 0 && escolhaPaciente <= totalPacientes) {
            int pacienteIndex = escolhaPaciente - 1;

            printf("\n========= A G E N D A M E N T O   DE   C O N S U L T A =======\n");
            printf("DIGITE O DIA: ");
            scanf(" %[^\n]s", agendamentos[totalAgendamentos].dia);

            printf("DIGITE A HORA: ");
            scanf(" %[^\n]s", agendamentos[totalAgendamentos].hora);

            printf("DIGITE O TIPO DE MÉDICO: ");
            scanf(" %[^\n]s", agendamentos[totalAgendamentos].especialidade);

            int disponibilidadeConsulta = verificarDisponibilidadeConsulta(agendamentos, totalAgendamentos, agendamentos[totalAgendamentos].dia, agendamentos[totalAgendamentos].hora);
            if (disponibilidadeConsulta == 0) {
                printf("\n------- O HORÁRIO JÁ ESTÁ AGENDADO, ESCOLHA OUTRO HORÁRIO -------\n");
                system("pause");
                system("cls");
                break;
            }

            agendamentos[totalAgendamentos].pacienteIndex = pacienteIndex;
            totalAgendamentos++;

            printf("\n ++++++++++++++ AGENDAMENTO REALIZADO COM SUCESSO! ++++++++++++\n");
            system("pause");
            system("cls");
        }
        break;
    }


            case 3:
                system("cls");
                exibirListaPacientes(pacientes, totalPacientes);
                system("pause");
                break;

            case 4:
                system("cls");
                remarcarOuCancelarConsulta(pacientes, agendamentos, &totalAgendamentos);
                system("pause");
                break;

            default:
                printf("\n ============ SUA OPÇÃO ESTÁ EQUIVOCADA, DIGITE NOVAMENTE.....\n");
        }
    } while (opcao != 0);

    return 0;
}
