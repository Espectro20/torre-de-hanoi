#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprime( int *tab, int fil, int col, int ultNum )
{
    /*
    Precondición:
    *tab    Puntero a una matriz de tipo entero.
    fil     Entero que indica el numero de filas de la matriz.
    col     Entero que indica el numero de columnas de la matriz.
    disc    Parámetro de tipo entero que indica el numero de discos usados.
    ultNum  Entero que indica el numero que esta usando el disco mas grande.
    */
    int f, c;
    int i, esp; //crea variables auxiliares para hacer funcionar el for

  
    for( c=col-1; c >= 0; c-- ) //Cantidad de discos 
    {
        for( f=0; f < fil; f++ ) //Torres
        {
            esp = ( ultNum - tab[col*f+c] )/2; //Divide cada torre entre izquierda y derecha, para establecer las coordenadas de impresión de los comodines 

// Espacios a la izquierda
            for( i=0; i < esp; i++ )
                printf( " " );

// Imprime los comodines
            for( i=0; i < tab[col*f+c]; i++ ) //Solo se ejecuta si hay comodines que imprimir
                printf( "*" );

// Espacios a la derecha
            for( i=0; i < esp; i++ )
                printf( " " );

            printf( "\t" ); //Espacios entre torres
        };

        printf( "\n" ); //Filas
    };


};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void mueveDisco( int *tab, int fil, int col, int ultNum, int filOrig, int filDest )
{
    /*
    Precondición:
    *tab  Puntero a una matriz de tipo entero.
    fil    Entero que indica el numero de filas de la matriz.
    col    Entero que indica el numero de columnas de la matriz.
    disc  Parámetro de tipo entero que indica el numero de discos usados.
    ultNum  Entero que indica el numero que esta usando el disco mas grande.
    filOrig  Entero que indica el numero de fila de la matriz en la cual hay que coger el numero/disco
    filDest  Entero que indica el numero de fila de la matriz en la cual hay que dejar el numero/disco.
    Poscondición:
    Se mueve el disco y se llama a la función que imprime el tablero.
    */


    int cO=col-1, cD=col-1;


// Se busca el disco que se encuentre mas arriba y por lo tanto el mas pequeño de la fila de origen.
    while( cO >= 0  &&  tab[col*filOrig+cO] == 0 ) //aqui se ejecuta la ecuacion para mover los dicos 
    {
        cO--;
    };
    if( cO < 0 )
        cO = 0;

// Ahora se calcula cual es la posición libre mas arriba de la fila de destino
    while( cD >= 0  &&  tab[col*filDest+cD] == 0 )
    {
        cD--;
    };

// Se mueve el disco de la fila de origen a la de destino:
    tab[col*filDest+cD+1] = tab[col*filOrig+cO];
    tab[col*filOrig+cO] = 0;

// Se imprime el tablero:
    imprime( tab, fil, col, ultNum );
};

void hanoi( int *tab, int fil, int col, int disc, int ultNum, int O, int A, int D )
{
    /*
    Precondición:
     *tab  Puntero a una matriz de tipo entero.
     fil    Entero que indica el numero de filas de la matriz.
     col    Entero que indica el numero de columnas de la matriz.
     disc  Parámetro de tipo entero que indica el numero de discos usados.
     ultNum  Entero que indica el numero que esta usando el disco mas grande.
     O,A,D  Tres enteros que indican la fila desde donde se ha de coger el disco y a donde se ha de traspasar. La primera vez que se llama a hanoi tienen los valores de: 0 ,1 y 2 respectivamente.
    Poscondición:
     Se llama recursivamente a hanoi hasta resolver el tablero.
    */


    if( disc==1 )
    {
// Se borra la pantalla, se imprime la tabla y se hace una pausa que varia dependiendo del numero de discos:
        system("cls");
        mueveDisco( tab, fil, col, ultNum, O, D );
        if(col<=5) delay(4);
        else if(col<=10) delay(3);
        else if(col<=15) delay(2);
        else if(col>15) delay(1);
    }
    else
    {
        hanoi( tab, fil, col, disc-1, ultNum, O, D, A );

        system("cls");
        mueveDisco( tab, fil, col, ultNum, O, D );
        if(col<=5) delay(4);
        else if(col<=10) delay(3);
        else if(col<=15) delay(2);
        else if(col>15) delay(1);

        hanoi( tab, fil, col, disc-1, ultNum, A, O, D );
    };

};

void delay(int tiempo)
{

    int c, d;
    while(tiempo >= 0)
    {
        for (c = 1; c <= 10000; c++)
            for (d = 1; d <= 10000; d++)
            {}
        tiempo--;
    }

}

int main()
{
    int fil=3, col, *tablero = NULL;
    int f, c, disc=1, ultNum;

    

    printf( "Indique el numero de discos: " ); //el usuario dice la cantidad de discos a utilizar
    scanf( "%i", &col ); //esto es para que el % que ponga el usuario sea igual al valor de col

    tablero = malloc( sizeof(int)*fil*col ); // Se crea un array dinámico con la función malloc


// Resetea las torres poniendo "los discos" en una de ellas y 0 en el resto.
    for( f=0; f < fil; f++ ) //Cuenta de manera ascendente desde el 0 hasta el 2
        for( c=col-1; c >= 0; c-- ) //Cuenta de manera descendente desde col-1 hasta el 0
            if( f==0 ) //Primera torre
            {
                tablero[col*f+c] = disc; //Aqui se guardan la cantidad de discos en el array mediante la relación dada por la ecuación [col*f+c]
                disc+=2; // Se incrementa los disco de 2 en 2 
            }
            else
                tablero[col*f+c] = 0; //Se guardan 0 en la posición que no se encuentran discos

    ultNum = disc; //Ultima fila de los discos, almacena el disco final

// Se imprime el tablero antes de iniciar ningún movimiento:
    system("cls"); //Borra la pantalla
    imprime( tablero, fil, col, ultNum ); //Llama la función para imprimir 
    delay(6);


// Se llama a hanoi para comenzar "la partida":
    hanoi( tablero, fil, col, col, ultNum, 0, 1, 2 );

    return 0;
    system("pause"); //esto es para que el progama se pause cuando ternime de analizar
};