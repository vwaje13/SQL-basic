#This Makefile file builds my assignment 8 project
# @Name: Veer Waje
# @Class: CS3377.007
# @Date: 03/05/2024

create_city_tables : create_city_tables.c
	g++ create_city_tables.c -o create_city_tables -l sqlite3

populate_city_tables : populate_city_tables.c 
	g++ populate_city_tables.c -o populate_city_tables -l sqlite3

country_capital_list : country_capital_list.c
	g++ country_capital_list.c -o country_capital_list -l sqlite3

english_country_list : english_country_list.c
	g++ english_country_list.c -o english_country_list -l sqlite3

clean : 
	rm -f city.db create_city_tables populate_city_tables country_capital_list english_country_list *.zip
package : 
	zip assignment8_veer_waje.zip *.c Makefile
