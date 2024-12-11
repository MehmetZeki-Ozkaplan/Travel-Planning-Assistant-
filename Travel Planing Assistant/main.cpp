#include "library.h"							//Included library library with defined functions

// The constructor-constructor function of the graph class has been created, value assignment operations have been performed  
// This function creates the size of the graph and the adjacency matrix
Graf::Graf(int n) 
{
    this->n = n;  							// Takes the number of nodes of the graph and assigns it to n variables of the class

    // The adjacency matrix is filled with -1. -1 will indicate that there is no connection between the two venues
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) 
	{
            komsulukMatrisi[i][j] = -1;
        }
}
    mekanIsimleri[0] = "BASLANGIC (ABIDE KAVSAGI)";
    mekanIsimleri[1] = "BALIKLIGOL";
    mekanIsimleri[2] = "GOBEKLITEPE";
    mekanIsimleri[3] = "ARKEOLOJI MUZESI";
    mekanIsimleri[4] = "MOZAIK MUZESI";
    mekanIsimleri[5] = "KARAHANTEPE";
    mekanIsimleri[6] = "EYUPNEBI";
    mekanIsimleri[7] = "HZ. IBRAHIM MAKAMI";
    mekanIsimleri[8] = "HALFETI TEKNE TURU";
    mekanIsimleri[9] = "KAPALI CARSI";
    mekanIsimleri[10] = "SIRA GECESI";
    mekanIsimleri[11] = "HASIMIYE CIGER YEMEGI";
    mekanIsimleri[12] = "BALON TURU";
    mekanIsimleri[13] = "ANTIK HARRAN UNIVERSITESI KALINTILARI";
    mekanIsimleri[14] = "HZ. YAKUP KUYUSU";
    mekanIsimleri[15] = "GERMUS KILISESI";
    
    // Names of places were assigned
}

// grafOlustur() function and body structure created
// The grafOlustur() function creates a graph by reading data from a mesafeler.txt file
void Graf::grafOlustur() 
{
    FILE* dosya = fopen("mesafeler.txt", "r"); 				// By performing file operations, reading is done on the desired file
    if (dosya == nullptr) 
	{ 								// If the file cannot be opened, we print an error message
        cout << "Dosya acilamadi!" << endl;
        return;
    	}

    int mekan1, mekan2, mesafe;

    // The neighborhood matrix has been reset - initially all its values have been set to 0 - 
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++) 
		{
            komsulukMatrisi[i][j] = 0;
        }
    }

    // The data in the file is read line by line and the neighborhood matrix is filled in
    while (fscanf(dosya, "%d %d %d", &mekan1, &mekan2, &mesafe) == 3) 
	{
        // Checking if valid IDs are within the specified range of 0 - 15
        if (mekan1 >= 0 && mekan1 < n && mekan2 >= 0 && mekan2 < n) 
	{
            komsulukMatrisi[mekan1][mekan2] = mesafe;
            komsulukMatrisi[mekan2][mekan1] = mesafe;			 // If it is not directional, we also add the mutual link
        } 
		else 
		{
            cout << "Hata: Dosyada geçersiz mekan numarası: " << mekan1 << ", " << mekan2 << endl;
        	}
 	}

    fclose(dosya); 							// A shutdown operation is performed on the read file 
}

// En kısa yolun hesaplanması için Dijkstra algoritması kuullanılır 
void Graf::enKisaYolHesapla(int baslangic, int gezilecekMekanlar[], int secimSayisi)
{
    int mesafe[n];  							// Distance array to store distances for each venue
    bool ziyaretEdildi[n]; 						// Array to be used to check if venues have been visited
    int oncelik[n];  							// The sequence that prioritizes each venue
    int toplamSure = 0, toplamMasraf = 0; 				// Variables and variables were assigned to calculate the duration and expense of the trip

    // Initially, all distances are set to a very large value (INT_MAX)
    // They will be set to 'false' because they are not visited
    // The priority array is set to -1
    for (int i = 0; i < n; i++) 
	{
        mesafe[i] = INT_MAX;
        ziyaretEdildi[i] = false;
        oncelik[i] = -1;
    	}

    mesafe[baslangic] = 0;  						// The distance of the starting point is assigned as zero

    // The basic loop of the Dijkstra algorithm has been created
    for (int i = 0; i < n - 1; i++) 
	{
        int minMesafe = INT_MAX, minIndex;

        // The node with the shortest distance, which has not yet been visited, is found
        for (int j = 0; j < n; j++) 
	{
            if (!ziyaretEdildi[j] && mesafe[j] <= minMesafe) 
		{
                minMesafe = mesafe[j];
                minIndex = j;
            	}
        }

        ziyaretEdildi[minIndex] = true; 				// This node was visited

        // Neighbor nodes are updated
        for (int k = 0; k < n; k++) 
	{
            if (!ziyaretEdildi[k] && komsulukMatrisi[minIndex][k] != -1 &&
                mesafe[minIndex] + komsulukMatrisi[minIndex][k] < mesafe[k]) 
		{
                mesafe[k] = mesafe[minIndex] + komsulukMatrisi[minIndex][k];
                oncelik[k] = minIndex;  				// Priority is updated
            	}
        }
    }

    // The output of the shortest path is printed on the screen
    cout << "\n\n <<--------\t Onerilen Gezi Rotasi \t-------->>" << endl;
    for (int i = 0; i < secimSayisi; i++) 
	{
        cout << " --> "<< mekanIsimleri[gezilecekMekanlar[i]] ;
    	}
    // The details of the places to visit are printed on the screen
    cout << "\n\n <<--------\t Mekan Detaylari \t-------->>" << endl;
    for (int i = 0; i < secimSayisi; i++) 
	{
        int mekan = gezilecekMekanlar[i];
        // Venue data including trip duration and expense information
        int geziSuresi, girisUcreti;
        // Here, the duration of each venue and the entrance fee are defined
        if (mekan == 1) { geziSuresi = 30; girisUcreti = 10; }
        else if (mekan == 2) { geziSuresi = 120; girisUcreti = 90; }
        else if (mekan == 3) { geziSuresi = 90; girisUcreti = 150; }
        else if (mekan == 4) { geziSuresi = 50; girisUcreti = 50; }
        else if (mekan == 5) { geziSuresi = 45; girisUcreti = 100; }
        else if (mekan == 6) { geziSuresi = 30; girisUcreti = 8; }
        // Additional information may be added
        toplamSure += geziSuresi;
        toplamMasraf += girisUcreti;

        cout << mekanIsimleri[mekan] << " ---> " << geziSuresi << " dakika, " << girisUcreti << " TL\n";
    	}

    // The total time and expense are printed on the screen
    cout << "\nToplam Gezi Suresi: " << toplamSure << " dk" << endl;
    cout << "Toplam Gezi Masrafi: " << toplamMasraf << " TL\n";
}

// dosyaOku() The contents of the mekanlar.txt file are read with the function
void dosyaOku(Mekan mekanlar[], int &mekanSayisi) 
{
    FILE* dosya = fopen("mekanlar.txt", "r");

    if (dosya == nullptr) 
    {
        cerr << "Dosya acilamadi!" << endl;				 // It is printed on the screen with an error message with the CERR parameter
        return;
    }

    char satir[256];
    // Every line in the file is read
    while (fgets(satir, sizeof(satir), dosya)) 
	{
        Mekan yeniMekan;
        char isimBuffer[100];

        // The line is processed and the venue information is obtained
        if (sscanf(satir, "%d\t%[^\t]\t%d\t%d", &yeniMekan.id, isimBuffer, &yeniMekan.geziSuresi, &yeniMekan.girisUcreti) == 4) 
	{
            yeniMekan.isim = isimBuffer; 				 // The name of the place is converted to string
            mekanlar[mekanSayisi++] = yeniMekan; 			 // New locations are added to the array
        }
    }

    fclose(dosya); 							 // Closing the file closes the read mekanlar.txt file
}

// mekanSirala() With the function, the entrance fees of the venues specified in the mekanlar.txt file will be sorted in ascending order
void mekanSirala() 
{
    Mekan mekanlar[100];						 // A series is defined for a maximum of 100 venues
    int mekanSayisi = 0;

    dosyaOku(mekanlar, mekanSayisi); 					 // The spaces in the file are read using the dosyaOku() function

    if (mekanSayisi == 0) 
	{
        cout << "Mekanlar listesi bos!" << endl;
        return;
    	}

    // Venues are sorted by entrance fee
    for (int i = 0; i < mekanSayisi - 1; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < mekanSayisi; j++) {
            if (mekanlar[j].girisUcreti < mekanlar[minIndex].girisUcreti) 
	    {
                minIndex = j;
            }
        }
        swap(mekanlar[i], mekanlar[minIndex]);  			  // The location of the array elements is changed
    }

    // Sorted places are printed on the screen
    cout << "\nMekanlar (Giris Ucretine Gore Siralanmis):\n";
    for (int i = 0; i < mekanSayisi; i++) 
	{
        cout << mekanlar[i].isim << " - " << mekanlar[i].girisUcreti << " TL" << endl;
    	}
}


// menu() function, the names of the places will be printed on the screen
void menu() 
{
    cout << "<<--------\t Sanliurfa Gezi Rehberi \t-------->>" << endl;
    cout << "| 0\t BASLANGIC (ABIDE KAVSAGI)" << endl;
    cout << "| 1\t BALIKLIGOL" << endl;
    cout << "| 2\t GOBEKLITEPE" << endl;
    cout << "| 3\t ARKEOLOJI MUZESI" << endl;
    cout << "| 4\t MOZAIK MUZESI " << endl;
    cout << "| 5\t KARAHANTEPE" << endl;
    cout << "| 6\t EYUPNEBI" << endl;
    cout << "| 7\t HZ. IBRAHIM MAKAMI" << endl;
    cout << "| 8\t HALFETI TEKNE TURU" << endl;
    cout << "| 9\t KAPALI CARSI" << endl;
    cout << "| 10\t SIRA GECESI" << endl;
    cout << "| 11\t HASIMIYE CIGER YEMEGI" << endl;
    cout << "| 12\t BALON TURU" << endl;
    cout << "| 13\t ANTIK HARRAN UNIVERSITESI KALINTILARI" << endl;
    cout << "| 14\t HZ. YAKUP KUYUSU" << endl;
    cout << "| 15\t GERMUS KILISESI" << endl;
    cout << "<<------------------------------------------------------>>" << endl;
}

int main() 
{
    // It starts by printing the menu of the travel guide.
    menu();

    // The graph object is created. There are 16 spaces, so a 16-dimensional graph is created.
    Graf g(16);

    // We create the graph (distances and connections between spaces are made here).
    g.grafOlustur();

    // The IDs of the places they want to visit are taken from the user.
    cout << "Gezmek Istediginiz mekanlari seciniz >> (Girilen ID numaralari arasinda bosluk birakiniz !): ";
    int gezilecekMekanlar[16], secimSayisi = 0;

    // Venue IDs are obtained from the user. The cycle ends when the Enter key is pressed or 16 venues are entered.
    while (cin >> gezilecekMekanlar[secimSayisi]) 
	{
        secimSayisi++; 							       // We move on to the ID of the next venue.
        
        // If the user presses a line break (Enter) key, the loop ends.
        if (cin.get() == '\n') break;
    	}

    // The price list of the venues received from the user is printed.
    cout << "\n\n <<--------\t Gezilecek Yerlerin Fiyat Listesi \t-------->>" << endl;
    mekanSirala();  								// Prices are printed in order.

    // "Baslangic (Abide Kavşağı)" is chosen as the starting point.
    int baslangic = 0;

    // The shortest route is calculated based on the attractions selected by the user.
    g.enKisaYolHesapla(baslangic, gezilecekMekanlar, secimSayisi);

    return 0;
}
