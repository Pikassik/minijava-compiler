# minijava-compiler

#### Вывод оптимизаций
```bash
./mjava -call -eseq -lin sample_name.mjava
```

Можно вывести только `-call`, тогда увидите eseq'и, при `-call -eseq`
будут удалены eseq'и, при `-call -eseq -lin` дерево будет линеаризовано.   

#### Вывод IR
```bash
./mjava -irt sample_name.mjava
```
Дерево будет в `sample_name.ir.txt`  
Необходимый пример уже в `Samples/ir_sample.mjava` и `Samples/ir_sample.mjava.ir.txt` 
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