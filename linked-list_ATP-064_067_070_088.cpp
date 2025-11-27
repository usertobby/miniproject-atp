#include <iostream>
#include <string>

using namespace std;

// Struct untuk menyimpan variabel dan pointer
struct Menu {
    string name; // nama makanan
    string type; // jenis (Pembuka, Utama, Penutup)
    int price;   // harganya
    Menu* next;  // buat variabel pointer untuk menyimpan alamat dari variabel setelahnya
};

Menu m;
//Fungsi untuk meng-lowercase-kan input (untuk check duplicate)
string toLowerCase(const string& str) { 
    string lower = str;
    for (char& c : lower)
        c = tolower(c);
    return lower;
}

//Fungsi untuk membuat huruf pertama string kapital
string kapitalAwal(const string& str) {
    if (str.empty()) {                          // jika string empty
        return str;
    }
    string kap = str;
    kap[0] = toupper(kap[0]);                   // bikin huruf pertama kapital
    for (size_t i = 1; i < kap.size(); i++) {
        kap[i] = tolower(kap[i]);               // bikin sisa string lowercase
    }
    return kap;
}

//Fungsi untuk mengecek apakah ada menu yang sama (check duplicate)
bool isDuplicate (Menu* head, const string& name) {
    string lowerName = toLowerCase(name);       // konversi input ke lowercase
    Menu* temp = head;
    while (temp != nullptr) {                   // loop list menunya(Transversing)
        if (toLowerCase(temp->name) == lowerName) {       // ini ngecek jika ada nama node yang sama dengan nama yang ingin di input
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// insert at beginning
void insertAtBeginning(Menu*& head, string name, string type, int price) {
    // check duplicate
    if (isDuplicate(head, name)) {
        cout << "\nMenu sudah ada di daftar!\n\n";
        return;
    }
    // create new node pointing to current head
    Menu* newNode = new Menu{name, type, price, head};
    // define head to new node
    head = newNode;
    cout << "\nPenambahan berhasil!\n\n";
}

// insert at end
void insertAtEnd(Menu*& head, string name, string type, int price) {
    // check duplicate
    if (isDuplicate(head, name)) {
        cout << "\nMenu sudah ada di daftar!\n\n";
        return;
    }
    Menu* newNode = new Menu{name, type, price, nullptr};
    // check if the list is empty, the new node menjadi head nya
    if (head == nullptr) {
        head = newNode;
        cout << "\nPenambahan berhasil!\n\n";
    } else {
        // if list is not empty, bakal jalan terus sampai ketemu nullptr (index terakhir di list)
        Menu* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        // kalau sudah ketemu null ptr bakalan taruh new node di situ
        temp->next = newNode;
        cout << "\nPenambahan berhasil!\n\n";
    }
}

// insert at certain index
void insertAtIndex(Menu*& head, string name, string type, int price, int index) {
    // check duplicate
    if (isDuplicate(head, name)) {
        cout << "\nMenu sudah ada di daftar!\n\n";
        return;
    }

    // if user wants to insert at beginning instead (index can mean at any index)
    if (index == 0) {
        insertAtBeginning(head, name, type, price);
        return;
    }

    // buat node baru    
    Menu* newNode = new Menu{name, type, price, nullptr};

    Menu* temp = head;          // mulai dari head

    // loop untuk move ke posisi index (yang ingin di insert) - 1, jadi misal ingin masukin di index 6, maka bakal nyari index ke 5. (karena index - 1)
    for (int i = 0; i < index - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    // kalo index yg di mau in out of range
    if (temp == nullptr) {
        cout << "\nIndex tidak dapat dijangkau!\n" << endl;
        delete newNode;
        return;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    cout << "\nPenambahan berhasil\n\n";
}

// delete from beginning
void deleteFromBeginning(Menu*& head) {
    // menghindari menghapus list jika tidak ada
    if (head == nullptr) {
        cout << "\nMenu anda kosong!\n" << endl;
        return;
    }
    // kalau hanya ada 1 node di list
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << "\nPenghapusan berhasil (Menu anda kosong)\n\n";
        return;
    }
    Menu* temp = head;      // simpan head node yg sekarang
    head = head->next;      // pindahkan head ke node ke-dua
    delete temp;            // hapus node lama
    cout << "\nPenghapusan berhasil\n\n";
}

// delete from end
void deleteFromEnd (Menu*& head) {
    // check if list is empty
    if (head == nullptr) {
        cout << "\nMenu anda kosong!\n" << endl;
        return;
    }
    // kalau hanya ada 1 node di list
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        cout << "\nPenghapusan berhasil (Menu anda kosong)\n\n";
        return;
    }

    // mulai dari node head
    Menu* temp = head;
    while (temp->next->next != nullptr) {   // loop sampai ketemu node ke-dua dari akhir
        temp = temp->next;
    }
    delete temp->next;              // hapus node terakhir
    temp->next = nullptr;           // simpan end baru dari list dengan gunakan nullptr
    cout << "\nPenghapusan berhasil\n\n";
}

// delete at certain index
void deleteAtIndex(Menu*& head, int index) {
    if (head == nullptr) {
        cout << "\nMenu anda kosong!\n" << endl;
        return;
    }

    if (index < 0) {
        cout << "\nNomor menu tidak valid!\n" << endl;
        return;
    }

    // delete the head or index 0
    if (index == 0) {
        Menu* temp = head;
        head = head->next;
        delete temp;
        cout << "\nPenghapusan berhasil!\n\n";
        return;
    }

    Menu* temp = head;          // mulai dari head
    for (int i = 0; i < index - 1 && temp != nullptr; i++) { // loop sampai ketemu index - 1
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {         // jika out of range
        cout << "\nIndex tidak dapat dijangkau!\n" << endl;
        return;
    }

    Menu* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    cout << "\nPenghapusan berhasil\n\n";
}

// untuk print hasil
void display(Menu* head) {
    Menu* temp = head;
    int i = 1;
    cout << "\nMenu anda : \n";

    //Cek apakah menu kosong atau tidak
    if(temp == nullptr ){
        cout << "Menu anda kosong!\n\n";
        return;
    }

    //Transversing untuk menampilkan menu yang ada
    while (temp != nullptr) {
        cout << i << ". " << kapitalAwal(temp->name) << " (" << temp->type << ") Rp" << temp->price << endl;
        temp = temp->next;
        i++;
    }
    
    cout << endl;
}

//Cek batasan harga agar sesuai dengan harga restaurant
bool checkPrice(int price){
    if(price < 100){
        cout << "\nHarga yang kamu masukkan tidak masuk akal!\n\n";
        return false;
    }else if(price > 500000){
        cout << "\nKami tidak memiliki menu pada harga tersebut!\n\n";
        return false;
    }else{
        return true;
    }
}

//Fungsi untuk mengambil input user
void inputUser(){
    int typeChoice;

    cout << "Masukkan nama [string]: ";
    getline(cin, m.name);

    while (true) {
        cout << "Pilih jenis menu:\n";
        cout << "1. Pembuka\n";
        cout << "2. Utama\n";
        cout << "3. Minuman\n";
        cout << "4. Penutup\n";
        cout << "Pilih [1-4]: ";
        cin >> typeChoice;

        switch (typeChoice) {
            case 1:
                m.type = "Pembuka";
                break;
            case 2:
                m.type = "Utama";
                break;
            case 3:
                m.type = "Minuman";
                break;
            case 4:
                m.type = "Penutup";
                break;
            default:
                cout << "\nHanya ada 4 opsi! Silakan pilih angka 1-4.\n\n";
                continue;
        }
        break;
    }

    cout << "Masukkan harga [angka]: ";
    cin >> m.price;
}

int main() {
    Menu* head = nullptr;
    int choice, index;

    cout << "==============================\n";
    cout << "==== Restaurant Suka Maju ====\n";
    cout << "==============================\n\n";

    
   do {
        cout << "===== OPSI MENU =====\n";
        cout << "1. Tambah menu di awal            5. Hapus menu di akhir\n";
        cout << "2. Tambah menu di akhir           6. Hapus menu di index tertentu\n";
        cout << "3. Tambah menu di index tertentu  7. Tampilkan semua menu\n";
        cout << "4. Hapus menu di awal             0. Keluar\n";
        cout << "Pilih [ANGKA 0-7]: ";
        cin >> choice;
        cin.ignore();//Agar getline tidak membaca input enter dari user

        switch(int(choice)){
            case 1: 
                inputUser();

                if(checkPrice(m.price)){
                    insertAtBeginning(head, m.name, m.type, m.price);
                    break;
                }
                break;
            case 2: 
                inputUser();    

                if(checkPrice(m.price)){
                    insertAtEnd(head, m.name, m.type, m.price);
                    break;
                }
                break;
            case 3: 
                inputUser();  
                cout << "Masukkan index [angka]: ";
                cin >> index;

                if(checkPrice(m.price)){
                    insertAtIndex(head, m.name, m.type, m.price, index - 1);
                    break;
                }
                break;
            case 4:
                deleteFromBeginning(head);
                break;
            case 5:
                deleteFromEnd(head);
                break;
            case 6:
                cout << "Masukkan index yang ingin dihapus: ";
                cin >> index;
                deleteAtIndex(head, index - 1);
                break;
            case 7:
                display(head);
                break;
            case 0:
                cout << "\nKeluar dari program.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n\n";         
        }
        
   } while(choice);
}

// I Made Tobby Anantha Adiwaya (5027251064)
// Muhammad Yusuf (5027251067)
// Sultan Ahmad Maulana Bahyshidqi (5027251070)
// Wildan Alfarezy (5027251088)

// This project was successfully demonstrated on the 18th of November 2025.

// Published to this Repository on the 27th of November 2025.