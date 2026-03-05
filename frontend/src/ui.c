/**
 * ui.c - Implementação da Interface do Usuário
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void print_header(void) {
    printf("\n");
    printf("============================================================\n");
    printf("         SISTEMA DE ANALISE DE HEMOGRAMA - MED IA          \n");
    printf("============================================================\n");
    printf("\n");
}

int show_main_menu(void) {
    int option;
    
    printf("\n--- MENU PRINCIPAL ---\n\n");
    printf("1. Inserir novo hemograma para analise\n");
    printf("2. Sobre o sistema\n");
    printf("3. Sair\n");
    printf("\nEscolha uma opcao: ");
    
    if (scanf("%d", &option) != 1) {
        // Limpa buffer em caso de entrada inválida
        while (getchar() != '\n');
        return -1;
    }
    
    // Limpa o buffer
    while (getchar() != '\n');
    
    return option;
}

/* Função auxiliar para ler um valor double com validação*/
static int read_double(const char *prompt, const char *unit, double *value) {
    printf("%s (%s): ", prompt, unit);
    
    if (scanf("%lf", value) != 1) {
        while (getchar() != '\n');
        return 0;
    }
    
    while (getchar() != '\n');
    return 1;
}

int collect_hemograma_data(HemogramaData *data) {
    if (data == NULL) return 0;
    
    // Zera a estrutura
    memset(data, 0, sizeof(HemogramaData));
    
    printf("\n--- SERIE VERMELHA ---\n\n");
    
    if (!read_double("Hemacias (RBC)", "milhoes/mm3", &data->rbc)) {
        printf("[ERRO] Valor invalido para Hemacias\n");
        return 0;
    }
    
    if (!read_double("Hemoglobina (HGB)", "g/dL", &data->hgb)) {
        printf("[ERRO] Valor invalido para Hemoglobina\n");
        return 0;
    }
    
    if (!read_double("Hematocrito (HCT)", "%", &data->hct)) {
        printf("[ERRO] Valor invalido para Hematocrito\n");
        return 0;
    }
    
    if (!read_double("VCM - Volume Corpuscular Medio", "fL", &data->vcm)) {
        printf("[ERRO] Valor invalido para VCM\n");
        return 0;
    }
    
    if (!read_double("HCM - Hemoglobina Corpuscular Media", "pg", &data->hcm)) {
        printf("[ERRO] Valor invalido para HCM\n");
        return 0;
    }
    
    if (!read_double("CHCM - Concentracao HCM", "g/dL", &data->chcm)) {
        printf("[ERRO] Valor invalido para CHCM\n");
        return 0;
    }
    
    if (!read_double("RDW - Red Cell Distribution Width", "%", &data->rdw)) {
        printf("[ERRO] Valor invalido para RDW\n");
        return 0;
    }
    
    printf("\n--- SERIE BRANCA ---\n\n");
    
    if (!read_double("Leucocitos (WBC)", "/mm3", &data->wbc)) {
        printf("[ERRO] Valor invalido para Leucocitos\n");
        return 0;
    }
    
    if (!read_double("Neutrofilos", "%", &data->neutrophils)) {
        printf("[ERRO] Valor invalido para Neutrofilos\n");
        return 0;
    }
    
    if (!read_double("Linfocitos", "%", &data->lymphocytes)) {
        printf("[ERRO] Valor invalido para Linfocitos\n");
        return 0;
    }
    
    if (!read_double("Monocitos", "%", &data->monocytes)) {
        printf("[ERRO] Valor invalido para Monocitos\n");
        return 0;
    }
    
    if (!read_double("Eosinofilos", "%", &data->eosinophils)) {
        printf("[ERRO] Valor invalido para Eosinofilos\n");
        return 0;
    }
    
    if (!read_double("Basofilos", "%", &data->basophils)) {
        printf("[ERRO] Valor invalido para Basofilos\n");
        return 0;
    }
    
    printf("\n--- PLAQUETAS ---\n\n");
    
    if (!read_double("Plaquetas (PLT)", "/mm3", &data->plt)) {
        printf("[ERRO] Valor invalido para Plaquetas\n");
        return 0;
    }
    
    return 1;
}

void display_result(const char *result) {
    if (result == NULL) {
        printf("\n[ERRO] Nenhum resultado para exibir\n");
        return;
    }
    
    printf("\n============================================================\n");
    printf("                    RESULTADO DA ANALISE                    \n");
    printf("============================================================\n\n");
    
    // Parse simples do JSON para exibição
    // Em produção, usar uma biblioteca JSON adequada
    printf("%s\n", result);
    
    printf("\n============================================================\n");
}

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_for_enter(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}
