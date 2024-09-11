### Данная программа создаёт список всех файлов из заданного каталога, тип или имя которых не содержатся в списке исключения **manual_ignore.txt**.

> [!TIP]
>Текстовый файл входных параметров: **manual_ignore.txt**( необходимо поместить рядом с исполняемым файлом ).  
>Текстовый файл в результате работы программы: **.gitignore**  
>Для правильной работы программы необходимо создать файл **.gitignore** и **manual_ignore.txt** и указать следующие данные в **manual_ignore.txt**:  
>1 строка  содержит путь до **.gitignore**   
>2 строка содержит путь до исходников проекта  
>3 и последующие строки расширения файлов или имена файлов  

Собрана на Qt 6.2.0. Запускал на Windows 10
