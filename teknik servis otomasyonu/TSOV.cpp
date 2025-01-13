#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
/* öğrenci no:2412729009,  ad-soyad:doğukan burak çelikten,  ödev konusu:teknik servis otomasyonu*/
using namespace std;

struct Cihaz {
    char marka[80];
    char model[80];
    char seri_no[20];
    char ariza_turu[100];
};

struct ServisTalepleri {
    char seri_no[20];
    char ariza_turu[100];
    char musteri_adi[80];
    char teslim_tarihi[20];
    char servis_durumu[100];
};

void cihazEkle();
void servisTalepleriEkle();
void cihazListele();
void servisListele();
void servisDurumGuncelle();
void cihazSil();
void servisTalepleriAra();
void servisTalepleriSil();

int main() {
    char secim;
    do {
        system("cls");
        cout << "|------- Teknik Servis Otomasyonu -------|" << endl;
        cout << "| 1 - Cihaz Ekle                         |" << endl;
        cout << "| 2 - Servis Talebi Ekle                 |" << endl;
        cout << "| 3 - Cihaz Listele                      |" << endl;
        cout << "| 4 - Servis Talepleri Listele           |" << endl;
        cout << "| 5 - Servis Durumunu Güncelle           |" << endl;
        cout << "| 6 - Cihaz Sil                          |" << endl;
        cout << "| 7 - Servis Talepleri Ara               |" << endl;
        cout << "| 8 - Servis Talebi Sil                  |" << endl;
        cout << "| Çıkmak için 'q' tuşuna basın.          |" << endl;
        cout << "|----------------------------------------|" << endl;
        cin >> secim;
        
        switch(secim) {
            case '1': cihazEkle(); break;
            case '2': servisTalepleriEkle(); break;
            case '3': cihazListele(); break;
            case '4': servisListele(); break;
            case '5': servisDurumGuncelle(); break;
            case '6': cihazSil(); break;
            case '7': servisTalepleriAra(); break;
            case '8': servisTalepleriSil(); break;
            case 'q': break;
            default: cout << "Geçersiz seçenek!" << endl;
        }
        
        cout << "Ana menüye dönmek için 'a', çıkmak için 'q' basın: ";
        cin >> secim;
    } while (secim != 'q');
    
    return 0;
}

void cihazEkle() {
    Cihaz cihaz;
    ofstream yaz("cihazlar.dat", ios::binary | ios::app);
    
    char secim;
    do {
        cout << "Cihaz Marka: ";
        cin >> cihaz.marka;
        cout << "Cihaz Model: ";
        cin >> cihaz.model;
        cout << "Cihaz Seri Numarası: ";
        cin >> cihaz.seri_no;
        cout << "Cihaz Arıza Türü: ";
        cin >> cihaz.ariza_turu;
        
        yaz.write((char*)&cihaz, sizeof(cihaz));
        cout << "Başka cihaz eklemek ister misiniz? (E/H): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');
    
    yaz.close();
}

void servisTalepleriEkle() {
    ServisTalepleri servis;
    ofstream yaz("servis_talepleri.dat", ios::binary | ios::app);
    
    char secim;
    do {
        cout << "Cihaz Seri Numarası: ";
        cin >> servis.seri_no;
        cout << "Cihaz Arıza Türü: ";
        cin >> servis.ariza_turu;
        cout << "Müşteri Adı: ";
        cin >> servis.musteri_adi;
        cout << "Teslim Tarihi (GG/AA/YYYY): ";
        cin >> servis.teslim_tarihi;
        cout << "Servis Durumu: ";
        cin >> servis.servis_durumu;
        
        yaz.write((char*)&servis, sizeof(servis));
        cout << "Başka servis talebi eklemek ister misiniz? (E/H): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');
    
    yaz.close();
}

void cihazListele() {
    ifstream oku("cihazlar.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritabanı bulunamadı!" << endl;
        return;
    }
    
    Cihaz cihaz;
    int i = 1;
    while (oku.read((char*)&cihaz, sizeof(cihaz))) {
        cout << i++ << ". Cihaz Marka: " << cihaz.marka << ", Model: " << cihaz.model
             << ", Seri No: " << cihaz.seri_no << ", Arıza Türü: " << cihaz.ariza_turu << endl;
    }
    
    oku.close();
}

void servisListele() {
    ifstream oku("servis_talepleri.dat", ios::binary);
    
    if (!oku) {
        cout << "Servis talepleri veritabanı bulunamadı!" << endl;
        return;
    }
    
    ServisTalepleri servis;
    int i = 1;
    while (oku.read((char*)&servis, sizeof(servis))) {
        cout << i++ << ". Cihaz Seri No: " << servis.seri_no << ", Arıza Türü: " << servis.ariza_turu
             << ", Müşteri: " << servis.musteri_adi << ", Teslim Tarihi: " << servis.teslim_tarihi
             << ", Servis Durumu: " << servis.servis_durumu << endl;
    }
    
    oku.close();
}

void servisDurumGuncelle() {
    ifstream oku("servis_talepleri.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);
    
    if (!oku) {
        cout << "Servis talepleri veritabanı bulunamadı!" << endl;
        return;
    }
    
    char seri_no[20];
    cout << "Güncellemek istediğiniz cihazın seri numarasını girin: ";
    cin >> seri_no;
    
    ServisTalepleri servis;
    bool bulundu = false;
    
    while (oku.read((char*)&servis, sizeof(servis))) {
        if (strcmp(servis.seri_no, seri_no) == 0) {
            bulundu = true;
            cout << "Servis Durumu : ";
            cin >> servis.servis_durumu;
        }
        gecici.write((char*)&servis, sizeof(servis));
    }
    
    oku.close();
    gecici.close();
    
    if (bulundu) {
        remove("servis_talepleri.dat");
        rename("gecici.dat", "servis_talepleri.dat");
    } else {
        remove("gecici.dat");
        cout << "Cihaz bulunamadı!" << endl;
    }
}

void cihazSil() {
    ifstream oku("cihazlar.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);
    
    if (!oku) {
        cout << "Veritabanı bulunamadı!" << endl;
        return;
    }
    
    char seri_no[20];
    cout << "Silmek istediğiniz cihazın seri numarasını girin: ";
    cin >> seri_no;
    
    Cihaz cihaz;
    bool bulundu = false;
    
    while (oku.read((char*)&cihaz, sizeof(cihaz))) {
        if (strcmp(cihaz.seri_no, seri_no) != 0) {
            gecici.write((char*)&cihaz, sizeof(cihaz));
        } else {
            bulundu = true;
            cout << "Cihaz silindi!" << endl;
        }
    }
    
    oku.close();
    gecici.close();
    
    if (bulundu) {
        remove("cihazlar.dat");
        rename("gecici.dat", "cihazlar.dat");
    } else {
        remove("gecici.dat");
        cout << "Cihaz bulunamadı!" << endl;
    }
}

void servisTalepleriAra() {
    ifstream oku("servis_talepleri.dat", ios::binary);
    
    if (!oku) {
        cout << "Servis talepleri veritabanı bulunamadı!" << endl;
        return;
    }
    
    char arama[80];
    cout << "Aramak istediğiniz müşteri adı veya cihaz seri numarasını girin: ";
    cin >> arama;
    
    ServisTalepleri servis;
    bool bulundu = false;
    
    while (oku.read((char*)&servis, sizeof(servis))) {
        if (strstr(servis.musteri_adi, arama) != NULL || strstr(servis.seri_no, arama) != NULL) {
            bulundu = true;
            cout << "Cihaz Seri No: " << servis.seri_no << ", Müşteri: " << servis.musteri_adi
                 << ", Arıza Türü: " << servis.ariza_turu << ", Teslim Tarihi: " << servis.teslim_tarihi
                 << ", Servis Durumu: " << servis.servis_durumu << endl;
        }
    }
    
    if (!bulundu) {
        cout << "Aradığınız kayıt bulunamadı!" << endl;
    }
    
    oku.close();
}

void servisTalepleriSil() {
    ifstream oku("servis_talepleri.dat", ios::binary);
    ofstream gecici("gecici_servis.dat", ios::binary);
    
    if (!oku || !gecici) {
        cout << "Servis talepleri veritabanı açılamadı!" << endl;
        return;
    }
    
    char seri_no[20];
    cout << "Silmek istediğiniz servis talebinin cihaz seri numarasını girin: ";
    cin >> seri_no;
    
    ServisTalepleri servis;
    bool bulundu = false;
    
    while (oku.read((char*)&servis, sizeof(servis))) {
        if (strcmp(servis.seri_no, seri_no) != 0) {
            gecici.write((char*)&servis, sizeof(servis));
        } else {
            bulundu = true;
            cout << "Servis talebi silindi!" << endl;
        }
    }
    
    oku.close();
    gecici.close();
    
    if (bulundu) {
        remove("servis_talepleri.dat");
        rename("gecici_servis.dat", "servis_talepleri.dat");
    } else {
        remove("gecici_servis.dat");
        cout << "Servis talebi bulunamadı!" << endl;
    }
}