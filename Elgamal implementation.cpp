#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
int choosePrime();
unsigned long long GetRand();
unsigned long long ModExp( unsigned long long base,unsigned long long modulo,unsigned long long exponent);
int factor(int,int);
int generator(int,int,int[],int);
long assignNum(char);
char assignChar(int);

int main()
{
    int choice;
    do
    {

        cout <<"\n\nWELCOME! THIS IS A PROGRAM THAT IMPLEMENTS THE EL GAMAL CRYPTOSYSTEM.\n\nYOU ARE ADVICED TO FOLLOW THE INSTRUCTIONS FOR AN EFFICIENT RESULT.";
        cout <<"ENTER 1 TO ENCRYPT OR 0 TO DECRYPT.\nCHOICE= ";
        cin >>choice;
//BEGINING OF ENCRYPTION
        if(choice==1)
        {
            int number,publicKeyAlice=0,privateKeyBob=0;

            cout <<"\n\nPLEASE DO YOU ALREADY HAVE A KEY TO BE USED FOR ENCRYPTION? ENTER 1 FOR YES OTHERWISE ENTER 0 SO YOU CAN GENERATE A NEW KEY.\nCHOICE= ";
            cin >>choice;
            if (choice==0)
            {
//SELECTING PRIME
                do
                {
                    number= choosePrime();
                    cout <<"\n\nDO YOU PREFER " <<number <<" AS THE PRIME TO BE USED?\nENTER 1 FOR YES AND 0 FOR NO\nCHOICE= ";
                    cin >>choice;
                }
                while(choice==0);
//END OF SELECTION OF PRIME



//BEGINING OF FACTORING
                int phiNumber= number-1, lastFactor=1, cnt=-1, Factor[phiNumber], no_of_factors=0;
                while(lastFactor != phiNumber)
                {
                    lastFactor= factor(phiNumber,lastFactor);
                    Factor[++cnt]= lastFactor;
                    ++no_of_factors;
                }
//END OF FACTORING

//CHOOSING A GENERATOR
                int Generator, starter=2;
                do
                {
                    Generator= generator(number,no_of_factors,Factor,starter);
                    cout <<"\nDO YOU PREFER " <<Generator <<" AS THE DESIRED GENERATOR?\nENTER 1 FOR YES AND 0 FOR NO\nCHOICE= ";
                    starter= Generator+1;
                    cin >>choice;
                }
                while(choice==0);

//END OF CHOOSING THE GENERATOR


//CHOOSING PRIVATE KEY
                cout <<"PLEASE ENTER ANY CHOICE OF NUMBER IN THE RANGE OF 2 TO " <<phiNumber-1 <<" WHICH WILL SERVE AS YOUR PRIVATE KEY.\nENTER CHOICE OF PRIVATE KEY: ";
                cin >>privateKeyBob;

                int publicKeyBob= ModExp(Generator,number,privateKeyBob);
                cout <<"\n\nYOUR PUBLIC KEY IS " <<publicKeyBob <<endl;
//END OF CHOOSING PRIVATE KEY
            }
//USER IS TO ENTER KEY DETAILS
            else
            {
                cout <<"PLEASE PROVIDE THE REQUESTED DETAILS BELOW.\n";
                cout <<"\nPRIME MODULO= ";
                cin >>number;
                cout <<"\nYOUR PRIVATE KEY= ";
                cin >>privateKeyBob;
                cout <<"\nPUBLIC KEY OF YOUR ALLY= ";
                cin >>publicKeyAlice;
            }
//END OF KEY DETAILS
            cout <<"\n\nDO YOU WISH TO NOW PROCEED WITH ENCRYPTION? ENTER 1 FOR YES 0 OTHERWISE.\nCHOICE= ";
            cin >>choice;
            if(choice==0)
            {
                cout<<"\n\nTHANKS FOR GENERATING YOUR KEYS!";
                exit(0);
            }

//ASK FOR ALICE KEY IF NOT PROVIDED
            if(publicKeyAlice==0)
            {
                cout<<"\nPLEASE ENTER PUBLIC KEY OF YOUR ALLY= ";
                cin >>publicKeyAlice;
            }


//ENTERING OF TEXT
            cout <<"PROCEED TO ENTER THE TEXT TO BE ENCRYPTED. INPUT # AT THE END OF YOUR TEXT.\n\n";
            char alp[1039999], watch='a', trans1;
            unsigned long long count=0;
            long long num[103999], trans2;
            while(watch!='#')
            {
                cin>> watch;
                if(watch=='#')
                    break;
                alp[count]= watch;
                trans1= alp[count];
                num[count]= assignNum(trans1);
                trans2= (num[count]* ModExp(publicKeyAlice,number,privateKeyBob))%number;
                alp[count]= assignChar(trans2);
                ++count;
            }
            cout <<"\n\nTHE CIPHERTEXT IS:\n\n";
            for(unsigned long long i=0; i<count; i++)
            {
                cout <<alp[i];
            }


        }
//END OF ENCRYPTION


//BEGINING OF DECRYPTION
        else
        {
//ENTERING KEY DETAILS
            long long number,privateKeyAlice,publicKeyBob;
            cout <<"\n\nPLEASE ENTER THE DETAILS REQUESTED BELOW:\n\n";
            cout <<"\nPRIME MODULO= ";
            cin >>number;
            cout <<"\nYOUR ALLY'S PUBLIC KEY= ";
            cin >>publicKeyBob;
            cout <<"\nYOUR PRIVATE KEY= ";
            cin >>privateKeyAlice;
//END OF KEY DETAILS

//COMPUTING OF EPHIMERAL KEY AND IT'S INVERSE
            long ephmKey= ModExp(publicKeyBob,number,privateKeyAlice);
            long INVephmKey;

            for(int i=2; 1<number; i++)
            {
                if(((ephmKey*i)%number)==1)
                {
                    INVephmKey= i;
                    break;
                }
            }

//END OF COMPUTATION OF EPHIMERAL KEY

//ENTERING OF CIPHERTEXT
            cout <<"PROCEED TO ENTER THE CIPHERTEXT TO BE DECRYPTED. INPUT # AT THE END OF YOUR TEXT.\n\n";
            char alp[1039999], watch='a', trans1;
            unsigned long long count=0;
            long long num[103999], trans2;
            while(watch!='#')
            {
                cin>> watch;
                if(watch=='#')
                    break;
                alp[count]= watch;
                trans1= alp[count];
                num[count]= assignNum(trans1);
                trans2= (INVephmKey*num[count])%number;
                alp[count]= assignChar(trans2);
                ++count;
            }
            cout <<"\n\nTHE PLAINTEXT IS:\n\n";
            for(unsigned long long i=0; i<count; i++)
            {
                cout <<alp[i];
            }
//END OF CIPHERTEXT



        }

//END OF DECRYPTION

        cout <<"\n\nDO YOU WISH TO CARRYOUT THE PROCESS AGAIN? ENTER 1 FOR YES AND 0 FOR NO.\nCHOICE= ";
        cin >>choice;
    }
    while(choice==1);





    return 0;
}













//###################
int choosePrime()
{

    srand(time(0));

    unsigned long long answer=0, value;


    while(answer != 2)
    {
        value= GetRand();
        answer= ModExp(2,value,value);

    }

    return value;
}

//###################
unsigned long long GetRand()
{

    return (rand()%41)+52;

}

//###################
unsigned long long ModExp( unsigned long long a, unsigned long long n, unsigned long long p)
{

    unsigned long long excess=1;

    while(p != 1)
    {

        if((p%2)==1)
        {

            excess= (excess*a)%n;

        }

        a= (a*a)%n;
        p = p/2;

        if(p==1)
        {
            a=(excess*a)%n;

        }

    }

    ;
    return a;

}



//###################
int factor(int Number, int lastfactor)
{
    for(int j= lastfactor+1; j<=Number; j++)
    {
        if((Number%j)==0)
        {
            //++lastfactor;
            return j;
        }
    }

}

//###################
int generator(int Number,int cnt,int Factor[],int starter)
{
    int phiNumber= Number-1;
    for(int gen=starter; gen<=(phiNumber-1); gen++)
    {
        for(int j=0; j<=(cnt-2); j++)
        {
            //cnt-2 allows me exclude the phiNumber
            int result= ModExp(gen,Number,phiNumber/Factor[j]);
            if(result==1)
            {
                break;
            }
            if(j==cnt-2)
            {
                return gen;
            }
        }
    }
}




//###################
long assignNum(char alphTrans)
{
    long x;
    switch(alphTrans)
    {
    case '~': x=0;break;
    case 'A':x=1;break;
    case 'B':x=2;break;
    case 'C':x=3;break;
    case 'D':x=4;break;
    case 'E':x=5;break;
    case 'F':x=6;break;
    case 'G':x=7;break;
    case 'H':x=8;break;
    case 'I':x=9;break;
    case 'J':x=10;break;
    case 'K':x=11;break;
    case 'L':x=12;break;
    case 'M':x=13;break;
    case 'N':x=14;break;
    case 'O':x=15;break;
    case 'P':x=16;break;
    case 'Q':x=17;break;
    case 'R':x=18;break;
    case 'S':x=19;break;
    case 'T':x=20;break;
    case 'U':x=21;break;
    case 'V':x=22;break;
    case 'W':x=23;break;
    case 'X':x=24;break;
    case 'Y':x=25;break;
    case 'Z':x=26;break;
    case 'a':x=27;break;
    case 'b':x=28;break;
    case 'c':x=29;break;
    case 'd':x=30;break;
    case 'e':x=31;break;
    case 'f':x=32;break;
    case 'g':x=33;break;
    case 'h':x=34;break;
    case 'i':x=35;break;
    case 'j':x=36;break;
    case 'k':x=37;break;
    case 'l':x=38;break;
    case 'm':x=39;break;
    case 'n':x=40;break;
    case 'o':x=41;break;
    case 'p':x=42;break;
    case 'q':x=43;break;
    case 'r':x=44;break;
    case 's':x=45;break;
    case 't':x=46;break;
    case 'u':x=47;break;
    case 'v':x=48;break;
    case 'w':x=49;break;
    case 'x':x=50;break;
    case 'y':x=51;break;
    case 'z':x=52;break;
//**************************
    case '[':x=53;break;
    case '\\':x=54;break;
    case ']':x=55;break;
    case '^':x=56;break;
    case '_':x=57;break;
    case '`':x=58;break;
    case '!': x=59;break;
    case '"': x=60;break;
    case '@': x=61;break;
    case '$': x=62;break;
    case '%': x=63;break;
    case '&': x=64;break;
    case '\'':x=65;break;
    case '(': x=66;break;
    case ')': x=67;break;
    case '*':x=68;break;
    case '+':x=69;break;
    case ',':x=70;break;
    case '-':x=71;break;
    case '.':x=72;break;
    case '/':x=73;break;
    case '0':x=74;break;
    case '1':x=75;break;
    case '2':x=76;break;
    case '3':x=77;break;
    case '4':x=78;break;
    case '5':x=79;break;
    case '6':x=80;break;
    case '7':x=81;break;
    case '8':x=82;break;
    case '9':x=83;break;
    case ':':x=84;break;
    case ';':x=85;break;
    case '<':x=86;break;
    case '=':x=87;break;
    case '>':x=88;break;
    case '?':x=89;break;
    case '{':x=90;break;
    case '|':x=91;break;
    case '}':x=92;break;

    }

    return x;
}






//###################
char assignChar(int numTrans)
{
    char x;
    switch(numTrans)
    {
    case 0:x='~';break;
    case 1:x='A';break;
    case 2:x='B';break;
    case 3:x='C';break;
    case 4:x='D';break;
    case 5:x='E';break;
    case 6:x='F';break;
    case 7:x='G';break;
    case 8:x='H';break;
    case 9:x='I';break;
    case 10:x='J';break;
    case 11:x='K';break;
    case 12:x='L';break;
    case 13:x='M';break;
    case 14:x='N';break;
    case 15:x='O';break;
    case 16:x='P';break;
    case 17:x='Q';break;
    case 18:x='R';break;
    case 19:x='S';break;
    case 20:x='T';break;
    case 21:x='U';break;
    case 22:x='V';break;
    case 23:x='W';break;
    case 24:x='X';break;
    case 25:x='Y';break;
    case 26:x='Z';break;
    case 27:x='a';break;
    case 28:x='b';break;
    case 29:x='c';break;
    case 30:x='d';break;
    case 31:x='e';break;
    case 32:x='f';break;
    case 33:x='g';break;
    case 34:x='h';break;
    case 35:x='i';break;
    case 36:x='j';break;
    case 37:x='k';break;
    case 38:x='l';break;
    case 39:x='m';break;
    case 40:x='n';break;
    case 41:x='o';break;
    case 42:x='p';break;
    case 43:x='q';break;
    case 44:x='r';break;
    case 45:x='s';break;
    case 46:x='t';break;
    case 47:x='u';break;
    case 48:x='v';break;
    case 49:x='w';break;
    case 50:x='x';break;
    case 51:x='y';break;
    case 52:x='z';break;
//**************************
    case 53:x='[';break;
    case 54:x='\\';break;
    case 55:x=']';break;
    case 56:x='^';break;
    case 57:x='_';break;
    case 58:x='`';break;
    case 59:x='!';break;
    case 60:x='"';break;
    case 61:x='@';break;
    case 62:x='$';break;
    case 63:x='%';break;
    case 64:x='&';break;
    case 65:x='\'';break;
    case 66:x='(';break;
    case 67:x=')';break;
    case 68:x='*';break;
    case 69:x='+';break;
    case 70:x=',';break;
    case 71:x='-';break;
    case 72:x='.';break;
    case 73:x='/';break;
    case 74:x='0';break;
    case 75:x='1';break;
    case 76:x='2';break;
    case 77:x='3';break;
    case 78:x='4';break;
    case 79:x='5';break;
    case 80:x='6';break;
    case 81:x='7';break;
    case 82:x='8';break;
    case 83:x='9';break;
    case 84:x=':';break;
    case 85:x=';';break;
    case 86:x='<';break;
    case 87:x='=';break;
    case 88:x='>';break;
    case 89:x='?';break;
    case 90:x='{';break;
    case 91:x='|';break;
    case 92:x='}';break;


    }

    return x;
}

