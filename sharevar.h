#ifndef SHAREVAR_H
#define SHAREVAR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSerialPort>
extern int function_sql;
extern int current_row;
extern int current_table;
extern QSqlDatabase db;
extern QString gmaster_wendu;
extern QString gmaster_shidu;
extern QString gjiedian_wendu;
extern QString gjiedian_shidu;
extern QString gjiedian_soil;
extern QString gjiedian_light;
extern QSerialPort *serialaPort;
class shareVar
{
public:
    shareVar();

};

#endif // SHAREVAR_H
