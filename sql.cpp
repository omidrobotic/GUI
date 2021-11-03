#include "sql.h"
//#ifdef _WIN32
//#include <Windows.h>
//#else
#include <unistd.h>
//#endif
const char* data = "Callback function called";

class sqlInit{
public:
    sqlite3 *db;
    char *zErrMsg = 0;
    char *sql = 0;
    const char *location=0;

};


sqlInit configDataBase;
sqlInit refreeDataBase;
sqlInit robotsDataBase;
setData seter;
char logs[50];

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    //fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    seter.name=azColName[0];
//    seter.value=atof(argv[0]);
    seter.value=(argv[0]);
    //printf("\n");
    return 0;
}
int dataBase(char *command,sqlInit *sqlData)
{

    /* Execute SQL statement */
    int rc = sqlite3_exec(sqlData->db, command, callback, (void*)data, &sqlData->zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", sqlData->zErrMsg);
        sqlite3_free(sqlData->zErrMsg);
        return false;
    } else {
        fprintf(stdout, "Operation done successfully\n");
        return true;
    }
    return false;
}
int removeDataInDataBase(int ID,char* table,sqlInit *sqlData)
{
//    char *command;
//    sprintf(command,"DELETE from %s where ID=%d;",table,ID);
//    return dataBase(command,sqlData);
    QString str=QString("DELETE from %1 where ID=%2; ").arg(table).arg(ID);
    return  dataBase((char *) str.toStdString().c_str(),sqlData);
}
int removeDataInDataBase(char* name,char* table,sqlInit *sqlData)
{
//    char *command;
//    sprintf(command,"DELETE from %s where ID=%d;",table,ID);
//    return dataBase(command,sqlData);
    QString str=QString("DELETE from %1 where NAME='%2'; ").arg(table).arg(name);
    return  dataBase((char *) str.toStdString().c_str(),sqlData);
}
int insertDataInDataBase(char* table,int ID,char* name,char* value,char* valueString,char* type,sqlInit *sqlData)
{
//    char *command;
    QString str=QString("INSERT INTO %1 VALUES(%2, '%3', '%4', '%5', %6);").arg(table).arg(ID).arg(name).arg(type).arg(valueString).arg(value);
//    sprintf(command2,"INSERT INTO %s VALUES(%d, '%s', '%s', '%s', %d);",table,ID,name,type,valueString,valueNumber);
    return dataBase((char *) str.toStdString().c_str(),sqlData);
}
int updateDataBase(char* table,char *column,int ID,char *value,sqlInit *sqlData)
{
//    char *command;
//    sprintf(command,"UPDATE %s set EQUL = %f where NAME='%s'; ",table,value,name);
//    return dataBase(command,sqlData);
    QString str=QString("UPDATE %1 set %2 = '%3' where ID=%4; ").arg(table).arg(column).arg(value).arg(ID);
    return  dataBase((char *) str.toStdString().c_str(),sqlData);
}
int findDataBase(char *table,char *name,sqlInit *sqlData)
{
    char *command;
    sprintf(command,"SELECT EQUL FROM %s WHERE NAME='%s';",table,name);
    return dataBase(command,sqlData);
}
int findDataBaseId(char *table,char *type,int ID,sqlInit *sqlData)
{
//    char *command;
    QString str=QString("SELECT %1 FROM %2 WHERE ID='%3';").arg(type).arg(table).arg(ID);
//    sprintf(command,"SELECT EQUL FROM %s WHERE ID='%d';",table,ID);
    return dataBase((char *)str.toStdString().c_str(),sqlData);
}
int openDataBase(sqlInit *sqlData)
{
    int rc;

    rc = sqlite3_open(sqlData->location, &sqlData->db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sqlData->db));
        strcat(logs,"Can't open database:");
        strcat(logs,sqlite3_errmsg(sqlData->db));
        strcat(logs,"\n");
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Can't open database.");
        msgBox.exec();
    } else {
        fprintf(stderr, "Opened database successfully\n");
        strcat(logs,"Opened database successfully");
        strcat(logs,"\n");
    }
    /* Execute SQL statement */
    rc = sqlite3_exec(sqlData->db, sqlData->sql, callback, 0, &sqlData->zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", sqlData->zErrMsg);
        strcat(logs,"SQL error: ");
//        strcat(logs,char(sqlData->zErrMsg));
        strcat(logs,"\n");

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("SQL error.");
        msgBox.exec();
        sqlite3_free(sqlData->zErrMsg);
        return false;
    } else {
        fprintf(stdout, "Table created successfully\n");
        strcat(logs,"Table created successfully");
        strcat(logs,"\n");
        return true;
    }
    return false;
}
void closeDataBase(sqlInit *sqlData)
{
    sqlite3_close(sqlData->db);
}

void configConfigDatabase(sqlInit *sqlData)
{
    sqlData->sql=
            "CREATE TABLE IF NOT EXISTS config("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "EQULSTRING           TEXT    NOT NULL," \
      "EQULVALUE            TEXT     NOT NULL);";
    std::string str(configLocation);
    sqlData->location=strdup(str.c_str());
}
void configRobotsDatabase(sqlInit *sqlData)
{
    sqlData->sql=
            "CREATE TABLE IF NOT EXISTS robot("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "EQULSTRING     TEXT    NOT NULL," \
      "EQULVALUE     TEXT     NOT NULL);";
    std::string str(robotLocation);
    sqlData->location=strdup(str.c_str());
}
void configRefreeDatabase(sqlInit *sqlData)
{
    sqlData->sql=
            "CREATE TABLE IF NOT EXISTS refree("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "EQULSTRING           TEXT    NOT NULL," \
      "EQULVALUE           TEXT     NOT NULL);";
    std::string str(refreeLocation);
    sqlData->location=strdup(str.c_str());
}
