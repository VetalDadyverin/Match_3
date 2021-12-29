#include "mylistmodel.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

MyListModel::MyListModel(QObject *parent) : QAbstractListModel(parent){
    read_Json_file(":config.json");
    m_roleNames[QolorRole] = "color";
    m_roleNames[RemoveRole] = "remove";
    start_shuffle();
}
MyListModel::~MyListModel(){

}


int MyListModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return m_cells.count();
}

QHash<int, QByteArray> MyListModel::roleNames() const{
    return m_roleNames;
}

QVariant MyListModel::data(const QModelIndex &index, int role) const{
    int row = index.row();
    if(row < 0 || row >= m_cells.count()){
        return QVariant();
    }
    switch (role) {
    case QolorRole:
        return m_cells.value(row).m_color;
    case RemoveRole:
        return m_cells.value(row).m_remove;
    }
    return QVariant();
}

int MyListModel::get_columns(){
    return this->m_columns;
}

int MyListModel::get_rows(){
    return this->m_rows;
}

int MyListModel::get_previous_index(){
    return this->m_previous_index;
}

void MyListModel::set_previous_index(const int index){
    m_previous_index = index;
    emit dataChanged(createIndex(0,0), createIndex(m_cells.size() - 1,0));
}

void MyListModel::start_shuffle(){
    srand(time(NULL));
    int color_size = m_colors.size(), number_buffer;
    QString color_buffer, color_buffer_1, color_buffer_2;
    do{
        m_cells.clear();
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                if(j > 1){
                    if(m_cells.at(i * m_columns + j - 1).m_color == m_cells.at(i * m_columns + j - 2).m_color){
                        color_buffer_1 = m_cells.at(i * m_columns + j - 1).m_color;
                    }
                }
                if(i > 1){
                    if(m_cells.at((i - 1) * m_columns + j).m_color == m_cells.at((i - 2) * m_columns + j).m_color){
                        color_buffer_2 = m_cells.at((i - 1) * m_columns + j).m_color;
                    }
                }
                number_buffer = rand() % color_size;
                color_buffer = m_colors[number_buffer];
                while((!color_buffer_1.isEmpty() && color_buffer == color_buffer_1) || (!color_buffer_2.isEmpty() && color_buffer == color_buffer_2)){
                    if(number_buffer != color_size - 1){
                        number_buffer++;
                    }
                    else{
                        number_buffer = 0;
                    }
                    color_buffer = m_colors[number_buffer];
                }
                m_cells.push_back(Cell(color_buffer));
            }
        }
        emit dataChanged(createIndex(0,0), createIndex(m_cells.size() - 1,0));
    } while(stop_game());
    m_score = 0;
}

bool MyListModel::check_three(int index_1, int index_2, int index_3){
    return m_cells.at(index_1).m_color == m_cells.at(index_2).m_color &&
            m_cells.at(index_2).m_color == m_cells.at(index_3).m_color;
}

bool MyListModel::stop_game(){
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            if(m_columns - j > 2){
                if(m_rows - i > 1 && check_three(i * m_columns + j, i * m_columns + j + 2, (i + 1) * m_columns + j + 1)){
                    //101
                    //010
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "101";
                    qDebug() << "010";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if(i > 0 && check_three(i * m_columns + j, i * m_columns + j + 2, (i - 1) * m_columns + j + 1)){
                    //010
                    //101
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "010";
                    qDebug() << "101";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if(i > 0 && check_three(i * m_columns + j, i * m_columns + j + 1, (i - 1) * m_columns + j + 2)){
                    //001
                    //110
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "001";
                    qDebug() << "110";
                    qDebug() << "((((((((((((((((";
                    return false;
                }

                if (m_rows - i > 1 && check_three(i * m_columns + j, i * m_columns + j + 1, (i + 1) * m_columns + j + 2)) {
                    //110
                    //001
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "110";
                    qDebug() << "001";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (m_columns - j > 3 && check_three(i * m_columns + j, i * m_columns + j + 1, i * m_columns + j + 3)) {
                    // 1101
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "1101";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
            }
            if(m_rows - i > 2){
                if(m_columns - j > 1 && check_three(i * m_columns + j, (i + 1) * m_columns + j + 1, (i + 2) * m_columns + j)){
                    //10
                    //01
                    //10
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "10";
                    qDebug() << "01";
                    qDebug() << "10";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if(j > 0 && check_three(i * m_columns + j, (i + 2) * m_columns + j, (i + 1) * m_columns + j - 1)){
                    //01
                    //10
                    //01
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "01";
                    qDebug() << "10";
                    qDebug() << "01";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (j > 0 && check_three(i * m_columns + j, (i + 1) * m_columns + j, (i + 2) * m_columns + j - 1)) {
                    //01
                    //01
                    //10
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "01";
                    qDebug() << "01";
                    qDebug() << "10";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (m_columns - j > 1 &&  check_three(i * m_columns + j, (i + 1) * m_columns + j, (i + 2) * m_columns + j + 1)) {
                    //10
                    //10
                    //01
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "10";
                    qDebug() << "10";
                    qDebug() << "01";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (m_rows - i > 3 && check_three(i * m_columns + j, (i + 1) * m_columns + j, (i + 3) * m_columns + j)) {
                    //1
                    //1
                    //0
                    //1
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "1";
                    qDebug() << "1";
                    qDebug() << "0";
                    qDebug() << "1";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
            }
            if (j > 1) {
                if (m_rows - i > 1 && check_three(i * m_columns + j, i * m_columns + j - 1, (i + 1) * m_columns + j - 2)) {
                    //011
                    //100
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "011";
                    qDebug() << "100";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (i > 0 && check_three(i * m_columns + j, i * m_columns + j - 1, (i - 1) * m_columns + j - 2)) {
                    //100
                    //011
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "100";
                    qDebug() << "011";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (j > 2 && check_three(i * m_columns + j, i * m_columns + j - 1, i * m_columns + j - 3)) {
                    // 1011
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "1011";
                    qDebug() << "((((((((((((((((";
                    return false;
                }

            }
            if (i > 1) {
                if (j > 0 && check_three(i * m_columns + j, (i - 1) * m_columns + j, (i - 2) * m_columns + j - 1)) {
                    //10
                    //01
                    //01
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "10";
                    qDebug() << "01";
                    qDebug() << "01";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (m_columns - j > 1 && check_three(i * m_columns + j, (i - 1) * m_columns + j , (i - 2) * m_columns + j + 1)) {
                    //01
                    //10
                    //10
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "01";
                    qDebug() << "10";
                    qDebug() << "10";
                    qDebug() << "((((((((((((((((";
                    return false;
                }
                if (i > 2 && check_three(i * m_columns + j, (i - 1) * m_columns + j, (i - 3) * m_columns + j)) {
                    //1
                    //0
                    //1
                    //1
                    qDebug() << "((((((((((((((((";
                    qDebug() << "index = " << i * m_columns + j;
                    qDebug() << "1";
                    qDebug() << "0";
                    qDebug() << "1";
                    qDebug() << "1";
                    qDebug() << "((((((((((((((((";
                    return false;
                }

            }
        }
    }
    return true;
}


void MyListModel::increment_score(int number){
    m_score += number;
}

int MyListModel::get_score(){
    return this->m_score;
}

void MyListModel::falling_down(){
    change_remove_parameter();
    int row, index, color_size = m_colors.size();
    //QTimer::singleShot(1200, this, [=] () {increment_score(m_index_to_remove.size());});
    increment_score(m_index_to_remove.size());
    while(!m_index_to_remove.isEmpty()){
        index = m_index_to_remove[0];
        row = index / m_columns;
        for(int i = 0 ; i < row; i++){
            swap_cells(index - i * m_columns, index - (i + 1) * m_columns);
        }
        beginRemoveRows(QModelIndex(),index - row * m_columns, index - row * m_columns);
        m_cells.remove((index - row * m_columns));
        endRemoveRows();
        beginInsertRows(QModelIndex(),index - row * m_columns, index - row * m_columns);
        m_cells.insert(index - row * m_columns, Cell(m_colors[rand() % color_size]));
        endInsertRows();
        m_index_to_remove.pop_front();
    }
}

bool MyListModel::check_for_removing(){
    QString color_buffer;
    int number_buffer, index_1, index_2, index_3;
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns - 2; ++j){
            index_1 = j + m_columns * i;
            index_2 = j + 2 + m_columns * i;
            index_3 = j + 1 + m_columns * i;
            color_buffer = m_cells.at(index_1).m_color;
            if(m_cells.at(index_2).m_color == color_buffer &&
                    color_buffer == m_cells.at(index_3).m_color){
                for(int k = 0; k < 3; ++k){
                    number_buffer = j + k + m_columns * i;
                    if(std::find(m_index_to_remove.begin(), m_index_to_remove.end(), number_buffer) == m_index_to_remove.end()){
                        m_index_to_remove.push_back(number_buffer);
                    }
                }
            }
        }
    }
    for(int i = 0; i < m_columns; ++i){
        for(int j = 0; j < m_rows - 2; ++j){
            index_1 = m_columns * j + i;
            index_2 = m_columns * (j + 2) + i;
            index_3 = m_columns * (j + 1) + i;
            color_buffer = m_cells.at(index_1).m_color;
            if(m_cells.at(index_2).m_color == color_buffer &&
                    color_buffer == m_cells.at(index_3).m_color){
                for(int k = 0; k < 3; ++k){
                    number_buffer = m_columns * (j + k) + i;
                    if(std::find(m_index_to_remove.begin(), m_index_to_remove.end(), number_buffer) == m_index_to_remove.end()){
                        m_index_to_remove.push_back(number_buffer);
                    }
                }
            }
        }
    }
    return !m_index_to_remove.empty();
}

void MyListModel::change_remove_parameter(){
    //std::sort(m_index_to_remove.begin(), m_index_to_remove.end(), std::greater<int>());
    std::sort(m_index_to_remove.begin(), m_index_to_remove.end());
    for(auto &index : m_index_to_remove){
        m_cells[index].m_remove = true;
    }
    //    for(const auto &point : m_index_to_remove){
    //        qDebug() << point << " ";
    //    }
    //    qDebug() << "||||||||||||";
    emit dataChanged(createIndex(0,0), createIndex(m_cells.size() - 1,0));
}

bool MyListModel::try_to_swap(const int first_index, const int second_index){
    if(check_mutual_position(first_index, second_index)){
        swap_cells(first_index, second_index);
        bool one = check_for_match_removing(first_index);
        bool two = check_for_match_removing(second_index);
        if(one && two){
            QTimer::singleShot(600, this, [=] () {swap_cells(first_index, second_index);});
            qDebug() << "Swap back";
            return false;
        }
        return true;
    }
    return false;
}

bool MyListModel::start_falling(){
    if(check_for_removing()){
        falling_down();
        return false;
    }
    return true;
}

bool MyListModel::check_mutual_position(const int first_index, const int second_index){
    int difference = abs(first_index - second_index);
    return (difference == 1 && (first_index / m_columns) == (second_index / m_columns)) || (difference == m_columns);
}

void MyListModel::swap_cells(const int first_index, const int second_index){
    int min = std::min(first_index, second_index);
    int max = std::max(first_index, second_index);
    if(beginMoveRows(QModelIndex(), min, min, QModelIndex(), max + 1)){
        m_cells.move(min, max);
        endMoveRows();
    }
    if(beginMoveRows(QModelIndex(), max - 1, max - 1, QModelIndex(), min)){
        m_cells.move(max - 1, min);
        endMoveRows();
    }
}

bool MyListModel::check_for_match_removing(const int index){
    int row, column, left_right_count = 0, top_bottom_count = 0;
    QString color = m_cells.at(index).m_color;
    QVector<int> buffer;
    row = index / m_columns;
    column = index - m_columns * row;
    for(int i = 1; i < column + 1; ++i){
        qDebug() << "Left count";
        if(m_cells.at(index - i).m_color == color){
            left_right_count++;
            buffer.push_back(index - i);
        }
        else{
            break;
        }
    }
    for(int i = 1; i < m_columns - column; ++i){
        qDebug() << "Right count";
        if(m_cells.at(index + i).m_color == color){
            left_right_count++;
            buffer.push_back(index + i);
        }
        else{
            break;
        }
    }
    if(left_right_count >= 2){
        for(const auto &point : buffer){
            m_index_to_remove.push_back(point);
        }
    }
    buffer.clear();
    for(int i = 1; i < row + 1; ++i){
        qDebug() << "Top count";
        if(m_cells.at(index - i * m_columns).m_color == color){
            top_bottom_count++;
            buffer.push_back(index - i * m_columns);
        }
        else{
            break;
        }
    }
    for(int i = 1; i < m_rows - row; ++i){
        qDebug() << "Bottom count";
        if(m_cells.at(index + i * m_columns).m_color == color){
            top_bottom_count++;
            buffer.push_back(index + i * m_columns);
        }
        else{
            break;
        }
    }
    if(top_bottom_count >= 2){
        for(const auto &point : buffer){
            m_index_to_remove.push_back(point);
        }
    }
    qDebug() << "My_index" << index;
    qDebug() << "Row = " << row << ", Column = " << column;
    qDebug() << "Left and Right count = " << left_right_count;
    qDebug() << "Top and Bottom count = " << top_bottom_count;
    qDebug() << "________________________";

    if((left_right_count < 2) && (top_bottom_count < 2)){
        return true;
    }
    else{
        m_index_to_remove.push_back(index);
        return false;
    }
}


QDebug& operator<< (QDebug& qd, std::string line){
    qd << QString::fromStdString(line);
    return qd;
}


bool MyListModel::read_Json_file(std::string json_path){
    QFile file_obj(QString::fromStdString(json_path));
    if(!file_obj.open(QIODevice::ReadOnly| QIODevice::Text)){
        qDebug() << "Cannot open " << json_path;
        return false;
    }
    QString json_string = file_obj.readAll();
    file_obj.close();
    QJsonDocument json_document = QJsonDocument::fromJson(json_string.toUtf8());
    if(json_document.isNull()){
        qDebug() << "Cannot create json_document";
        return false;
    }
    QJsonObject json_object = json_document.object();
    if(json_object.isEmpty()){
        qDebug() << "Json_object is empty";
        return false;
    }
    QJsonArray json_array = json_object["colors"].toArray();
    for(int i = 0; i < json_array.count(); ++i){
        m_colors.push_back(json_array[i].toString());
    }
    int buffer = json_object["columns"].toInt();
    m_columns = buffer > 25 ? 25 : (buffer < 4) ? 4 : buffer;
    buffer = json_object["rows"].toInt();
    m_rows = buffer > 14 ? 14 : (buffer < 4) ? 4 : buffer;
    while(m_colors.size() < 3){
        if(!m_colors.contains("red")){
            m_colors.push_back("red");
        }
        else if(!m_colors.contains("blue")){
            m_colors.push_back("blue");
        }else {
            m_colors.push_back("green");
        }
    }


    return true;
}

//"black",
//"green",
//"blue",
//"white",
//"red",
//"orange",
//"violet"
