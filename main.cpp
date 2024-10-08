


#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>

const QString NameManualFile = "manual_ignore.txt";

void addListPath(const QDir &curr_dir, QStringList &list_all_files, QDirIterator::IteratorFlag it_flag)
{

    QDirIterator it(curr_dir.path(), QDir::Files, it_flag);

    while (it.hasNext())
    {
        QString s_rel = curr_dir.relativeFilePath(it.next());
        list_all_files.append(s_rel);
    }

}

int init()
{
    qDebug()<<"Start app";

    QFile r_file(NameManualFile);

    if (!r_file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"manual_ignore.txt file not open";
        return 1;
    }

    QMap<QString, bool> map_exp;
    QTextStream input_stream(&r_file);

    const QString path_gitignore = input_stream.readLine();
    const QString path_dir = input_stream.readLine();

    QDir curr_dir(path_dir);

    while (!input_stream.atEnd())
    {
        QString s_key = input_stream.readLine();
        if (!s_key.isEmpty())
            map_exp[s_key] =  true;
    }

    r_file.close();

    QStringList list_all_files;

    addListPath(curr_dir, list_all_files, QDirIterator::Subdirectories);

    for (const QString &s : list_all_files)
    {

        QString file_name = QStringList(s.split(QDir::separator())).last();
        QString file_exp = file_name.right(file_name.length() - file_name.indexOf('.'));

        if (map_exp.value(file_exp))
        {
            int ind_of =  list_all_files.indexOf(s);
            list_all_files.replace(ind_of, "");
        }
    }

    QFile w_file(path_gitignore);

    if (!w_file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"gitignore file not open";
        return 1;
    }

    QTextStream output_stream(&w_file);

    for (auto it = list_all_files.begin(); it!=list_all_files.end(); ++it)
    {
        if (!it->isEmpty())
            output_stream << *it<<"\n";
    }

    w_file.close();

    return 0; //Все ОК
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   if (init() >0) //Если ошибка то остаемся
        a.exec();
   else           //Если все ОК то выходим
       return 0;
}






