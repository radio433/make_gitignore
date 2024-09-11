


#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>

void addListPath(const QString &curr_dir, QStringList &list_all_files, QDirIterator::IteratorFlag it_flag)
{

    QDirIterator it_sub(curr_dir, QDir::Files, it_flag);

    while (it_sub.hasNext())
    {
        QString s = it_sub.next();
        list_all_files.append(s);
    }

}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"Start app";

    QFile r_file("D:/manual_ignore.txt");

    if (!r_file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"ignore file not open";
        QCoreApplication::exit();
    }

    QMap<QString, bool> map_exp;
    QTextStream input_stream(&r_file);

    QString path_gitignore = input_stream.readLine();
    QString path_dir = input_stream.readLine();

    QDir curr_dir(path_dir);

    while (!input_stream.atEnd())
    {
        QString s_key = input_stream.readLine();
        if (!s_key.isEmpty())
            map_exp[s_key] =  true;
    }

    r_file.close();

    QStringList list_all_files;

    addListPath(curr_dir.path(), list_all_files, QDirIterator::Subdirectories);

    for (const QString &s : list_all_files)
    {

        QString file_name = QStringList(s.split("/")).last();
        QString file_exp = file_name.right(file_name.length() - file_name.indexOf('.'));

        qDebug()<<file_name<<file_exp;

        if (map_exp.value(file_exp))
        {
            int ind_of =  list_all_files.indexOf(s);
            list_all_files.replace(ind_of, "");
            qDebug()<<"match "<<file_exp;
        }
    }

    QFile w_file(path_gitignore);

    if (!w_file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"gitignore file not open";
        QCoreApplication::exit();
    }

    QTextStream output_stream(&w_file);

    for (auto it = list_all_files.begin(); it!=list_all_files.end(); ++it)
    {
        if (!it->isEmpty())
            output_stream << *it<<"\n";
    }

    w_file.close();

    return a.exec();
}





