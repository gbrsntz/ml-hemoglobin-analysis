/**
 * main.c - Ponto de Entrada do Sistema MED IA
 * Sistema de Análise de Hemograma com Machine Learning
 */


#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "communication.h"
#include "validators.h"
#include "gui.h"

/**
 * Executa a análise completa de hemograma
 */
static void run_analysis(void) {
    HemogramaData data;
    char result[BUFFER_SIZE];
    ValidationResult validation;
    
    clear_screen();
    print_header();
    printf("\n--- ANALISE DE HEMOGRAMA ---\n");
    printf("\nInsira os valores do exame de hemograma:\n");
    
    // Coleta os dados do usuário
    if (!collect_hemograma_data(&data)) {
        printf("\n[ERRO] Falha ao coletar dados do hemograma\n");
        wait_for_enter();
        return;
    }
    
    // Valida os dados antes de enviar
    validation = validate_hemograma(&data);
    if (!validation.is_valid) {
        printf("\n[ERRO] Validacao falhou: %s\n", validation.error_message);
        wait_for_enter();
        return;
    }
    
    printf("\n[INFO] Enviando dados para analise...\n");
    
    // Envia para o backend Python
    if (!send_hemograma_analysis(&data, result)) {
        printf("\n[ERRO] Falha na comunicacao com o servidor de ML\n");
        wait_for_enter();
        return;
    }
    
    // Exibe o resultado
    display_result(result);
    wait_for_enter();
}

/**
 * Exibe informações sobre o sistema
 */
static void show_about(void) {
    clear_screen();
    print_header();
    
    printf("\n--- SOBRE O SISTEMA ---\n\n");
    printf("Sistema MED IA - Analise de Hemograma com Machine Learning\n\n");
    printf("Este sistema utiliza inteligencia artificial para auxiliar\n");
    printf("na analise de exames de hemograma completo.\n\n");
    printf("IMPORTANTE: Este sistema e apenas para fins educacionais\n");
    printf("e de pesquisa. NAO substitui o diagnostico medico.\n\n");
    printf("Componentes:\n");
    printf("  - Frontend: C (executavel)\n");
    printf("  - Backend: Python (Machine Learning)\n");
    printf("  - Comunicacao: TCP/IP Socket (localhost)\n");
    printf("\n");
    printf("Parametros analisados:\n");
    printf("  - Serie Vermelha: RBC, HGB, HCT, VCM, HCM, CHCM, RDW\n");
    printf("  - Serie Branca: WBC, Neutrofilos, Linfocitos, etc.\n");
    printf("  - Plaquetas: PLT\n");
    printf("\n");
    
    wait_for_enter();
}

/**
 * Função principal
 */
int main(void) {

    // Inicializa comunicação com backend Python
    if (!comm_init()) {
        printf("[ERRO FATAL] Falha ao inicializar sistema de comunicacao\n");
        return 1;
    }

    // Inicia interface gráfica
    start_gui();

    // Finaliza comunicação
    comm_cleanup();

    printf("\nObrigado por usar o MED IA!\n");

    return 0;
}
