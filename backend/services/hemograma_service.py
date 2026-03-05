"""
Serviço de processamento de Hemograma.
Camada de serviço que orquestra a análise de hemograma.
"""

from typing import Dict, Any
from models.hemograma_model import HemogramaModel


class HemogramaService:
    """Serviço para análise de dados de hemograma."""
    
    def __init__(self):
        """Inicializa o serviço com o modelo de ML."""
        self.model = HemogramaModel()
    
    def analyze(self, data: Dict[str, Any]) -> Dict[str, Any]:
        """
        Analisa os dados de hemograma.
        
        Args:
            data: Dicionário com os valores do hemograma
            
        Returns:
            Resultado da análise
        """
        try:
            # Extrai apenas os valores numéricos do hemograma
            hemograma_data = self._extract_hemograma_values(data)
            
            # Realiza a predição/análise
            result = self.model.predict(hemograma_data)
            
            return result
            
        except Exception as e:
            return {
                'status': 'ERRO',
                'message': f'Erro ao processar hemograma: {str(e)}',
                'alerts': []
            }
    
    def _extract_hemograma_values(self, data: Dict[str, Any]) -> Dict[str, float]:
        """
        Extrai e converte valores do hemograma.
        
        Args:
            data: Dados brutos recebidos
            
        Returns:
            Dicionário com valores float
        """
        hemograma_fields = [
            'rbc', 'hgb', 'hct', 'vcm', 'hcm', 'chcm', 'rdw',
            'wbc', 'plt', 'neutrophils', 'lymphocytes', 
            'monocytes', 'eosinophils', 'basophils'
        ]
        
        result = {}
        
        for field in hemograma_fields:
            if field in data:
                try:
                    result[field] = float(data[field])
                except (ValueError, TypeError):
                    result[field] = 0.0
        
        return result
