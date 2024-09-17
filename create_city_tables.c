#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   const char *sql;

   /* Open database */
   rc = sqlite3_open("city.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE city(" \
         "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
         "Name char(35) NOT NULL DEFAULT ''," \
  	 "CountryCode char(3) NOT NULL DEFAULT ''," \
  	 "District char(20) NOT NULL DEFAULT ''," \
  	 "Population int NOT NULL DEFAULT '0'," \
  	 "FOREIGN KEY (CountryCode) REFERENCES country(Code));" ;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table city created successfully\n");
   }
   
   
   sql = "CREATE TABLE country(" \
  	"Code char(3) PRIMARY KEY NOT NULL DEFAULT ''," \
  	"Name char(52) NOT NULL DEFAULT ''," \
	"Continent TEXT CHECK( Continent IN ('Asia','Europe','North America','Africa','Oceania','Antarctica','South America')) NOT NULL DEFAULT 'Asia'," \
	"Region char(26) NOT NULL DEFAULT ''," \
  	"SurfaceArea decimal(10,2) NOT NULL DEFAULT '0.00'," \
  	"IndepYear smallint DEFAULT NULL,"  \
	"Population int NOT NULL DEFAULT '0'," \
  	"LifeExpectancy decimal(3,1) DEFAULT NULL," \
        "GNP decimal(10,2) DEFAULT NULL," \
  	"GNPOld decimal(10,2) DEFAULT NULL," \
  	"LocalName char(45) NOT NULL DEFAULT ''," \
  	"GovernmentForm char(45) NOT NULL DEFAULT ''," \
  	"HeadOfState char(60) DEFAULT NULL," \
  	"Capital int DEFAULT NULL," \
  	"Code2 char(2) NOT NULL DEFAULT '');" ;


   

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table country created successfully\n");
   }
   
   sql = "CREATE TABLE countrylanguage(" \
  	"CountryCode char(3) NOT NULL DEFAULT ''," \
  	"Language char(30) NOT NULL DEFAULT ''," \
  	"IsOfficial TEXT CHECK( IsOfficial IN ('T','F')) NOT NULL DEFAULT 'F'," \
  	"Percentage decimal(4,1) NOT NULL DEFAULT '0.0'," \
  	"FOREIGN KEY (`CountryCode`) REFERENCES `country` (`Code`));" ; 

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table countrylanguage created successfully\n");
   }
   

   sqlite3_close(db);
   return 0;
}
