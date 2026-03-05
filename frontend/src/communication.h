/**
 * communication.h - Comunicação com Backend
 * Declarações para comunicação via socket com o servidor Python
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "ui.h"

#define SERVER_HOST "127.0.0.1"
#define SERVER_PORT 5000
#define BUFFER_SIZE 8192

/**
 * Inicializa o sistema de comunicação (Winsock no Windows)
 * @return 1 se sucesso, 0 se erro
 */
int comm_init(void);

/**
 * Finaliza o sistema de comunicação
 */
void comm_cleanup(void);

/**
 * Envia dados do hemograma para o backend e recebe resultado
 * @param data Dados do hemograma a enviar
 * @param result Buffer para receber o resultado (deve ter BUFFER_SIZE bytes)
 * @return 1 se sucesso, 0 se erro
 */
int send_hemograma_analysis(const HemogramaData *data, char *result);

/**
 * Converte HemogramaData para JSON string
 * @param data Dados do hemograma
 * @param json Buffer para o JSON (deve ter BUFFER_SIZE bytes)
 * @return 1 se sucesso, 0 se erro
 */
int hemograma_to_json(const HemogramaData *data, char *json);

#endif // COMMUNICATION_H
