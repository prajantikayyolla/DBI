#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include "iostream"
using namespace std;

// stub file .. replace it with your own DBFile.cc

DBFile::DBFile () {
    
    current_record = new Record();
    page_index = 0;
    dirty_page = 0;
    eof = 0;
}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {
    file.Open(0,(char *) f_path);
    return 1;
}
void DBFile::Load (Schema &f_schema, const char *loadpath) {
    FILE* tf = fopen (loadpath,"r");
    while(current_record->SuckNextRecord(&f_schema,tf)!=0){
        Add(*current_record);
    }
    fclose(tf);
    

}

int DBFile::Open (const char *f_path) {
    file.Open(1,(char *) f_path);
    page_index=0;
    eof=0;
    return 1;
}

void DBFile::MoveFirst () {
    file.GetPage(&page,0);
}

int DBFile::Close () {
    if(dirty_page==1){
        file.AddPage(&page,page_index);
        page_index++;
        page.EmptyItOut();
        dirty_page=0;
    }
    eof=1;
    file.Close();
}

void DBFile::Add (Record &rec) {
    dirty_page=1;
    if(page.Append(&rec)==0){
        file.AddPage(&page,page_index);
        page_index++;
        page.EmptyItOut();
        page.Append(&rec);
    }
    
}

int DBFile::GetNext (Record &fetchme) {
    if(page.GetFirst(&fetchme)==0){
        page_index++;
        if(page_index>=file.GetLength()-1){
            eof=1;
            return 0;
        }
        else{
            file.GetPage(&page,page_index);
            page.GetFirst(&fetchme);
            return 1;
        }        
    }
    else{
        return 1;
    }
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
    ComparisonEngine c;
    if(GetNext(fetchme)==0){
        return 0;
    }
    while(c.Compare(&fetchme,&literal,&cnf)==0){
        if(GetNext(fetchme)==0){
        return 0;
    }
    }
    return 1;
}
