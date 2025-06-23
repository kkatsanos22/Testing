# progii


# Project: Phonebook & Data Structures (Programming II Exercises)

This repository contains the implementation and solution of exercises inspired by dynamic arrays, linked lists, file I/O, process management, and signal handling, based on the Programming II course (Lecture 2 and beyond).

---

## Συνόλο Άσκησης (Summary)

### Ερώτηση 1

**Εκφώνηση:**

> Στη διάλεξη 2 περιλαμβάνεται κώδικας για την υλοπίηση ενός phonebook ως δυναμικού πίνακα από εγγραφές. Αντέγραψε τον κώδικα σε ένα αρχείο C και πρόσθεσε:
>
> * Συνάρτηση `phonebook_print`
> * `main()` με επανάληψη για εισαγωγή εγγραφών.

```c
[πλήρης κώδικας phonebook με dynamic array]

```
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[64];
    char phone[64];
} entry;

typedef struct {
    entry *entries;
    int size;
} phonebook;

void phonebook_init(phonebook *pb) {
    pb->entries = NULL;
    pb->size = 0;
}

void phonebook_clear(phonebook *pb) {
    if (pb->size > 0) {
        free(pb->entries);
        pb->entries = NULL;
        pb->size = 0;
    }
}

int basic_find(const phonebook *pb, const char *name) {
    int i;
    for (i = 0; i < pb->size && strcmp(pb->entries[i].name, name); i++);
    return i;
}

int phonebook_find(const phonebook *pb, const char *name, char *phone) {
    int pos = basic_find(pb, name);
    if (pos == pb->size) return 0;
    strcpy(phone, pb->entries[pos].phone);
    return 1;
}

int phonebook_add(phonebook *pb, const char *name, const char *phone) {
    int pos = basic_find(pb, name);
    if (pos < pb->size) {
        strcpy(pb->entries[pos].phone, phone);
        return 2;
    }

    entry *entries = realloc(pb->entries, (pb->size + 1) * sizeof(entry));
    if (entries == NULL) return 0;

    pb->entries = entries;
    strcpy(pb->entries[pb->size].name, name);
    strcpy(pb->entries[pb->size].phone, phone);
    pb->size++;
    return 1;
}

int phonebook_rmv(phonebook *pb, const char *name) {
    int pos = basic_find(pb, name);
    if (pos == pb->size) return 0;

    pb->size--;
    pb->entries[pos] = pb->entries[pb->size];
    pb->entries = realloc(pb->entries, pb->size * sizeof(entry));
    return 1;
}

void phonebook_print(const phonebook *pb) {
    printf("=== PHONEBOOK (%d entries) ===\n", pb->size);
    for (int i = 0; i < pb->size; i++) {
        printf("%d. %s : %s\n", i + 1, pb->entries[i].name, pb->entries[i].phone);
    }
    printf("==============================\n");
}

int main() {
    phonebook pb;
    phonebook_init(&pb);

    int choice;
    char name[64], phone[64];

    do {
        printf("\n--- Phonebook Menu ---\n");
        printf("1. Add Entry\n");
        printf("2. Remove Entry\n");
        printf("3. Find Entry\n");
        printf("4. Print Phonebook\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Name: ");
                fgets(name, 64, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Phone: ");
                fgets(phone, 64, stdin);
                phone[strcspn(phone, "\n")] = 0;
                int res = phonebook_add(&pb, name, phone);
                if (res == 1) printf("Entry added.\n");
                else if (res == 2) printf("Phone updated.\n");
                else printf("Failed to add entry.\n");
                break;
            case 2:
                printf("Name to remove: ");
                fgets(name, 64, stdin);
                name[strcspn(name, "\n")] = 0;
                if (phonebook_rmv(&pb, name)) printf("Entry removed.\n");
                else printf("Entry not found.\n");
                break;
            case 3:
                printf("Name to find: ");
                fgets(name, 64, stdin);
                name[strcspn(name, "\n")] = 0;
                if (phonebook_find(&pb, name, phone))
                    printf("Found: %s\n", phone);
                else
                    printf("Entry not found.\n");
                break;
            case 4:
                phonebook_print(&pb);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    phonebook_clear(&pb);
    return 0;
}

```
---

### Ερώτηση 2

**Εκφώνηση:**

> Αφού ολοκληρώσεις το #1, άλλαξε τον κώδικα ώστε το phonebook να υλοποιείται ως δυναμικός πίνακας από δείκτες σε εγγραφές.

**Απάντηση:**
Αντί `entry *entries`, ορίζουμε `entry **entries`. Κάθε `entry` δημιουργείται με `malloc()` ξεχωριστά. Η διαγραφή και η εκκαθάριση χρειάζονται `free()` για κάθε `entry*`.

script:
```c
typedef struct {
    entry **entries; // δείκτες προς δυναμικά entries
    int size;
} phonebook;

```
Δηλαδή:
    Κάθε νέα εγγραφή γίνεται με malloc() για entry.

    Το realloc() αφορά μόνο τον πίνακα δεικτών (entry **).

    Στο phonebook_clear() κάνουμε free() κάθε entry*.

➡️ Πλεονέκτημα: Αντί για αντιγραφή ολόκληρων δομών, μετακινούμε απλώς δείκτες (πολύ πιο αποδοτικό).

---

### Ερώτηση 3

**Εκφώνηση:**

> Γράψε ένα πρόγραμμα στο οποίο φτιάχνεις μια απλά διασυνδεδεμένη λίστα ακεραίων, προσθέτεις μερικούς ακέραιους σε αυτή και εκτυπώνεις τα περιεχόμενά της.

```c
typedef struct node {
    int value;
    struct node *next;
} node;

void list_print(node *head) {
    while (head) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

```

---

### Ερώτηση 4

**Εκφώνηση:**

> Πρόσθεσε κώδικα στο #3 που ζητάει από τον χρήστη έναν ακέραιο και αφαιρεί από τη λίστα τον κόμβο που περιέχει αυτόν τον ακέραιο. Πρώτα για μία εμφάνιση και μετά για όλες.

 ORIGINAL:Πρόσθεσε κώδικα στο #3 που ζητάει από τον χρήστη έναν ακέραιο και αφαιρεί από τη 
λίστα τον κόμβο που περιέχει αυτόν τον ακέραιο (αν υπάρχει) απελευθερώνοντας την 
μνήμη του κόμβου. Αρχικά, γράψε κώδικα κάνοντας την υπόθεση ότι μια τιμή μπορεί να 
υπάρχει το πολύ μια φορά στην λίστα. Στην συνέχεια, άλλαξε τον κώδικα σου ώστε σε 
περίπτωση που μια τιμή υπάρχει περισσότερες από μια φορές στην λίστα, να αφαιρεί 
όλους τους αντίστοιχους κόμβους.  

```c
///1η Εκδοση
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

void list_print(node *head) {
    while (head) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

void remove_value_once(node **head_ref, int target) {
    node *current = *head_ref;
    node *prev = NULL;

    while (current != NULL) {
        if (current->value == target) {
            if (prev == NULL) {
                // Το στοιχείο είναι στην αρχή της λίστας
                *head_ref = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    // Δημιουργία απλής λίστας για παράδειγμα
    node *head = malloc(sizeof(node));
    head->value = 1;
    head->next = malloc(sizeof(node));
    head->next->value = 2;
    head->next->next = malloc(sizeof(node));
    head->next->next->value = 3;
    head->next->next->next = NULL;

    list_print(head);

    int x;
    printf("Δώσε έναν ακέραιο προς αφαίρεση: ");
    scanf("%d", &x);
    remove_value_once(&head, x);

    list_print(head);

    // Απελευθέρωση μνήμης
    while (head) {
        node *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}

```


```c 
///2η εκδοση

void remove_all_occurrences(node **head_ref, int target) {
    node *current = *head_ref;
    node *prev = NULL;

    while (current != NULL) {
        if (current->value == target) {
            node *to_delete = current;
            if (prev == NULL) {
                *head_ref = current->next;
                current = *head_ref;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}
void remove_all_occurrences(node **head_ref, int target) {
    node *current = *head_ref;
    node *prev = NULL;

    while (current != NULL) {
        if (current->value == target) {
            node *to_delete = current;
            if (prev == NULL) {
                *head_ref = current->next;
                current = *head_ref;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

```


---

### Ερώτηση 5

**Εκφώνηση:**

> Κάνε τις ασκήσεις #3 και #4 αλλά με λίστα που είναι διπλά-διασυνδεδεμένη, κυκλική με sentinel.

```c
// Βασικες δομες κωδικα
#include <stdio.h>
#include <stdlib.h>

// Ορισμός κόμβου: διπλά διασυνδεδεμένος
typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

// Εκτύπωση της λίστας
void list_print(node *sentinel) {
    node *current = sentinel->next;
    while (current != sentinel) {
        printf("%d <-> ", current->value);
        current = current->next;
    }
    printf("SENTINEL\n");
}

// Δημιουργία και προσθήκη νέου κόμβου στο τέλος
void list_append(node *sentinel, int value) {
    node *new_node = malloc(sizeof(node));
    new_node->value = value;

    node *last = sentinel->prev;

    new_node->next = sentinel;
    new_node->prev = last;

    last->next = new_node;
    sentinel->prev = new_node;
}

int main() {
    // Δημιουργία sentinel
    node *sentinel = malloc(sizeof(node));
    sentinel->next = sentinel;
    sentinel->prev = sentinel;

    // Προσθήκη στοιχείων
    list_append(sentinel, 1);
    list_append(sentinel, 2);
    list_append(sentinel, 3);
    list_append(sentinel, 2);
    list_append(sentinel, 4);

    printf("Αρχική λίστα:\n");
    list_print(sentinel);

    int x;
    printf("Δώσε ακέραιο για διαγραφή: ");
    scanf("%d", &x);

    // 1η εκδοχή: διαγράφει ΜΟΝΟ ΜΙΑ φορά
    // remove_value_once(sentinel, x);

    // 2η εκδοχή: διαγράφει ΟΛΕΣ τις εμφανίσεις
    remove_all_occurrences(sentinel, x);

    printf("Τελική λίστα:\n");
    list_print(sentinel);

    // Απελευθέρωση μνήμης
    node *curr = sentinel->next;
    while (curr != sentinel) {
        node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(sentinel);

    return 0;
}

```
```c
///1η Εκδοση
void remove_value_once(node *sentinel, int target) {
    node *current = sentinel->next;
    while (current != sentinel) {
        if (current->value == target) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return; // ΜΟΝΟ η πρώτη εμφάνιση
        }
        current = current->next;
    }
}


```


```c
///2η Εκδοση
void remove_all_occurrences(node *sentinel, int target) {
    node *current = sentinel->next;
    while (current != sentinel) {
        if (current->value == target) {
            node *to_delete = current;
            current = current->next;

            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
            free(to_delete);
        } else {
            current = current->next;
        }
    }
}

```

---

### Ερώτηση 6

**Εκφώνηση:**

> Οι πίνακες κατακερματισμού είναι ουσιαστικά πίνακες από δείκτες σε λίστες. Αν έχεις καταλάβει τα παραπάνω, δεν πρέπει να έχεις πρόβλημα να φτιάξεις κάτι τέτοιο.

```c
#define TABLE_SIZE 100

typedef struct hashnode {
    char *key;
    char *value;
    struct hashnode *next;
} hashnode;

hashnode *table[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int h = 0;
    while (*key)
        h = (h << 5) + *key++;
    return h % TABLE_SIZE;
}

void insert(const char *key, const char *value) {
    unsigned int i = hash(key);
    hashnode *n = malloc(sizeof(hashnode));
    n->key = strdup(key);
    n->value = strdup(value);
    n->next = table[i];
    table[i] = n;
}
```
ΚΑΝΟΝΙΚΗ ΑΠΑΝΤΗΣΗ

### Hash Table με Χειρισμό Συγκρούσεων μέσω Λιστών (Chaining)

Αυτό το αρχείο εξηγεί και παρουσιάζει μια απλή υλοποίηση **πίνακα κατακερματισμού (hash table)** σε γλώσσα **C**, με χρήση:

- Πίνακα από δείκτες σε λίστες (`node* table[N]`)
- Αλυσίδωση (chaining) για αντιμετώπιση συγκρούσεων
- Συνάρτηση κατακερματισμού: `index = value % N`


#### Τι είναι οι Πίνακες Κατακερματισμού;

Ένας πίνακας κατακερματισμού (hash table) είναι μια δομή δεδομένων που επιτρέπει **γρήγορη αποθήκευση και αναζήτηση** στοιχείων. Βασίζεται σε έναν πίνακα όπου κάθε θέση (κάδος) δείχνει σε μια λίστα στοιχείων.

Όταν προσπαθούμε να βάλουμε ένα στοιχείο, η συνάρτηση κατακερματισμού μας λέει σε ποιον κάδο θα το τοποθετήσουμε. Αν ο κάδος είναι ήδη γεμάτος (σύγκρουση), προσθέτουμε το νέο στοιχείο στη λίστα που αντιστοιχεί σε αυτόν.


##### Δομή Δεδομένων

```c
typedef struct node {
    int value;
    struct node* next;
} node;

#define SIZE 10
node* table[SIZE];
```c
####Συνάρτηση Κατακερματισμού
int index = value % SIZE;
```
```c
#### Εισαγωγή στοιχείου
void insert(int x) {
    int index = x % SIZE;
    node* new_node = malloc(sizeof(node));
    new_node->value = x;
    new_node->next = table[index];
    table[index] = new_node;
}
 ///εκτυπωση
void print_table() {
    for (int i = 0; i < SIZE; i++) {
        printf("Κάδος %d: ", i);
        node* current = table[i];
        while (current) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}
```
ΠΧ

```c
///main
int main() {
    for (int i = 0; i < SIZE; i++)
        table[i] = NULL;

    insert(15); // 15 % 10 = 5
    insert(25); // 25 % 10 = 5 (σύγκρουση με 15)
    insert(9);  // 9 % 10 = 9
    insert(3);  // 3 % 10 = 3

    print_table();
    return 0;
}
``` 

και output 
```c
Κάδος 0: NULL
Κάδος 1: NULL
Κάδος 2: NULL
Κάδος 3: 3 -> NULL
Κάδος 4: NULL
Κάδος 5: 25 -> 15 -> NULL
Κάδος 6: NULL
Κάδος 7: NULL
Κάδος 8: NULL
Κάδος 9: 9 -> NULL

```




---

### Ερώτηση 7

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 11. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις.


---

### Ερώτηση 8

**Εκφώνηση:**

> Γράψε πρόγραμμα που δημιουργεί αρχείο και γράφει λέξεις 5 γραμμάτων. Ύστερα, αναζητά και εκτυπώνει την ν-οστή λέξη.

```c
FILE *fp = fopen("words.txt", "w+");
char word[6];
for (int i = 0; i < 10; i++) {
    scanf("%5s", word);
    fprintf(fp, "%s\n", word);
}
fseek(fp, 0, SEEK_SET);
int n;
scanf("%d", &n);
for (int i = 0; i < n - 1 && fgets(word, 6, fp); i++);
if (fgets(word, 6, fp))
    printf("%s\n", word);
else
    printf("Δεν υπάρχει τέτοια λέξη.\n");
fclose(fp);
```

ΕΞηγηση

**Εξήγηση προγράμματος**

Το πρόγραμμα κάνει τα εξής:

1. Δημιουργεί ή ανοίγει το αρχείο "words.txt" για εγγραφή και ανάγνωση.
2. Διαβάζει από τον χρήστη 10 λέξεις, η κάθε μία μέχρι 5 χαρακτήρες.
3. Αποθηκεύει αυτές τις λέξεις στο αρχείο, μία λέξη σε κάθε γραμμή.
4. Μετακινεί τον δείκτη του αρχείου στην αρχή.
5. Διαβάζει έναν ακέραιο αριθμό n από τον χρήστη.
6. Διαβάζει και αγνοεί τις πρώτες n-1 λέξεις από το αρχείο.
7. Προσπαθεί να διαβάσει την ν-οστή λέξη και αν υπάρχει, την εκτυπώνει.
8. Αν η ν-οστή λέξη δεν υπάρχει (π.χ. αν το n είναι μεγαλύτερο από 10), τυπώνει το μήνυμα "Δεν υπάρχει τέτοια λέξη.".
9. Κλείνει το αρχείο.



**Λεπτομέρειες κώδικα:**

* `FILE *fp = fopen("words.txt", "w+");`
  Ανοίγει το αρχείο για εγγραφή και ανάγνωση, διαγράφοντας το προηγούμενο περιεχόμενο.

* `char word[6];`
  Πίνακας χαρακτήρων για αποθήκευση λέξης μήκους 5 χαρακτήρων + τερματικό χαρακτήρα.

* Βρόχος `for` με `scanf("%5s", word);`
  Διαβάζει 10 λέξεις από τον χρήστη.

* `fprintf(fp, "%s\n", word);`
  Γράφει κάθε λέξη στο αρχείο με αλλαγή γραμμής.

* `fseek(fp, 0, SEEK_SET);`
  Επαναφέρει το δείκτη αρχείου στην αρχή για ανάγνωση.

* `scanf("%d", &n);`
  Διαβάζει τη θέση της λέξης που θέλουμε να εμφανίσουμε.

* Βρόχος `for` με `fgets(word, 6, fp);`
  Αγνοεί τις πρώτες n-1 λέξεις.

* `if (fgets(word, 6, fp))`
  Αν διαβάσει τη ν-οστή λέξη, την εκτυπώνει, αλλιώς τυπώνει μήνυμα λάθους.

* `fclose(fp);`
  Κλείνει το αρχείο.


### Ερώτηση 9

**Εκφώνηση:**

> Ξανακάνε την άσκηση #8 αλλά με εγγραφή και ανάγνωση δυαδικών ακεραίων (int).

```c
FILE *fp = fopen("nums.bin", "wb+");
int num;
for (int i = 0; i < 10; i++) {
    scanf("%d", &num);
    fwrite(&num, sizeof(int), 1, fp);
}
int n;
scanf("%d", &n);
fseek(fp, (n - 1) * sizeof(int), SEEK_SET);
if (fread(&num, sizeof(int), 1, fp))
    printf("%d\n", num);
else
    printf("Δεν υπάρχει τέτοιος αριθμός.\n");
fclose(fp);
```

Ας κάνουμε μία εξήγηση σε απλό κείμενο (txt) για αυτή τη νέα άσκηση που ζητάει εγγραφή και ανάγνωση δυαδικών (binary) ακεραίων.


**Εξήγηση προγράμματος (δυαδικοί ακέραιοι)**

Το πρόγραμμα:

1. Δημιουργεί ή ανοίγει το αρχείο `"nums.bin"` σε δυαδική μορφή για εγγραφή και ανάγνωση (`"wb+"`).
2. Διαβάζει από τον χρήστη 10 ακέραιους αριθμούς.
3. Αποθηκεύει αυτούς τους αριθμούς στο αρχείο σε δυαδική μορφή (με `fwrite`).
4. Διαβάζει έναν ακέραιο `n` που δείχνει ποιον αριθμό θέλουμε να αναζητήσουμε.
5. Μετακινεί τον δείκτη του αρχείου στη θέση που αντιστοιχεί στον (n-1)-οστό ακέραιο (λόγω μηδενικής βάσης, χρησιμοποιεί `(n-1) * sizeof(int)`).
6. Διαβάζει έναν ακέραιο (`fread`) από αυτή τη θέση.
7. Αν υπάρχει αριθμός, τον εκτυπώνει.
8. Αν όχι, τυπώνει μήνυμα ότι δεν υπάρχει τέτοιος αριθμός.
9. Κλείνει το αρχείο.

**Λεπτομέρειες κώδικα:**

* `FILE *fp = fopen("nums.bin", "wb+");`
  Ανοίγει ή δημιουργεί το αρχείο `"nums.bin"` σε δυαδική μορφή για εγγραφή και ανάγνωση, διαγράφοντας το περιεχόμενο.

* `int num;`
  Μεταβλητή για αποθήκευση ακέραιου.

* Βρόχος `for (int i = 0; i < 10; i++)` με `scanf("%d", &num);`
  Διαβάζει 10 ακέραιους από τον χρήστη.

* `fwrite(&num, sizeof(int), 1, fp);`
  Γράφει τον ακέραιο στο αρχείο σε δυαδική μορφή.

* `scanf("%d", &n);`
  Διαβάζει τον ακέραιο `n` που δείχνει ποιον αριθμό θέλουμε να διαβάσουμε.

* `fseek(fp, (n - 1) * sizeof(int), SEEK_SET);`
  Μετακινεί τον δείκτη αρχείου στην θέση του ν-οστού αριθμού.

* `fread(&num, sizeof(int), 1, fp)`
  Διαβάζει έναν ακέραιο από το αρχείο.

* Αν το `fread` πετύχει, τυπώνει τον αριθμό, αλλιώς τυπώνει μήνυμα ότι δεν υπάρχει αριθμός.

* `fclose(fp);`
  Κλείνει το αρχείο.


### Ερώτηση 10

**Εκφώνηση:**

> Αν βρεθεί η ν-οστή εγγραφή, να αντιγράφεται στο τέλος του αρχείου. Ισχύει και για #9.

```c
// Στην περίπτωση αρχείου με λέξεις:
fseek(fp, (n - 1) * 6, SEEK_SET);
if (fgets(word, 6, fp)) {
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s\n", word);
}
```
#### Για την 8

```c
FILE *fp = fopen("words.txt", "r+");  // Άνοιγμα για ανάγνωση/εγγραφή χωρίς να διαγραφεί περιεχόμενο
if (!fp) {
    printf("Σφάλμα ανοίγματος αρχείου.\n");
    return 1;
}

char word[6];
int n;
scanf("%d", &n);

// Μετακινούμαστε στην ν-οστή λέξη
for (int i = 0; i < n - 1 && fgets(word, sizeof(word), fp); i++);
if (fgets(word, sizeof(word), fp)) {
    printf("Η λέξη είναι: %s", word);

    // Μετακινούμαστε στο τέλος του αρχείου για προσθήκη
    fseek(fp, 0, SEEK_END);

    // Γράφουμε ξανά τη λέξη στο τέλος
    fprintf(fp, "%s", word);
} else {
    printf("Δεν υπάρχει τέτοια λέξη.\n");
}

fclose(fp);

```
Εξηγηση

Τι κάνει:
Άνοιγμα αρχείου με "r+":
Δηλαδή ανοίγει το αρχείο για ανάγνωση και εγγραφή, χωρίς να διαγραφεί το περιεχόμενο που ήδη υπάρχει.

Διαβάζει έναν ακέραιο n:
Τη θέση της λέξης που θέλουμε να βρούμε.

Μετακίνηση στο αρχείο και εύρεση της ν-οστής λέξης:
Με τη βοήθεια του βρόχου for και της fgets αγνοεί τις πρώτες n-1 λέξεις και διαβάζει τη ν-οστή.

Αν η λέξη βρεθεί, την τυπώνει στην οθόνη.

Μετακινείται στο τέλος του αρχείου με fseek(fp, 0, SEEK_END);.

Γράφει ξανά την ίδια λέξη στο τέλος του αρχείου (fprintf), δηλαδή την αντιγράφει πίσω από όλες τις υπάρχουσες λέξεις.

Κλείνει το αρχείο.



#### Για την 9
```c
FILE *fp = fopen("nums.bin", "rb+");  // Άνοιγμα για ανάγνωση/εγγραφή χωρίς διαγραφή περιεχομένου
if (!fp) {
    printf("Σφάλμα ανοίγματος αρχείου.\n");
    return 1;
}

int num;
int n;
scanf("%d", &n);

// Μετακινούμαστε στη θέση του ν-οστού ακέραιου
if (fseek(fp, (n - 1) * sizeof(int), SEEK_SET) == 0 && fread(&num, sizeof(int), 1, fp) == 1) {
    printf("Ο αριθμός είναι: %d\n", num);

    // Πάμε στο τέλος του αρχείου για προσθήκη
    fseek(fp, 0, SEEK_END);

    // Γράφουμε τον αριθμό ξανά στο τέλος
    fwrite(&num, sizeof(int), 1, fp);
} else {
    printf("Δεν υπάρχει τέτοιος αριθμός.\n");
}

fclose(fp);

```

Εξηγηση

Τι κάνει:
Άνοιγμα αρχείου με "rb+":
Δηλαδή ανοίγει το αρχείο για ανάγνωση και εγγραφή δυαδικών δεδομένων, χωρίς να διαγραφεί το περιεχόμενο.

Διαβάζει έναν ακέραιο n:
Τη θέση του αριθμού που θέλουμε να βρούμε.

Μετακινείται στο αρχείο στη θέση του ν-οστού ακέραιου:
Η θέση υπολογίζεται με (n-1) * sizeof(int) γιατί κάθε ακέραιος έχει σταθερό μέγεθος.

Διαβάζει τον ακέραιο στην αντίστοιχη θέση.

Αν βρεθεί ο αριθμός, τον τυπώνει.

Μετακινείται στο τέλος του αρχείου.

Γράφει ξανά τον αριθμό στο τέλος του αρχείου (fwrite), δηλαδή τον αντιγράφει στο τέλος.

Κλείνει το αρχείο.

Γιατί κάνουμε έτσι;
Το άνοιγμα σε "r+" και "rb+" αντί για "w+" ή "wb+" επιτρέπει να μην σβήνουμε τα ήδη υπάρχοντα δεδομένα στο αρχείο.

Με το fseek στο τέλος μπορούμε να προσθέσουμε νέα δεδομένα, χωρίς να σβήσουμε τα παλιά.

Με αυτόν τον τρόπο, η ν-οστή εγγραφή (λέξη ή αριθμός) διατηρείται και επαναγράφεται στο τέλος, δηλαδή αντιγράφεται.

Αν δεν υπάρχει η εγγραφή (λέξη ή αριθμός) στην θέση n, τότε εμφανίζεται κατάλληλο μήνυμα.
---

### Ερώτηση 11

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 12. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις. Τρέξε τα. Βλέπεις τα αποτελέσματα που περίμενες;


---

### Ερώτηση 12

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 16. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις. Τρέξε τα.


---

### Ερώτηση 13

**Εκφώνηση:**

> Ξεκίνα από πρόγραμμα με fork/printf. Τι εκτυπώνεται; Τι αλλάζει αν γίνει return στον κώδικα του παιδιού;

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        return 7;
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child exited with %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}
```
Εξηγηση

### Τι κάνει το πρόγραμμα:

1. Καλεί `fork()` και δημιουργεί μια νέα διεργασία — το **παιδί** (child) και ο γονιός (parent).

2. Ο κώδικας μετά το `fork()` εκτελείται **και από το παιδί και από τον γονιό**, αλλά με διαφορετικά `pid`:

   * `pid == 0` σημαίνει πως είμαστε στο **παιδί**.
   * `pid > 0` σημαίνει πως είμαστε στον **γονιό** (και `pid` είναι το ID του παιδιού).

3. Στο **παιδί**:

   * Εκτυπώνει `"Child process\n"`.
   * Κάνει `return 7;` που σημαίνει ότι το πρόγραμμα (η διεργασία) τερματίζει με κωδικό εξόδου 7.

4. Στον **γονιό**:

   * Περιμένει να τελειώσει το παιδί με `wait(&status);`.
   * Έπειτα ελέγχει αν το παιδί τερμάτισε κανονικά (`WIFEXITED(status)`).
   * Αν ναι, εκτυπώνει τον κωδικό εξόδου που επέστρεψε το παιδί (`WEXITSTATUS(status)`).


### Τι εκτυπώνεται:

* Πρώτα, το **παιδί** εκτυπώνει:

```
Child process
```

* Μετά, αφού το παιδί τερματίσει, ο γονιός εκτυπώνει:

```
Child exited with 7
```

Άρα συνολικά στην οθόνη θα δεις:

```
Child process
Child exited with 7
```


### Τι αλλάζει αν στο παιδί αντί για `return 7;` βάλουμε `exit(7);`

* **Δεν αλλάζει τίποτα στην έξοδο του προγράμματος**.
  Και τα δύο (`return` μέσα στη `main` ή `exit`) τερματίζουν την διεργασία με κωδικό εξόδου 7.

* Η μόνη διαφορά είναι πως:

  * Το `return 7;` επιστρέφει τον κωδικό εξόδου από τη `main`.
  * Το `exit(7);` τερματίζει άμεσα την διεργασία με κωδικό 7 (μπορεί να χρησιμοποιηθεί και εκτός `main`).



### Τι θα συνέβαινε αν δεν είχαμε καθόλου `return` ή `exit` στο παιδί;

* Το παιδί θα συνέχιζε να εκτελεί τον κώδικα μετά το `if` (δηλαδή και τον κώδικα του γονιού).
* Αυτό θα οδηγούσε σε απρόβλεπτη συμπεριφορά γιατί τόσο παιδί όσο και γονιός θα έτρεχαν την ίδια λογική.


### Επιπλέον:

* Ο κωδικός εξόδου (7) που επιστρέφει το παιδί είναι διαθέσιμος στον γονιό μέσω της `wait()` και εκτυπώνεται με το `WEXITSTATUS`.
* Με αυτόν τον τρόπο ο γονιός μπορεί να μάθει αν το παιδί τερμάτισε κανονικά και με ποιο κωδικό.

Φυσικά! Να σου εξηγήσω πιο αναλυτικά πώς λειτουργεί το `fork()` και πώς σχετίζονται οι `exit()`, `wait()` και `waitpid()`.

### ΣΥΝΕΧΕΙΑ

### Πώς λειτουργεί το `fork()`

* Η `fork()` δημιουργεί ένα **αντίγραφο** της τρέχουσας διεργασίας.
* Από τη στιγμή της κλήσης, υπάρχουν δύο διεργασίες που τρέχουν **παράλληλα**: η **γονική** και η **παιδική**.
* Η `fork()` επιστρέφει:

  * **0** στο παιδί.
  * Το **PID** του παιδιού στον γονιό.
* Κάθε διεργασία έχει τη δική της μνήμη και εκτελεί τον ίδιο κώδικα **μετά το fork()**, αλλά ξεχωριστά.


### `exit()` και `return`

* Η `exit(int status)` τερματίζει τη διεργασία άμεσα και στέλνει τον κωδικό εξόδου `status` στο λειτουργικό σύστημα.
* Αν η `return` χρησιμοποιηθεί στη `main()`, ισοδυναμεί με `exit()` με τον ίδιο κωδικό εξόδου.
* Ο κωδικός εξόδου μπορεί να "διαβαστεί" από τον γονιό μέσω της `wait()`.


### `wait()` και `waitpid()`

* Η `wait(int *status)` σταματά τη γονική διεργασία μέχρι να τερματίσει ένα παιδί της.
* Επιστρέφει το PID του παιδιού που τερμάτισε.
* Το `status` περιέχει πληροφορίες για το πώς τερμάτισε το παιδί (κανονικά, σήμα, κτλ).
* Με μακροεντολές όπως `WIFEXITED(status)` και `WEXITSTATUS(status)` μπορούμε να δούμε αν το παιδί τερμάτισε κανονικά και με ποιο κωδικό.
* Η `waitpid(pid_t pid, int *status, int options)` είναι πιο ευέλικτη, επιτρέπει να περιμένεις συγκεκριμένο παιδί ή να κάνεις μη αποκλειστική αναμονή (με options).


### Παράδειγμα με `waitpid()`:

```c
pid_t pid = fork();
if (pid == 0) {
    // παιδί
    printf("Child\n");
    exit(5);
} else {
    int status;
    waitpid(pid, &status, 0);  // Περιμένουμε συγκεκριμένο παιδί
    if (WIFEXITED(status)) {
        printf("Child exited with %d\n", WEXITSTATUS(status));
    }
}
```


---

### Ερώτηση 14

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 17. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί.

---

### Ερώτηση 15

**Εκφώνηση:**

> Γράψε ένα πρόγραμμα που δημιουργεί 3 ανώνυμους αγωγούς και 2 διεργασίες παιδιά. 
Ο γονιός, σε επανάληψη, διαβάζει έναν αριθμό από τη συμβατική του είσοδο, τον γράφει 
στον 1ο αγωγό, διαβάζει έναν αριθμό από τον 3ο αγωγό και τον εκτυπώνει στην συμβατική 
του έξοδο. Το 1ο παιδί, σε επανάληψη, διαβάζει έναν αριθμό από τον 1ο αγωγό, τον 
πολλαπλασιάζει με -1, και γράφει το αποτέλεσμα στον 2ο αγωγό. Αν η read επιστρέψει 0, 
κλείνει το άκρο εγγραφής του 2ου αγωγού και τερματίζει. Το 2ο παιδί, σε επανάληψη, 
διαβάζει έναν αριθμό από τον 2ο αγωγό, του προσθέτει 10, και γράφει το αποτέλεσμα στον 
3ο αγωγό. Αν η read επιστρέψει 0, κλείνει το άκρο εγγραφής του 3ου αγωγού και 
τερματίζει. 
Με βάση την παραπάνω περιγραφή, το πρόγραμμα δεν τερματίζει ποτέ. Υλοποίησε 
διάφορες παραλλαγές:  
α) Η επανάληψη του γονιού εκτελείται μέχρι να μην υπάρχουν άλλα δεδομένα να διαβάσει 
από την συμβατική είσοδο, και μετά σκοτώνει τα παιδιά στέλνοντας σήμα SIGTERM ή 
SIGKILL, τα περιμένει με waitpid και τερματίζει. 
β) Η επανάληψη του γονιού εκτελείται μέχρι να μην υπάρχουν άλλα δεδομένα να διαβάσει 
από την συμβατική είσοδο, και μετά κλείνει το άκρο εγγραφής του 1ου αγωγού και 
περιμένει να επιστρέψουν τα παιδιά. Προσοχή: Σε κάθε περίπτωση, φρόντισε να κλείνουν 
τα άκρα αγωγών το νωρίτερο δυνατό. Σκέψου γιατί αυτό είναι απαραίτητο. 
γ) Πριν ξεκινήσει η "αλυσίδα" αναγνώσεων κι εγγραφών, ο γονιός δημιουργεί ένα 
ξυπνητήρι. Όταν χτυπήσει το ξυπνητήρι, ο γονιός κλείνει το άκρο εγγραφής του 1ου 
αγωγού και περιμένει να επιστρέψουν τα παιδιά.  
δ) Άλλαξε τον κώδικα των παιδιών ώστε το πρώτο παιδί να επιστρέφει όταν τελειώσει 
(μέσω return) τον αριθμό των ακέραιων τιμών που διάβασε/έγραψε, και το δεύτερο παιδί 
να επιστρέφει το άθροισμα των τιμών που έγραψε. Πρόσθεσε κώδικα στο γονιό που να 
ανιχνεύει και να εκτυπώνει αυτή την τιμή. Τρέξε δοκιμές έτσι ώστε τουλάχιστον ένα από τα 
παιδιά να επιστρέφει τιμή έξω από το διάστημα [0..255]. Τι παρατηρείς και γιατί;  


## Βασικό πρόγραμμα (σκελετός)

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    int pipe1[2], pipe2[2], pipe3[2];
    pid_t child1, child2;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child1 = fork();
    if (child1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // Πρώτο παιδί
        close(pipe1[1]); // Κλείνουμε το άκρο εγγραφής 1ου αγωγού
        close(pipe2[0]); // Κλείνουμε το άκρο ανάγνωσης 2ου αγωγού
        close(pipe3[0]); close(pipe3[1]); // Δεν το χρησιμοποιεί

        int num, r;
        while ((r = read(pipe1[0], &num, sizeof(int))) > 0) {
            num = -num;
            if (write(pipe2[1], &num, sizeof(int)) == -1) {
                perror("write child1");
                break;
            }
        }
        close(pipe1[0]);
        close(pipe2[1]);
        _exit(0);  // Τερματισμός παιδιού 1
    }

    child2 = fork();
    if (child2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {
        // Δεύτερο παιδί
        close(pipe1[0]); close(pipe1[1]); // Δεν το χρησιμοποιεί
        close(pipe2[1]); // Κλείνουμε άκρο εγγραφής 2ου αγωγού
        close(pipe3[0]); // Κλείνουμε άκρο ανάγνωσης 3ου αγωγού

        int num, r;
        while ((r = read(pipe2[0], &num, sizeof(int))) > 0) {
            num += 10;
            if (write(pipe3[1], &num, sizeof(int)) == -1) {
                perror("write child2");
                break;
            }
        }
        close(pipe2[0]);
        close(pipe3[1]);
        _exit(0); // Τερματισμός παιδιού 2
    }

    // Γονιός
    close(pipe1[0]); // Κλείνουμε άκρο ανάγνωσης 1ου αγωγού
    close(pipe2[0]); close(pipe2[1]); // Δεν το χρησιμοποιεί ο γονιός
    close(pipe3[1]); // Κλείνουμε άκρο εγγραφής 3ου αγωγού

    int num, r;
    while ((r = scanf("%d", &num)) == 1) {
        if (write(pipe1[1], &num, sizeof(int)) == -1) {
            perror("write parent");
            break;
        }
        if (read(pipe3[0], &num, sizeof(int)) <= 0) {
            break;
        }
        printf("Result: %d\n", num);
        fflush(stdout);
    }

    // Θα υλοποιήσουμε παραλλαγές παρακάτω

    // Κλείσιμο αγωγών γονιού
    close(pipe1[1]);
    close(pipe3[0]);

    wait(NULL);
    wait(NULL);

    return 0;
}
```



## Παραλλαγή (α) - Τερματισμός παιδιών με σήμα SIGTERM/SIGKILL

Πρόσθεσε μετά το τέλος ανάγνωσης στη γονική διεργασία:

```c
// Γονιός: Αν τελειώσουν τα δεδομένα, στέλνει SIGTERM στα παιδιά
kill(child1, SIGTERM);
kill(child2, SIGTERM);

waitpid(child1, NULL, 0);
waitpid(child2, NULL, 0);
```

Επίσης, πρέπει τα παιδιά να αγνοούν SIGTERM (ή να το χειρίζονται για σωστό τερματισμό), αλλιώς θα πεθάνουν άμεσα.


## Παραλλαγή (β) - Κλείσιμο άκρου εγγραφής 1ου αγωγού από τον γονιό

Μετά το τέλος εισόδου:

```c
close(pipe1[1]); // Κλείσιμο άκρου εγγραφής 1ου αγωγού

waitpid(child1, NULL, 0);
waitpid(child2, NULL, 0);
```

Προσοχή: τα παιδιά θα αντιληφθούν EOF μέσω read == 0 και θα τερματίσουν.

## Παραλλαγή (γ) - Χρήση ξυπνητηριού (alarm)

Πριν την επανάληψη εισόδου:

```c
#include <signal.h>

void alarm_handler(int sig) {
    // Σήμα ξυπνητηριού: κλείνουμε το άκρο εγγραφής 1ου αγωγού
    close(pipe1[1]);
}

int main() {
    // ... πριν το while εισόδου

    signal(SIGALRM, alarm_handler);
    alarm(10); // πχ ξυπνητήρι στα 10 δευτερόλεπτα

    // μετά η επανάληψη
}
```


## Παραλλαγή (δ) - Παιδιά επιστρέφουν τιμές μέσω return

Τροποποίησε τα παιδιά να μετράνε τι έκαναν:

Στο πρώτο παιδί:

```c
int count = 0;
while ((r = read(pipe1[0], &num, sizeof(int))) > 0) {
    num = -num;
    if (write(pipe2[1], &num, sizeof(int)) == -1) break;
    count++;
}
close(pipe1[0]);
close(pipe2[1]);
_exit(count);  // Επιστροφή πλήθους
```

Στο δεύτερο παιδί:

```c
int sum = 0;
while ((r = read(pipe2[0], &num, sizeof(int))) > 0) {
    num += 10;
    if (write(pipe3[1], &num, sizeof(int)) == -1) break;
    sum += num;
}
close(pipe2[0]);
close(pipe3[1]);
_exit(sum & 0xFF);  // Επιστρέφουμε τα χαμηλότερα 8 bit (λόγω περιορισμού return)
```

Στον γονιό, μετά το `waitpid`:

```c
int status;
waitpid(child1, &status, 0);
if (WIFEXITED(status)) {
    printf("Child1 returned %d\n", WEXITSTATUS(status));
}

waitpid(child2, &status, 0);
if (WIFEXITED(status)) {
    printf("Child2 returned %d\n", WEXITSTATUS(status));
}
```

### Παρατήρηση

Η επιστρεφόμενη τιμή είναι 8-bit unsigned (0-255), οπότε αν το `sum` ή `count` ξεπεράσουν το 255, θα «κοπούν» (wrap-around). Αυτό σημαίνει πως δεν μπορούμε να πάρουμε σωστά μεγάλες τιμές μέσω return. Για μεγαλύτερες επιστροφές, θα πρέπει να χρησιμοποιήσουμε άλλους μηχανισμούς (π.χ. αγωγούς, shared memory, αρχεία).

Φυσικά! Ας τα πάρουμε βήμα-βήμα, με απλά λόγια, τι κάνει κάθε μέρος και γιατί:


## Το βασικό πρόγραμμα

Έχουμε:

* **3 ανώνυμους αγωγούς (pipes)**:

  * `pipe1`: Ο γονιός γράφει στον πρώτο, το πρώτο παιδί διαβάζει από αυτόν.
  * `pipe2`: Το πρώτο παιδί γράφει σε αυτόν, το δεύτερο παιδί διαβάζει από αυτόν.
  * `pipe3`: Το δεύτερο παιδί γράφει σε αυτόν, ο γονιός διαβάζει από αυτόν.

* **2 παιδιά**:

  * Πρώτο παιδί: διαβάζει αριθμούς από τον `pipe1`, τους πολλαπλασιάζει με -1 και τους γράφει στον `pipe2`.
  * Δεύτερο παιδί: διαβάζει αριθμούς από τον `pipe2`, τους προσθέτει 10 και τους γράφει στον `pipe3`.

* **Ο γονιός**:

  * Διαβάζει αριθμούς από την είσοδο (π.χ. πληκτρολόγιο), τους στέλνει στον πρώτο αγωγό.
  * Διαβάζει τα αποτελέσματα από τον τρίτο αγωγό και τα τυπώνει.


### Γιατί κλείνουμε άκρες των αγωγών;

Κάθε αγωγός έχει 2 άκρα: ανάγνωσης και εγγραφής. Οι διεργασίες πρέπει να κλείνουν τα άκρα που δεν χρησιμοποιούν:

* Για να μη "κολλάνε" οι `read()` όταν περιμένουν δεδομένα, γιατί αν κάποιο άκρο εγγραφής παραμένει ανοιχτό, το `read()` δεν επιστρέφει 0 (EOF).
* Για να απελευθερώνονται πόροι συστήματος και να μη μπλέκουν τα δεδομένα.


## Παραλλαγές:

### (α) Τερματισμός παιδιών με σήμα SIGTERM ή SIGKILL

* **Τι γίνεται:**
  Όταν ο γονιός σταματήσει να διαβάζει από την είσοδο (π.χ. Ctrl+D), τα παιδιά δεν ξέρουν ότι πρέπει να σταματήσουν, οπότε το πρόγραμμα δεν τελειώνει ποτέ.
* **Λύση:**
  Ο γονιός στέλνει σήμα (π.χ. SIGTERM) στα παιδιά, αναγκάζοντάς τα να τερματίσουν.
* **Προσοχή:**
  Τα παιδιά πρέπει να μπορούν να χειριστούν αυτό το σήμα ή να το αγνοήσουν. Αν όχι, θα κλείσουν αμέσως, ίσως χωρίς να καθαρίσουν σωστά.

### (β) Κλείσιμο άκρου εγγραφής του 1ου αγωγού από τον γονιό

* **Τι γίνεται:**
  Όταν ο γονιός κλείσει το άκρο εγγραφής του 1ου αγωγού (`pipe1[1]`), το πρώτο παιδί που κάνει `read(pipe1[0])` θα λάβει 0 (EOF) όταν διαβάσει τα τελευταία δεδομένα.
* **Γιατί βοηθάει:**
  Το EOF λέει στα παιδιά να σταματήσουν με φυσικό τρόπο — χωρίς σήματα ή αναγκαστικό τερματισμό.
* **Τελικό αποτέλεσμα:**
  Τα παιδιά τερματίζουν κανονικά, το πρόγραμμα ολοκληρώνεται φυσιολογικά.


### (γ) Χρήση ξυπνητηριού (alarm)

* **Τι είναι:**
  Μπορούμε να βάλουμε ένα χρονόμετρο (π.χ. 10 δευτερόλεπτα) που όταν λήξει θα στείλει σήμα `SIGALRM` στον γονιό.
* **Τι κάνει ο γονιός στο σήμα:**
  Κλείνει το άκρο εγγραφής του 1ου αγωγού, σηματοδοτώντας στα παιδιά να τελειώσουν.
* **Πλεονέκτημα:**
  Αυτόματα διακόπτει την είσοδο μετά από συγκεκριμένο χρόνο, χωρίς να χρειάζεται ο χρήστης να κάνει κάτι.


### (δ) Παιδιά επιστρέφουν αριθμούς (return value)

* **Τι γίνεται:**
  Ο κάθε γιος όταν τερματίζει κάνει `return` ή `_exit` με κάποια αριθμητική τιμή:

  * Πρώτο παιδί επιστρέφει το πλήθος των αριθμών που διάβασε/έγραψε.
  * Δεύτερο παιδί επιστρέφει το άθροισμα των αριθμών που έγραψε.

* **Πρόβλημα:**
  Η τιμή που επιστρέφεται από `return` σε C είναι 8-bit (0-255). Αν το αποτέλεσμα είναι μεγαλύτερο από 255, η τιμή «τυλίγεται» (wrap-around).

* **Συμπέρασμα:**
  Δεν μπορούμε να επιστρέψουμε σωστά μεγάλους αριθμούς με αυτόν τον τρόπο. Για να μεταφέρουμε μεγαλύτερες τιμές, πρέπει να χρησιμοποιήσουμε άλλους μηχανισμούς, π.χ. αγωγούς, αρχεία, shared memory.

## Γιατί το αρχικό πρόγραμμα δεν τερματίζει μόνο του;

* Αν ο γονιός κλείσει το άκρο εγγραφής του 1ου αγωγού, το πρώτο παιδί βλέπει EOF στο `read` και τερματίζει.
* Αν δεν το κλείσει, ο πρώτος αγωγός μένει ανοιχτός και το παιδί περιμένει πάντα για δεδομένα, άρα δεν τελειώνει ποτέ.
* Αν το πρώτο παιδί δεν τερματίσει, το δεύτερο παιδί επίσης δεν θα δει EOF.
* Συνεπώς, πρέπει να κλείσουμε σωστά τα άκρα ώστε οι `read()` να επιστρέφουν 0 όταν δεν υπάρχουν άλλα δεδομένα.


## Συνοψίζοντας
| Παραλλαγή                      | Τι κάνει                                             | Πλεονέκτημα                    | Τι πρέπει να προσέξουμε              |
| ------------------------------ | ---------------------------------------------------- | ------------------------------ | ------------------------------------ |
| (α) SIGTERM / SIGKILL          | Ο γονιός σκοτώνει τα παιδιά με σήμα                  | Αναγκαστικός τερματισμός       | Παιδιά μπορεί να μη καθαρίσουν σωστά |
| (β) Κλείσιμο αγωγού 1ου        | Ο γονιός κλείνει άκρο 1ου αγωγού, παιδιά βλέπουν EOF | Φυσικός, ομαλός τερματισμός    | Πρέπει να κλείνουμε άμεσα τα άκρα    |
| (γ) Alarm ξυπνητήρι            | Αυτόματο κλείσιμο αγωγού μετά από συγκεκριμένο χρόνο | Αυτόματη λήξη προγράμματος     | Απαιτεί χειρισμό σήματος             |
| (δ) Επιστροφή τιμών από παιδιά | Παιδιά επιστρέφουν στατιστικά μέσω return            | Εύκολο να πάρουμε αποτελέσματα | Επιστρέφονται μόνο τιμές 0-255       |


---

### Ερώτηση 16

**Εκφώνηση:**

> Γράψε ένα πρόγραμμα που δημιουργεί μια διεργασία παιδί. Το παιδί αλλάζει την 
πολιτική εσωτερικής αποθήκευσης της βιβλιοθήκης stdio σε not buffered,  μπλοκάρει το 
σήμα SIGALRM,  κάνει sleep για 3 δευτερόλεπτα, ελέγχει αν εκκρεμεί SIGALRM κι αν ναι 
εκτυπώνει ένα μήνυμα στην συμβατική έξοδο, ξεμπλοκάρει το SIGALRM, εκτυπώνει ένα 
δεύτερο μήνυμα και τερματίζει επιστρέφοντας την τιμή 3. Ο γονιός κάνει sleep για 1 
δευτερόλεπτο, στέλνει στο παιδί 3 φορές το σήμα SIGALRM και μετά περιμένει το παιδί να 
τερματίσει κι ελέγχει αν το παιδί τερμάτισε ομαλά κι επέστρεψε 3 ή αν τερμάτισε λόγω 
σήματος.  
α) Τρέξε το πρόγραμμα. Πόσες φορές εκτυπώνεται το 1ο μήνυμα του παιδιού, πόσες το 2ο 
και τι εκτυπώνει ο γονιός; Γιατί; 
β) Στήσε ένα χειριστή σήματος στο παιδί για το SIGALRM και μέσα σε αυτόν τύπωσε ένα 
τρίτο μήνυμα. Τρέξε το πρόγραμμα και απάντησε τα ερωτήματα του (α). Άλλαξε κάτι και 
γιατί; 
γ) Άλλαξε το χειρισμό του σήματος SIGALRM στο παιδί σε παράβλεψη (ignore). Τρέξε το 
πρόγραμμα και απάντησε τα ερωτήματα του (α). Άλλαξε κάτι και γιατί; 
δ) Στην αρχική έκδοση του προγράμματος, αντικατέστησε τη sleep(3) του παιδιού με μια 
sigwait που περιμένει μέχρι να γίνει εκκρεμές το σήμα SIGALRM οπότε κι εκτυπώνεται ένα 
μήνυμα. Τρέξε το πρόγραμμα. Τι εκτυπώνει και γιατί;



## Βασικό πρόγραμμα (Αρχική έκδοση - χωρίς signal handler)

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Παιδί
        // Αλλαγή buffering της stdio σε no buffering
        setbuf(stdout, NULL);

        // Μπλοκάρισμα SIGALRM
        sigset_t blockset;
        sigemptyset(&blockset);
        sigaddset(&blockset, SIGALRM);
        if (sigprocmask(SIG_BLOCK, &blockset, NULL) < 0) {
            perror("sigprocmask");
            exit(EXIT_FAILURE);
        }

        sleep(3);

        // Έλεγχος αν εκκρεμεί SIGALRM
        sigset_t pending;
        if (sigpending(&pending) < 0) {
            perror("sigpending");
            exit(EXIT_FAILURE);
        }

        if (sigismember(&pending, SIGALRM)) {
            printf("Πρώτο μήνυμα: Υπάρχει εκκρεμές SIGALRM\n");
        }

        // Ξεμπλοκάρισμα SIGALRM
        if (sigprocmask(SIG_UNBLOCK, &blockset, NULL) < 0) {
            perror("sigprocmask unblock");
            exit(EXIT_FAILURE);
        }

        printf("Δεύτερο μήνυμα: Ξεμπλοκάρισμα SIGALRM και τερματισμός\n");
        exit(3);
    } else {  // Γονιός
        sleep(1);
        for (int i = 0; i < 3; i++) {
            kill(pid, SIGALRM);
        }

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Γονιός: Παιδί τερμάτισε κανονικά με κωδικό %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Γονιός: Παιδί τερμάτισε από σήμα %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
```


### Ερωτήματα (α)

* Πόσες φορές εκτυπώνεται το πρώτο μήνυμα του παιδιού;
  **Μόνο 1 φορά** (αν υπάρχει εκκρεμές SIGALRM).
* Πόσες φορές το δεύτερο μήνυμα;
  **1 φορά** πάντα πριν το τέλος.
* Τι εκτυπώνει ο γονιός;
  Τυπώνει ότι το παιδί τερμάτισε κανονικά με κωδικό 3.
* Γιατί;
  Το παιδί μπλοκάρει το SIGALRM, οπότε τα σήματα συσσωρεύονται εκκρεμή. Μετά το sleep(3), το παιδί βλέπει ότι έχει 3 σήματα εκκρεμή και εκτυπώνει το πρώτο μήνυμα. Μόλις ξεμπλοκάρει το SIGALRM, όλα τα σήματα επεξεργάζονται και το πρόγραμμα συνεχίζει και τερματίζει κανονικά με exit(3).


## (β) Προσθήκη handler SIGALRM στο παιδί

Προσθέτουμε handler για το SIGALRM που τυπώνει μήνυμα.

```c
// Προσθήκη πριν το sleep(3) στο παιδί:
void sigalrm_handler(int signo) {
    printf("Τρίτο μήνυμα: Handler SIGALRM εκτελέστηκε\n");
}
```

Και στο main παιδιού:

```c
signal(SIGALRM, sigalrm_handler);
```


### Ερωτήματα (β)

* Τώρα το πρώτο μήνυμα εκτυπώνεται;
  **Ναι**, αλλά πιθανώς 0 φορές γιατί handler θα επεξεργαστεί τα σήματα μόλις ξεμπλοκαριστούν.
* Τρίτο μήνυμα τυπώνεται 3 φορές (για τα 3 σήματα).
* Το δεύτερο μήνυμα τυπώνεται πάντα 1 φορά.
* Ο γονιός τυπώνει το ίδιο όπως πριν.
* Αλλαγή: Τα σήματα δεν παραμένουν εκκρεμή για το sigpending γιατί τα χειρίζεται ο handler όταν ξεμπλοκάρει το SIGALRM.


## (γ) Παράβλεψη (ignore) SIGALRM στο παιδί

Προσθέτουμε:

```c
signal(SIGALRM, SIG_IGN);
```

---

### Ερωτήματα (γ)

* Το πρώτο μήνυμα **δεν θα εκτυπωθεί** γιατί τα SIGALRM αγνοούνται, δεν παραμένουν εκκρεμή.
* Το δεύτερο μήνυμα εκτυπώνεται κανονικά.
* Ο γονιός πάλι δείχνει exit code 3.
* Αλλαγή: Δεν υπάρχουν εκκρεμή σήματα γιατί αγνοούνται.


## (δ) Αντικατάσταση sleep(3) με sigwait

```c
// Αντικατάσταση sleep(3) στο παιδί:
sigset_t waitset;
sigemptyset(&waitset);
sigaddset(&waitset, SIGALRM);

int sig;
printf("Παιδί: Περιμένω SIGALRM...\n");
sigwait(&waitset, &sig);
printf("Παιδί: Λάβαμε SIGALRM μέσω sigwait\n");
```

### Ερωτήματα (δ)

* Τυπώνει:

  * "Παιδί: Περιμένω SIGALRM..."
  * "Παιδί: Λάβαμε SIGALRM μέσω sigwait"
  * Το πρώτο μήνυμα **δεν τυπώνεται** γιατί το σήμα λαμβάνεται από το sigwait.
* Ο γονιός τυπώνει πάλι ότι το παιδί τερμάτισε με 3.
* Γιατί;
  Το sigwait καταναλώνει το σήμα και δεν μένει εκκρεμές.

Φυσικά! Θα σου εξηγήσω αναλυτικά κάθε βήμα, τι γίνεται στο πρόγραμμα, τι σημαίνουν τα σήματα, το μπλοκάρισμα, το χειρισμό τους, και γιατί βλέπουμε τα αποτελέσματα που περιγράφονται.


## Βασικές έννοιες που χρειάζεται να κατανοήσουμε πρώτα

* **Σήματα (signals)**: Είναι ένας τρόπος επικοινωνίας ανάμεσα σε διεργασίες ή στο ίδιο πρόγραμμα με τον πυρήνα του λειτουργικού. Όταν φτάνει ένα σήμα σε μια διεργασία, μπορεί να εκτελεστεί κάποιος handler (ρουτίνα χειρισμού) ή να γίνει default συμπεριφορά (τερματισμός, αγνόηση κτλ).

* **Μπλοκάρισμα σήματος (signal blocking)**: Με το `sigprocmask` μπορούμε να μπλοκάρουμε (να "κρύψουμε") κάποια σήματα προσωρινά, ώστε να μην παραληφθούν αμέσως. Τα σήματα που έρχονται τότε μένουν *εκκρεμή* (pending), δηλαδή περιμένουν.

* **sigpending**: Ελέγχει αν υπάρχουν σήματα που έχουν φτάσει αλλά είναι μπλοκαρισμένα και άρα εκκρεμή.

* **sigwait**: Περιμένει *συνειδητά* να έρθει σήμα και το "παίρνει" χειροκίνητα, χωρίς να ενεργοποιήσει handler ή default behavior.

* **Buffering της stdio**: Το stdout έχει συνήθως buffer, που σημαίνει ότι δεν τυπώνεται το κείμενο αμέσως αλλά «κρατιέται» και τυπώνεται μαζικά. Με `setbuf(stdout, NULL)` απενεργοποιούμε αυτό το buffering για να βλέπουμε αμέσως την έξοδο.


## Αρχικό πρόγραμμα (χωρίς handler)

### Τι γίνεται;

1. Ο γονιός δημιουργεί το παιδί.
2. Το παιδί μπλοκάρει το σήμα SIGALRM.
3. Το παιδί κάνει `sleep(3)`.
4. Ο γονιός κάνει `sleep(1)`, και στέλνει 3 φορές SIGALRM στο παιδί.
5. Επειδή το παιδί μπλοκάρει το SIGALRM, τα 3 σήματα **δεν εκτελούνται αμέσως**, αλλά μένουν εκκρεμή.
6. Μετά το sleep, το παιδί ρωτάει αν υπάρχει εκκρεμές SIGALRM (με `sigpending`).
7. Εφόσον υπάρχουν, τυπώνει το πρώτο μήνυμα.
8. Ξεμπλοκάρει το SIGALRM.
9. Το παιδί τυπώνει το δεύτερο μήνυμα και τερματίζει με exit code 3.
10. Ο γονιός περιμένει το παιδί να τελειώσει, βλέπει ότι έφυγε κανονικά με 3.

### Γιατί;

* Τα σήματα SIGALRM που έστειλε ο γονιός δεν «χάθηκαν» επειδή ήταν μπλοκαρισμένα.
* Όταν ξεμπλοκάρουν, το παιδί λαμβάνει το σήμα ή το χειρίζεται (στην περίπτωση χωρίς handler, το σήμα δεν κάνει τίποτα επικίνδυνο, απλά παραμένει ως εκκρεμές).
* Το πρόγραμμα τυπώνει τα μηνύματα με τη σωστή σειρά.
* Ο γονιός βλέπει τον κωδικό εξόδου που επέστρεψε το παιδί (3).


## Με handler SIGALRM (β)

### Τι αλλάζει;

* Ορίζουμε handler για το SIGALRM που απλώς τυπώνει ένα μήνυμα κάθε φορά που το σήμα λαμβάνεται.
* Όταν το παιδί ξεμπλοκάρει το SIGALRM, τα 3 σήματα θα προκαλέσουν 3 εκτελέσεις του handler.
* Επειδή το παιδί έχει handler, τα σήματα δεν θεωρούνται εκκρεμή πια μετά το ξεμπλοκάρισμα.
* Το πρώτο μήνυμα (που δείχνει εκκρεμές σήμα) **μπορεί να μην εκτυπωθεί** αφού τα σήματα θα έχουν ήδη ληφθεί από τον handler.
* Ο γονιός βλέπει πάλι κωδικό 3.

### Γιατί;

* Με handler, όταν ξεμπλοκάρει το σήμα, κάθε εκκρεμές σήμα προκαλεί την κλήση του handler.
* Τα σήματα «καταναλώνονται» από τον handler και δεν θεωρούνται πλέον εκκρεμή.
* Το πρώτο μήνυμα, που ελέγχει για pending σήματα, τυπώνεται αν τα σήματα δεν έχουν ληφθεί ακόμα από τον handler.


## Παράβλεψη SIGALRM (ignore) (γ)

### Τι αλλάζει;

* Αν αγνοούμε το SIGALRM με `signal(SIGALRM, SIG_IGN)`, τότε όταν φτάνουν τα σήματα, απλά χάνονται (δεν γίνονται εκκρεμή, δεν ενεργοποιούν handler).
* Το πρώτο μήνυμα (που ελέγχει για εκκρεμή σήματα) **δεν εκτυπώνεται ποτέ**.
* Το δεύτερο μήνυμα τυπώνεται κανονικά.
* Ο γονιός βλέπει πάλι κωδικό 3.

### Γιατί;

* Τα σήματα αγνοούνται τελείως, δεν μένουν εκκρεμή, δεν ενεργοποιούν handler, ούτε τερματίζουν το παιδί.
* Το πρόγραμμα τρέχει κανονικά.


## Χρήση sigwait αντί για sleep (δ)

### Τι αλλάζει;

* Το παιδί δεν κάνει `sleep(3)`.
* Αντίθετα, το παιδί *περιμένει συνειδητά* να λάβει το σήμα SIGALRM με την `sigwait`.
* Το σήμα φτάνει, το `sigwait` επιστρέφει, και τυπώνεται μήνυμα.
* Το πρώτο μήνυμα (pending) δεν τυπώνεται, γιατί το σήμα *παραλαμβάνεται* άμεσα από το sigwait.
* Ο γονιός βλέπει exit code 3.

### Γιατί;

* Το sigwait είναι blocking κλήση που *καταναλώνει* το σήμα.
* Δεν μένει εκκρεμές το σήμα.
* Δεν καλείται handler (εφόσον δεν υπάρχει).


# Συνοψίζοντας:

| Περίπτωση              | 1ο μήνυμα (pending) | 2ο μήνυμα (ξεμπλοκάρισμα) | 3ο μήνυμα (handler) | Συμπεριφορά γονιού             |
| ---------------------- | ------------------- | ------------------------- | ------------------- | ------------------------------ |
| Αρχική (χωρίς handler) | 1 φορά              | 1 φορά                    | -                   | Παιδί τερματίζει κανονικά με 3 |
| Με handler SIGALRM     | 0 ή 1 φορές         | 1 φορά                    | 3 φορές             | Παιδί τερματίζει κανονικά με 3 |
| Με ignore SIGALRM      | 0                   | 1 φορά                    | -                   | Παιδί τερματίζει κανονικά με 3 |
| Με sigwait             | 0                   | -                         | -                   | Παιδί τερματίζει κανονικά με 3 |




