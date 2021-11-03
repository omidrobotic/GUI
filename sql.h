#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "qmessagebox.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <filesystem>


#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMainWindow>




extern char logs[50];
extern char fileLocation[];
extern char configLocation[];
extern char robotLocation[];
extern char refreeLocation[];
extern char add[];
extern char config[];
extern char robot[];
extern char refree[];


class sqlInit;

class setData;

class setData {
public:
    std::string name;
    std::string value;
};
extern sqlInit configDataBase;
extern sqlInit refreeDataBase;
extern sqlInit robotsDataBase;
extern setData seter;

int dataBase(char *command,sqlInit *sqlData);
int removeDataInDataBase(int ID,char* table,sqlInit *sqlData);
int removeDataInDataBase(char* name,char* table,sqlInit *sqlData);

int insertDataInDataBase(char* table,int ID,char* name,char* value,char* valueString,char* type,sqlInit *sqlData);
int updateDataBase(char* table,char *column,int ID,char *value,sqlInit *sqlData);
int findDataBase(char *table,char *name,sqlInit *sqlData);
int findDataBaseId(char *table,char *type,int ID,sqlInit *sqlData);
int openDataBase(sqlInit *sqlData);
void closeDataBase(sqlInit *sqlData);
void configConfigDatabase(sqlInit *sqlData);
void configRobotsDatabase(sqlInit *sqlData);
void configRefreeDatabase(sqlInit *sqlData);



#endif // SQL_H
