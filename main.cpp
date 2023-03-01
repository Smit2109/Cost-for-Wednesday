#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
//#include <curl>

#define DOLAR 4,63

using namespace std;

class TotiParticipantii{
private:
    int numarActori;
    int numarFiguranti;
    int numarTotal;
    
public:
    TotiParticipantii(){
        //cout << "a fost creata clasa participantilor\n";
    }

    //metode de accesare ale variabilelor private
    int getNumarActori() { return numarActori; }
    int getNumarFiguranti() { return numarFiguranti; }
    int getNumarTotal() { return numarTotal; }

    //metode de modificare a variabilelor private
    void setNumarActori(int varActori) { numarActori = varActori; }
    void setNumarFiguranti(int varFiguranti) { numarFiguranti = varFiguranti; }
    void setNumarTotal(int varTotal) { numarTotal = varTotal; }

    ~TotiParticipantii(){
        //cout << "a fost stearsa clasa participantilor\n";
    }
};

class Participant{
private:
    string nume;
    string rol;
    string monstru;
    string mancare;

public:
    Participant(){
        //cout << "a fost creat un participant\n";
    }

    //metode de accesare a variabilelor private
    string getNume() { return nume; }
    string getRol() { return rol; }
    string getMonstru() { return monstru; }
    string getMancare() { return mancare; }

    //metode de modificare a variabilelor private
    void setNume(string varNume) { nume = varNume; }
    void setRol(string varRol) { rol = varRol; }
    void setMonstru(string varMonstru) { monstru = varMonstru; }
    void setMancare(string varMancare) { mancare = varMancare; }

    ~Participant(){
        //cout << "a fost sters un participant\n";
    }
};

class Money : TotiParticipantii{
private:
    //preturile puteai fi float pentru a fi exacte, dar fiind deja perturi mari am ales sa le fac int
    int pretMachiaj; //pret pe zi
    int pretMancare; //pret pe zi
    int pretBautura; //pret pe zi
    int pretCazare; //pret pe zi
    int pretAutocare; //pret dus
    int pretInchiriere; //pret pe numar de zile
    int pretTotal;  //pret pe numar de zile

public:
    //metode de accesare a variabilelor private
    int getPretMachiaj() { return pretMachiaj; }
    int getPretMancare() { return pretMancare; }
    int getPretBautura() { return pretBautura; }
    int getPretCazare() { return pretCazare; }
    int getPretAutocare() { return pretAutocare; }
    int getPretInchiriere() { return pretInchiriere; }
    int getPretTotal() { return pretTotal; }

    //metode de modificare a variabilelor private
    void setPretMachiaj (int pret) { pretMachiaj = pret; }
    void setPretMancare (int pret) { pretMancare = pret; }
    void setPretBautura (int pret) { pretBautura = pret; }
    void setPretCazare (int pret) { pretCazare = pret; }
    void setPretAutocare (int pret) { pretAutocare = pret; }
    void setPretInchiriere (int pret) {pretInchiriere = pret; }
    void setPretTotal (int pret) { pretTotal = pret; }
};

//am declarat global pentru a fi mai usor de accesat variabilele
TotiParticipantii wednesday;
Money Pretul;
Participant Actor[1000];    //am pus 1000, dar sunt 735 de actori in cast + 132 de figuranti = 867
//de asemenea nu era neaparata nevoie sa salvez actorii in  interiorul programului deoarece
//am rezolvat prolemele de cand i-am citit
//sunt salvati pentru viitoare functionalitati ale programului

void castInitial(){
    try{
        ifstream MyFile;

        MyFile.open("w-wednesdayCast.csv");

        //verificam daca primim eroare cand deschidem fisierul
        if(!MyFile.is_open()){
            //daca intra in acest if inseamna ca nu s-a deschis fisierul si aruncam un text
            throw "Fisierul folosit in functia castInitial pnu a fost deschis!";
        }

        int i = 0, random, persoane = -1, actori = 0;
        int machiajPeZi = 0, mancarePeZi = 0;
        string word;
        string monstrii[5] = {"Vampiri", "Vârcolaci", "Sirene","Clarvăzători", "Om"};
        int costMonstrii[5] = {230, 555, 345, 157, 55};

        while(!MyFile.eof()){
            //nume
            persoane ++;
            getline(MyFile,word,',');
            Actor[i].setNume(word);;

            //rol
            getline(MyFile,word,'\n');
            Actor[i].setRol(word);

            if(word.find("actor/actress") != std::string::npos){
                actori ++;

                //tip de monstru
                random = rand()%5;
                Actor[i].setMonstru(monstrii[random]);
                machiajPeZi += costMonstrii[random];
            }
        }
        //salvam numarul de actori si numarul total de participanti
        wednesday.setNumarActori(actori);
        wednesday.setNumarTotal(persoane);

        //setam prejul machiajului pe zi
        Pretul.setPretMachiaj(machiajPeZi);

        MyFile.close();
    }
    catch (string x){
        //daca nu am putut deschide fisierul prindem eroarea aici
        cout << "Programul nu a rulat corespunzator deoarece " << x << "\n";
    }
}

void figuranti(){
    try{
        ifstream MyFile;

        MyFile.open("w-randomNames.csv");
        if(!MyFile.is_open()){
            throw "Fisierul din functia figuranti nu a fost deschis!";
        }

        int total = 0, i = 0, random;
        int var = wednesday.getNumarTotal()-1;
        string firstName[300], lastName[300], name;

        for(i = 0; i < 300; i++){
            //salvam numele din fisierul de intrare in aplicatie pentru a putea genera random numele figurantilor
            getline(MyFile, firstName[i],',');
            getline(MyFile, lastName[i],'\n');
        }
        for(i = 0; i < 132; i++){
            name = firstName[rand()%300] + " " + lastName[rand()%300];
            Actor[var + i].setNume(name);
            Actor[var + i].setRol("Figurant");
        }

        //modificam numarul total de participanti deoarece am adaugat figurantii
        wednesday.setNumarTotal(wednesday.getNumarTotal()+132);
        wednesday.setNumarFiguranti(132);
    }
    catch (string x){
        cout << "Programul nu a rulat corespunzator deoarece " << x << "\n";
    }
}

void finisaje(){
    int bautura = 0, autocare = 0, cazare = 0, mancare = 0;
    int random, i, var, var2;
    int costMancare[3] = {40, 33, 46};
    string vectorMancare[3] = {"Aptă să mănânce orice","Vegetariană","Flexitariană"};

    //mancare
    for(i = 0; i < wednesday.getNumarTotal(); i++){
        random = rand() % 3;
        Actor[i].setMancare(vectorMancare[random]);
        mancare += costMancare[random];
    }

    //autocare
    var = wednesday.getNumarTotal() /50;
    if(50 * var != wednesday.getNumarTotal()){
        var ++; //daca nu se imparte egal inseamna ca mai avem nevoie de un autocar
    }
    autocare = 5680 * var * 2; //inmultim cu 2 pentru ca trebuie dus intors

    //bautura
    var = wednesday.getNumarTotal();
    bautura = var * (3 + 15 + 2 /0.8 *8); //am facut suma bauturilor scalate pe persoana

    //cazare
    var = wednesday.getNumarTotal()-wednesday.getNumarFiguranti();
    //verificam daca cei din castul initial sunt in numar par, iar daca nu trebuie sa luam o camera in +
    if(var /2 *2 != var){
        var = var /2 + 1;
    }
    else{
        var = var /2;
    }

    //verificam daca numarul de figuranti se imparte exact la 3, iar daca nu trebuie sa luam o camera in +
    var2 = wednesday.getNumarFiguranti();
    if(var2 /3 *3 != var2){
        var2 = var2 /3 + 1;
    }
    else{
        var2 = var2 /3;
    }
    cazare = var * 350 + var2 * 420;

    //salvam preturile calculate mai sus
    Pretul.setPretMancare(mancare);
    Pretul.setPretBautura(bautura);
    Pretul.setPretAutocare(autocare);
    Pretul.setPretCazare(cazare);
}

void generezCastComplet(){
    try{
        ifstream MyFile;
        MyFile.open("w-wednesdayCastComplet.csv");

        ofstream tempFile("temp.csv");

        if(!MyFile.is_open()){
            throw "Fisierul folosit in functia generezCastComplet() nu a fost deschis!";
        }
        if(!tempFile.is_open()){
            throw "Fisierul temporar nu a fost deschis!";
        }

        string line;
        int castInitial = wednesday.getNumarTotal() - wednesday.getNumarFiguranti();
        int numarLinie = 0, i;

        while (!MyFile.eof()){
            getline(MyFile, line);
            numarLinie++;

            //verificam daca trebuie sa introducem figurantii
            if (numarLinie > castInitial) {
                break;
            } else {
                tempFile << line << "\n";
            }
        }
        for(i = -2; i < 132 ; i++){
            tempFile << Actor[i + numarLinie].getNume() << "," << Actor[i + numarLinie].getRol() << "\n";
        }

        MyFile.close();
        tempFile.close();

        // Stergem fisierul vechi
        remove("w-wednesdayCastComplet.csv");
        // Redenum fisierul nou
        rename("temp.csv", "w-wednesdayCastComplet.csv");
    }
    catch (string x){
        cout << "Programul nu a rulat corespunzator deoarece " << x << "\n";
    }
}

void calculamPeZile(int numarZile, int &varMachiaj, int &varMancare, int &varBautura,
                    int &varCazare, int &varAutocare, int &varInchiriere, int &varTotal){

    varMachiaj = Pretul.getPretMachiaj() * numarZile / DOLAR;
    varMancare = Pretul.getPretMancare() * numarZile / DOLAR;
    varBautura = Pretul.getPretBautura() * numarZile / DOLAR;
    varCazare = Pretul.getPretCazare() * numarZile / DOLAR;
    varAutocare = Pretul.getPretAutocare() / DOLAR;

    int reducere, multipliiDe10;

    multipliiDe10 = numarZile / 10;
    reducere = multipliiDe10 *2; //2 % este reducerea

    //aplicam reducerea pentru numarul de zile care este multiplu de 10 si adunam restul de zile
    varInchiriere = (((10000 * multipliiDe10) * (100-reducere)/100) + (numarZile-multipliiDe10) * 10000)/ DOLAR;

    varTotal = varMachiaj + varMancare + varBautura + varCazare + varAutocare + varInchiriere;

    //salvam preturile
    Pretul.setPretInchiriere(varInchiriere); //modificam in functie de numarul de zile
    Pretul.setPretTotal(varTotal); //modificam in functie de numarul de zile
}

void scriuPreturile(){
    try{
        ofstream MyFile;
        MyFile.open("w-preturiPerioade.csv");

        if(!MyFile.is_open()){
            throw "Fisierul nu a fost deschis!";
        }

        int varMachiaj=0, varMancare=0, varBautura=0, varCazare=0, varAutocare=0, varInchiriere=0, varTotal=0;
        int numarZile = 0;

        MyFile << "Preturile sunt afisate in $ cu urmatorul curs: 1 $ = 4.63 RON\n";
        MyFile << "Zile,Machiaj,Mancare si apa,Cazare,Transport,Inchiriere spatiu, Total\n";

        //calculam pretul pentru fiecare numar de zile cerut si afisam in csv

        calculamPeZile(30,varMachiaj,varMancare,
                       varBautura, varCazare, varAutocare,
                       varInchiriere, varTotal);

        MyFile << "30,"<< varMachiaj << "," << varMancare + varBautura << ","
                << varCazare << "," << varAutocare << ","
                << varInchiriere << "," << varTotal << "," <<"\n";

        calculamPeZile(45,varMachiaj,varMancare,
                       varBautura, varCazare, varAutocare,
                       varInchiriere, varTotal);

        MyFile << "45,"<< varMachiaj << "," << varMancare + varBautura << ","
                << varCazare << "," << varAutocare << ","
                << varInchiriere << "," << varTotal << "," <<"\n";

        calculamPeZile(60,varMachiaj,varMancare,
                       varBautura, varCazare, varAutocare,
                       varInchiriere, varTotal);

        MyFile << "60,"<< varMachiaj << "," << varMancare + varBautura << ","
                << varCazare << "," << varAutocare << ","
                <<varInchiriere << "," << varTotal << "," <<"\n";

        calculamPeZile(100,varMachiaj,varMancare,
                       varBautura, varCazare, varAutocare,
                       varInchiriere, varTotal);

        MyFile << "100,"<< varMachiaj << "," << varMancare + varBautura << ","
                << varCazare << "," << varAutocare << ","
                << varInchiriere << "," << varTotal << "," <<"\n";

        MyFile.close();
    }
    catch (string x){
        cout << "Programul nu a rulat corespunzator deoarece ";
        cout << x << "\n";
    }
}

//folosim mai jos pentru a nu avea un fel de mancare in 2 zile
void facUnu(int vector[9]){
    int i;
    for(i = 0; i < 9; i++){
        vector[i] = 1;
    }
}

//pentru a nu repeta aceasta structura de 3 ori am declarat-o aici
void modificVector(int tinCont[9], int &random, int varDieta, int auxDieta){
    random = rand() % varDieta + auxDieta;
    while(tinCont[random] == 0){
        random = rand() % varDieta + auxDieta;
    }
    tinCont[random] = 0;
}

void scriuMeniu(){
    try{
        ofstream MyFile;
        MyFile.open("w-meniuZile.csv");

        if(!MyFile.is_open()){
            throw "Fisierul folosit in functia scriuMeniu nu a fost deschis!";
        }

        //varDieta si auxDieta ajuta la determinarea felurile pe care le pot manca oamenii
        //aux tine minte tipul de dieta
        int random, i, j, aux = -1, varDieta, auxDieta;
        int tinContCiorba[9], tinContPrincipal[9], tinContDesert[9]; //folosim vectorul asta sa ne asiguram ca nu se repeta mancarea

        string ciorbe[9] = {"Ciorba de perisoare", "Ciorba de vacuta", "Ciorba de pui",
                            "Ciorba de legume", "Supa de fasole vegetariana si orz", "Supa crema de legume",
                            "Ciorba de peste", "Ciorba de fasole cu tarhon", "Supa de peste"};

        string felPrincipal[9] = {"Snitel cu piure", "Sarmalute cu mamaliga", "Chiftele cu orez",
                                  "Sarmalute cu hribi si malai", "Ratatouille", "Mancare de cartofi",
                                  "Crap la cuptor cu legume","Dorada pe sare la cuptor", "Somon pajit"};

        string desert[8] = {"Tort de ciocolata", "Inghetata cu caramel", "Profiterol",
                            "Tort cu lamaie", "Cicocolata vegana", "Salata de fructe",
                            "Placinta de morcovi", "Dulceata de capsuni"};

        string dieta[3] = {"Apt sa mnanance orice", "Vegetarian", "Flexitarian"};

        MyFile << "Zi,Dieta,Ciorba/Supa, Fel principal, Desert\n";

        for(i = 1; i <= 9; i++){
            if((i-1)%3 == 0){
                aux++;
                facUnu(tinContCiorba);
                facUnu(tinContPrincipal);
                facUnu(tinContDesert);
            }
            MyFile << (i % 3 + 1) << ",";
            MyFile << dieta[aux] << ",";

            switch (aux) {
                case 0: //apt sa manance orice
                    //poate mancare oricare din cele 9 feluri
                    varDieta = 9;
                    auxDieta = 0;
                    break;

                case 1: //vegetarian
                    //poate manca doar din felurile 3, 4, 5
                    varDieta = 3;
                    auxDieta = 3;
                    break;

                case 2: //flexitarian
                    //poate manca doar din felurile 6,7,8
                    varDieta = 3;
                    auxDieta = 6;
                    break;
            }

            modificVector(tinContCiorba, random, varDieta, auxDieta);
            MyFile << ciorbe[random] << ",";

            modificVector(tinContPrincipal, random, varDieta, auxDieta);
            MyFile << felPrincipal[random] << ",";

            modificVector(tinContDesert, random, varDieta, auxDieta);
            MyFile << desert[random] << "\n";

        }
    }
    catch (string x){
        cout << "Programul nu a rulat corespunzator deoarece ";
        cout << x << "\n";
    }
};

//am incercat sa folosesc un API pentru traducerea automata a fisierelor
/*string translate(const string& text, const string& source_language, const string& target_language)
{
    string api_key = "AIzaSyCMb3Hj8bi2_YHrbYd-6QCC5A_KYC8cR8M";
    string url = "https://translation.googleapis.com/language/translate/v2?q=" + text + "&source=" + source_language + "&target=" + target_language + "&key=" + api_key;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return std::string();
}*/


void traducereAutomata(char x[1000]){
    ifstream MyFile;
    MyFile.open(x);

    ofstream tempFile("temp.csv");

    string line;

    if(!MyFile.is_open()){
        throw "Fisierul folosit in functia generezCastComplet() nu a fost deschis!";
    }
    if(!tempFile.is_open()){
        throw "Fisierul temporar nu a fost deschis!";
    }

    while (!MyFile.eof()){
        getline(MyFile, line);
        //translate(line,"ro","en");
        tempFile << line << "\n";
    }

    MyFile.close();
    tempFile.close();

    // Stergem fisierul vechi
    remove(x);
    // Redenum fisierul nou
    rename("temp.csv", x);
}

int main() {
    int limba;
    cout << "Choose language/Alege limba:\n1-English\n2-Romana\n";
    cin >> limba;
    castInitial();
    figuranti();
    finisaje();
    generezCastComplet();
    scriuPreturile();
    scriuMeniu();

    /*if(limba == 1){
        traducereAutomata("w-preturiPerioade.csv");
        traducereAutomata("w-meniuZile.csv");
    }*/
    return 0;
}
