#ifndef LIBRARY_H 									// Bu dosyanýn birden fazla kez dahil edilmesini önlemek için bir önlem
#define LIBRARY_H 

#include <iostream> 								// Giriþ ve çýkýþ iþlemleri için gerekli kütüphane dahil edildi
#include <cstdio>   								// Standart giriþ/çýkýþ fonksiyonlarý için gerekli kütüphane dahil edildi
#include <cstring>  								// Karakter dizisi iþlemleri için gerekli kütüphane dahil edildi
#include <climits>  								// Maksimum ve minimum deðerler için sabitler dahil edildi
#include <string>   								// String veri tipini kullanmak için gerekli kütüphane dahil edildi
using namespace std; 								// Standart isim alanýný kullanýlýr

// Mekan bilgilerini tutmak için bir yapý tanýmlanýr
struct Mekan {
    int id;          								// Mekanýn benzersiz ID'sini tutacak deðiþken tanýmlanýr
    string isim;     								// Mekan adýný tutacak deðiþken tanýmlanýr
    int geziSuresi;  								// Mekanýn gezilme süresi
    int girisUcreti; 								// Mekanýn giriþ ücreti
};

// Graf yapýsýný ve ilgili iþlemleri tanýmlamak için bir sýnýf oluþturulur
class Graf {
public:
    int komsulukMatrisi[16][16]; 					// Mesafeleri tutmak için 16x16 boyutunda komþuluk matrisi tanýmlanýr
    int n;                       					// Graf içerisindeki toplam düðüm sayýsý tanýmlanýr
    string mekanIsimleri[16];    					// Mekan isimlerini saklayan bir dizi tanýmlanýr

    // Kurucu-Construcot fonksiyon: Graf nesnesini baþlatýr
    Graf(int n);

    // Grafý dosya verilerinden okuyarak oluþturur
    void grafOlustur();

    // Dijkstra algoritmasýný kullanarak en kýsa yolu hesaplar
    // Parametreler: - baslangic: Baþlangýç noktasý - gezilecekMekanlar: Kullanýcýnýn seçtiði mekanlarýn ID'leri - secimSayisi: Seçilen mekan sayýsý
    void enKisaYolHesapla(int baslangic, int gezilecekMekanlar[], int secimSayisi);
};

// Mekan bilgilerini dosyadan okuyan bir fonksiyon
// Parametreler:  - mekanlar: Mekan bilgilerini tutan dizi - mekanSayisi: Toplam mekan sayýsýný tutan deðiþken
void dosyaOku(Mekan mekanlar[], int &mekanSayisi);

// Mekanlarý sýralayan ve sýralamayý ekrana yazdýran bir fonksiyon
// Mekanlar giriþ ücreti veya gezi süresi gibi kriterlere göre sýralanýr
void mekanSirala();

// Kullanýcýya menüyü göstermek ve programda gezinmesini saðlamak için bir fonksiyon tanýmlanýr
void menu();

#endif 												// LIBRARY_H // Include Guard'ýn sonu
