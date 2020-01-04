#include <stdio.h>
#include <stdlib.h>

//List structure:
struct El 
{
	int  info;
	struct  El *next;
};

typedef struct El  ElementoLista;


// Functions/Procedure  to be implemented:
ElementoLista* readList(ElementoLista **lista, int dis);
int maxDistance(ElementoLista *lista);
ElementoLista* CancellaMax(ElementoLista **lista, int maxdis);

//Function to print all the elements of the list:
void printList(ElementoLista *list) 
{
	printf("(");
	while (list != NULL) 
    {
		printf("%d ", list->info);
		list = list->next;
	}
	printf(")\n");
}

int main() 
{
	ElementoLista *list = NULL, *list_aux = NULL;
	int boundis, maxdis;

	//Read the  bounded distance
	scanf("%d", &boundis);

	//Read and print the list
	list_aux = readList(&list, boundis);

	printf("La lista bounded-%d e':\n", boundis);

	if (list_aux != NULL)
	{
		list = list_aux;
		list_aux = NULL;
	}

	printList(list);

	//Compute and print the maxdistance of the  list
	maxdis = maxDistance(list);
	printf("La distanza massima e':\n%d\n", maxdis);

	//Removes the elements at distance maxdistance
	list_aux = CancellaMax(&list, maxdis);
    
	printf("La lista modificata e':\n");

	if (list_aux != NULL) list = list_aux;

	printList(list);
	return 0;
}


ElementoLista *ins(ElementoLista *lista, int el)
{
    ElementoLista *ult = lista;
    ElementoLista *new = malloc(sizeof(ElementoLista));

    new->info = el;
    new->next = NULL;

    if(lista == NULL)
        return new;
    
    while (ult->next != NULL)
        ult = ult->next;
    
    ult->next = new;

    return lista;
}

ElementoLista* readList(ElementoLista **lista, int dis)
{
    int n, prec;

    scanf("%d", &n);

    *lista = malloc(sizeof(ElementoLista));

    ElementoLista *head = *lista;

    ins(*lista, n);
    prec = n;
    scanf("%d", &n);
    *lista = (*lista)->next;

    while(abs(prec-n) <= dis)
    {
        ins(*lista, n);
        prec = n;
        scanf("%d", &n);
        *lista = (*lista)->next;
    }

    return head->next;
}

int maxDistance(ElementoLista *lista)
{
    ElementoLista *tmp = lista;
    int dis, max = abs(tmp->info - tmp->next->info);

    tmp = tmp->next;

    while(tmp->next != NULL)
    {
        dis = abs(tmp->info - tmp->next->info);
        if(dis > max)
            max = dis;

        tmp = tmp->next;
    }

    return max;
}

ElementoLista *CancellaMax(ElementoLista **lista, int maxdis)
{
    ElementoLista *tmp = (*lista)->next, 
                  *current = *lista,
                  *prev = NULL;
    int dis;
                  
    
    while(current->next != NULL)
    {
        dis = abs(current->info - tmp->info);

        //Head
        if(prev == NULL)
    
            //There is something to delete
            if(dis == maxdis)
            {
                free(current);
                *lista = tmp;
                current = tmp;
                tmp = tmp->next;
            }
            //Nothing to delete
            else
            {
                prev = *lista;
                current = current->next;
                tmp = tmp->next;
            }   
    
        //NOT head
        else
    
            //There is something to delete
            if(dis == maxdis)
            {
                prev->next = tmp;
                free(current);
                current = tmp;
                tmp = tmp->next;
            }
            //Nothing to delete
            else
            {
                prev = current;
                current = current->next;
                tmp = tmp->next;
            }
    
    }

    return *lista;
}
