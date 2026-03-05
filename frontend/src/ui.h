/**
 * ui.h - Interface do Usuário
 * Declarações para coleta e exibição de dados
 */

#ifndef UI_H
#define UI_H

/**
 * Estrutura que armazena todos os valores do hemograma
 */
typedef struct {
    double rbc;         // Hemácias (milhões/mm³)
    double hgb;         // Hemoglobina (g/dL)
    double hct;         // Hematócrito (%)
    double vcm;         // Volume Corpuscular Médio (fL)
    double hcm;         // Hemoglobina Corpuscular Média (pg)
    double chcm;        // Concentração HCM (g/dL)
    double rdw;         // Red Cell Distribution Width (%)
    double wbc;         // Leucócitos (/mm³)
    double plt;         // Plaquetas (/mm³)
    double neutrophils; // Neutrófilos (%)
    double lymphocytes; // Linfócitos (%)
    double monocytes;   // Monócitos (%)
    double eosinophils; // Eosinófilos (%)
    double basophils;   // Basófilos (%)
} HemogramaData;

/**
 * Exibe o cabeçalho do programa
 */
void print_header(void);

/**
 * Exibe o menu principal
 * @return Opção selecionada pelo usuário
 */
int show_main_menu(void);

/**
 * Coleta todos os dados do hemograma do usuário
 * @param data Ponteiro para estrutura que receberá os dados
 * @return 1 se sucesso, 0 se erro
 */
int collect_hemograma_data(HemogramaData *data);

/**
 * Exibe o resultado da análise
 * @param result String JSON com o resultado
 */
void display_result(const char *result);

/**
 * Limpa a tela do console
 */
void clear_screen(void);

/**
 * Aguarda o usuário pressionar Enter
 */
void wait_for_enter(void);

#endif // UI_H
