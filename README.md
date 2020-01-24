# DB
A simple Data Base

my database's main function is exec(str) 
and exec() take a string as command 


My Data Base work with these command

1- {for create a new Table :
CT name_of_table property1 type_of_property property2 type_of_property2 ...
type of properties : INT for integer 
                     TEXT for string
                     FLOAT for float
                     
example:
        CT student id INT name TEXT grade FLOAT
        
}

2- for insert a new record:
INSERT name_of_table property1 value_of_property property2 value_of_property2 ...

example:
        INSERT student id 97 name ali grade 2.6


3- for print a table :
PRINT name_of_table

example :
         PRINT student
         
4- for update a record of table:

UPDATE name_of_table property1 value_of_property1 property2 value_of_property2
first find a record according to property1 & its value
then update table's property2 to new value

example 
       UPDATE student name ali id 95
       
       
5-for delete a record:
DELETER name_of_table property value_of_property

example:
        DELETER student name ali 
        
        
6- for delete a table :
DELETEC name_of_table

example:
         DELETEC student 


        
