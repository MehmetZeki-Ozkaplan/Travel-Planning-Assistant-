#ifndef LIBRARY_H 									// Bu dosyan�n birden fazla kez dahil edilmesini �nlemek i�in bir �nlem
#define LIBRARY_H 

#include <iostream> 								// Giri� ve ��k�� i�lemleri i�in gerekli k�t�phane dahil edildi
#include <cstdio>   								// Standart giri�/��k�� fonksiyonlar� i�in gerekli k�t�phane dahil edildi
#include <cstring>  								// Karakter dizisi i�lemleri i�in gerekli k�t�phane dahil edildi
#include <climits>  								// Maksimum ve minimum de�erler i�in sabitler dahil edildi
#include <string>   								// String veri tipini kullanmak i�in gerekli k�t�phane dahil edildi
using namespace std; 								// Standart isim alan�n� kullan�l�r

// Mekan bilgilerini tutmak i�in bir yap� tan�mlan�r
struct Mekan {
    int id;          								// Mekan�n benzersiz ID'sini tutacak de�i�ken tan�mlan�r
    string isim;     								// Mekan ad�n� tutacak de�i�ken tan�mlan�r
    int geziSuresi;  								// Mekan�n gezilme s�resi
    int girisUcreti; 								// Mekan�n giri� �creti
};

// Graf yap�s�n� ve ilgili i�lemleri tan�mlamak i�in bir s�n�f olu�turulur
class Graf {
public:
    int komsulukMatrisi[16][16]; 					// Mesafeleri tutmak i�in 16x16 boyutunda kom�uluk matrisi tan�mlan�r
    int n;                       					// Graf i�erisindeki toplam d���m say�s� tan�mlan�r
    string mekanIsimleri[16];    					// Mekan isimlerini saklayan bir dizi tan�mlan�r

    // Kurucu-Construcot fonksiyon: Graf nesnesini ba�lat�r
    Graf(int n);

    // Graf� dosya verilerinden okuyarak olu�turur
    void grafOlustur();

    // Dijkstra algoritmas�n� kullanarak en k�sa yolu hesaplar
    // Parametreler: - baslangic: Ba�lang�� noktas� - gezilecekMekanlar: Kullan�c�n�n se�ti�i mekanlar�n ID'leri - secimSayisi: Se�ilen mekan say�s�
    void enKisaYolHesapla(int baslangic, int gezilecekMekanlar[], int secimSayisi);
};

// Mekan bilgilerini dosyadan okuyan bir fonksiyon
// Parametreler:  - mekanlar: Mekan bilgilerini tutan dizi - mekanSayisi: Toplam mekan say�s�n� tutan de�i�ken
void dosyaOku(Mekan mekanlar[], int &mekanSayisi);

// Mekanlar� s�ralayan ve s�ralamay� ekrana yazd�ran bir fonksiyon
// Mekanlar giri� �creti veya gezi s�resi gibi kriterlere g�re s�ralan�r
void mekanSirala();

// Kullan�c�ya men�y� g�stermek ve programda gezinmesini sa�lamak i�in bir fonksiyon tan�mlan�r
void menu();

#endif 												// LIBRARY_H // Include Guard'�n sonu
