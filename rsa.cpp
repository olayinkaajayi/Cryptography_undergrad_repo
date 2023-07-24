#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int choosePrime();
unsigned long long GetRand();
unsigned long long ModExp( unsigned long long,unsigned long long,unsigned long long);
int gcd(int,int);
int InvF(int,int);
long assignNum(char);
char assignChar(int);
void split(long,long &,long &);




int main()
{
  int response;
  do
  {
    cout <<"\nWELCOME!\nTHIS IS AN RSA ENCRYPTION PROGRAM.\nFOR EFFECTIVE USE, KINDLY FOLLOW THE INSTRUCTION. THANK YOU.\nENTER '1' TO ENCRYPT(OR GENERATE NEW KEY), OR '0' TO DECRYPT.\nCHOICE: ";
    int /* p[2],*/N;
    long const p[2]= {83,109};
    int e,d;//THE ENCRYPTING AND DECRYPTING EXPONENTS
    cin>> response;
    
    if(response==1)
    {
      cout <<"\n\nDO YOU ALREADY GAVE A KEY? IF YES ENTER '1', ELSE ENTER '0' TO GENERATE A NEW KEY.\nCHOICE: ";
      cin>>response;
      
      
      
      if(response==0)
      {
        redo:while(response!=1)
        {
          for(int i=0; i<=1; i++)
          {
            // p[i]= choosePrime();
          }
          
          if(((p[0]*p[1])<8989) ||(p[0]==p[1])||((p[0]*p[1])>9999))
            goto redo;
          cout <<"\n\nDO YOU PREFER " <<p[0] <<" AND " <<p[1] <<" FOR YOUR PRIMES? ENTER '1' IN AGREEMENT, '0' OTHERWISE.\nDECISION: "; cin>> response;
        }
        
        N= p[0]*p[1];          
        int phiN=(p[0]-1)*(p[1]-1), E[5], j=0;
        for(int i=3; i<=(phiN-1); i++)
        {
          if(gcd(i,phiN)==1)
          {
            E[j]= i;
            j++;
            if(j==4)
              break;
          }
        }
        
        
        cout <<"\n\nPLEASE SELECT ONE OF THE NUMBERS BELOW FOR YOUR ENCRYPTING EXPONENT\n";
        
        
        for(int i=0; i<=3; i++)
        {
          cout <<"  " <<E[i];
        }
        
        cout  <<"\nENTER e: ";
        cin >>e;
        
        d= InvF(e,phiN);
        
        cout <<"\n\n(" <<e <<"," <<N <<") AND (" <<d <<"," <<N <<") ARE YOUR PUBLIC AND PRIVATE KEYS RESPECTIVELY. THE PRIVATE KEY IS HIGHLY CONFIDENTIAL!!!";
        
      }
      else
      {
        cout <<"\n\nENTER THE VALUE FOR 'e' AND 'n' RESPECTIVELY.\ne= "; cin>>e;
        
        cout <<"n= "; cin>>N;
        
      }  
      
      cout <<"\n\nENTER '1' TO PROCEED WITH ENCRYPTION, '0' OTGERWISE\nDECISION: "; cin>> response;
      
      if(response!=1)
      {
        cout <<"\n\nTHANK YOU FOR GENERATING YOUR KEYS....";
        exit(0);
        
      }
      
      
      char alp[1039999], watch='a';
      unsigned long long count=0;
      cout <<"\n\nKINDLY PROCEED TO ENTER THE MESSAGE TO BE ENCRYPTED. ENTER '@' AT THE END OF YOUR MESSAGE:\n\n" ;
      
      while(watch!='@')
      {
        cin>> watch;
        if(watch=='@')
          break;
        alp[count]= watch;
        ++count;
      }
      
      if((count%2)==1)
      {
        ++count;
        alp[count]= '.';
      }
      
      unsigned long long i, r, last=(count/2)-1;
      long n[count/2], num[count];
      
      for(i=count-1, r= 0; i>=1, r<=last; i= i-2, r++)
      {
        char trans1= alp[i-1], trans2= alp[i];
        n[r]= (assignNum(trans1)*100)+assignNum(trans2);
        
        
        n[r]= ModExp(n[r],N,e);
        
        split(n[r], num[i-1], num[i]);
        
      }
      
      //THE CIPHER TEXT:
      cout <<"\n\nTHE CIPHER TEXT IS:\n\n";
      for(i=0; i<=(count-1) ; i++)
      {
        cout << assignChar(num[i]);
        
      }
      
    }
    
    else
    {
      cout <<"\nPROCEED TO INPIT THE DETAILS OF YOUR PRIVATE KEY.\nENTER THE VALUE FOR 'd' AND 'n' RESPECTIVELY." <<endl <<"d= ";
      
      cin>>d;
      cout <<"n= ";
      cin>>N;
      
      char alp[1039999], watch='a';
      unsigned long long count=0;
      cout <<"\n\nKINDLY PROCEED TO ENTER THE MESSAGE TO BE DECRYPTED. ENTER '@' AT THE END OF YOUR MESSAGE:\n\n" ;
      
      while(watch!='@')
      {
        cin>> watch;
        if(watch=='@')
          break;
        alp[count]= watch;
        ++count;
      }
      
      if((count%2)==1)
        ++count;
      
      
      unsigned long long i, r, last=(count/2)-1;
      long n[count/2], num[count];
      
      for(i=count-1, r= 0; i>=1, r<=last; i= i-2, r++)
      {
        char trans1= alp[i-1], trans2= alp[i];
        n[r]= (assignNum(trans1)*100)+assignNum(trans2);
        
        
        n[r]= ModExp(n[r],N,d);
        
        split(n[r], num[i-1], num[i]);
        
      }
      
      //THE PLAIN TEXT:
      cout <<"\n\nTHE PLAIN TEXT IS:\n\n";
      for(i=0; i<=(count-1) ; i++)
      {
        cout << assignChar(num[i]);
        
      }
      
    }
    
    cout <<"\n\nDO YOU WISH TO UNDERGO THE PROCESS AGAIN?\nENTER '1' FOR YES, '0' OTHERWISE: ";
    cin >>response;
  }
  while(response !=0);
  
  
  
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
  
  return (rand()%991)+9;
  
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
int gcd(int s,int r)
{
  while(s != r)
  {
    if(s>r)
      s -= r;
    else if(r>s)
      r -= s;
    
  }
  
  return s;
}


//###################
int InvF(int q, int r)
{
  
  int d, ans;
  for(d=1; d<r; d++)
  {
    ans= (q*d)%r;
    if(ans == 1)
      break;
  }
  
  
  return d;
  
}

//###################
long assignNum(char alphTrans)
{
  long x;
  switch(alphTrans)
  {
  case '~': x=0;break;
  case '!': x=1;break;
  case '"': x=2;break;
  case '#': x=3;break;
  case '$': x=4;break;
  case '%': x=5;break;
  case '&': x=6;break;
  case '\'': x=7;break;
  case '(': x=8;break;
  case ')': x=9;break;
  case '*': x=10;break;
  case '+': x=11;break;
  case ',': x=12;break;
  case '-': x=13;break;
  case '.': x=14;break;
  case '/': x=15;break;
  case '0': x=16;break;
  case '1': x=17 ;break;
  case '2': x=18;break;
  case '3': x=19;break;
  case '4': x=20;break;
  case '5': x=21;break;
  case '6': x=22;break;
  case '7': x=23;break;
  case '8': x=24;break;
  case '9': x=25;break;
  case ':': x=26;break;
  case ';': x=27;break;
  case '<': x=28;break;
  case '=': x=29;break;
  case '>': x=30;break;
  case '?': x=31;break;
  case 'A': x=32;break;
  case 'B': x=33;break;
  case 'C': x=34;break;
  case 'D': x=35;break;
  case 'E': x=36;break;
  case 'F': x=37;break;
  case 'G': x=38;break;
  case 'H': x=39;break;
  case 'I': x=40;break;
  case 'J': x=41;break;
  case 'K': x=42;break;
  case 'L': x=43;break;
  case 'M': x=44;break;
  case 'N': x=45;break;
  case 'O': x=46;break;
  case 'P': x=47;break;
  case 'Q': x=48;break;
  case 'R': x=49;break;
  case 'S': x=50;break;
  case 'T': x=51;break;
  case 'U': x=52;break;
  case 'V': x=53;break;
  case 'W': x=54;break;
  case 'X': x=55;break;
  case 'Y': x=56;break;
  case 'Z': x=57 ;break;
  case '[': x=58;break;
  case '\\': x=59;break;
  case ']': x=60;break;
  case '^': x=61;break;
  case '_': x=62;break;
  case '`': x=63;break;
  case 'a': x=64;break;
  case 'b': x=65;break;
  case 'c': x=66;break;
  case 'd': x=67 ;break;
  case 'e': x=68 ;break;
  case 'f': x=69 ;break;
  case 'g': x= 70 ;break;
  case 'h': x= 71 ;break;
  case 'i': x= 72 ;break;
  case 'j': x= 73 ;break; 
  case 'k': x=74 ;break;
  case 'l': x=75 ;break;
  case 'm': x=76 ;break;
  case 'n': x=77 ;break;
  case 'o': x=78 ;break;
  case 'p': x=79 ;break;
  case 'q': x=80;break;
  case 'r': x=81;break;
  case 's': x=82;break;
  case 't': x=83;break;
  case 'u': x=84;break;
  case 'v': x=85;break;
  case 'w': x=86;break;
  case 'x': x=87 ;break;
  case 'y': x=88;break;
  case 'z': x=89;break;
  case '{': x=90;break;
  case '|': x=91;break;
  case '}': x=92;break;
  //????????????????????
  case 'ˆ': x=93;break;//136
  case '¬': x=94;break;//172
  case '˜': x=95;break;//152
  case 'º': x=96;break;//186
  case '²': x=97;break;//178
  case '³': x=98;break;//179
  case '¹': x=99;break;//185
  //default:
  }
  
  return x;
}






//###################
char assignChar(int numTrans)
{
  char x;
  switch(numTrans)
  {
  case 0:  x=' ';break; 
  case 1:  x='!';break;
  case 2:  x='"';break;
  case 3:  x='#';break;
  case 4:  x='$';break;
  case 5:  x='%';break;
  case 6:  x='&';break;
  case 7:  x='\'';break;
  case 8:  x='(';break;
  case 9:  x=')';break;
  case 10:  x='*';break;
  case 11: x='+';break;
  case 12: x=',';break;
  case 13: x='-';break;
  case 14: x='.';break;
  case 15: x='/';break;
  case 16: x='0';break;
  case 17: x='1';break;
  case 18: x='2';break;
  case 19: x='3';break;
  case 20: x='4';break;
  case 21: x='5';break;
  case 22: x='6';break;
  case 23: x='7';break;
  case 24: x='8';break;
  case 25: x='9';break;
  case 26: x=':';break;
  case 27: x=';';break;
  case 28: x='<';break;
  case 29: x='=';break;
  case 30: x='>';break;
  case 31: x='?';break;
  case 32: x='A';break;
  case 33: x='B';break;
  case 34: x='C';break;
  case 35: x='D';break;
  case 36: x='E';break;
  case 37: x='F';break;
  case 38: x='G';break;
  case 39: x='H';break;
  case 40: x='I';break;
  case 41: x='J';break;
  case 42: x='K';break;
  case 43: x='L';break;
  case 44: x='M';break;
  case 45: x='N';break;
  case 46: x='O';break;
  case 47: x='P';break;
  case 48: x='Q';break;
  case 49: x='R';break;
  case 50: x='S';break;
  case 51: x='T';break;
  case 52: x='U';break;
  case 53: x='V';break;
  case 54: x='W';break;
  case 55: x='X';break;
  case 56: x='Y';break;
  case 57: x='Z';break;
  case 58: x='[';break;
  case 59: x='\\';break;
  case 60: x=']';break;
  case 61: x='^';break;
  case 62: x='_';break;
  case 63: x='`';break;
  case 64: x='a';break;
  case 65: x='b';break;
  case 66: x='c';break;
  case 67: x='d';break;   
  case 68: x='e' ;break;
  case 69: x='f' ;break;
  case 70: x='g' ;break;
  case 71: x='h' ;break;
  case 72: x='i' ;break;
  case 73: x='j' ;break;  
  case 74: x='k';break;
  case 75: x='l';break;
  case 76: x='m';break;
  case 77: x='n';break;
  case 78: x='o';break;
  case 79: x='p';break;
  case 80: x='q';break;
  case 81: x='r';break;
  case 82: x='s';break;
  case 83: x='t';break;
  case 84: x='u';break;
  case 85: x='v';break;
  case 86: x='w';break;
  case 87: x='x';break;
  case 88: x='y';break;
  case 89: x='z';break;
  case 90: x='{';break;
  case 91: x='|';break;
  case 92: x='}';break;
  //????????????????????
  case 93: x='ˆ';break;
  case 94: x='¬';break;
  case 95: x='˜';break;
  case 96: x='º';break;
  case 97: x='²';break;
  case 98: x='³';break;
  case 99: x='¹';break;
  //default: x='£';break;
  }
  
  return x;
}



void split(long nnumber, long &a, long &c)
{
  
  
  //initialisation of counter
  int ncounter=2; 
  
  while(0<=ncounter)
  {//The computation below extracts the digits in two's from the 4 digit variable "nnumber" one after the other
    if(ncounter==2)
    {
      a= nnumber/pow(10,ncounter);
      
      nnumber -= pow(10,ncounter)*a;
    }
    else
    {
      c= nnumber/pow(10,ncounter);
      
      nnumber -= pow(10,ncounter)*c;
    }
    ncounter -=2;
  }
  
  
}

