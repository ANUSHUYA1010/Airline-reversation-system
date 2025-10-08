#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_SEATS 10 

 

typedef struct { 

    int seatNumber; 

    char passengerName[50]; 

    int isBooked; 

} Seat; 

 

Seat seats[MAX_SEATS];  
void initializeSeats() { 

    for (int i = 0; i < MAX_SEATS; i++) { 

        seats[i].seatNumber = i + 1; 

        seats[i].isBooked = 0; 

        strcpy(seats[i].passengerName, ""); 

    } 

} 

 

void printHTMLHeader() { 

    printf("Content-type: text/html\n\n"); 

    printf("<html><head><title>Airline Reservation</title></head><body>"); 

} 

 

void printHTMLFooter() { 

    printf("</body></html>"); 

} 

 

void displaySeats() { 

    printf("<h2>Available Seats</h2>"); 

    for (int i = 0; i < MAX_SEATS; i++) { 

        if (!seats[i].isBooked) 

            printf("<p>Seat %d is available</p>", seats[i].seatNumber); 

    } 

} 

 

void bookTicket(int seatNum, char name[]) { 

    if (seatNum < 1 || seatNum > MAX_SEATS || seats[seatNum - 1].isBooked) { 

        printf("<p>Invalid seat number or already booked!</p>"); 

        return; 

    } 

 

    seats[seatNum - 1].isBooked = 1; 

    strcpy(seats[seatNum - 1].passengerName, name); 

    printf("<p>Ticket booked for %s (Seat %d)</p>", name, seatNum); 

} 

 

void cancelTicket(int seatNum) { 

    if (seatNum < 1 || seatNum > MAX_SEATS || !seats[seatNum - 1].isBooked) { 

        printf("<p>Invalid seat number or not booked!</p>"); 

        return; 

    } 

 

    seats[seatNum - 1].isBooked = 0; 

    strcpy(seats[seatNum - 1].passengerName, ""); 

    printf("<p>Ticket for seat %d has been canceled.</p>", seatNum); 

} 

 

int main() { 

    char *queryString = getenv("QUERY_STRING"); 

    int seatNum; 

    char name[50]; 

 

    initializeSeats(); 

    printHTMLHeader(); 

 

    if (queryString) { 

        if (sscanf(queryString, "book=%d&name=%49s", &seatNum, name) == 2) { 

            bookTicket(seatNum, name); 

        } else if (sscanf(queryString, "cancel=%d", &seatNum) == 1) { 

            cancelTicket(seatNum); 

        } 

    } 

 

    displaySeats(); 

 

    printf("<h2>Book a Ticket</h2>"); 

    printf("<form action='/cgi-bin/airline.exe' method='GET'>"); 

    printf("Seat Number: <input type='number' name='book' required><br>"); 

    printf("Name: <input type='text' name='name' required><br>"); 

    printf("<input type='submit' value='Book Ticket'></form>"); 

 

    printf("<h2>Cancel a Ticket</h2>"); 

    printf("<form action='/cgi-bin/airline.exe' method='GET'>"); 

    printf("Seat Number: <input type='number' name='cancel' required><br>"); 

    printf("<input type='submit' value='Cancel Ticket'></form>"); 

 

    printHTMLFooter(); 

    return 0; 

} 