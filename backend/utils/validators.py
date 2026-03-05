"""
Validadores de dados de entrada.
Garante que os dados recebidos são válidos antes do processamento.
"""

from typing import Dict, Any, Tuple


def validate_hemograma_input(data: Dict[str, Any]) -> Tuple[bool, str]:
    """
    Valida os dados de entrada do hemograma.
    
    Args:
        data: Dicionário com os dados a serem validados
        
    Returns:
        Tupla (is_valid, error_message)
    """
    if not isinstance(data, dict):
        return False, "Dados devem ser um objeto JSON"
    
    if not data:
        return False, "Dados vazios"
    
    # Campos válidos do hemograma
    valid_fields = {
        'rbc', 'hgb', 'hct', 'vcm', 'hcm', 'chcm', 'rdw',
        'wbc', 'plt', 'neutrophils', 'lymphocytes',
        'monocytes', 'eosinophils', 'basophils'
    }
    
    # Limites de segurança (valores absurdamente fora da realidade)
    safety_limits = {
        'rbc': {'min': 0, 'max': 20},
        'hgb': {'min': 0, 'max': 30},
        'hct': {'min': 0, 'max': 100},
        'vcm': {'min': 0, 'max': 200},
        'hcm': {'min': 0, 'max': 100},
        'chcm': {'min': 0, 'max': 50},
        'rdw': {'min': 0, 'max': 50},
        'wbc': {'min': 0, 'max': 500000},
        'plt': {'min': 0, 'max': 2000000},
        'neutrophils': {'min': 0, 'max': 100},
        'lymphocytes': {'min': 0, 'max': 100},
        'monocytes': {'min': 0, 'max': 100},
        'eosinophils': {'min': 0, 'max': 100},
        'basophils': {'min': 0, 'max': 100}
    }
    
    has_valid_field = False
    
    for key, value in data.items():
        if key not in valid_fields:
            continue
        
        has_valid_field = True
        
        # Verifica se é um número
        if not isinstance(value, (int, float)):
            try:
                float(value)
            except (ValueError, TypeError):
                return False, f"Campo '{key}' deve ser um número"
        
        # Verifica limites de segurança
        num_value = float(value)
        
        if num_value < 0:
            return False, f"Campo '{key}' não pode ser negativo"
        
        if key in safety_limits:
            limits = safety_limits[key]
            if num_value < limits['min'] or num_value > limits['max']:
                return False, f"Campo '{key}' fora dos limites seguros ({limits['min']}-{limits['max']})"
    
    if not has_valid_field:
        return False, "Nenhum campo válido de hemograma encontrado"
    
    return True, ""


def sanitize_input(value: str) -> str:
    """
    Sanitiza string de entrada.
    
    Args:
        value: String a ser sanitizada
        
    Returns:
        String sanitizada
    """
    if not isinstance(value, str):
        return str(value)
    
    # Remove caracteres potencialmente perigosos
    dangerous_chars = ['<', '>', '"', "'", '\\', '\x00']
    
    result = value
    for char in dangerous_chars:
        result = result.replace(char, '')
    
    return result.strip()
