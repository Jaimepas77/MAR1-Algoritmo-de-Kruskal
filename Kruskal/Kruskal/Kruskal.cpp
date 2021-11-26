//Autor: Jaime Pastrana García (jaipas01@ucm.es)
//Asignatura: Métodos algorítmicos en resolución de problemas
#include <iostream>
#include <vector>

using namespace std;

class Particion
{
private:
    struct tNodoParticion//Información que se tiene de cada nodo en la estructura de partición
    {
        int altura = 0;
        int padre;
    };
    vector<tNodoParticion>nodos;

public:
    Particion(int tam)//Constructor con tamaño de la estructura
    {
        nodos.resize(tam);
        for (int i = 0; i < tam; i++)
        {
            nodos[i].altura = 0;
            nodos[i].padre = i;//El puntero del padre apunta a ellos mismos inicialmente
        }
    }

    void fusionar(int e1, int e2)//Fusionar los conjuntos de dos elementos
    {
        //Si no son el elemento padre de su conjunto, se busca para poder hacer la unión
        if (nodos[e1].padre != e1)
            e1 = buscar(e1);

        if(nodos[e2].padre != e2)
            e2 = buscar(e2);

        //Comparar alturas para decidir cuál es el padre del otro
        int h1 = nodos[e1].altura;
        int h2 = nodos[e2].altura;
        if (h1 > h2)
        {
            nodos[e2].padre = e1;
        }
        else if (h1 == h2)
        {
            nodos[e2].padre = e1;
            nodos[e1].altura++;
        }
        else
        {
            nodos[e1].padre = e2;
        }
    }

    int buscar(int elem)//Se devuelve el elemento que representa el conjunto del elemento buscado
    {
        int ret;//Valor a calcular y retornar (el representante del conjunto)
        if (nodos[elem].padre != elem)
        {
            ret = buscar(nodos[elem].padre);//Búsqueda recursiva hasta encontrar al padre
            nodos[elem].padre = ret;//Compresión de caminos (el padre se actualiza al representante del conjunto para mejorar la eficiencia)
        }
        else
        {
            ret = elem;
        }

        return ret;
    }

    void imprimir()//Función de depuración
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < nodos.size(); j++)
                if (nodos[j].altura == i)
                    cout << j << " ";

            cout << endl;

            for (int j = 0; j < nodos.size(); j++)
                if (nodos[j].altura == i)
                {
                    if (nodos[j].padre != j)
                        cout << "| ";
                    else
                        cout << "  ";
                }


            cout << endl;
        }
    }
};

int main()
{
    //Cada vértice del grafo se identifica por un nº únicamente para él entre 0 y n-1 (siendo n el nº de vértices)

    //Probando...
    Particion conjunto(5);
    conjunto.fusionar(2, 3);
    conjunto.fusionar(4, 2);
    conjunto.imprimir();

    conjunto.fusionar(0, 1);
    conjunto.fusionar(1, 2);
    conjunto.imprimir();
    cout << conjunto.buscar(4) << endl;

    cout << "Execution finished\n";
}