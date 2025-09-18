//questo codice sorgente gestisce un archivio organizzato ad accesso diretto
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // Apro in modalità append + input (per controllare se il file è vuoto)
    fstream file("studenti.txt", ios::in | ios::out | ios::app);

    if (!file) {
        cerr << "Errore nell'apertura del file!" << endl;
        return 1;
    }

    //scelta lettura/scrittura
    int scelta;
    cout << "inserire 1 per Scrivere sull'archivio, 2 per leggere, oppure un altro numero per selezionare un record specifico: ";
    cin >> scelta;
    cout << endl;

    if (scelta == 1) {


    int n;
    cout << "Quanti studenti vuoi inserire? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int id;
        string nome, cognome, nascita, corso;

        cout << "\nStudente " << i + 1 << endl;
        cout << "ID (intero): ";
        cin >> id;

        cout << "Nome (max 10 caratteri): ";
        cin >> nome;

        cout << "Cognome (max 10 caratteri): ";
        cin >> cognome;

        cout << "Data di nascita (YYYYMMDD, 8 caratteri): ";
        cin >> nascita;

        cout << "Corso (max 10 caratteri): ";
        cin >> corso;

        // scrittura su file con larghezza fissa
        file << left << setw(5) << id
            << setw(12) << nome.substr(0, 10)
            << setw(12) << cognome.substr(0, 10)
            << setw(10) << nascita.substr(0, 8)
            << setw(12) << corso.substr(0, 10)
            << endl;
    }
    cout << "\nDati aggiunti correttamente su studenti.txt" << endl;
    }
    else if (scelta == 2) {
        string rec;


        cout << "\n--- Contenuto di studenti.txt ---\n" << endl;
        // stampa nuova intestazione a video
        cout << left << setw(5) << "ID"
            << setw(12) << "Nome"
            << setw(12) << "Cognome"
            << setw(10) << "Nascita"
            << setw(12) << "Corso"
            << endl;

        int id;
        string nome, cognome, nascita, corso;

        // lettura dei campi dal file
        while (getline(file, rec)) {
            id = stoi(rec.substr(0, 5));
            nome = rec.substr(5, 10);
            cognome = rec.substr(17, 10);
            nascita = rec.substr(29, 10);
            corso = rec.substr(39, 10);

            cout << left << setw(5) << id
                << setw(12) << nome
                << setw(12) << cognome
                << setw(10) << nascita
                << setw(12) << corso
                << endl;
        }
        //che succede se un altro applicativo permette l'inserimento del campo nome con 20 caratteri anzichè 10?
        //oppure se prevedeva l'inserimento della data nel formato GGMMAAAA?
    }
    else {
        int id;
        string nome, cognome, nascita, corso;

        int numrec;
        int lrec = 53;

        cout << "inserisci il numero del record da leggere: ";
        cin >> numrec;
        cout << endl;

        file.seekg((numrec - 1)* lrec  , ios::beg);

        string rec;
        if (getline(file, rec)) {
            id = stoi(rec.substr(0, 5));
            nome = rec.substr(5, 10);
            cognome = rec.substr(17, 10);
            nascita = rec.substr(29, 10);
            corso = rec.substr(39, 10);

            cout << left << setw(5) << id
                << setw(12) << nome
                << setw(12) << cognome
                << setw(10) << nascita
                << setw(12) << corso
                << endl;
        }
        //quindi possiamo saltare ad un certo record senza visitare i precedenti
    }


    file.close();
    

    return 0;
}

//che succede se un altro applicativo permette l'inserimento del campo nome con 20 caratteri anzichè 10?
//oppure se prevedeva l'inserimento della data nel formato GGMMAAAA?
/*
Come faccio ad aggiornare un record?
come faccio ad inserire un nuovo record in mezzo a 2 altri già esistenti?
come faccio a cancellare un record che non sia l'ultimo? 

che succede se inserisco gli stessi dati per più record?
che succede se modifico il file studenti.txt direttamente?
*/
