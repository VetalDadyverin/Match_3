#ifndef BACKEND_H
#define BACKEND_H
#include <QAbstractListModel>
#include <QObject>
#include <QVariant>
#include <QList>
#include <QVector>
#include <QString>
#include <QHash>

struct Cell{
    Cell(QString color) : m_color(color){}
    Cell(){}

    QString m_color;
    bool m_remove = false;
};

enum RoleNames {
    QolorRole = Qt::UserRole,
    RemoveRole = Qt::UserRole + 1,
};

class MyListModel : public QAbstractListModel{
    Q_OBJECT

public:
    explicit MyListModel(QObject *parent = 0);
    ~MyListModel();
    int rowCount(const QModelIndex &parent)const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE int get_columns();
    Q_INVOKABLE int get_rows();
    Q_INVOKABLE int get_previous_index();
    Q_INVOKABLE int get_score();
    Q_INVOKABLE void set_previous_index(const int index);
    Q_INVOKABLE bool try_to_swap(const int first_index, const int second_index);
    Q_INVOKABLE bool stop_game();
    Q_INVOKABLE void start_shuffle();
    Q_INVOKABLE bool start_falling();
    Q_INVOKABLE void falling_down();

private:
    QList<Cell> m_cells;
    QVector<QString> m_colors;
    QVector<int> m_index_to_remove;
    QHash<int, QByteArray> m_roleNames;
    int m_previous_index = -1;
    int m_score = 0;
    int m_columns;
    int m_rows;

    void increment_score(int number);
    bool check_three(int index_1, int index_2, int index_3);
    bool check_for_removing();
    void change_remove_parameter();
    bool read_Json_file(std::string json_path);
    void swap_cells(const int first_index, const int second_index);
    bool check_mutual_position(const int first_index, const int second_index);
    bool check_for_match_removing(const int index);
};


#endif // BACKEND_H

