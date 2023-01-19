#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
using namespace std;
int Puntaje_o, Puntaje_p, Puntaje_b;
struct arbol
{
    char nombre[15]; //Dato 
    char nacionalidad[15];
    struct arbol *nodo_izq; //Hijo izquierdo
    struct arbol *nodo_der; //Hijo Derecho
};

struct arbol *Inicializar(struct arbol *a)
{
    a = NULL;
    return a;
}
struct arbol *insertarNumero(struct arbol *a, char *nombre, char *nacionalidad)
{
    if (a == NULL)
    {
        struct arbol *aux = NULL;
        aux = (struct arbol *)malloc(sizeof(struct arbol));
        aux->nodo_izq = NULL;
        aux->nodo_der = NULL;
        strcpy(aux->nombre, nombre);
        strcpy(aux->nacionalidad, nacionalidad);
        return aux;
    }

    if (strcmp(nombre,a->nombre) > 0)
        a->nodo_izq = insertarNumero(a->nodo_izq, nombre, nacionalidad);
    else
        a->nodo_der = insertarNumero(a->nodo_der, nombre, nacionalidad);
    return a;
}
char Busqueda(struct arbol *a, char* nombre, char* nacionalidad)
{
    char bandera;
    if(a == NULL)
    {
        bandera &= 0;
        return bandera;
    }else if(strcmp(a->nombre, nombre) == 0 && strcmp(a->nacionalidad, nacionalidad) == 0)
    {
        bandera |= 1;
        return bandera;
    }else if(strcmp(nombre,a->nombre) > 0)
    return Busqueda(a->nodo_izq, nombre, nacionalidad);
    else return Busqueda(a->nodo_der, nombre, nacionalidad);
}
void Busqueda_exhaustiva_O(struct arbol *a, char *nacionalidad)
{
    if(a != NULL)
    {
        if(strcmp(a->nacionalidad,nacionalidad) == 0)
        {
            Puntaje_o += 10;
            cout<<a->nombre<<"\t\t"<<a->nacionalidad<<"\t\toro"<<endl;
        }
        Busqueda_exhaustiva_O(a->nodo_der, nacionalidad);
        Busqueda_exhaustiva_O(a->nodo_izq, nacionalidad);
    }
}
void Busqueda_exhaustiva_P(struct arbol *a, char *nacionalidad)
{
    if(a != NULL)
    {
        if(strcmp(a->nacionalidad,nacionalidad) == 0)
        {
            Puntaje_p += 5;
            cout<<a->nombre<<"\t\t"<<a->nacionalidad<<"\t\tplata"<<endl;
        }
        Busqueda_exhaustiva_P(a->nodo_der, nacionalidad);
        Busqueda_exhaustiva_P(a->nodo_izq, nacionalidad);
    }
}
void Busqueda_exhaustiva_B(struct arbol *a, char *nacionalidad)
{
    if(a != NULL)
    {
        if(strcmp(a->nacionalidad,nacionalidad) == 0)
        {
            Puntaje_b += 2;
            cout<<a->nombre<<"\t\t"<<a->nacionalidad<<"\t\tbronze"<<endl;
        }
        Busqueda_exhaustiva_P(a->nodo_der, nacionalidad);
        Busqueda_exhaustiva_P(a->nodo_izq, nacionalidad);
    }
}

char menu()
{
       char opcion;
       cout<<"Ingrese alguna opcion"<<endl;
       cout<<"1. Agregar Atletas"<<endl;
       cout<<"2. Buscar un Atleta"<<endl;
       cout<<"3. Buscar un equipo"<<endl;
       cout<<"4. Salir"<<endl;
       cin>>opcion;
       return opcion;
}

int main()
{
    int numero;
    struct arbol *oro;
    struct arbol *plata;
    struct arbol *bronze;
    oro = Inicializar(oro);
    plata = Inicializar(plata);
    bronze = Inicializar(bronze);
    int suma;
    char nombre[15];
    char nacionalidad[15];
    char c;

    FILE *Data;
    Data = fopen("Medallas.txt", "r");
    if(Data != NULL)
    {
        while(!feof(Data))
        {
            c = fgetc(Data);
            if(c == '\n')
                continue;
            switch(c)
            {
            case 'o':
                fscanf(Data, "%s %s", nacionalidad, nombre);
                oro = insertarNumero(oro, nombre, nacionalidad);
                break;
            case 'p':
                fscanf(Data, "%s %s", nacionalidad, nombre);
                plata = insertarNumero(plata,nombre,nacionalidad);
                break;
            case 'b':
                fscanf(Data, "%s %s", nacionalidad, nombre);
                bronze = insertarNumero(bronze,nombre,nacionalidad);
                break;
            default:
                break;
            }
        }

    }

   do{
        switch(menu())
        {
            case '1':
                cout<<"Ya finalizaron los juegos, no se puede Agregar mas Atletas";
                break;

            case '2':
                cout<<"Ingrese el nombre de Atleta: ";
                cin>>nombre;
                cout<<endl<<"Ingrese su nacionalidad: ";
                //scanf("%s", &nacionalidad);
                cin>>nacionalidad;
                if(Busqueda(oro, nombre, nacionalidad))
                {
                    cout<<"El Atleta "<<nombre<<" gano una medalla de oro para "<<nacionalidad<<endl;
                }else if(Busqueda(plata, nombre, nacionalidad))
                {
                    cout<<"El Atleta "<<nombre<<" gano una medalla de plata para "<<nacionalidad<<endl;
                }else if(Busqueda(bronze, nombre, nacionalidad))
                {
                    cout<<"El Atleta "<<nombre<<" gano una medalla de bronze para "<<nacionalidad<<endl;
                } else cout<<"El atleta no esta registrado";
                break;
            case '3':
                cout<<"Ingrese la nacionalidad del equipo: ";
                cin>>nacionalidad;
                Puntaje_o = 0;
                Puntaje_p = 0;
                Puntaje_b = 0;
                Busqueda_exhaustiva_O(oro, nacionalidad);
                Busqueda_exhaustiva_P(plata, nacionalidad);
                Busqueda_exhaustiva_B(bronze, nacionalidad);
                suma = Puntaje_o + Puntaje_p + Puntaje_b;
                cout<<"El equipo de "<<nacionalidad<<" gano "<<suma<<" puntos";
                break;

            case '4':
                return 0;
                break;

            default:
                cout<<"Ingrese solo alguna de las opciones disponibles"<<endl;
                system("pause");
                break;   
        }
    }while(1);
       return 0;
}