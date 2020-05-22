# minijava-compiler

#### Вывод IR
```bash
./mjava -irt sample_name.mjava
```
Дерево будет в `sample_name.ir.txt`
#### Как запускать?
```bash
./mjava sample.mjava
```
#### Опции
  * -t вывод debug информации парсера
  * -d dump AST в формате png
  * Выполняется первый аргумент, не подходящий под критерии выше 

#### Samples
  В папке Samples можно найти много примеров использования (в том числе с ошибками)