//
//  main.c
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

unsigned long factor(unsigned base) {
    if (base == 0 || base == 1) {
        return 1;
    }
    if (base > 12) {
        return 0;
    }
    unsigned factorial = 1;
    for (int i = 1; i <= base; ++i) {
        factorial *= i;
    }
    return factorial;
}

int main(int argc, const char * argv[]) {
    int server = socket_s(AF_INET, SOCK_STREAM, 0); // Создаем слушающий сокет с протоколом IPv4
    struct sockaddr_in addr = {0}; //Ожидаем соединение от любого сетевого адаптера (0.0.0.0)
    socklen_t addrlen = 0;
    //Инициализируем структуру адреса сокета
    addr.sin_family = AF_INET;
    addr.sin_port = htons(34543); //Указываем, что будем прослушивать указанный порт, учитывая возможные разницы в порядке расположения байтов
    bind_s(server, (struct sockaddr*) &addr, sizeof(addr)); //Связываем сокет
    listen(server, 1); //Прослушиваем указанный порт, не более 1-го клиента возможно
    addrlen = sizeof(addr);
    int fd = accept_s(server, (struct sockaddr*) &addr, &addrlen); // Принимаем клиента
    //Считываем запрос клиента (клиент отправляет одно беззнаковое целое)
    unsigned readed_number = 0;
    ssize_t nbytes = read(fd,(void*)&readed_number,sizeof(unsigned));
    printf("Принято число: %u\n", readed_number);
    switch (nbytes) {
        case -1:
            perror("Error while reading");
            exit(EXIT_FAILURE);
            break;
        case 0:
            printf("EOF\n");
            exit(EXIT_FAILURE);
            break;
        default:
            break;
    }
    //Обрабатываем запрос (вычисляем факториал)
    unsigned long factorial = 0;
    unsigned i = 1;
    while (i <= readed_number) {
        factorial += factor(i++);
    }
    //Отправляем ответ на запрос клиенту
    write(fd, (void*)&factorial, sizeof(factorial));
    //Закрываем сокеты
    sleep(1);
    close(fd);
    close(server);
    return 0;
}
