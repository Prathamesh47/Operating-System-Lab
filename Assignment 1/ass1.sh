#!/bin/bash

Create() {
    echo "Enter address book name"
    read ab
    if [ -e "$ab" ]; then
        echo "Error, File already exist!"
    else 
        touch "$ab"
        echo "File created successfully"
    fi
}

Display() {
    echo "Enter address book name you want to display"
    read ab
    if [ -e "$ab" ]; then
        cat "$ab"
    else 
        echo "File does not exist"
    fi
}

Insert(){
    echo "Enter the name of address book in which you want to insert"
    read ab
    if [ -e "$ab" ]; then
        echo "Enter ID"
        read id

        while true; do
            echo "Enter Name"
            read name
            if [[ "$name"=~ ^[0-9]]];then
                echo "Invalid name"
            else
                break
            fi
        done

        while true; do
            echo "Enter Phone number"
            read phone
            if [[ "$phone"=~ ^[0-9]{10}$ ]];then
                break
            else 
                echo "Invalid number"
            fi
        done

        echo "Enter city"
        read city

        record = "$id $name $phone $city"
        echo "$record" >> $ab
        echo "Record Inserted Successfully"
    else
        echo "File does not exist"
    fi

}

Modify()
{
    echo "Enter the address book name in which data has to modify"
    read ab
    if [ -e "$ab" ]; then
        echo "Enter the id of the entry in which data has to modify"
        read modifyId
        echo "Enter the new data (ID Name Phone City):"
        read newdata
        sed -i "/^$modifyId/c$newdata" $ab
        echo "Entry modified successfully"
    else
        echo "File does not exist"
    fi
}
Delete()
{
    echo "Enter the address book name in which data has to modify"
    read ab
    if [ -e "$ab" ]; then
        echo "Enter the id of the entry in which data has to delete"
        read deleteId
        sed -i "/^$deleteId/d" $ab
        echo "Entry modified successfully"
    else
        echo "File does not exist"
    fi
}

while true; do

    echo "1) Create"
    echo "2) Display"
    echo "3) Insert"
    echo "4) Modify"
    echo "5) Delete"
    echo "6) Exit"
    echo "Choice:"

    read choice
    case $choice in
        1) Create ;;
        2) Display ;;
        3) Insert ;;
        4) Modify ;;
        5) Delete ;;
        6) exit ;;
        *) echo "Invalid Choice"

    esac
done
