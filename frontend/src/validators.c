/**
 * validators.c - Implementação da Validação de Inputs
 */

#include <stdio.h>
#include <string.h>
#include "validators.h"

int is_in_range(double value, double min, double max) {
    return (value >= min && value <= max);
}

int is_positive(double value) {
    return (value >= 0);
}

ValidationResult validate_hemograma(const HemogramaData *data) {
    ValidationResult result;
    result.is_valid = 1;
    result.error_message[0] = '\0';
    
    if (data == NULL) {
        result.is_valid = 0;
        strcpy(result.error_message, "Dados nulos");
        return result;
    }
    
    // Validação de Hemácias (RBC)
    if (!is_positive(data->rbc)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Hemacias (RBC) nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->rbc, 0, 20)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Hemacias (RBC) fora do limite seguro (0-20)");
        return result;
    }
    
    // Validação de Hemoglobina (HGB)
    if (!is_positive(data->hgb)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Hemoglobina (HGB) nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->hgb, 0, 30)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Hemoglobina (HGB) fora do limite seguro (0-30)");
        return result;
    }
    
    // Validação de Hematócrito (HCT)
    if (!is_positive(data->hct)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Hematocrito (HCT) nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->hct, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Hematocrito (HCT) fora do limite seguro (0-100)");
        return result;
    }
    
    // Validação de VCM
    if (!is_positive(data->vcm)) {
        result.is_valid = 0;
        strcpy(result.error_message, "VCM nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->vcm, 0, 200)) {
        result.is_valid = 0;
        strcpy(result.error_message, "VCM fora do limite seguro (0-200)");
        return result;
    }
    
    // Validação de HCM
    if (!is_positive(data->hcm)) {
        result.is_valid = 0;
        strcpy(result.error_message, "HCM nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->hcm, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "HCM fora do limite seguro (0-100)");
        return result;
    }
    
    // Validação de CHCM
    if (!is_positive(data->chcm)) {
        result.is_valid = 0;
        strcpy(result.error_message, "CHCM nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->chcm, 0, 50)) {
        result.is_valid = 0;
        strcpy(result.error_message, "CHCM fora do limite seguro (0-50)");
        return result;
    }
    
    // Validação de RDW
    if (!is_positive(data->rdw)) {
        result.is_valid = 0;
        strcpy(result.error_message, "RDW nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->rdw, 0, 50)) {
        result.is_valid = 0;
        strcpy(result.error_message, "RDW fora do limite seguro (0-50)");
        return result;
    }
    
    // Validação de Leucócitos (WBC)
    if (!is_positive(data->wbc)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Leucocitos (WBC) nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->wbc, 0, 500000)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Leucocitos (WBC) fora do limite seguro (0-500000)");
        return result;
    }
    
    // Validação de Plaquetas (PLT)
    if (!is_positive(data->plt)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Plaquetas (PLT) nao pode ser negativo");
        return result;
    }
    if (!is_in_range(data->plt, 0, 2000000)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Plaquetas (PLT) fora do limite seguro (0-2000000)");
        return result;
    }
    
    // Validação de porcentagens (devem estar entre 0-100)
    if (!is_in_range(data->neutrophils, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Neutrofilos deve estar entre 0-100%");
        return result;
    }
    
    if (!is_in_range(data->lymphocytes, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Linfocitos deve estar entre 0-100%");
        return result;
    }
    
    if (!is_in_range(data->monocytes, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Monocitos deve estar entre 0-100%");
        return result;
    }
    
    if (!is_in_range(data->eosinophils, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Eosinofilos deve estar entre 0-100%");
        return result;
    }
    
    if (!is_in_range(data->basophils, 0, 100)) {
        result.is_valid = 0;
        strcpy(result.error_message, "Basofilos deve estar entre 0-100%");
        return result;
    }
    
    // Validação: soma das porcentagens dos leucócitos
    double total_percent = data->neutrophils + data->lymphocytes + 
                          data->monocytes + data->eosinophils + data->basophils;
    
    // Permite uma margem de erro de 5% devido a arredondamentos
    if (total_percent > 105) {
        result.is_valid = 0;
        sprintf(result.error_message, 
                "Soma das porcentagens dos leucocitos muito alta (%.1f%%)", 
                total_percent);
        return result;
    }
    
    return result;
}
