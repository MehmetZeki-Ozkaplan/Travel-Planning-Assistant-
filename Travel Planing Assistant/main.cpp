#include "library.h"		//Tan�mlanm�� fonksiyonlar� i�eren library k�t�phanesi dahil edildi

// Graf s�n�f�n�n kurucu-constructor fonksiyonu olu�turuldu de�er atama i�lemleri ger�ekle�tirildi  
// Bu fonksiyon, graf�n boyutunu ve kom�uluk matrisini olu�turur
Graf::Graf(int n) 
{
    this->n = n;  													 		// Graf�n d���m say�s�n� al�r ve s�n�f�n n de�i�kenine atar

    // Kom�uluk matrisi -1 ile doldurulur. -1, iki mekan aras�nda ba�lant� olmad���n� belirtmeyi sa�layacakt�r
    for (int i = 0; i < n; i++)
	{
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
    
    // Mekan isimlerinin atamas� yap�ld�
}

// grafOlustur() fonksiyonu ve g�vde yap�s� olu�turuldu
// grafOlustur() fonksiyonu mesafeler.txt dosyas�ndan verileri okuyarak graf olu�turur
void Graf::grafOlustur() 
{
    FILE* dosya = fopen("mesafeler.txt", "r"); 								// Dosya i�lemleri yap�larak istenen dosya �zerinde okuma i�lemi yap�l�r
    if (dosya == nullptr) 
	{ 																		// Dosya a��lamazsa hata mesaj� yazd�r�yoruz
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    int mekan1, mekan2, mesafe;

    // Kom�uluk matrisi s�f�rland� - ba�lang��ta t�m de�erleri 0 yap�ld� - 
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++) 
		{
            komsulukMatrisi[i][j] = 0;
        }
    }

    // Dosyadaki veriler sat�r sat�r okutularak kom�uluk matrisi doldurulur
    while (fscanf(dosya, "%d %d %d", &mekan1, &mekan2, &mesafe) == 3) 
	{
        // Ge�erli ID'lerin belirlenen 0 - 15 aral���nda olup olmad��� kontrol ediliyor
        if (mekan1 >= 0 && mekan1 < n && mekan2 >= 0 && mekan2 < n) 
		{
            komsulukMatrisi[mekan1][mekan2] = mesafe;
            komsulukMatrisi[mekan2][mekan1] = mesafe;						 // Y�nl� de�ilse kar��l�kl� ba�lant�y� da ekliyoruz
        } 
		else 
		{
            cout << "Hata: Dosyada ge�ersiz mekan numaras�: " << mekan1 << ", " << mekan2 << endl;
        }
    }

    fclose(dosya); // Okunan dosya �zerinde kapatma i�lemi ger�ekle�tirilir 
}

// En k�sa yolun hesaplanmas� i�in Dijkstra algoritmas� kuullan�l�r 
void Graf::enKisaYolHesapla(int baslangic, int gezilecekMekanlar[], int secimSayisi)
{
    int mesafe[n];  														// Her bir mekana ait mesafeleri saklamak i�in mesafe dizisi
    bool ziyaretEdildi[n]; 												    // Mekanlar�n ziyaret edilip edilmedi�ini kontrol etmek i�in kullan�lacak olan dizi
    int oncelik[n];  														// Her bir mekan�n �nceli�ini tutan dizi
    int toplamSure = 0, toplamMasraf = 0; 									// Gezi s�resi ve masraf�n� hesaplamak i�in de�i�kenler ve ded�i�ken atamalar� yap�ld�

    // Ba�lang��ta t�m mesafeler �ok b�y�k bir de�ere (INT_MAX) ayarlan�r
    // Ziyaret edilmedikleri i�in 'false' olarak ayarlanacaktor
    // �ncelik dizisini -1 yap�l�r
    for (int i = 0; i < n; i++) 
	{
        mesafe[i] = INT_MAX;
        ziyaretEdildi[i] = false;
        oncelik[i] = -1;
    }

    mesafe[baslangic] = 0;  												// Ba�lang�� noktas�n�n mesafesi s�f�r olarak atan�r

    // Dijkstra algoritmas�n�n temel d�ng�s� olu�turuldu
    for (int i = 0; i < n - 1; i++) 
	{
        int minMesafe = INT_MAX, minIndex;

        // En k�sa mesafeye sahip, hen�z ziyaret edilmemi� olan d���m� bulunur
        for (int j = 0; j < n; j++) {
            if (!ziyaretEdildi[j] && mesafe[j] <= minMesafe) 
			{
                minMesafe = mesafe[j];
                minIndex = j;
            }
        }

        ziyaretEdildi[minIndex] = true; 									// Bu d���m� ziyaret edildi

        // Kom�u d���mleri g�ncellenir
        for (int k = 0; k < n; k++) 
		{
            if (!ziyaretEdildi[k] && komsulukMatrisi[minIndex][k] != -1 &&
                mesafe[minIndex] + komsulukMatrisi[minIndex][k] < mesafe[k]) 
			{
                mesafe[k] = mesafe[minIndex] + komsulukMatrisi[minIndex][k];
                oncelik[k] = minIndex;  									// �ncelik g�ncellenir
            }
        }
    }

    // En k�sa yolun ��kt�s�n� ekrana yazd�r�l�r
    cout << "\n\n <<--------\t Onerilen Gezi Rotasi \t-------->>" << endl;
    for (int i = 0; i < secimSayisi; i++) 
	{
        cout << " --> "<< mekanIsimleri[gezilecekMekanlar[i]] ;
    }
	// Gezilecek mekanlar�n detaylar�n� ekrana yazd�r�l�r
    cout << "\n\n <<--------\t Mekan Detaylari \t-------->>" << endl;
    for (int i = 0; i < secimSayisi; i++) 
	{
        int mekan = gezilecekMekanlar[i];
        // Gezi s�resi ve masraf bilgilerini i�eren mekan verileri
        int geziSuresi, girisUcreti;
        // Burada her mekan�n s�resi ve giri� �creti tan�mlan�r
        if (mekan == 1) { geziSuresi = 30; girisUcreti = 10; }
        else if (mekan == 2) { geziSuresi = 120; girisUcreti = 90; }
        else if (mekan == 3) { geziSuresi = 90; girisUcreti = 150; }
        else if (mekan == 4) { geziSuresi = 50; girisUcreti = 50; }
        else if (mekan == 5) { geziSuresi = 45; girisUcreti = 100; }
        else if (mekan == 6) { geziSuresi = 30; girisUcreti = 8; }
        // Ek bilgiler eklenebilir
        toplamSure += geziSuresi;
        toplamMasraf += girisUcreti;

        cout << mekanIsimleri[mekan] << " ---> " << geziSuresi << " dakika, " << girisUcreti << " TL\n";
    }

    // Toplam s�re ve masraf ekrana yazd�r�l�r
    cout << "\nToplam Gezi Suresi: " << toplamSure << " dk" << endl;
    cout << "Toplam Gezi Masrafi: " << toplamMasraf << " TL\n";
}

// dosyaOku() fonksiyonu ile mekanlar.txt dosyas�n�n i�eri�i okunur
void dosyaOku(Mekan mekanlar[], int &mekanSayisi) 
{
    FILE* dosya = fopen("mekanlar.txt", "r");

    if (dosya == nullptr) 
	{
        cerr << "Dosya acilamadi!" << endl;									// cerr parametresi ile hata mesaj� ile ekrana yazd�r�l�r
        return;
    }

    char satir[256];
    // Dosyadaki her sat�r� okunur
    while (fgets(satir, sizeof(satir), dosya)) 
	{
        Mekan yeniMekan;
        char isimBuffer[100];

        // Sat�r i�lenip mekan bilgileri al�n�r
        if (sscanf(satir, "%d\t%[^\t]\t%d\t%d", &yeniMekan.id, isimBuffer, &yeniMekan.geziSuresi, &yeniMekan.girisUcreti) == 4) 
		{
            yeniMekan.isim = isimBuffer; 									// Mekan ismi string'e d�n��t�r�l�r
            mekanlar[mekanSayisi++] = yeniMekan; 							// Yeni mekanlar diziye eklenir
        }
    }

    fclose(dosya); 															// Dosyay� kapatma i�lemi ile okunan mekanlar.txt dosyas� kapat�l�r
}

// mekanSirala() fonksiyonu ile mekanlar.txt dosyas�nda belirtilen mekanlar giri� �cretleri artan bir �ekilde s�ralanacakt�r
void mekanSirala() 
{
    Mekan mekanlar[100];													// Maksimum 100 mekan i�in dizi tan�mlan�yor
    int mekanSayisi = 0;

    dosyaOku(mekanlar, mekanSayisi); 										// Dosyadaki mekanlar dosyaOku() fonksiyonu kullan�larak okutulur

    if (mekanSayisi == 0) 
	{
        cout << "Mekanlar listesi bos!" << endl;
        return;
    }

    // Mekanlar giri� �cretine g�re s�ralan�r
    for (int i = 0; i < mekanSayisi - 1; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < mekanSayisi; j++) {
            if (mekanlar[j].girisUcreti < mekanlar[minIndex].girisUcreti) 
			{
                minIndex = j;
            }
        }
        swap(mekanlar[i], mekanlar[minIndex]);  							// Dizi elemanlar�n�n yeri de�i�tirilir
    }

    // S�ralanm�� mekanlar ekrana yazd�r�l�r
    cout << "\nMekanlar (Giris Ucretine Gore Siralanmis):\n";
    for (int i = 0; i < mekanSayisi; i++) 
	{
        cout << mekanlar[i].isim << " - " << mekanlar[i].girisUcreti << " TL" << endl;
    }
}


// menu() fonksiyonu ile mekan isimleri ekrana yazd�r�lacakt�r
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
    // Gezi rehberinin men�s� yazd�r�larak ba�lan�r.
    menu();

    // Graf nesnesi olu�turulur. 16 mekan var, bu y�zden 16 boyutlu bir graf olu�turulur.
    Graf g(16);

    // Graf� olu�turuyoruz (mekanlar aras� mesafeler ve ba�lant�lar burada yap�l�r).
    g.grafOlustur();

    // Kullan�c�dan gezmek istedi�i mekanlar�n ID'lerini al�n�r.
    cout << "Gezmek Istediginiz mekanlari seciniz >> (Girilen ID numaralari arasinda bosluk birakiniz !): ";
    int gezilecekMekanlar[16], secimSayisi = 0;

    // Kullan�c�dan mekan ID'leri al�n�r. Enter tu�una bas�ld���nda veya 16 mekan girildi�inde d�ng� sonlan�r.
    while (cin >> gezilecekMekanlar[secimSayisi]) 
	{
        secimSayisi++; 														// Bir sonraki mekan�n ID'sine ge�iyoruz.
        
        // Kullan�c� bir sat�r sonu (Enter) tu�una basarsa d�ng� sonlan�r.
        if (cin.get() == '\n') break;
    }

    // Kullan�c�dan al�nan mekanlar�n fiyat listesi yazd�r�l�r.
    cout << "\n\n <<--------\t Gezilecek Yerlerin Fiyat Listesi \t-------->>" << endl;
    mekanSirala();  														// Fiyatlar s�ralanarak yazd�r�l�r.

    // Ba�lang�� noktas� olarak "Baslangic (Abide Kav�a��)" se�iliyor.
    int baslangic = 0;

    // Kullan�c� taraf�ndan se�ilen gezilecek mekanlar �zerinden en k�sa yol hesaplan�r.
    g.enKisaYolHesapla(baslangic, gezilecekMekanlar, secimSayisi);

    return 0;
}
