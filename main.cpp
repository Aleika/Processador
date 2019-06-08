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

       cout << " ---- Ciclo de busca ----" << endl << endl;
       // MAR <- PC
       if(MAR.size() == 1){
           MAR.pop_back();
       }
        MAR.push_back(PC[0]);

        cout << "MAR1 = " << MAR[0] << endl;

        //MBR <- memoria[MAR][]
        int mar = converterBinarioDecimal(MAR, 16);

        cout << "Posicao da memoria " << mar << endl;
        string inst = memoria[mar][0];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        MBR.push_back(inst);

        cout << "MBR : " << MBR[0] << endl;

        //IR <-MBR
        if(IR.size() == 1){
            IR.pop_back();
        }
        IR.push_back(MBR[0]);

        cout << "INTRUCAO " << IR[0] << endl;

        //OPCODE <- IR[0:6]
        if(OPCODE.size() == 1){
            OPCODE.pop_back();
        }

        string concatenar("000000");
        for(int i =0; i<6;i++){
            concatenar[i] = IR[0][i];
        }

        OPCODE.push_back(concatenar);

        cout << "OPCODE " << OPCODE[0] << endl;

        //MAR <- IR[7:16]
        if(MAR.size() == 1){
            MAR.pop_back();
        }

        string concatenar2("0000000000000000");

        for(int i =6; i<16;i++){
            concatenar2[i] = IR[0][i];
        }

        MAR.push_back(concatenar2);

        cout << "MAR2 = " << MAR[0] << endl;

        cout << "------ Fim ciclo de busca -------- " << endl << endl;
    }

    void cicloDeExecucao(){

        cout << "------ Inicio ciclo de execucao -------- " << endl << endl;

        int opcode = converterBinarioDecimal(OPCODE,6);

        switch (opcode) {
        case 10:
            cout << "loadMQ" << endl;
            loadMQ();
            break;
        case 9:
            cout << " -----------------------------------------------------------------------------------------------------loadMQX" << endl;
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

            mulX();
            break;
        case 12:
            cout << "divX" << endl;

            divX();
            break;
        default:
            cout<<"ERRO!!!"<< endl;
            break;
        }

        cout << "------ Fim ciclo de execucao -------- " << endl << endl;

    }

    int converterBinarioDecimal(vector<string> &v, int n){

        int i,j, soma=0;

        for(i=n-1,j=0;i>=0;i--,j++){
            soma += (int)(v[0][i] - 48)*pow(2,j);
        }
        return soma;
    }

    string converterDecimalBinarioString(int n, int nBits){

        string temp("0000000000000000");

        if(nBits == 32){
           temp += "0000000000000000";
        }

        for(int i =(nBits-1);i>=0;i--){
            if(n%2==0){
                temp[i]='0';
                n=n/2;
            }else{
                temp[i]='1';
                n=n/2;
            }
        }

        return temp;
    }


    // Conjunto de instruções

    void loadX(){

        cout << "Valor de MAR " << MAR[0] << endl;
        int mar = converterBinarioDecimal(MAR, 16);
        string inst = memoria[mar][0];

        if(AC.size() == 1){
            AC.pop_back();
        }
        AC.push_back(inst);

        cout << "Valor de AC " << AC[0] << endl;

    }
    void loadMQ(){

        if(AC.size() == 1){
            AC.pop_back();
        }
        AC.push_back(MQ[0]);

        cout << "Valor AC " << AC[0] << endl;
        cout << "Valor MQ " << MQ[0] << endl;


    }

    void loadMQX(){

        int mar = converterBinarioDecimal(MAR, 16);
        string inst = memoria[mar][0];


        if(MBR.size() == 1){
            MBR.pop_back();
        }

        MBR.push_back(inst);

        cout << "Valor MBR " << MBR[0] << endl;


        if(MQ.size() == 1){
            MQ.pop_back();
        }

        MQ.push_back(MBR[0]);

        cout << "Valor MQ " << MQ[0] << endl;

    }

    void storX(){

        int mar = converterBinarioDecimal(MAR, 16);

        if(memoria[mar].size() == 1){
            memoria[mar].pop_back();
        }

        memoria[mar].push_back(AC[0]);

        cout << "Valor memoria[mar] " << memoria[mar][0] << endl;
    }

    void addX(){

        int mar = converterBinarioDecimal(MAR, 16);
        string inst = memoria[mar][0];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(inst);

        cout << "Valor MBR " << MBR[0] << endl;

        //RT <- AC
        vector<string> reg_temp;

        if(reg_temp.size() == 1){
            reg_temp.pop_back();
        }
        reg_temp.push_back(AC[0]);

        cout << "Valor AC " << reg_temp[0] << endl;


        //AC<-RT+MBR
        if(AC.size() == 1){
            AC.pop_back();
        }

        int rt = converterBinarioDecimal(reg_temp, 16);
        int mbr = converterBinarioDecimal(MBR, 16);
        int soma = rt+mbr;
        string sum = converterDecimalBinarioString(soma,16);


        AC.push_back(sum);

        cout << "Valor AC (soma) " << AC[0] << endl;

    }
    void subX(){

        int mar = converterBinarioDecimal(MAR, 16);
        string inst = memoria[mar][0];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(inst);

        cout << "Valor MBR " << MBR[0] << endl;

        //RT <- AC
        vector<string> reg_temp;

        if(reg_temp.size() == 1){
            reg_temp.pop_back();
        }
        reg_temp.push_back(AC[0]);

        cout << "Valor reg) " << reg_temp[0] << endl;

        //AC <- RT-MBR
        if(AC.size() == 1){
            AC.pop_back();
        }

        int rt = converterBinarioDecimal(reg_temp, 16);
        int mbr = converterBinarioDecimal(MBR, 16);
        int sub = rt-mbr;
        string subtracao = converterDecimalBinarioString(sub,16);

        AC.push_back(subtracao);

        cout << "Valor AC (subtracao) " << AC[0] << endl;

    }

    void mulX(){

        cout << "Valor MAR " << MAR[0] << endl;

        int mar = converterBinarioDecimal(MAR, 16);
        string inst = memoria[mar][0];

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(inst);

        cout << "Valor MBR " << MBR[0] << endl;
        cout << "Valor MQ " << MQ[0] << endl;


        vector<string> reg_temp;

        if(reg_temp.size() == 1){
            reg_temp.pop_back();
        }

        int mq = converterBinarioDecimal(MQ,16);
        int mbr = converterBinarioDecimal(MBR,16);
        //Realiza a operacao em decimal:
        int mult = mq*mbr;
        cout << "multiplicacao " << mult << endl;
        //converte o resultado pra binario:
        string MULT = converterDecimalBinarioString(mult,32);

        //RT <- MQ*MBR
        vector<string> aux;
        aux.push_back(MULT);

        if(AC.size() == 1){
            AC.pop_back();
        }

        if(MQ.size() == 1){
            MQ.pop_back();
        }

        string concatenar;
        for(int i=16; i<32;i++){
            concatenar += aux[0][i];
        }

        MQ.push_back(concatenar);

        string concatenar2;
        for(int i=0; i<16;i++){
            concatenar2 += aux[0][i];
        }

       AC.push_back(concatenar2);

        cout << "Valor MQ (mais signi) " << MQ[0] << endl;
        cout << "Valor AC (menos sign) " << AC[0] << endl;
    }

    void divX(){
        int mar = converterBinarioDecimal(MAR, 16);

        cout << "valor ende " << mar << endl;

        if(MBR.size() == 1){
            MBR.pop_back();
        }
        //MBR <- MEMORIA[MAR]
        MBR.push_back(memoria[mar][0]);

        cout << "MBR" << MBR[0] << endl;


        if(MQ.size() == 1){
            MQ.pop_back();
        }

        int ac = converterBinarioDecimal(AC, 16);
        int mbr = converterBinarioDecimal(MBR, 16);

        cout << "ac = " << ac << endl;
        cout << "mbr = " << mbr << endl;

        int resto = ac%mbr;
        int q = ac/mbr;


        cout << "resto = " << resto << endl;
        cout << "q = " << q << endl;

        //AC,MQ <- AC/MBR
        if(AC.size() == 1){
            AC.pop_back();
        }

        string AC_string = converterDecimalBinarioString(resto,16);
        string MQ_string = converterDecimalBinarioString(q,16);

        AC.push_back(AC_string);
        MQ.push_back(MQ_string);

        cout << "AC " << AC[0] << endl;
        cout << "MQ " << MQ[0] << endl;


    }

};

int main()
{

    // --------------------- Inserindo as instruções na memória ------------------------
        //LOAD MQ, 22
        word.push_back("0010010000010110");
        memoria.push_back(word);
        word.pop_back();

        //MUL 21
        word.push_back("0010110000010101");
        memoria.push_back(word);
        word.pop_back();

        //LOAD MQ
        word.push_back("0010100000000000");
        memoria.push_back(word);
        word.pop_back();

        //ADD 20
        word.push_back("0001010000010100");
        memoria.push_back(word);
        word.pop_back();

        //STOR 27
        word.push_back("1000010000011011");
        memoria.push_back(word);
        word.pop_back();

        //LOAD MQ, 24
        word.push_back("0010010000011000");
        memoria.push_back(word);
        word.pop_back();

        //MUL 25
        word.push_back("0010110000011001");
        memoria.push_back(word);
        word.pop_back();

         //LOAD MQ
        word.push_back("0010100000000000");
        memoria.push_back(word);
        word.pop_back();

        //STOR 28
        word.push_back("1000010000011100");
        memoria.push_back(word);
        word.pop_back();

        //LOAD 23
        word.push_back("0000010000010111");
        memoria.push_back(word);
        word.pop_back();

        //SUB 28
        word.push_back("0001100000011100");
        memoria.push_back(word);
        word.pop_back();

        //STOR 29
        word.push_back("1000010000011101");
        memoria.push_back(word);
        word.pop_back();

        //LOAD 23
        word.push_back("0000010000010111");
        memoria.push_back(word);
        word.pop_back();

        //SUB 28
        word.push_back("0001100000011100");
        memoria.push_back(word);
        word.pop_back();

        //STOR 29
        word.push_back("1000010000011101");
        memoria.push_back(word);
        word.pop_back();

        //LOAD 27
        word.push_back("0000010000011011");
        memoria.push_back(word);
        word.pop_back();

        //DIV 29
        word.push_back("0011000000011101");
        memoria.push_back(word);
        word.pop_back();

        //STOR 27
        word.push_back("1000010000011011");
        memoria.push_back(word);
        word.pop_back();

        //LOAD MQ
        word.push_back("0010100000000000");
        memoria.push_back(word);
        word.pop_back();

        //STOR 26
        word.push_back("1000010000011010");
        memoria.push_back(word);
        word.pop_back();



        // --------------------- Inserindo os valores das variáveis na memória ------------------

        // A = 37 (na posicao 20 da memoria)
        word.push_back("0000000000100101");
        memoria.push_back(word);
        word.pop_back();

        // B = 80 (na posicao 21 da memoria)
        word.push_back("0000000001010000");
        memoria.push_back(word);
        word.pop_back();

        // C = 23 (na posicao 22 da memoria)
        word.push_back("0000000000010111");
        memoria.push_back(word);
        word.pop_back();

        // D = 16 (na posicao 23 da memoria)
        word.push_back("0000000000010000");
        memoria.push_back(word);
        word.pop_back();

        // E = 63 (na posicao 24 da memoria)
        word.push_back("0000000000111111");
        memoria.push_back(word);
        word.pop_back();

        // F = 11 (na posicao 25 da memoria)
        word.push_back("0000000000001011");
        memoria.push_back(word);
        word.pop_back();

        // X = ? (na posicao 26 da memoria)
        word.push_back("0000000000000000");
        memoria.push_back(word);
        word.pop_back();

        //  = ? (na posicao 27 da memoria)
        word.push_back("0000000000000000");
        memoria.push_back(word);
        word.pop_back();

        //  = ? (na posicao 28 da memoria)
        word.push_back("0000000000000000");
        memoria.push_back(word);
        word.pop_back();

        //  = ? (na posicao 29 da memoria)
        word.push_back("0000000000000000");
        memoria.push_back(word);
        word.pop_back();


        Processador *cpu = new Processador;

        PC.push_back("0000000000000000");

        for(int i=0; i< 20 ; i++){
            cpu->cicloDeBusca();
            cpu->cicloDeExecucao();

            int pc = cpu->converterBinarioDecimal(PC,16);
            pc++;

            PC.pop_back();
            string pc_string = cpu->converterDecimalBinarioString(pc,16);
            PC.push_back(pc_string);

        }

        cout << endl << endl;
        cout << " --- Considerando que o resultado eh dado em modulo e X eh inteiro --- " << endl;
        cout << endl;
        cout << "No final, o valor na posicao X eh : " <<endl;
        cout << "Em binario: " << memoria[26][0] << endl;
        cout << "Em decimal: " << cpu->converterBinarioDecimal(memoria[26],16) << endl;


        return 0;

}
