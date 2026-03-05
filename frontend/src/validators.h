/**
 * validators.h - Validação de Inputs
 * Declarações para validação de dados antes de enviar ao backend
 */

#ifndef VALIDATORS_H
#define VALIDATORS_H

#include "ui.h"

/**
 * Resultado da validação
 */
typedef struct {
    int is_valid;
    char error_message[256];
} ValidationResult;

/**
 * Valida todos os dados do hemograma
 * @param data Dados a serem validados
 * @return Resultado da validação
 */
ValidationResult validate_hemograma(const HemogramaData *data);

/**
 * Verifica se um valor está dentro de um range
 * @param value Valor a verificar
 * @param min Valor mínimo
 * @param max Valor máximo
 * @return 1 se válido, 0 se inválido
 */
int is_in_range(double value, double min, double max);

/**
 * Verifica se um valor é positivo
 * @param value Valor a verificar
 * @return 1 se positivo, 0 se não
 */
int is_positive(double value);

#endif // VALIDATORS_H
