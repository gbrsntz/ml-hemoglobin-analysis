# Projeto MED IA - Análise de Hemograma com Machine Learning

## Arquitetura do Projeto

```
Projeto_MED_IA/
│
├── backend/                    # Backend Python (Machine Learning)
│   ├── main.py                 # Servidor API principal
│   ├── models/                 # Modelos de ML
│   │   ├── __init__.py
│   │   └── hemograma_model.py  # Modelo base para hemograma
│   ├── services/               # Serviços de processamento
│   │   ├── __init__.py
│   │   └── hemograma_service.py
│   ├── utils/                  # Utilitários
│   │   ├── __init__.py
│   │   └── validators.py       # Validação de dados
│   └── requirements.txt
│
├── frontend/                   # Frontend C (Executável)
│   ├── src/
│   │   ├── main.c              # Ponto de entrada
│   │   ├── ui.c                # Interface do usuário
│   │   ├── ui.h
│   │   ├── communication.c     # Comunicação com backend
│   │   ├── communication.h
│   │   ├── validators.c        # Validação de inputs
│   │   └── validators.h
│   └── Makefile
│
└── README.md
```

## Fluxo de Comunicação

1. **Usuário** → Executa o programa C
2. **Frontend C** → Coleta inputs do hemograma
3. **Frontend C** → Valida dados localmente
4. **Frontend C** → Envia JSON via socket TCP (localhost:5000)
5. **Backend Python** → Recebe e valida dados
6. **Backend Python** → Processa com ML
7. **Backend Python** → Retorna resultado JSON
8. **Frontend C** → Exibe resultado ao usuário

## Inputs de Hemograma Suportados (Teste)

- Hemácias (RBC)
- Hemoglobina (HGB)
- Hematócrito (HCT)
- VCM (Volume Corpuscular Médio)
- HCM (Hemoglobina Corpuscular Média)
- CHCM (Concentração de Hemoglobina Corpuscular Média)
- RDW (Red Cell Distribution Width)
- Leucócitos (WBC)
- Plaquetas (PLT)
- Neutrófilos
- Linfócitos
- Monócitos
- Eosinófilos
- Basófilos

## Como Executar

### Backend (Python)
```bash
cd backend
pip install -r requirements.txt
python main.py
```

### Frontend (C)
```bash
cd frontend
make
./hemograma_app.exe
```

## Segurança

- Validação dupla de dados (frontend + backend)
- Comunicação apenas via localhost
- Sanitização de inputs
- Tratamento de erros robusto
