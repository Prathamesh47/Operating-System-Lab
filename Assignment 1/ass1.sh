#!/bin/bash
echo "This is a program for employee database"
menu_choice=1
while [ $menu_choice -gt 0 ]
do
    echo "Enter"
    echo "1 for CREATE"
    echo "2 for INSERT"
    echo "3 for SEARCH"
    echo "4 for DISPLAY"
    echo "5 for DELETE"
    echo "6 for UPDATE"
    echo "7 for EXIT"
    read user_choice
    
    case $user_choice in
        1)
            echo "CREATE"
            # Check if the database file already exists
            if [ -f "File.txt" ]; then
                echo "Database already exists."
            else
                touch "File.txt"
                echo "Database created successfully."
            fi
        ;;
        2)
            echo "INSERT"
            
            echo "Enter Employee ID"
            read emp_id
            echo "Enter Employee Name"
            read emp_name
            echo "Enter Employee Department"
            read dept
            record="$emp_id $emp_name $dept"
            echo $record >> File.txt
            # Record will be appended to File.txt
            echo "Record inserted successfully."
        ;;
        3)
            echo "SEARCH"
            echo "Enter Name to be searched"
            read name_to_search
            # Search for the given name in the database file and get the line number
            lineNum="$(grep -n "$name_to_search" File.txt | head -n 1 | cut -d: -f1)"
            if [ -z "$lineNum" ]; then
                echo "Record not found."
            else
                echo "Record found at line: $lineNum"
                echo "$(sed -n "${lineNum}p" File.txt)"
            fi
        ;;
        4)
            echo "DISPLAY"
            # Display the content of the database file
            output="File.txt"
            if [ ! -s "$output" ]; then
                echo "Database is empty."
                
            else
                cat "$output"
            fi
        ;;
        5)
            echo "DELETE"
            echo "Enter ID to be deleted"
            read id_to_delete
            # First line with the record ID will be found
            if grep -q "^$id_to_delete " File.txt; then
                grep -v "^$id_to_delete " File.txt > temp_db && mv temp_db File.txt
                echo "Record with Employee ID $id_to_delete has been deleted."
                # Using a temp file, we will delete the data from the file by only copying those contents which are not the ID using grep -v
            else
                echo "Record not found."
            fi
        ;;
        6)
            echo "UPDATE"
            echo "Enter ID to be updated"
            # Check if the record with the given ID exists in the database file
            read id_to_update
            if grep -q "^$id_to_update " File.txt; then
                echo "Enter Employee Name"
                read updated_emp_name
                echo "Enter Employee Department"
                read updated_dept
                updated_record="$id_to_update $updated_emp_name $updated_dept"
                sed -i "s/^$id_to_update.*/$updated_record/" File.txt
                echo "Record updated successfully."
                
            else
                echo "Record Not Found"
            fi
        ;;
        7)
            echo "EXIT"
            menu_choice=-1
        ;;
        *)
            echo "WRONG"
        ;;
    esac
done
