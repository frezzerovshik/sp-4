//
//  client.c
//  sp_4_lab
//
//  Created by Артем Шарапов on 06.06.2020.
//  Copyright © 2020 Artem Sharapov. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "safe_net.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, const char * argv[]) {
    int fd = socket_s(AF_INET, SOCK_STREAM, 0); // Создаем слушающий сокет с протоколом IPv4
    struct sockaddr_in addr = {0}; //Ожидаем соединение от любого сетевого адаптера (0.0.0.0)
    //Инициализируем структуру адреса сокета
    addr.sin_family = AF_INET;
    addr.sin_port = htons(34543); //Указываем, что будем прослушивать указанный порт, учитывая возможные разницы в порядке расположения байтов
    inet_pton_s(AF_INET, "127.0.0.1", &addr.sin_addr);//Указываем ip сервера, к которому хотим подключиться
    connect(fd, (struct sockaddr*)&addr, sizeof(addr)); //Соединяемся
    printf("Введите число:\n");
    unsigned num;
    scanf("%u",&num);
    write(fd, (void*)&num, sizeof(unsigned));
    unsigned long response = 0;
    ssize_t response_size = 0;
    response_size = read(fd, (void*)&response, sizeof(unsigned long));
    if (response_size == -1) {
        perror("Error while reading");
        exit(EXIT_FAILURE);
    }
    if (response_size == 0) {
        printf("EOF\n");
        exit(EXIT_FAILURE);
    }
    if (response == 0) {
        printf("Результат не влез в разрядную сетку\n");
    }
    if (response_size == sizeof(unsigned long)) {
        printf("Сумма факториалов от 1 до %u равна %lu\n", num,response);
    }
    sleep(1);
    close(fd);
    return 0;
}
