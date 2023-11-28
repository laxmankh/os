
# Define the address book file
address_book_file="address_book.txt"

# Function to create a new address book
create_address_book() {
    touch $address_book_file
    echo "Address book created."
}

# Function to view the address book
view_address_book() {
    if [ -e "$address_book_file" ]; then
        cat $address_book_file
    else
        echo "Address book is empty."
    fi
}

# Function to insert a new record
insert_record() {
    echo "Enter the name: "
    read name
    echo "Enter the address: "
    read address
    echo "Enter the phone number: "
    read phone
    echo "$name, $address, $phone" >> $address_book_file
    echo "Record inserted successfully."
}

# Function to delete a record
delete_record() {
    echo "Enter the name to delete: "
    read name
    if grep -i "$name" $address_book_file; then
        sed -i "/$name/d" $address_book_file
        echo "Record deleted successfully."
    else
        echo "Record not found."
    fi
}

# Function to modify a record
modify_record() {
    echo "Enter the name to modify: "
    read name
    if grep -i "$name" $address_book_file; then
        echo "Enter the new address: "
        read new_address
        echo "Enter the new phone number: "
        read new_phone
        sed -i "s/$name,.*,.*/$name, $new_address, $new_phone/" $address_book_file
        echo "Record modified successfully."
    else
        echo "Record not found."
    fi
}

# Main program loop
while true; do
    echo "Address Book Menu"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "Enter your choice (1/2/3/4/5/6): "
    read choice

    case $choice in
        1)
            create_address_book
            ;;
        2)
            view_address_book
            ;;
        3)
            insert_record
            ;;
        4)
            delete_record
            ;;
        5)
            modify_record
            ;;
        6)
            echo "Exiting the Address Book program."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter a valid option."
            ;;
    esac
done
