#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;
#define tam 16


vector<string> MAR;
vector<string> MBR;
vector<string> IR;
vector<string> MQ;
vector<string> AC;
vector<string> PC;
vector<string> OPCODE;


vector<vector<string>> memoria;
vector<string> word;


class Processador{

public:

    void cicloDeBusca(){
       // MAR <- PC
       if(MAR.size() == 1){
           MAR.pop_back();
       }
        MAR.push_back(PC[0]);

        //MBR <- memoria[MAR][]
        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        MBR.push_back(inst[0]);

        //IR <-MBR
        if(IR.size() == 1){
            IR.pop_back();
        }
        IR.push_back(MBR[0]);

        //OPCODE <- IR[0:6]
        if(OPCODE.size() == 1){
            OPCODE.pop_back();
        }

        string concatenar;
        for(int i =0; i<6;i++){
            concatenar += IR[0][i];
        }

        OPCODE.push_back(concatenar);

        //MAR <- IR[7:16]
        if(MAR.size() == 1){
            MAR.pop_back();
        }

        string concatenar2;
        for(int i=0; i<6;i++){
            concatenar2 += '0';
        }
        for(int i =6; i<16;i++){
            concatenar2 += IR[0][i];
        }

        MAR.push_back(concatenar2);
    }

    void cicloDeExecucao(){

        int opcode = converterBinarioDecimal(OPCODE,6);

        switch (opcode) {
        case 10:
            cout << "loadMQ" << endl;
            loadMQ();
            break;
        case 9:
            cout << "loadMQX" << endl;
            loadMQX();
            break;
        case 33:
            cout << "storX" << endl;
            storX();
            break;
        case 1:
            cout << "loadX" << endl;
            loadX();
            break;
        case 5:
            cout << "addX" << endl;
            addX();
            break;
        case 6:
            cout << "subX" << endl;
            subX();
            break;
        case 11:
            cout << "mulX" << endl;

        //    mulX();
            break;
        case 12:
            cout << "divX" << endl;

        //    divX();
            break;
        default:
            cout<<"ERRO!!!"<< endl;
            break;
        }

    }

    int converterBinarioDecimal(vector<string> &v, int n){

        int i,j, soma=0;

        for(i=n-1,j=0;i>=0;i--,j++){
            soma += (int)(v[0][i] - 48)*pow(2,j);
        }
        return soma;
    }
    void converterDecimalBinarioString(int n){
        int temp[10];
        vector<string> bin;
        int aux;
        
        for(aux=10;aux>=0;aux--){
            if(n%2==0){
                temp[aux]=0;
                n=n/2;
            }else{
                temp[aux]=1;
                n=n/2;
            }
        }
        
        string returnstring = "";
        for (int temp = 0; temp < tem.sizeof(temp); temp++){
            returnstring += itoa(int_array[temp]);//itoa converte int em string.
       }
       
       int zeros = 16 - strlen(returnstring);
       for(int i=0;i<zeros;i++){
           returnstring+="0";
       }
        
       bin.push_back(returnstring);
        
    }
    

    // Conjunto de instruções
    
    void loadX(){
        
        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];
        
        if(AC.size() == 1){
            AC.pop_back();
        }
        AC.push_back(inst[0]);
        
    }
    void loadMQ(){

        if(AC.size() == 1){
            AC.pop_back();
        }
        AC.push_back(MQ[0]);
    }

    void loadMQX(){

        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];

        if(MBR.size() == 1){
            MBR.pop_back();
        }

        MBR.push_back(inst[0]);

        if(MQ.size() == 1){
            MQ.pop_back();
        }

        MQ.push_back(MBR[0]);
    }

    void storX(){

        int mar = converterBinarioDecimal(MAR, 16);

        if(AC.size() == 1){
            AC.pop_back();
        }

        AC.push_back(memoria[mar][0]);
    }

    void addX(){

        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(inst[0]);

        //RT <- AC
        vector<string> reg_temp;

        if(reg_temp.size() == 1){
            reg_temp.pop_back();
        }
        reg_temp.push_back(AC);

        //AC<-RT+MBR
        if(AC.size() == 1){
            AC.pop_back();
        }

        AC.push_back(reg_temp[0]+MBR[0]);

    }
    void subX(){

        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(inst[0]);

        //RT <- AC
        vector<string> reg_temp;

        if(reg_temp.size() == 1){
            reg_temp.pop_back();
        }
        reg_temp.push_back(AC);

        //AC <- RT-MBR
        if(AC.size() == 1){
            AC.pop_back();
        }

        AC.push_back(reg_temp[0]-MBR[0]);

    }

    void mulX(){

        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];
    }

    void divX(){
        int mar = converterBinarioDecimal(MAR, 16);
        vector<string> inst = memoria[mar];
        
        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(inst[0]);
        
        //AC,MQ <- AC/MBR
        if(AC.size() == 1){
            AC.pop_back();
        }

        AC.push_back(AC[0]%MBR[0]);
        MQ.push_back(MQ[0]/MBR[0]);
        
    }

};

int main()
{

    word.push_back("0010010000000000");
    memoria.push_back(word);

    Processador *cpu = new Processador;

    PC.push_back("0000000000000000");


    cpu->cicloDeBusca();
    cpu->cicloDeExecucao();

    return 0;
}
