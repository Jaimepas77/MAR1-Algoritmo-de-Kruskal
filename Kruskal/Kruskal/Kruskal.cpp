//Autor: Jaime Pastrana García (jaipas01@ucm.es)
//Asignatura: Métodos algorítmicos en resolución de problemas
#include <iostream>
#include <vector>
#include <fstream>//Para leer un fichero con el grafo

using namespace std;

struct arista
{
	int v1, v2;//Vértices que conecta
	int peso;
};

class Particion
{
private:
	struct tNodoParticion//Información que se tiene de cada nodo en la estructura de partición
	{
		int altura = 0;
		int padre;
	};
	vector<tNodoParticion> nodos;

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

		if (nodos[e2].padre != e2)
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

class Grafo
{
public:
	struct vertice
	{
		vector<pair<int, int>> aristas;//Lista de adyacencia de cada vértice
		//first: vértice adyacente
		//second: peso de la arista
	};
	vector<vertice> vertices;//Vértices que conforman el grafo

	Grafo(int tam)//Constructor en función del nº de nodos que tiene el grafo
	{
		vertices.resize(tam);
	}

	void agregarArista(arista a)//Añade la información de una arista en la lista de adyacencia de ambos vértices
	{
		vertices[a.v1].aristas.push_back({ a.v2, a.peso });
		vertices[a.v2].aristas.push_back({ a.v1, a.peso });
	}

	void imprimir()//Para facilitar la depuración
	{
		//Imprimir lista de adyacencia del grafo
		int i = 0;
		for (const auto &x : vertices)
		{
			cout << i << ": ";
			for (const auto &y : x.aristas)
				cout << y.first << " " << y.second << " | ";
			cout << endl;
			i++;
		}
	}
};

Grafo leerGrafo(string fichero)//Se lee desde un fichero fuente el grafo
{
	//Para visualizar los grafos introducir el fichero fuente en la página del 
	// siguiente link y borrar la primera línea (la de nº de vértices y aristas)
	// https://csacademy.com/app/graph_editor/  PD: si el grafo es enorme la página colapsará
	// (se asume que el grafo es conexo)

	ifstream input;
	input.open(fichero);
	if (!input.is_open())
	{
		cout << "Fichero no encontrado para leer el grafo\n";
		Grafo g(0);//Si no se encuentra se devuelve vacío
		return g;
	}

	//Se lee el grafo como, dado su nº de vertices y aristas, una lista de aristas.
	//(luego, en la estructura, se guardan en listas de adyacencia por vértices)
	int vertices, aristas;
	input >> vertices >> aristas;
	Grafo g(vertices);

	for (int i = 0; i < aristas; i++)
	{
		arista a;
		input >> a.v1 >> a.v2 >> a.peso;
		g.agregarArista(a);
	}
	input.close();

	return g;
}

/*To do:
	-estructura para guardar el grafo valorado (listas de adyacencia) -> done
	-estructura para guardar las aristas ordenadas de menor a mayor. -> vector de aristas
	-estructura para guardar el ARM -> conjunto de aristas -> estructura para guardar conjuntos de aristas -> done
	*/

int main()
{
	//Cada vértice del grafo se identifica por un nº únicamente para él entre 0 y n-1 (siendo n el nº de vértices)

	//Probando la estructura de partición...
	/*Particion conjunto(5);
	conjunto.fusionar(2, 3);
	conjunto.fusionar(4, 2);
	conjunto.imprimir();

	conjunto.fusionar(0, 1);
	conjunto.fusionar(1, 2);
	conjunto.imprimir();
	cout << conjunto.buscar(4) << endl;*/

	cout << "Indique el fichero desde el cual quiere cargar el grafo: ";
	string fichero;
	cin >> fichero;

	Grafo g = leerGrafo(fichero);//Leer un grafo desde un fichero

	g.imprimir();

	//vector<arista> arm = kruskal(g);//Se genera el ARM del grafo como un conjunto de aristas

	//Se imprime la solución...

	cout << "Execution finished\n";
}