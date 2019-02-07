
/*
 *	@brief: Funcion getItem: Encuentra un item en una lista de productos
 *
 *	@param: *file: Apuntador a archivo abierto
 *	@param:	filesize: entero, tamano del archivo
 *	@param:	indice:	 entero, indice del item a buscar
 *
 *	@return: Apuntador al item en el archivo, representado com una linea
 *
 */	


char * getItem (FILE *file, int fileSize, int indice)
{
	
	char buffer[fileSize];
	int linecount = 0;
	char * str = malloc(sizeof(char)*128);
	rewind(file);

	while (fgets(buffer, fileSize,(FILE*)file))
	{
		if (linecount == indice)
		{
			strcpy(str,buffer);

			return (str);

			break;
		}

		else
		{ 
			linecount++;
		}
	}
	printf("str es %s \n",str);
	return ("MISSINGNO.");
}

/*
 *	@brief: Funcion getAttrib: De un item extrae un atributo
 *					 	
 *						query = 0: Nombre
 *					  			1: Volumen
 * 					 			2: Complejidad		
 *
 *	@param: *file: Apuntador a archivo abierto
 *	@param:	filesize: entero, tamano del archivo
 *	@param:	indice:	 entero, indice del item a buscar
 *
 *	@return: string: Complejidad del item
 *
 */	

char * getAttrib (FILE *file, int fileSize, int indice, int query)
{
	char * item = getItem(file,fileSize,indice);
	char *r = malloc(sizeof(item));
	strcpy(r,item);
	
	char * token;
	char * token1;
	char * token2;

	const char s[2] = "\t";
	token = strsep(&r, "\t");
	token1 = strsep(&r, "\t");
	token2 = strsep(&r, "\t");

	if (query==0)
		free(item);
		return(token);

	if (query==1)
		free(item);
		return(token1);

	if (query==2)
		free(item);
		return(token2);

}

/*
 *	@brief: Estructura stack: Pila
 *
 *	@attrib: items: Elementos de la pila
 *	@attrib: maxItems: Cantidad maxima de elementos que puede poseer la pila
 *	@attrib: top: Cantidad de elementos que posee la pila
 *
 */

typedef struct stack
{
	int * items;
	int maxItems;
	int top;
	int capacidad;
	int carga;
} stack;

/*
 *	@brief: Funcion s_size: Retorna el tamaño de la pila
 *
 *	@param: *s: Apuntador a la pila
 *
 *	@return: int: Entero, tamaño de la pila
 *
 */

int s_size(stack *s)
{
	return (s->top);
}

/*
 *	@brief: Funcion s_vacio: Comprueba si la pila esta vacia
 *
 *	@param: *s: Apuntador a la pila
 *
 *	@return: int: Retorna un entero que especifica si esta vacia la pila
 *
 */

int s_vacio(stack *s)
{
	return (s_size(s) <= 0);
}

/*
 *	@brief: Funcion s_full: Comprueba si la pila esta al maximo de su capacidad
 *
 *	@param: *s: Apuntador a una pila
 *
 *	@return: int: Retorna un entero que especifica si la pila esta llena
 *
 */

int s_full(stack *s)
{
	return (s_size(s) == s->maxItems-1);
}

/*
 *	@brief: Funcion s_pop: Elimina el siguiente elemento en orden de la pila
 *
 *	@param: *s: Apuntador a una pila
 *
 *	@return: int: Retorna un apuntador al espacio liberado
 *
 */

int * s_pop(stack *s)
{
	int * tmp = malloc(sizeof(int));
	if (s_vacio(s))
	{
		printf("Stack vacio\n");
	}
	else
	{
		*tmp =  s->items[s->top];
		s->top--;
		//printf("Pop %d\n", *tmp);
		return(tmp);
	}
}

/*
 *	@brief: Funcion s_peek: Permite saber que elemento se encuentra en el tope de la pila
 *
 *	@param: *s: Apuntador a una pila
 *
 *	@return: int: Retorna el valor del elemento tope de la pila
 *
 */

int * s_peek(stack *s)
{
	int * tmp = malloc(sizeof(int));
	if (s_vacio(s))
	{
		printf("Stack vacio\n");
	}
	else
	{
		*tmp =  s->items[s->top];
		return(tmp);
	}
}

/*
 *	@brief: Funcion s_size: Retorna el tamaño de la pila
 *
 *	@param: *s: Apuntador a una pila
 *	@param: k: Entero k que sera añadido a la pila
 *
 */

void s_push(stack *s, int k)
{
	if (s_full(s))
	{
		printf("Stack full");
	}
	else
	{
		s->top++;
		s->items[s->top] = k;
	}
}

/*
 *	@brief: Funcion s_purge: Vacia por completo una pila
 *
 *	@param: *s: Apuntador a una pila
 *
 */

void s_purge(stack *s)
{
	int * temp;

	while(s_vacio(s)==false)
	{
		temp = s_pop(s);
		free(temp);
	}
}

/*
 *	@brief: Estructura nodoCola: Nodo de cola
 *
 *	@attrib: key: Identificador del nodo
 *	@attrib: *next: Apuntador al siguiente nodo
 *	@attrib: itemStack: Pila
 *
 */

typedef struct nodoCola
{
    int key;
    struct nodoCola *next;
    stack * itemStack; 

} nodoCola;
 
/*
 *	@brief: Estructura Cola: Cola
 *
 *	@attrib: *front: Apuntador al primer elemento de la cola
 *	@attrib: *rear: Apuntador al ultimo elemento de la cola
 *	@attrib: vacia: 
 *
 */

typedef struct Cola
{
    nodoCola *front, *rear;
    int vacia;
    int capacidad;
    int carga;
} Cola;

/*
 *	@brief: Funcion nodoNuevo: Crea un nuevo nodo de una lista enlazada
 *
 *	@param: k: Entero k que sera el identificador del nodo
 *
 *	@return: nodoCola: Retorna el nodo creado
 *
 */

nodoCola * nodoNuevo(int k)
{
    nodoCola *temp = (nodoCola*)malloc(sizeof(nodoCola));
    temp->key = k;
    temp->next = NULL;
    return temp; 
}

/*
 *	@brief: Funcion crearCola: Crea una cola
 *
 *	@return: Cola: Retorna la cola creada
 *
 */

Cola * crearCola()
{
    Cola *q = (Cola*)malloc(sizeof(struct Cola));
    q->front = q->rear = NULL;
    q->vacia = true;
    return q;
};

/*
 *	@brief: Funcion encolar: Añade un elemento a la cola
 *
 *	@param: *q: Apuntador a la cola
 *	@param: k: Entero k que sera el identificador del elemento añadido a la cola
 *
 */

void encolar(Cola *q, int k)
{
    nodoCola *temp = nodoNuevo(k);

    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       q->vacia = false;
       return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

/*
 *	@brief: Funcion *desencolar: Elimina el siguiente elemento en orden de la cola
 *
 *	@param: *q: Apuntador a la cola
 *
 *	@return: nodoCola: Elemento eliminado
 *
 */

nodoCola *desencolar(Cola *q)
{
    if (q->front == NULL)
       return NULL;

    nodoCola *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    	q->rear = NULL;
    	q->vacia = true;
    return temp;
}

/*
 *	@brief: Funcion printItems: Imprime en pantalla los elementos de una cola 
 *
 *	@param: *q: Apuntador a una cola
 *	@param: *file: Apuntador al archivo .txt
 *	@param: fileSize: Entero, tamaño del archivo .txt
 *
 */

void printItems(Cola *q, FILE *file, int fileSize)
{
	nodoCola * p = q->front;
	char * aux_s;
	while(p != NULL)
	{
		if(p->next == NULL)
		{
			aux_s = getAttrib(file,fileSize,p->key,0);
			printf("%s.\n", aux_s);	
			free(aux_s);
		}

		else
		{
			aux_s = getAttrib(file,fileSize,p->key,0);
			printf("%s, ", aux_s);
			free(aux_s);
		}	
			
		p = p->next;
	}
}

/*
 *	@brief: Funcion randRange: Crea 
 *
 *	@param: n: Entero n para calcular el limite de rango
 *
 *	@return: int: 
 *
 */
																		
int randRange(int n)														
{
    int limit;
    int r;

    limit = RAND_MAX - (RAND_MAX % n);

    while((r = rand()) >= limit);

    return r % n;
}

/*
 *	@brief: Funcion swap: Cambia un elemento por otro
 *
 *	@param: *a: Apuntador a un entero a
 *	@param: *b: Apuntador a un entero b
 *
 */

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 *	@brief: Funcion printArray: Imprime en consola todos los elementos de un arreglo de enteros
 *
 *	@param: arr[]: Arreglo de enteros
 *	@param: n: Entero, maximo de elementos para imprimir
 *
 */

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
/*
 *	@brief: Funcion randomizar: Organiza un arreglo desordenadamente
 *
 *	@param: arr[]: Arreglo de enteros
 *	@param: n: Entero, limite de elementos en el arreglo
 *
 */

void randomizar(int arr[],int n)
{
    srand ( time(NULL) );
 
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);

        swap(&arr[i], &arr[j]);
    }
}    

/*
 *	@brief: Funcion espacioCarrito: Reserva espacio en memoria para la pila de un carrito
 *
 *	@param: *carro: Apuntador al nodo carrito
 *
 */

void espacioCarrito (nodoCola *carro)
{
	carro->itemStack = malloc(sizeof(stack));
	carro->itemStack->items = malloc(sizeof(int)*carro->key);
}

/*
 *	@brief: Funcion llenaCarrito: Llena la pila de cada carrito con la cantidad elementos asignada 
 *
 *	@param: *carro: Apuntador al carrito que se va a llenar
 *	@param: *p: Apuntador al elemento para ser agregado a la pila del carro en turno
 *	@param: *file: Apuntador al archivo .txt
 *	@param: fileSize: Entero, tamaño del archivo .txt
 *
 */

void llenaCarrito(nodoCola *carro, int *p, FILE *file, int fileSize)
{
	int i=0;	
	int *q = p;
	int *r = q;
	int mayor = *p;
	int tamanoMayor;
	int tamanoQ;
	int res=0;

	while(i<carro->key)
	{
		for(int j =0;j<carro->key;j++)
		{	
			j=j+res;
			
			if (*q != -1)
			{
				tamanoQ = atoi(getAttrib(file,fileSize,*q,1));
				tamanoMayor = atoi(getAttrib(file,fileSize,mayor,1));

				if ( tamanoQ >= tamanoMayor)
				{
					mayor = *q;
					r = q;
				}	
			}
			q++;
		}

		s_push(carro->itemStack,mayor);
		*r = -1;
		q = p;
		res=0;

		while(*q==-1)
		{
			q++;
			res++;
		}

		mayor = *q;
		i++;	
	}
}

/*
 *	@brief: Funcion llenaBanda: Llena la cola de la banda transportadora de elementos hasta su capacidad maxima 
 *
 *	@param: *carro: Apuntador al carrito que se va a llenar
 *	@param: *banda: Apuntador a la banda transportadora
 *	@param: *file: Apuntador al archivo .txt
 *	@param: fileSize: Entero, tamaño del archivo .txt
 *	@param: modalidad: Especifica la modalidad en la que esta siendo ejecutada la simulacion
 *
 */

void llenaBanda(nodoCola *carro, Cola *banda, FILE *file, int fileSize, int modalidad)
{
	int * item;
	int itemSize;
	char * itemCarrito;
	char * aux;

	if(!s_vacio(carro->itemStack))
	{

		item = s_peek(carro->itemStack);
		aux = getAttrib(file,fileSize,*item,1);
		itemSize = atoi(aux);
		free(aux);

		if(itemSize > banda->capacidad && banda->carga == 0)
		{
			item = s_pop(carro->itemStack);
			encolar(banda,*item);
			banda->carga = itemSize;
			free(item);
			//printf("Item grande! (%s)\n",getAttrib(file,fileSize,*item,0));
			//printf("%d+%d <= %d!!\n",itemSize,banda->carga,banda->capacidad);
			return;
				
		}
	
		while (banda->carga < banda->capacidad)
		{

			item = s_peek(carro->itemStack);
			aux = getAttrib(file,fileSize,*item,1);
			itemSize = atoi(aux);
			free(aux);

			if(banda->carga+itemSize <= banda->capacidad)
			{
				item = s_pop(carro->itemStack);
				//printf("Cargo un %s a la banda\n",getAttrib(file,fileSize,*item,0));
				//printf("%d+%d <= %d\n",itemSize,banda->carga,banda->capacidad);
				encolar(banda,*item);
				free(item);
				banda->carga = banda->carga+itemSize;
				//printf("Carga actual %d\n",banda->carga);

				if(s_vacio(carro->itemStack))
				{
					if (modalidad == 0)
					{
						printf("Carro vacio\n");	
					}
					
					break;	
				}
				
			}
			else
			{
				break;
			}
			
		}

		if (modalidad == 0)
		{
			if (carro->itemStack->top > 0)
			{
				printf("\n[Carro]: ");	
			}
			
			for (int k = 1; k < carro->itemStack->top + 1; k++)
			{
				aux =getAttrib(file,fileSize,carro->itemStack->items[k],0);
				itemCarrito = aux;
				printf("%s",itemCarrito);
				free(aux);

				if (k < carro->itemStack->top)
				{
					printf(", ");
				}
			}

			if (carro->itemStack->top > 0)
			{
				printf(".\n");
			}
		}
	}

	else
	{
		;
	}
}