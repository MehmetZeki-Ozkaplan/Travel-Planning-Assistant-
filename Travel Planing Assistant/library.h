#ifndef LIBRARY_H 									// A precaution to prevent this file from being included more than once
#define LIBRARY_H 

#include <iostream> 								// Included the library required for check-in and check-out
#include <cstdio>   								// Included library required for standard input/output functions
#include <cstring>  								// Included library required for string operations
#include <climits>  								// Constants included for maximum and minimum values
#include <string>   								// Included the library required to use the String data type
using namespace std; 								// The standard namespace is used

// A structure is defined to hold space information
struct Mekan 
{
    int id;          								// The variable that will hold the unique ID of the venue is defined
    string isim;     								// The variable that will hold the name of the place is defined
    int geziSuresi;  								// Duration of the visit of the place
    int girisUcreti; 								// Entrance fee of the venue
};

// A class is created to define the graph structure and related operations
class Graf 
{
public:
    int komsulukMatrisi[16][16]; 					// A 16x16 adjacency matrix is defined to keep distances
    int n;                       					// The total number of nodes in the graph is defined
    string mekanIsimleri[16];    					// A sequence is defined that stores the names of places

    // Constructor-Construcot function: Initializes the graph object
    Graf(int n);

    // Creates the graph by reading it from file data
    void grafOlustur();

    // Calculates the shortest path using the Dijkstra algorithm
    // Parameters: - start: Starting point - destinations: IDs of the venues selected by the user - number of selections: Number of selected venues
    void enKisaYolHesapla(int baslangic, int gezilecekMekanlar[], int secimSayisi);
};

// A function that reads venue information from a file
// Parameters: - venues: Array holding venue information - venueNumber: Variable holding the total number of venues
void dosyaOku(Mekan mekanlar[], int &mekanSayisi);

// A function that sorts the spaces and prints the order on the screen
// Venues are ranked according to criteria such as entrance fee or duration of excursions
void mekanSirala();

// A function is defined to show the user the menu and allow him to navigate the program
void menu();

#endif 												// LIBRARY_H // End of Include Guard
