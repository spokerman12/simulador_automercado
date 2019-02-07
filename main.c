/* 
 * Universidad Simon Bolivar
 * Departamento de Computación y Tecnologı́a de la Información
 * Sistemas de Operacion I - CI3825
 * Trimestre Enero-Marzo 2018
 *
 * Tarea
 * 
 * Simulador de Tienda de Autoservicio: Este programa permite simular el procedimiento
 *                         				de compra de productos en una tienda de 
 *                         				autoservicios.
 *
 * Ultima modificacion: 12.02.2018
 *
 * @Autores: Daniel Francis. 12-10863
 *          Javier Vivas. 12-11067
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "funciones.h"


int main(int argc, char *argv[])
{
	FILE *f;
	FILE *log;
	char *aux1;
	char *aux2;
	int *aux3;


	// Crea un archivo .log para almacenar la corrida de la simulacion
	log = fopen("main.log","w");						

	// Distintos valores que son establecidos por defecto en la simulacion	
	int modalidad = 0;
	
	// Cantidad de carritos por defecto
	int cantidadCarritos = 3;												

	int linecount = 0;

	// Tiempo de facturacion de la cajera por defecto
	int t_facturacion = 130;

	// Capacidad maxima que soporta una bolsa por defecto
	int capacidadBolsa = 120;

	// Capacidad maxima que soporta la banda transportadora por defecto
	int capacidadBanda = 200;

	// Capacidad maxima que soporta el area de embolsado por defecto
	int capacidadBolsero = 150;

	// Velocidad de la cajera en procesar un producto por defecto
	float velocidadCajera = 2;

	// Velocidad en que se embolsa un producto por defecto
	float velocidadBolsero = 4;

	char *filename = malloc(128);

	// Lectura del archivo .txt											
	f = fopen(argv[1], "r");
	fprintf(log,"Nombre del archivo: %s \n",argv[1]);
	
	// Da error si no encuentra un .txt con el nombre proporcionado
	if (f == NULL)															
	{
		printf("El archivo %s no fue encontrado o es invalido\n",filename);
		exit(EXIT_FAILURE);
	}

	// Cuenta las lineas del archivo .txt, equivalente a la cantidad de productos de la lista
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int contadorLineas = 0;
	while ((read = getline(&line, &len, f)) != -1)
	{
        contadorLineas++;
    }

    // Total de productos que hay en la simulacion
    int totalItems = contadorLineas;

	// Numero maximo de productos que puede tener un carrito
	int maximoItems = totalItems;

    //Libera el espacio de memoria ocupado originalmente por filename
	free(filename);
	
	fseek (f,0,SEEK_END);
	int lSize = ftell(f);
	rewind(f);

	// Crea un arreglo del tamaño de cantidad de productos
	int arr[totalItems];													
	int n = sizeof(arr)/ sizeof(arr[0]);									

	for (int i = 0; i < totalItems; i++)
	{
		arr[i] = i;
	}

	// El arreglo se desordena para ser utilizado luego
    randomizar (arr, n);														


	int opcionMenu;
	int cambiarOpcion;
	int opcion1;


	// Inicio del menu
	do 																		
	{
		printf("\nMenu\n");
		// Ejecuta la simulacion de la compra en un mercado
		printf("\n1: Ejecutar la simulacion\n");
		// Ejecuta la simulacion de la compra en un mercado							
		printf("2: Cambiar las opciones de simulacion\n");
		// Sale del programa de simulacion					
		printf("3: Salir del programa\n");									
		scanf("%d",&opcionMenu);

		switch(opcionMenu)
		{
				// Ejecutar
				break;

			case 2:

				do 															
				{															
					// Presenta los distintos valores disponibles para modificar
					printf("\nOpciones de la simulacion\n");
					printf("1: Modalidad\n");
					printf("2: Cantidad de carritos en cola\n");
					printf("3: Cantidad maxima de productos por carrito\n");
					printf("4: Capacidad maxima de la banda transportadora\n");
					printf("5: Velocidad de la cajera\n");
					printf("6: Velocidad del embolsador\n");
					printf("7: Tiempo de facturacion\n");
					printf("8: Capacidad maxima del area de embolsado\n");
					printf("9: Capacidad maxima de una bolsa\n");
					printf("10: Volver\n");
					scanf("%d",&cambiarOpcion);

					switch(cambiarOpcion)
					{
						case 1:

							do 												
							{
								// Presenta la opcion de correr el simulador de forma interactiva o automatica
								printf("\nModalidad\n");
								printf("1: Interactiva\n");
								printf("2: Automatica\n");
								printf("3: Volver \n");					
								scanf("%d",&opcion1);

								switch (opcion1)
								{
									case 1:
										modalidad = 0;
										printf("Modalidad seleccionada\n");
										break;

									case 2: 
										modalidad = 1;
										printf("Modalidad seleccionada\n");
										break;

									default:
										if (opcion1 != 3)
										{
											printf("\nOpcion invalida\n");	
										}
										
										break;
								}
							} while (opcion1 != 3); break;
													
						case 2:
							printf("Indique cantidad de carritos en cola: ");
							scanf("%d",&cantidadCarritos);

							if (cantidadCarritos < 1)
							{
								cantidadCarritos = 1;
								printf("\nLa cantidad de carritos no puede ser menor a 1\n");
							}

							break;

						case 3:
							printf("Indique cantidad maxima de productos por carrito: ");
							scanf("%d",&maximoItems);

							if (maximoItems < 1)
							{
								maximoItems = totalItems;
								printf("\nEl maximo de productos por carrito no puede ser menor a 1\n");
							}

							break;

						case 4:
							printf("Indique capacidad maxima de la banda transportadora: ");
							scanf("%d",&capacidadBanda);

							if (capacidadBanda < 1)
							{
								capacidadBanda = 200;
								printf("\nLa capacidad de la banda no puede ser menor a 1\n");
							}

							break;

						case 5:
							printf("Indique la velocidad de la cajera: ");
							scanf("%f",&velocidadCajera);

							if (velocidadCajera < 1)
							{
								velocidadCajera = 2;
								printf("\nLa velocidad de la cajera no puede ser menor a 1\n");
							}

							break;

						case 6:
							printf("Indique la velocidad del embolsador: ");
							scanf("%f",&velocidadBolsero);

							if (velocidadBolsero < 1)
							{
								velocidadBolsero = 4;
								printf("\nLa velocidad del embolsador no puede ser menor a 1\n");
							}

							break;

						case 7:
							printf("Indique el tiempo de facturacion: ");
							scanf("%d",&t_facturacion);

							if (t_facturacion < 1)
							{
								t_facturacion = 130;
								printf("\nEl tiempo de facturacion no puede ser menor a 1\n");
							}

							break;

						case 8:
							printf("Indique la capacidad maxima del area de embolsado: ");
							scanf("%d",&capacidadBolsero);

							if (capacidadBolsero < 1)
							{
								capacidadBolsero = 150;
								printf("\nLa capacidad del area de embolsado no puede ser menor a 1\n");
							}

							break;

						case 9:
							printf("Indique la capacidad maxima de una bolsa: ");
							scanf("%d",&capacidadBolsa);

							if (capacidadBolsa < 1)
							{
								capacidadBolsa = 120;
								printf("\nLa capacidad por bolsa no puede ser menor a 1\n");
							}

							break;

						default:
							if (cambiarOpcion != 10)
							{
								printf("\nOpcion invalida\n");
							}
							
							break;
					}

				} while (cambiarOpcion != 10); break;

			case 3:
				exit(0);

			default:
				if (opcionMenu != 1)
				{
					printf("\nOpcion invalida\n");	
				}
				
				break;

		}

	} while (opcionMenu != 1);

	if (cantidadCarritos > totalItems)
	{
		printf("\nHay %d productos y no pueden haber mas carritos que productos\n",totalItems);
		exit(0);
	}

	if (maximoItems > totalItems)
	{
		printf("\nHay %d productos y el maximo de productos de un carrito no puede ser mayor a la cantidad de productos\n",totalItems);
		exit(0);
	}

	if ((cantidadCarritos * maximoItems) < totalItems)
	{
		printf("\nEl maximo de productos por carrito no permite que todos los productos sean comprados, seleccione una capacidad mayor \n");
		exit(0);
	}

	fprintf(log,"Cantidad de carritos: %d \n",cantidadCarritos);

	int resto;
	int x;
	int k;
	int r = 1;
	int contadorSort = totalItems;
	int contadorCarritos = 0;
	int tempMaximoItems = maximoItems;

	// Reserva espacio para la cola de carritos y la crea
	Cola *colaCarritos = malloc(sizeof(Cola));
	colaCarritos = crearCola();

	while(contadorCarritos < cantidadCarritos - 1)
	{
		if (tempMaximoItems == totalItems)
		{
			k = cantidadCarritos - r;
			maximoItems = contadorSort - k;	
		}

		srand(time(NULL));

		x = randRange(maximoItems) + 1;
		fprintf(log,"La cantidad de productos en el carrito %d es: %d \n",contadorCarritos,x);

		// Añade a la cola de carritos un carrito con el numero de items que posee
		encolar(colaCarritos, x);									
																	
		contadorSort = contadorSort - x;
		resto = contadorSort;
		contadorCarritos++;
		r++;														
	}															

	encolar(colaCarritos,resto);
	fprintf(log,"La cantidad de productos en el carrito %d es: %d \n",contadorCarritos,resto);

	fprintf(log,"Capacidad de la banda transportadora: %d \n",capacidadBanda);
	fprintf(log,"Velocidad de la cajera: %f \n",velocidadCajera);
	fprintf(log,"Velocidad del embolsador: %f \n",velocidadBolsero);
	fprintf(log,"Tiempo de facturacion: %d \n",t_facturacion);
	fprintf(log,"Capacidad del area de embolsado: %d \n",capacidadBolsero);
	fprintf(log,"Capacidad de una bolsa: %d \n",capacidadBolsa);

	int *apunta = &arr[0];
	nodoCola *carroActual = colaCarritos->front;

	// Llena cada carrito con la cantidad de productos establecidos para cada uno
	for (int i=0; i<cantidadCarritos;i++)
	{
		espacioCarrito(carroActual);
		llenaCarrito(carroActual,apunta,f,lSize);
		apunta = apunta + carroActual->key;
		carroActual = carroActual->next;
	}

	int t_global = 0;
	int t_actual = 0;

	carroActual = colaCarritos->front;
	int numCarros = 0; 

	// Creacion de la banda transportadora de productos
	Cola * banda = crearCola();
	banda->capacidad = capacidadBanda;

	int itemCajera;
	nodoCola * nodoCajera;
	int cajeraLista = true;
	div_t latenciaCajera;
	int facturando = false;

	int itemBolsero;
	nodoCola * nodoBolsero;
	int bolseroListo = true;
	div_t latenciaBolsero;
	int itemSize = 0;

	// Creacion de la pila del area de embolsado
	stack * stackBolsero;
	stackBolsero = malloc(sizeof(stack));
	stackBolsero->items = malloc(sizeof(int)*capacidadBolsero);
	stackBolsero->carga = 0;
	stackBolsero->capacidad = capacidadBolsero;

	// Creacion de la pila de una bolsa
	stack * stackBolsa = malloc(sizeof(stack));
	stackBolsa->items = malloc(sizeof(int)*capacidadBolsa);
	stackBolsa->carga = 0;
	stackBolsa->capacidad = capacidadBolsa;
	int numBolsas = 0;

	// Crea un arreglo para almacenar el tiempo que toma cada carrito en ser procesado
	int arregloTiempos[cantidadCarritos];

	fflush(stdin);
	fflush(stdout);

	while(carroActual != NULL)
	{
		while (true)
			{
				if (modalidad==0)			
				{
					while(getchar() != '\n');
				}

				// Llena la banda transportadora de productos
				llenaBanda(carroActual,banda,f,lSize,modalidad);

				if(banda->front != NULL)
				{
					if (modalidad == 0)
					{
						printf("[Banda]: ");
						printItems(banda,f,lSize);
					}	
				}

				else
				{
					if (modalidad == 0)
					{
						printf("[Banda]: -\n");
					}
				}
				
				if(cajeraLista)
				{
					if (banda->front == NULL && latenciaCajera.quot == 0)
					{
						// La cajera empieza a facturar si ya proceso todos los productos
						latenciaCajera.quot = div(t_facturacion,velocidadCajera).quot+1;
						cajeraLista = false;
						facturando = true;
					}

					else
					{
						// Procesa los productos aun en la banda transportadora
						itemCajera = banda->front->key;
						aux1 = getAttrib(f,lSize,itemCajera,2);
						latenciaCajera = div(atoi(aux1),velocidadCajera);
						free(aux1);
						latenciaCajera.quot++;

						desencolar(banda);
						aux1 = getAttrib(f,lSize,itemCajera,1);
						banda->carga = banda->carga - atoi(aux1);
						free(aux1);
						if (banda->carga < 0)
						{
							banda->carga = 0;
						}

						cajeraLista = false;
					}
				}

				if(!cajeraLista)
				{
					latenciaCajera.quot--;

					if(facturando)
					{
						if (modalidad == 0)
						{
							printf("[Cajera]: Facturando (%ds restantes)\n",latenciaCajera.quot);
						}
						
						if (latenciaCajera.quot == 0)
						{
							if (modalidad == 0)
							{
								printf("Cliente %d facturado\n",numCarros);
							}
							
							// Guarda en un arreglo el tiempo que tomo procesar por completo cada carrito
							arregloTiempos[numCarros] = t_actual;
							t_actual = 0;
							cajeraLista = true;
							facturando = false;
							break;
						}
					}
					else
					{
						if (modalidad == 0)
						{
							aux1 = getAttrib(f,lSize,itemCajera,0);
							printf("[Cajera]: %s",aux1);
							printf(" (%ds restantes)\n", latenciaCajera.quot);
							free(aux1);
						}
					}

					if (latenciaCajera.quot == 0 && !facturando)
					{	
						// Pasa el producto de la banda transportadora al area de embolsado
						s_push(stackBolsero,itemCajera);
						cajeraLista = true; 
					}
				}

				if(bolseroListo)
				{	
					if (stackBolsero->top > 0)
					{
						// Saca el producto del area de embolsado
						aux3 = s_pop(stackBolsero);
						itemBolsero = *aux3;
						aux1 = getAttrib(f,lSize,itemBolsero,1);
						itemSize = atoi(aux1);
						aux2 = getAttrib(f,lSize,itemBolsero,2);
						latenciaBolsero = div(atoi(aux2),velocidadBolsero);
						latenciaBolsero.quot++;
						bolseroListo = false;
						free(aux1);
						free(aux2);
					}			
				}
				
				if(!bolseroListo)
				{
					if (modalidad == 0)
					{
						aux1 = getAttrib(f,lSize,itemBolsero,0);
						printf("[Area de embolsado]: %s", aux1);
						printf(" (%ds restantes)\n", latenciaBolsero.quot);
						free(aux1);
					}
					
					latenciaBolsero.quot--;
					
					if (latenciaBolsero.quot==0)
					{
						if(stackBolsa->carga+itemSize <= stackBolsa->capacidad)
						{
							if (modalidad == 0)
							{
								aux1 = getAttrib(f,lSize,itemBolsero,0);
								printf("[Bolsa %d]: %s\n",numBolsas,aux1);
								free(aux1);
							}
							
							// Pasa el producto a la bolsa
							s_push(stackBolsa,itemBolsero);
							stackBolsa->carga = stackBolsa->carga + itemSize;

						}

						if(itemSize > stackBolsa->capacidad)
						{
							// Limpia por completo la pila en la bolsa
							s_purge(stackBolsa);
							if (modalidad == 0)
							{
								aux1 = getAttrib(f,lSize,itemBolsero,0);
								printf("[No cabe]: %s\n",aux1);
								free(aux1);
							}
							
							s_push(stackBolsa,itemBolsero);
						}
						else
						{
							// Vacia por completo la pila en la bolsa
							s_purge(stackBolsa);
							numBolsas++;
						}
						free(aux3);
						bolseroListo = true;
					}
				}
	
				t_actual++;
				t_global++;
			}

		// Pasa a procesar al siguiente carrito en la cola
		numCarros++;
		carroActual=carroActual->next;
	}

	// Imprime en pantalla el tiempo que tomo cada carrito en ser procesado
	printf("\n");
	for (int j = 0; j < cantidadCarritos; j++)
	{
		printf("El tiempo que tomo el carro %d en ser procesado es: %d \n",j,arregloTiempos[j]);
		fprintf(log,"El tiempo que tomo el carro %d en ser procesado es: %d \n",j,arregloTiempos[j]);
	}

	// Imprime en pantalla el tiempo total que tomo toda la simulacion
	printf("Tiempo total: %d \n", t_global);
	fprintf(log,"Tiempo total: %d \n",t_global);
	
	printf("-\n Fin de la simulacion\n");

	fclose(f);
	fclose(log);

	return 0;
}