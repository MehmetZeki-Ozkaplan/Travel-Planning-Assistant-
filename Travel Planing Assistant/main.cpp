#include "library.h"		//Tanýmlanmýþ fonksiyonlarý içeren library kütüphanesi dahil edildi

// Graf sýnýfýnýn kurucu-constructor fonksiyonu oluþturuldu deðer atama iþlemleri gerçekleþtirildi  
// Bu fonksiyon, grafýn boyutunu ve komþuluk matrisini oluþturur
Graf::Graf(int n) 
{
    this->n = n;  													 		// Grafýn düðüm sayýsýný alýr ve sýnýfýn n deðiþkenine atar

    // Komþuluk matrisi -1 ile doldurulur. -1, iki mekan arasýnda baðlantý olmadýðýný belirtmeyi saðlayacaktýr
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
    
    // Mekan isimlerinin atamasý yapýldý
}

// grafOlustur() fonksiyonu ve gövde yapýsý oluþturuldu
// grafOlustur() fonksiyonu mesafeler.txt dosyasýndan verileri okuyarak graf oluþturur
void Graf::grafOlustur() 
{
    FILE* dosya = fopen("mesafeler.txt", "r"); 								// Dosya iþlemleri yapýlarak istenen dosya üzerinde okuma iþlemi yapýlýr
    if (dosya == nullptr) 
	{ 																		// Dosya açýlamazsa hata mesajý yazdýrýyoruz
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    int mekan1, mekan2, mesafe;

    // Komþuluk matrisi sýfýrlandý - baþlangýçta tüm deðerleri 0 yapýldý - 
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++) 
		{
            komsulukMatrisi[i][j] = 0;
        }
    }

    // Dosyadaki veriler satýr satýr okutularak komþuluk matrisi doldurulur
    while (fscanf(dosya, "%d %d %d", &mekan1, &mekan2, &mesafe) == 3) 
	{
        // Geçerli ID'lerin belirlenen 0 - 15 aralýðýnda olup olmadýðý kontrol ediliyor
        if (mekan1 >= 0 && mekan1 < n && mekan2 >= 0 && mekan2 < n) 
		{
            komsulukMatrisi[mekan1][mekan2] = mesafe;
            komsulukMatrisi[mekan2][mekan1] = mesafe;						 // Yönlü deðilse karþýlýklý baðlantýyý da ekliyoruz
        } 
		else 
		{
            cout << "Hata: Dosyada geçersiz mekan numarasý: " << mekan1 << ", " << mekan2 << endl;
        }
    }

    fclose(dosya); // Okunan dosya üzerinde kapatma iþlemi gerçekleþtirilir 
}

// En kýsa yolun hesaplanmasý için Dijkstra algoritmasý kuullanýlýr 
void Graf::enKisaYolHesapla(int baslangic, int gezilecekMekanlar[], int secimSayisi)
{
    int mesafe[n];  														// Her bir mekana ait mesafeleri saklamak için mesafe dizisi
    bool ziyaretEdildi[n]; 												    // Mekanlarýn ziyaret edilip edilmediðini kontrol etmek için kullanýlacak olan dizi
    int oncelik[n];  														// Her bir mekanýn önceliðini tutan dizi
    int toplamSure = 0, toplamMasraf = 0; 									// Gezi süresi ve masrafýný hesaplamak için deðiþkenler ve dedðiþken atamalarý yapýldý

    // Baþlangýçta tüm mesafeler çok büyük bir deðere (INT_MAX) ayarlanýr
    // Ziyaret edilmedikleri için 'false' olarak ayarlanacaktor
    // Öncelik dizisini -1 yapýlýr
    for (int i = 0; i < n; i++) 
	{
        mesafe[i] = INT_MAX;
        ziyaretEdildi[i] = false;
        oncelik[i] = -1;
    }

    mesafe[baslangic] = 0;  												// Baþlangýç noktasýnýn mesafesi sýfýr olarak atanýr

    // Dijkstra algoritmasýnýn temel döngüsü oluþturuldu
    for (int i = 0; i < n - 1; i++) 
	{
        int minMesafe = INT_MAX, minIndex;

        // En kýsa mesafeye sahip, henüz ziyaret edilmemiþ olan düðümü bulunur
        for (int j = 0; j < n; j++) {
            if (!ziyaretEdildi[j] && mesafe[j] <= minMesafe) 
			{
                minMesafe = mesafe[j];
                minIndex = j;
            }
        }

        ziyaretEdildi[minIndex] = true; 									// Bu düðümü ziyaret edildi

        // Komþu düðümleri güncellenir
        for (int k = 0; k < n; k++) 
		{
            if (!ziyaretEdildi[k] && komsulukMatrisi[minIndex][k] != -1 &&
                mesafe[minIndex] + komsulukMatrisi[minIndex][k] < mesafe[k]) 
			{
                mesafe[k] = mesafe[minIndex] + komsulukMatrisi[minIndex][k];
                oncelik[k] = minIndex;  									// Öncelik güncellenir
            }
        }
    }

    // En kýsa yolun çýktýsýný ekrana yazdýrýlýr
    cout << "\n\n <<--------\t Onerilen Gezi Rotasi \t-------->>" << endl;
    for (int i = 0; i < secimSayisi; i++) 
	{
        cout << " --> "<< mekanIsimleri[gezilecekMekanlar[i]] ;
    }
	// Gezilecek mekanlarýn detaylarýný ekrana yazdýrýlýr
    cout << "\n\n <<--------\t Mekan Detaylari \t-------->>" << endl;
    for (int i = 0; i < secimSayisi; i++) 
	{
        int mekan = gezilecekMekanlar[i];
        // Gezi süresi ve masraf bilgilerini içeren mekan verileri
        int geziSuresi, girisUcreti;
        // Burada her mekanýn süresi ve giriþ ücreti tanýmlanýr
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

    // Toplam süre ve masraf ekrana yazdýrýlýr
    cout << "\nToplam Gezi Suresi: " << toplamSure << " dk" << endl;
    cout << "Toplam Gezi Masrafi: " << toplamMasraf << " TL\n";
}

// dosyaOku() fonksiyonu ile mekanlar.txt dosyasýnýn içeriði okunur
void dosyaOku(Mekan mekanlar[], int &mekanSayisi) 
{
    FILE* dosya = fopen("mekanlar.txt", "r");

    if (dosya == nullptr) 
	{
        cerr << "Dosya acilamadi!" << endl;									// cerr parametresi ile hata mesajý ile ekrana yazdýrýlýr
        return;
    }

    char satir[256];
    // Dosyadaki her satýrý okunur
    while (fgets(satir, sizeof(satir), dosya)) 
	{
        Mekan yeniMekan;
        char isimBuffer[100];

        // Satýr iþlenip mekan bilgileri alýnýr
        if (sscanf(satir, "%d\t%[^\t]\t%d\t%d", &yeniMekan.id, isimBuffer, &yeniMekan.geziSuresi, &yeniMekan.girisUcreti) == 4) 
		{
            yeniMekan.isim = isimBuffer; 									// Mekan ismi string'e dönüþtürülür
            mekanlar[mekanSayisi++] = yeniMekan; 							// Yeni mekanlar diziye eklenir
        }
    }

    fclose(dosya); 															// Dosyayý kapatma iþlemi ile okunan mekanlar.txt dosyasý kapatýlýr
}

// mekanSirala() fonksiyonu ile mekanlar.txt dosyasýnda belirtilen mekanlar giriþ ücretleri artan bir þekilde sýralanacaktýr
void mekanSirala() 
{
    Mekan mekanlar[100];													// Maksimum 100 mekan için dizi tanýmlanýyor
    int mekanSayisi = 0;

    dosyaOku(mekanlar, mekanSayisi); 										// Dosyadaki mekanlar dosyaOku() fonksiyonu kullanýlarak okutulur

    if (mekanSayisi == 0) 
	{
        cout << "Mekanlar listesi bos!" << endl;
        return;
    }

    // Mekanlar giriþ ücretine göre sýralanýr
    for (int i = 0; i < mekanSayisi - 1; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < mekanSayisi; j++) {
            if (mekanlar[j].girisUcreti < mekanlar[minIndex].girisUcreti) 
			{
                minIndex = j;
            }
        }
        swap(mekanlar[i], mekanlar[minIndex]);  							// Dizi elemanlarýnýn yeri deðiþtirilir
    }

    // Sýralanmýþ mekanlar ekrana yazdýrýlýr
    cout << "\nMekanlar (Giris Ucretine Gore Siralanmis):\n";
    for (int i = 0; i < mekanSayisi; i++) 
	{
        cout << mekanlar[i].isim << " - " << mekanlar[i].girisUcreti << " TL" << endl;
    }
}


// menu() fonksiyonu ile mekan isimleri ekrana yazdýrýlacaktýr
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
    // Gezi rehberinin menüsü yazdýrýlarak baþlanýr.
    menu();

    // Graf nesnesi oluþturulur. 16 mekan var, bu yüzden 16 boyutlu bir graf oluþturulur.
    Graf g(16);

    // Grafý oluþturuyoruz (mekanlar arasý mesafeler ve baðlantýlar burada yapýlýr).
    g.grafOlustur();

    // Kullanýcýdan gezmek istediði mekanlarýn ID'lerini alýnýr.
    cout << "Gezmek Istediginiz mekanlari seciniz >> (Girilen ID numaralari arasinda bosluk birakiniz !): ";
    int gezilecekMekanlar[16], secimSayisi = 0;

    // Kullanýcýdan mekan ID'leri alýnýr. Enter tuþuna basýldýðýnda veya 16 mekan girildiðinde döngü sonlanýr.
    while (cin >> gezilecekMekanlar[secimSayisi]) 
	{
        secimSayisi++; 														// Bir sonraki mekanýn ID'sine geçiyoruz.
        
        // Kullanýcý bir satýr sonu (Enter) tuþuna basarsa döngü sonlanýr.
        if (cin.get() == '\n') break;
    }

    // Kullanýcýdan alýnan mekanlarýn fiyat listesi yazdýrýlýr.
    cout << "\n\n <<--------\t Gezilecek Yerlerin Fiyat Listesi \t-------->>" << endl;
    mekanSirala();  														// Fiyatlar sýralanarak yazdýrýlýr.

    // Baþlangýç noktasý olarak "Baslangic (Abide Kavþaðý)" seçiliyor.
    int baslangic = 0;

    // Kullanýcý tarafýndan seçilen gezilecek mekanlar üzerinden en kýsa yol hesaplanýr.
    g.enKisaYolHesapla(baslangic, gezilecekMekanlar, secimSayisi);

    return 0;
}
