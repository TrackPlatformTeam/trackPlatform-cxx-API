1. Пользователь выбирает другое API.
2. Если соединения нет  
    2.1. Вывод об ошибке  
    2.2. Переход к пункту 14
3. Отправка команды отключения
4. Ожидание ответа о приеме команды
5. Если ответ ERROR  
    5.1. Переход к пункту 2.1  
6. Ожидание ответа о выполнении команды
7. Если ответ ERROR  
    7.1. Переход к пункту 2.1  
8. Отправка команды подключения с новым API
9. Ожидание ответа о приеме команды  
10. Если ответ ERROR  
    10.1. Переход к пункту 2.1
11. Ожидание ответа о выполнении команды
12. Если ответ ERROR
    12.1. Переход к пункту 2.1
13. Изменение GUI
14. Конец