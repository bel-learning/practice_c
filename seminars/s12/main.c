#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem * m_Next;
  int      m_Val;
} TITEM;

typedef struct TData
{
  TITEM * m_First;
  TITEM * m_Last;
} TDATA;

#endif /* __PROGTEST__ */

void insertStart ( TDATA * l, int x )
{
  /* TODO */
  // if it's the first element then both head and tail points to same place
  TITEM * newItem = (TITEM*) malloc (sizeof(TITEM));

  newItem->m_Val = x;

  if(l->m_First == NULL || l->m_Last == NULL) {
    newItem->m_Next = NULL;
    l->m_First = newItem;
    l->m_Last = newItem;
    return;
  }

  newItem->m_Next = l->m_First;
  l->m_First = newItem;
  return;
}
void insertEnd   ( TDATA * l, int x )
{
  /* TODO */
  TITEM * newItem = (TITEM*) malloc (sizeof(TITEM));
  newItem->m_Val = x;
  newItem->m_Next = NULL;
  // if there is no element to begin with;
  if(l->m_First == NULL || l->m_Last == NULL) {
    l->m_First = newItem;
    l->m_Last = newItem;
    return;
  }

  l->m_Last->m_Next = newItem;
  l->m_Last = newItem;
  return;

}

void removeLast (TDATA * l) {
  printf("Removing last element\n");
  if(l->m_First == NULL || l->m_Last == NULL)
    return;
  if(l->m_First == l->m_Last) {
    free(l->m_Last);
    l->m_First = NULL;
    l->m_Last = NULL;
    return;
  }
  
  TITEM * second_Last = l->m_First; 
  
  while(second_Last->m_Next != l->m_Last) {
      second_Last = second_Last ->m_Next;
  }

  l->m_Last = second_Last;
  TITEM * tmp = second_Last->m_Next;
  second_Last->m_Next = NULL;
  free(tmp);
  printf("Done\n");
  return;
}
int  removeMax   ( TDATA * l )
{
  /* TODO */
  // if the list is empty
  if(l->m_First == NULL || l->m_Last == NULL) {
    return 0;
  }
  // if there is only 1 element
  if(l->m_First == l->m_Last) {
    free(l->m_First);
    l->m_First = NULL;
    l->m_Last = NULL;
    return 1;
  }

  TITEM * current = l->m_First;
  int max = l->m_First->m_Val;
  // finds the maximum;
  while(current) {
    if(max < current->m_Val) {
      max = current->m_Val;
    }
    current = current->m_Next;
  }
  
  current = l->m_First;
  int cnt = 0;
  printf("max: %d\n", max);
  while(current) {
    if(current->m_Val == max) {
      // if the first element is the max

      if(current == l->m_First) {
        l->m_First = current->m_Next;
        TITEM * tmp = current;
        current = current->m_Next;
        free(tmp);
        cnt++;
        continue;
      }
      if(current == l->m_Last) {
        removeLast(l);
        cnt++;
        current = l->m_Last;
        continue;
      }
      
      // remove in between normal element
      TITEM * previous = l->m_First;
      while(previous->m_Next != current) {
        previous = previous->m_Next;
      }
      previous->m_Next = current->m_Next;
      TITEM * tmp = current;
      current = current->m_Next;
      free(tmp);
      cnt++;
      continue;
    }
    current = current->m_Next; 
  }
  return cnt;
}
void destroyAll  ( TDATA * l )
{
  /* TODO */
  TITEM * current = l->m_First;
  while(current) {
    TITEM * tmp = current;
    current = current->m_Next;
    free(tmp);
  }
  l->m_First = NULL;
  l->m_Last = NULL;
}
void printLinkedList( TDATA * l) {
  printf("List: ");
  TITEM * current = l->m_First;
  while(current) {
    printf("%d -> ", current->m_Val);
    current = current->m_Next;
  }
  printf("\n");
}


#ifndef __PROGTEST__
int main ( void )
{
  TDATA a;
  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 1 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 4 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 5 );
  printf("First assert: \n");
  printLinkedList(&a);
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 5
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  printf("Done\n");
  printLinkedList(&a);

  assert ( removeMax ( &a ) == 1 );
  printf("Should remove 5s\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  destroyAll ( &a );
  printf("All element must be removed\n");
  printLinkedList(&a);
  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 0 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertStart ( &a, 1 );
  insertStart ( &a, 2 );
  insertStart ( &a, 3 );
  printf("Insert elements\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 3
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 3 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 3 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 2 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 0
           && a . m_First -> m_Next == NULL
           && a . m_Last == a . m_First );
  destroyAll ( &a );

  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, -1 );
  insertEnd ( &a, -2 );
  insertEnd ( &a, -10000 );
  insertEnd ( &a, -1 );
  insertEnd ( &a, -300 );
  assert ( removeMax ( &a ) == 2 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == -2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == -10000
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == -300
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next );
  destroyAll ( &a );
  a . m_First = a . m_Last = NULL;
  insertEnd (&a, 2);
  insertEnd (&a, 2);

  assert ( removeMax (&a) == 2);
  printLinkedList(&a);
  return 0;
}
#endif /* __PROGTEST__ */
