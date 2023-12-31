## Устройство управления опорно-поворотным устройством PIH-301
Принимает команды управления положением по интерфейсу UART с физическим уровнем RS485 и выдает необходимое аналоговое воздействие на опорно-поворотное устройство (ОПУ). Для перемещение ОПУ в течении определенного интервала времени, зависящего от требуемого смещения, на обмоту двигателя подается ~24В 50Гц.

### Подключение устройства
Для питания используется напряжение ~230В. Подключение к ОПУ с помощью 6-и выводного разъема . Подключение к ПК осуществялется по интерфейсу UART с физическим уровнем RS485 (разъем RJ11, два контакта по центру: A, B).

Параметры UART:
- Скорость: 115200 бод
- Количество стоп-бит: 1
- Бит паритета: нет

### Команды управления
Команды состоят из 4-х последовательных байт. Если временной интервал между байтами команды больше 200 битовых импульсов, то байты не обрабатываются. Формат команд следующий:
- 1-2 байты: идентификатор команды (2 байтное число, первый байт младший)
- 2-4 байты: аргумент команды (2 байтное число, первый байт младший)

| Наименование | Id | Аргумент | Ответ |
| --- | --- | --- | --- |
| Сбросить МК | 1 | - | - |
| Запрос тестового ответа МК | 2 | - | 4 байта:<br>`0x02 0x0A 0x0A 0x0A` |
| Переключить светодиод | 3 | - | - |
| Задать коэфициент перечета угла азимута во время воздействия | 4 | Значение коэфициента мс/град | - |
| Задать коэфициент перечета угла места во время воздействия | 5 | Значение коэфициента мс/град | - |
| Задать текущее положение в качестве начала координат | 6 | - | - |
| Остановить ОПУ | 7 | - | - |
| Остановить ОПУ по углу азимута | 8 | - | - |
| Остановить ОПУ по углу места | 9 | - | - |
| Сместить ОПУ по углу азмимута | 10 | Знаковое целое число равное:<br>$10 \cdot offset$,<br>где *offset*, град - угловое смещение | - |
| Сместить ОПУ по углу места | 11 | Знаковое целое число равное:<br>$10 \cdot offset$,<br>где *offset*, град - угловое смещение | - |
| Запрос положения ОПУ по углу азимута | 12 | - | 4 байта:<br> 1-2 байты: число `12`,<br> 3-4 байты: знаковое целое число равное:<br>$10 \cdot pos$,<br>где *pos*, град - угловое положение |
| Запрос положения ОПУ по углу места | 13 | - | 4 байта:<br> 1-2 байты: число `13`,<br> 3-4 байты: знаковое целое число равное:<br>$10 \cdot pos$,<br>где *pos*, град - угловое положение |
| Запрос положения ОПУ | 14 | - | 6 байт:<br> 1-2 байты: число `14`,<br> 3-4 байты: знаковое целое число равное:<br>$10 \cdot pos_{az}$,<br>где $pos_{az}$, град - положение по углу азимуту<br> 5-6 байты: знаковое целое число равное:<br>$10 \cdot pos_{el}$,<br>где $pos_{el}$, град - положение по углу места |


### Примеры команд
- Запрос тестового ответа МК:<br>`0x02 0x00 0x00 0x00`<br>ответ:<br>`0x02 0x0A 0x0A 0x0A`
- Сместить положение ОПУ по углу азимута на 5 град:<br>`0x0A 0x00 0x32 0x00`
- Сместить положение ОПУ по углуазимуту на -5 град:<br>`0x0A 0x00 0xCE 0xFF`
- Запрос положения ОПУ:<br>`0x0E 0x00 0x00 0x00`<br>ответ:<br>`0x0E 0x00 0x32 0x00 0xCE 0xFF` - положение по углу азимуту 5 град, по углу места -5 град