#include <stdio.h>
#include <stdbool.h>// header file to do functions
#include<string.h>


#define NUM_SEATS 32 // integer constant 

typedef struct seat {//  declaring structure and using typedef to make own name of datatype
    int seatNumber;
    bool isOccupied; 
    int ticketNumber;
    char passengerName[50]; 
} Seat;

void displaymenu();
void viewSeatAvailability(Seat seats[]);// function prototypying
void bookSeat(Seat seats[]);
void cancelSeat(Seat seats[]);
void saveData(Seat seats[]);

int main() {
    Seat seats[NUM_SEATS];// array of structure
    int choice;

    FILE *file = fopen("sa.txt", "rb");// Open file for reading in binary mode

    if (file == NULL) {// if file doent open or certain problem exists creating new file with all seats availanble
        for (int i = 0; i < NUM_SEATS; i++) {
            seats[i].seatNumber = i + 1;
            seats[i].isOccupied = false;
            seats[i].ticketNumber = 0;
            seats[i].passengerName[0] = '\0'; // Initializing values
        }
    } else {
        fread(seats, sizeof(Seat), NUM_SEATS, file);// Read data from file
        fclose(file);// closing file
    }

    do {
        displaymenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewSeatAvailability(seats);// passing array to function which is pass by reference
                break;
            case 2:
                bookSeat(seats);
                break;
            case 3:
                cancelSeat(seats);
                break;
            case 4:
                saveData(seats);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);// a loop for bus ticket information which only ends if user presses 4

    return 0;// end of main function
}

void displaymenu() {// function to display the menu for booking ticket
    printf("************************************************************************\n\t\t WELCOME TO RAJ TRAVELS\n");
    printf("1. View Seat Availability\n");
    printf("2. Book a Seat\n");
    printf("3. Cancel Seat Reservation\n");
    printf("4. Exit\n");
}

void viewSeatAvailability(Seat seats[]) {// function that checks wether the seat is available or not with ticket number of booked seats
    printf("\nSeat Availability:\n");
    for (int i = 0; i < NUM_SEATS; i++) {
        if (seats[i].isOccupied==true) {// boolen value compared to check wether seat is available or not
            printf("Seat %d: Occupied (Ticket #: %d, Passenger: %s)\n", seats[i].seatNumber, seats[i].ticketNumber, seats[i].passengerName);
        } else {
            printf("Seat %d: Available\n", seats[i].seatNumber);
        }
    }
}

void bookSeat(Seat seats[]) {// function to book seat
    int seatNum;
    char name[50];

    printf("\nEnter the seat number to book (1-%d): ", NUM_SEATS);
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > NUM_SEATS) {// seat available is only 32 so user cancel book any extra seat
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNum - 1].isOccupied==true) {
        printf("Sorry, the seat is already occupied.\n");
    } else {
        printf("Enter passenger name: ");
        scanf(" %[^\n]s", name); // Reading the name with spaces

        seats[seatNum - 1].isOccupied = true;
        seats[seatNum - 1].ticketNumber = seatNum;// Assuming ticket number is seat number for simplicity
        strcpy(seats[seatNum - 1].passengerName, name); // Copying name to passengerName
        printf("Seat %d booked successfully. Ticket #: %d\n", seatNum, seatNum);
    }
    saveData(seats);// saves changes of book seat by passing array to saveData function
}

void cancelSeat(Seat seats[]) {//function to cancel seat
    int seatNum;

    printf("\nEnter the seat number to cancel reservation: ");
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > NUM_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNum - 1].isOccupied==true) {// here if seat is already booked i.e boolen is true then the if statement works and makes boolen false i.e cancel seat
        seats[seatNum - 1].isOccupied = false;
        seats[seatNum - 1].ticketNumber = 0;
        seats[seatNum - 1].passengerName[0] = '\0'; // Clearing passengerName
        printf("Reservation for seat %d cancelled.\n", seatNum);
    } else {
        printf("Seat %d is not occupied.\n", seatNum);
    }
    saveData(seats);// saving cancel seats
}

void saveData(Seat seats[]) {// function to save the initial or changed data 
    FILE *file = fopen("sa.txt", "wb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(seats, sizeof(Seat), NUM_SEATS, file); // binary function to write on file
    fclose(file); // closing of file
}
