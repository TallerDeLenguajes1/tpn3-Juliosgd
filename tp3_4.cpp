#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Producto
{
    int ProductoID;       //Numerado en ciclo iterativo
    int Cantidad;         // entre 1 y 10
    char *TipoProducto;   // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
};

struct Cliente
{
    int ClienteID;               // Numerado en el ciclo iterativo
    char *NombreCliente;         // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    struct Producto *Productos;  //El tamaño de este arreglo depende de la variable
    // “CantidadProductosAPedir”
};

void cargaClientes(struct Cliente *c, int Nclientes, char *TiposProductos[]);
void infoClientes(struct Cliente *c, int Nclientes);
float totalProducto(struct Producto *p, int j);

int main()
{

    int Nclientes;
    char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

    Nclientes = rand() % (5 - 1) + 1;
    struct Cliente *c;
    c = (struct Cliente *)malloc(sizeof(struct Cliente) * Nclientes);
    printf("cantidad de clientes:%d\n\n", Nclientes);

    cargaClientes(c, Nclientes, TiposProductos);
    infoClientes(c, Nclientes);

    return 0;
}

void cargaClientes(struct Cliente *c, int Nclientes, char *TiposProductos[])
{

    int aleatorio, longitud;
    int aux = 0;
    char nombre[100];
    for (int i = 0; i < Nclientes; i++)
    {
        printf("Ingrese el nombre del cliente %d\n", i + 1);
        scanf("%s", &nombre);
        fflush(stdin);
        c[i].ClienteID = i + 1;
        c[i].NombreCliente = (char *)malloc(sizeof(char) * strlen(nombre));
        strcpy(c[i].NombreCliente, nombre);
        c[i].CantidadProductosAPedir = rand() % (5 - 1) + 1;
        c[i].Productos = (struct Producto *)malloc(sizeof(struct Producto) * c[i].CantidadProductosAPedir);

        for (int j = 0; j < c[i].CantidadProductosAPedir; j++)
        {

            c[i].Productos[j].ProductoID = j + 1;
            aleatorio = rand() % 4 + 1;
            longitud = strlen(TiposProductos[aleatorio]);
            c[i].Productos[j].TipoProducto = (char *)malloc(longitud * sizeof(char));
            strcpy(c[i].Productos[j].TipoProducto, TiposProductos[aleatorio]);
            c[i].Productos[j].Cantidad = rand() % (10 - 1) + 1;
            c[i].Productos[j].PrecioUnitario = rand() % (100 - 10) + 10;
        }
    }
}

void infoClientes(struct Cliente *c, int Nclientes)
{
    float total = 0;
    for (int i = 0; i < Nclientes; i++)
    {

        printf("\nidcliente %d\n", c[i].ClienteID);
        printf("nombre cliente: %s\n", c[i].NombreCliente);
        printf("cantidad productos a pedir: %d\n\n", c[i].CantidadProductosAPedir);

        for (int j = 0; j < c[i].CantidadProductosAPedir; j++)
        {
            printf("id producto %d  cantidad producto:%d  tipo producto:%s  precio unitario:%.f\n", c[i].Productos[j].ProductoID, c[i].Productos[j].Cantidad, c[i].Productos[j].TipoProducto, c[i].Productos[j].PrecioUnitario);
            total += totalProducto(c[i].Productos, j);
        }

        printf("Total a pagar: %.f\n", total);
        total = 0;
        printf("\n\n");
    }
}

float totalProducto(struct Producto *p, int j)
{
    return p[j].Cantidad * p[j].PrecioUnitario;
}
