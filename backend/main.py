"""
Backend Principal - Servidor API para Machine Learning de Hemograma
"""

import json
import socket
import threading
from services.hemograma_service import HemogramaService
from utils.validators import validate_hemograma_input

HOST = '127.0.0.1'
PORT = 5000

def handle_client(conn, addr):
    """Processa requisição de um cliente."""
    print(f"[INFO] Conexão recebida de {addr}")
    
    try:
        # Recebe dados do cliente
        data = conn.recv(4096).decode('utf-8')
        
        if not data:
            return
        
        # Parse do JSON recebido
        try:
            input_data = json.loads(data)
        except json.JSONDecodeError as e:
            response = {
                "success": False,
                "error": f"JSON inválido: {str(e)}"
            }
            conn.sendall(json.dumps(response).encode('utf-8'))
            return
        
        # Valida os dados de entrada
        is_valid, error_msg = validate_hemograma_input(input_data)
        
        if not is_valid:
            response = {
                "success": False,
                "error": error_msg
            }
            conn.sendall(json.dumps(response).encode('utf-8'))
            return
        
        # Processa com o serviço de ML
        service = HemogramaService()
        result = service.analyze(input_data)
        
        response = {
            "success": True,
            "result": result
        }
        
        conn.sendall(json.dumps(response).encode('utf-8'))
        
    except Exception as e:
        response = {
            "success": False,
            "error": f"Erro interno: {str(e)}"
        }
        conn.sendall(json.dumps(response).encode('utf-8'))
    
    finally:
        conn.close()
        print(f"[INFO] Conexão com {addr} encerrada")


def start_server():
    """Inicia o servidor TCP."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.bind((HOST, PORT))
        server.listen(5)
        
        print(f"[INFO] Servidor iniciado em {HOST}:{PORT}")
        print("[INFO] Aguardando conexões...")
        
        while True:
            conn, addr = server.accept()
            thread = threading.Thread(target=handle_client, args=(conn, addr))
            thread.start()


if __name__ == "__main__":
    start_server()
