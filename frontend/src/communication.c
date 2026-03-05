/**
 * communication.c - Implementação da Comunicação com Backend
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "communication.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
#endif

static int is_initialized = 0;

int comm_init(void) {
#ifdef _WIN32
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        printf("[ERRO] Falha ao inicializar Winsock: %d\n", result);
        return 0;
    }
#endif
    is_initialized = 1;
    return 1;
}

void comm_cleanup(void) {
#ifdef _WIN32
    if (is_initialized) {
        WSACleanup();
    }
#endif
    is_initialized = 0;
}

int hemograma_to_json(const HemogramaData *data, char *json) {
    if (data == NULL || json == NULL) return 0;
    
    int written = snprintf(json, BUFFER_SIZE,
        "{"
        "\"rbc\": %.2f, "
        "\"hgb\": %.2f, "
        "\"hct\": %.2f, "
        "\"vcm\": %.2f, "
        "\"hcm\": %.2f, "
        "\"chcm\": %.2f, "
        "\"rdw\": %.2f, "
        "\"wbc\": %.2f, "
        "\"plt\": %.2f, "
        "\"neutrophils\": %.2f, "
        "\"lymphocytes\": %.2f, "
        "\"monocytes\": %.2f, "
        "\"eosinophils\": %.2f, "
        "\"basophils\": %.2f"
        "}",
        data->rbc,
        data->hgb,
        data->hct,
        data->vcm,
        data->hcm,
        data->chcm,
        data->rdw,
        data->wbc,
        data->plt,
        data->neutrophils,
        data->lymphocytes,
        data->monocytes,
        data->eosinophils,
        data->basophils
    );
    
    return (written > 0 && written < BUFFER_SIZE);
}

int send_hemograma_analysis(const HemogramaData *data, char *result) {
    if (!is_initialized) {
        printf("[ERRO] Sistema de comunicacao nao inicializado\n");
        return 0;
    }
    
    if (data == NULL || result == NULL) {
        return 0;
    }
    
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in server_addr;
    char json_buffer[BUFFER_SIZE];
    int bytes_received;
    
    // Converte para JSON
    if (!hemograma_to_json(data, json_buffer)) {
        printf("[ERRO] Falha ao converter dados para JSON\n");
        return 0;
    }
    
    // Cria socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("[ERRO] Falha ao criar socket\n");
        return 0;
    }
    
    // Configura endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    
    if (inet_pton(AF_INET, SERVER_HOST, &server_addr.sin_addr) <= 0) {
        printf("[ERRO] Endereco do servidor invalido\n");
        closesocket(sock);
        return 0;
    }
    
    // Conecta ao servidor
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("[ERRO] Falha ao conectar ao servidor Python\n");
        printf("       Certifique-se de que o backend esta rodando!\n");
        printf("       Execute: cd backend && python main.py\n");
        closesocket(sock);
        return 0;
    }
    
    // Envia dados
    if (send(sock, json_buffer, (int)strlen(json_buffer), 0) == SOCKET_ERROR) {
        printf("[ERRO] Falha ao enviar dados\n");
        closesocket(sock);
        return 0;
    }
    
    // Recebe resposta
    memset(result, 0, BUFFER_SIZE);
    bytes_received = recv(sock, result, BUFFER_SIZE - 1, 0);
    
    if (bytes_received == SOCKET_ERROR || bytes_received == 0) {
        printf("[ERRO] Falha ao receber resposta do servidor\n");
        closesocket(sock);
        return 0;
    }
    
    result[bytes_received] = '\0';
    
    // Fecha conexão
    closesocket(sock);
    
    return 1;
}
