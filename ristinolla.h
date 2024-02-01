#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define PELAAJA 'X'         
#define TIETOKONE 'O' 

char kentta[3][3];                                 //Pelikenttä array

void nollaaKentta();                               //Nollaa pelikentän muistin
void tulostaKentta(char kentta[3][3]);             //Tulostaa pelikentän
int vapaitaRuutuja();                              //Palauttaa vapaiden ruutujan määrän
void pelaajanVuoro();                              //Kysyy mihin X laitetaan
void tietokoneenVuoro();                           //Arpoo vastustajan siirron
char voittaja();                                   //Palauttaa voittajan
void tulostaaVoittajan(char);                      //Tulostaa voittajan
void tiktaktoe();                                  //Aloittaa pelin

//Täyttää kentän arvot tyhjällä "välilyönnillä".
void nollaaKentta()
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         kentta[i][j] = ' ';
      }
   }
}

//Tulostaa pelikentän.
void tulostaKentta(char kentta[3][3])
{   
    printf("\e[1;1H\e[2J");             //Tyjentää näytön
    printf("-------------\n");
    for (int i = 0; i < 3; i++) 
      {
        printf("| %c | %c | %c |\n", kentta[i][0], kentta[i][1], kentta[i][2]);
        printf("-------------\n");
      }
}

//Tarkastaa vapaiden ruutujen määrä.
int vapaitaRuutuja()
{
   int freeSpaces = 9;

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         if(kentta[i][j] != ' ')
         {
            freeSpaces--;
         }
      }
   }
   return freeSpaces;
}

//Ottaa pelaajan siirron ja tarkastaa onko se laillinen.
void pelaajanVuoro()
{
   int x,y;

   do
   {
      printf("Anna rivi #(1-3): ");
      scanf("%d", &x);
      x--;
      printf("Anna sarake #(1-3): ");
      scanf("%d", &y);
      y--;

      if(kentta[x][y] != ' ')
      {
         printf("Väärä valinta!\n");
      }
      else
      {
         kentta[x][y] = PELAAJA;
         break;
      }
   } while (kentta[x][y] != ' ');
   
}

//Arpoo tietokoneen siirron
void tietokoneenVuoro()
{
   //Arpoo tietokoneen vastauksen.
   srand(time(0));
   int x;
   int y;

   if(vapaitaRuutuja() > 0)
   {
      do
      {
         x = rand() % 3;
         y = rand() % 3;
      } while (kentta[x][y] != ' ');
      
      kentta[x][y] = TIETOKONE;
   }
   
}

//Tarkastaa löytyykö kolmen suora eli voittaja.
char voittaja()
{
   //Tarkastaa rivit
   for(int i = 0; i < 3; i++)
   {
      if(kentta[i][0] == kentta[i][1] && kentta[i][0] == kentta[i][2])
      {
         return kentta[i][0];
      }
   }
   //Tarkastaa sarakkeet
   for(int i = 0; i < 3; i++)
   {
      if(kentta[0][i] == kentta[1][i] && kentta[0][i] == kentta[2][i])
      {
         return kentta[0][i];
      }
   }
   //Tarkastaa viistot rivit
   if(kentta[0][0] == kentta[1][1] && kentta[0][0] == kentta[2][2])
   {
      return kentta[0][0];
   }
   if(kentta[0][2] == kentta[1][1] && kentta[0][2] == kentta[2][0])
   {
      return kentta[0][2];
   }

   return ' ';
}

//Tulostaa voittajan tai tasapelin
void tulostaaVoittajan(char Voittaja)
{
   if(Voittaja == PELAAJA)
   {
      printf("VOITIT TIETOKONEEN!");
   }
   else if(Voittaja == TIETOKONE)
   {
      printf("HÄVISIT!");
   }
   else{
      printf("TASAPELI!");
   }
}
//Pelilooppi jossa on tarvittavat funktiokutsut
void tiktaktoe(){
      char Voittaja = ' ';
      char uudestaan;

      do
      {
         nollaaKentta();
         
         //Tarkastaa onko Voittaja tyhjä sekä että kenttä ei ole täynnä
         while(Voittaja == ' ' && vapaitaRuutuja() != 0)
         {  
            tulostaKentta(kentta);           
            pelaajanVuoro();     
            Voittaja = voittaja();           

            if(Voittaja != ' ' || vapaitaRuutuja() == 0)
            {
               break;
            }

            tietokoneenVuoro();

            Voittaja = voittaja();     
            if(Voittaja != ' ' || vapaitaRuutuja() == 0)
            {
               break;
            }
         }
      
            tulostaKentta(kentta);
            tulostaaVoittajan(Voittaja);

            printf("\nUusi peli = (U)+ Enter : lopeta = peli Enter ");
            scanf("%c", &uudestaan);
            uudestaan = toupper(getchar());

            //Nollataan vanhan pelin tiedot
            nollaaKentta();               //
            vapaitaRuutuja();             //
            Voittaja = ' ';               //

      }while (uudestaan == 'U');

      printf("\nHeippa!");

}    

