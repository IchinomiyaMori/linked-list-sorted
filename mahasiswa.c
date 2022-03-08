#include <stdio.h>
#include <stdlib.h>

// create struct mahasiswa
struct mahasiswa {
  int nim;
  char nama[100];
  int nilai_a;
  int nilai_b;
  // pointer to next / prev mahasiswa
  struct mahasiswa *next;
  struct mahasiswa *prev;
};

// push mahasiswa to list
void push(struct mahasiswa **head, struct mahasiswa **tail, struct mahasiswa *mhs) {
  // if list is empty
  if (*head == NULL) {
    *head = mhs;
    *tail = mhs;
  } else {
    // insert to the end of list
    (*tail)->next = mhs;
    mhs->prev = *tail;
    *tail = mhs;
  }
}

// showlist with number
void showlist(struct mahasiswa *head) {
  int i = 1;
  while (head != NULL) {
    printf("%d. %s\n", i, head->nama);
    head = head->next;
    i++;
  }
}

// mergesort list by nim ascending
void mergesort(struct mahasiswa **head, struct mahasiswa **tail) {
  // if list is empty or has only one element
  if (*head == NULL || (*head)->next == NULL) {
    return;
  }

  // split list into two sublists
  struct mahasiswa *mid = *head;
  struct mahasiswa *mid_next = mid->next;
  while (mid_next != NULL) {
    mid = mid->next;
    mid_next = mid_next->next;
    if (mid_next != NULL) {
      mid_next = mid_next->next;
    }
  }

  // recursively sort each sublist
  mergesort(head, &mid->prev);
  mergesort(&mid->next, tail);

  // merge the two sorted sublists
  struct mahasiswa *p1 = *head;
  struct mahasiswa *p2 = mid->next;
  struct mahasiswa *tmp;
  while (p1 != mid && p2 != NULL) {
    if (p1->nim <= p2->nim) {
      tmp = p1;
      p1 = p1->next;
    } else {
      tmp = p2;
      p2 = p2->next;
    }
    tmp->prev = tmp->next = NULL;
    push(head, tail, tmp);
  }
  while (p1 != mid) {
    tmp = p1;
    p1 = p1->next;
    tmp->prev = tmp->next = NULL;
    push(head, tail, tmp);
  }
  while (p2 != NULL) {
    tmp = p2;
    p2 = p2->next;
    tmp->prev = tmp->next = NULL;
    push(head, tail, tmp);
  }
}

int main() {
  // input nim, nama, nilai a, nilai b
  int nim, nilai_a, nilai_b;
  char nama[100];

  // create menu selection
  int menu;

  // add struct mahasiswa
  struct mahasiswa mhs;

  // create head and tail
  struct mahasiswa *head = NULL;
  struct mahasiswa *tail = NULL;

  // switch menu
  while (1) {
    printf("\nMenu\n");
    printf("1. Add\n");
    printf("2. Show\n");
    printf("3. Sort\n");
    printf("4. Exit\n");
    printf("Pilih menu: ");
    scanf("%d", &menu);

    switch (menu) {
    case 1:
      // input nim, nama, nilai a, nilai b
      printf("NIM: ");
      scanf("%d", &nim);
      printf("Nama: ");
      scanf("%s", nama);
      printf("Nilai A: ");
      scanf("%d", &nilai_a);
      printf("Nilai B: ");
      scanf("%d", &nilai_b);

      // create struct mahasiswa
      mhs.nim = nim;
      strcpy(mhs.nama, nama);
      mhs.nilai_a = nilai_a;
      mhs.nilai_b = nilai_b;

      // push mahasiswa to list
      push(&head, &tail, &mhs);
      break;
    case 2:
      // show list
      showlist(head);
      break;
    case 3:
      // sort
      mergesort(&head, &tail);
      break;  
    case 4:
      // exit
      exit(0);
      break;
    default:
      printf("Menu tidak ada\n");
      break;
    }
  }

  return 0;
}
