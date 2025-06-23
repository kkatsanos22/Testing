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

---

### Ερώτηση 2

**Εκφώνηση:**

> Αφού ολοκληρώσεις το #1, άλλαξε τον κώδικα ώστε το phonebook να υλοποιείται ως δυναμικός πίνακας από δείκτες σε εγγραφές.

**Απάντηση:**
Αντί `entry *entries`, ορίζουμε `entry **entries`. Κάθε `entry` δημιουργείται με `malloc()` ξεχωριστά. Η διαγραφή και η εκκαθάριση χρειάζονται `free()` για κάθε `entry*`.

```c
[πλήρης κώδικας με entry**]
```

---

### Ερώτηση 3

**Εκφώνηση:**

> Γράψε ένα πρόγραμμα στο οποίο φτιάχνεις μια απλά διασυνδεδεμένη λίστα ακεραίων, προσθέτεις μερικούς ακέραιους σε αυτή και εκτυπώνεις τα περιεχόμενά της.

```c
[πλήρης κώδικας απλής συνδεδεμένης λίστας]
```

---

### Ερώτηση 4

**Εκφώνηση:**

> Πρόσθεσε κώδικα στο #3 που ζητάει από τον χρήστη έναν ακέραιο και αφαιρεί από τη λίστα τον κόμβο που περιέχει αυτόν τον ακέραιο. Πρώτα για μία εμφάνιση και μετά για όλες.

```c
[πλήρης κώδικας remove_once και remove_all]
```

---

### Ερώτηση 5

**Εκφώνηση:**

> Κάνε τις ασκήσεις #3 και #4 αλλά με λίστα που είναι διπλά-διασυνδεδεμένη, κυκλική με sentinel.

```c
[πλήρης κώδικας διπλής κυκλικής λίστας με sentinel]
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

---

### Ερώτηση 7

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 11. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις.

```c
// Παράδειγμα pointer arithmetic, struct, malloc
// Αναλόγως διαλέξεων του μαθήματος
```

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

---

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

---

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
---

### Ερώτηση 11

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 12. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις. Τρέξε τα. Βλέπεις τα αποτελέσματα που περίμενες;

```c
// Παράδειγμα με struct, pointers, δυναμική μνήμη
typedef struct {
    int a;
    int *b;
} sample;

int main() {
    sample s;
    s.a = 10;
    s.b = malloc(sizeof(int));
    *(s.b) = 20;
    printf("%d %d\n", s.a, *(s.b));
    free(s.b);
    return 0;
}
```

---

### Ερώτηση 12

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 16. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις. Τρέξε τα.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    fork();
    printf("1\n");
    fork();
    printf("2\n");
    return 0;
}
```

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

---

### Ερώτηση 14

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 17. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί.

```c
// Παράδειγμα: 2 παιδιά, 3 αγωγοί, χρήση pipe()
// Λειτουργία pipeline με πολλαπλές διεργασίες
```

---

### Ερώτηση 15

**Εκφώνηση:**

> Γράψε πρόγραμμα που δημιουργεί 3 ανώνυμους αγωγούς και 2 παιδιά. Το πρώτο παιδί πολλαπλασιάζει με -1, το δεύτερο προσθέτει 10. Ο γονιός διαβάζει είσοδο και εκτυπώνει έξοδο.

```c
// Ενδεικτική υλοποίηση για pipeline μετασχηματισμών:
int main() {
    int p1[2], p2[2], p3[2];
    pipe(p1); pipe(p2); pipe(p3);
    if (fork() == 0) {
        // Child 1
        close(p1[1]); close(p2[0]);
        int x;
        while (read(p1[0], &x, sizeof(int)) > 0) {
            x = -x;
            write(p2[1], &x, sizeof(int));
        }
        close(p1[0]); close(p2[1]);
        return 3;
    }
    if (fork() == 0) {
        // Child 2
        close(p2[1]); close(p3[0]);
        int x;
        while (read(p2[0], &x, sizeof(int)) > 0) {
            x += 10;
            write(p3[1], &x, sizeof(int));
        }
        close(p2[0]); close(p3[1]);
        return 5;
    }
    // Parent
    close(p1[0]); close(p2[0]); close(p2[1]); close(p3[1]);
    int x;
    while (scanf("%d", &x) == 1)
        write(p1[1], &x, sizeof(int));
    close(p1[1]);
    while (read(p3[0], &x, sizeof(int)) > 0)
        printf("%d\n", x);
    close(p3[0]);
    return 0;
}
```

---

### Ερώτηση 16

**Εκφώνηση:**

> Γράψε πρόγραμμα που δημιουργεί παιδί που μπλοκάρει SIGALRM, κάνει sleep(3), ελέγχει εκκρεμή σήματα και τερματίζει.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGALRM);
        sigprocmask(SIG_BLOCK, &set, NULL);
        sleep(3);
        sigpending(&set);
        if (sigismember(&set, SIGALRM)) {
            printf("SIGALRM pending!\n");
        }
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        printf("Child done.\n");
        return 3;
    } else {
        sleep(1);
        kill(pid, SIGALRM);
        kill(pid, SIGALRM);
        kill(pid, SIGALRM);
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Exited with %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Killed by signal %d\n", WTERMSIG(status));
    }
    return 0;
}
```

---

## Τέλος Ασκήσεων

Αυτό το README περιλαμβάνει όλες τις ασκήσεις 1–16 με τις εκφωνήσεις και ενδεικτικό κώδικα για κάθε μία. Για περισσότερα, συμβουλευτείτε τις διαλέξεις του μαθήματος.

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

---

### Ερώτηση 2

**Εκφώνηση:**

> Αφού ολοκληρώσεις το #1, άλλαξε τον κώδικα ώστε το phonebook να υλοποιείται ως δυναμικός πίνακας από δείκτες σε εγγραφές.

**Απάντηση:**
Αντί `entry *entries`, ορίζουμε `entry **entries`. Κάθε `entry` δημιουργείται με `malloc()` ξεχωριστά. Η διαγραφή και η εκκαθάριση χρειάζονται `free()` για κάθε `entry*`.

```c
[πλήρης κώδικας με entry**]
```

---

### Ερώτηση 3

**Εκφώνηση:**

> Γράψε ένα πρόγραμμα στο οποίο φτιάχνεις μια απλά διασυνδεδεμένη λίστα ακεραίων, προσθέτεις μερικούς ακέραιους σε αυτή και εκτυπώνεις τα περιεχόμενά της.

```c
[πλήρης κώδικας απλής συνδεδεμένης λίστας]
```

---

### Ερώτηση 4

**Εκφώνηση:**

> Πρόσθεσε κώδικα στο #3 που ζητάει από τον χρήστη έναν ακέραιο και αφαιρεί από τη λίστα τον κόμβο που περιέχει αυτόν τον ακέραιο. Πρώτα για μία εμφάνιση και μετά για όλες.

```c
[πλήρης κώδικας remove_once και remove_all]
```

---

### Ερώτηση 5

**Εκφώνηση:**

> Κάνε τις ασκήσεις #3 και #4 αλλά με λίστα που είναι διπλά-διασυνδεδεμένη, κυκλική με sentinel.

```c
[πλήρης κώδικας διπλής κυκλικής λίστας με sentinel]
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

---

### Ερώτηση 7

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 11. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις.

```c
// Παράδειγμα pointer arithmetic, struct, malloc
// Αναλόγως διαλέξεων του μαθήματος
```

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

---

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

---

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
---

### Ερώτηση 11

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 12. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις. Τρέξε τα. Βλέπεις τα αποτελέσματα που περίμενες;

```c
// Παράδειγμα με struct, pointers, δυναμική μνήμη
typedef struct {
    int a;
    int *b;
} sample;

int main() {
    sample s;
    s.a = 10;
    s.b = malloc(sizeof(int));
    *(s.b) = 20;
    printf("%d %d\n", s.a, *(s.b));
    free(s.b);
    return 0;
}
```

---

### Ερώτηση 12

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 16. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί αν τα τρέξεις. Τρέξε τα.

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    fork();
    printf("1\n");
    fork();
    printf("2\n");
    return 0;
}
```

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

---

### Ερώτηση 14

**Εκφώνηση:**

> Κατέβασε τα παραδείγματα της διάλεξης 17. Μελέτησε τον κώδικα και προσπάθησε να σκεφτείς τι θα εκτυπωθεί.

```c
// Παράδειγμα: 2 παιδιά, 3 αγωγοί, χρήση pipe()
// Λειτουργία pipeline με πολλαπλές διεργασίες
```

---

### Ερώτηση 15

**Εκφώνηση:**

> Γράψε πρόγραμμα που δημιουργεί 3 ανώνυμους αγωγούς και 2 παιδιά. Το πρώτο παιδί πολλαπλασιάζει με -1, το δεύτερο προσθέτει 10. Ο γονιός διαβάζει είσοδο και εκτυπώνει έξοδο.

```c
// Ενδεικτική υλοποίηση για pipeline μετασχηματισμών:
int main() {
    int p1[2], p2[2], p3[2];
    pipe(p1); pipe(p2); pipe(p3);
    if (fork() == 0) {
        // Child 1
        close(p1[1]); close(p2[0]);
        int x;
        while (read(p1[0], &x, sizeof(int)) > 0) {
            x = -x;
            write(p2[1], &x, sizeof(int));
        }
        close(p1[0]); close(p2[1]);
        return 3;
    }
    if (fork() == 0) {
        // Child 2
        close(p2[1]); close(p3[0]);
        int x;
        while (read(p2[0], &x, sizeof(int)) > 0) {
            x += 10;
            write(p3[1], &x, sizeof(int));
        }
        close(p2[0]); close(p3[1]);
        return 5;
    }
    // Parent
    close(p1[0]); close(p2[0]); close(p2[1]); close(p3[1]);
    int x;
    while (scanf("%d", &x) == 1)
        write(p1[1], &x, sizeof(int));
    close(p1[1]);
    while (read(p3[0], &x, sizeof(int)) > 0)
        printf("%d\n", x);
    close(p3[0]);
    return 0;
}
```

---

### Ερώτηση 16

**Εκφώνηση:**

> Γράψε πρόγραμμα που δημιουργεί παιδί που μπλοκάρει SIGALRM, κάνει sleep(3), ελέγχει εκκρεμή σήματα και τερματίζει.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGALRM);
        sigprocmask(SIG_BLOCK, &set, NULL);
        sleep(3);
        sigpending(&set);
        if (sigismember(&set, SIGALRM)) {
            printf("SIGALRM pending!\n");
        }
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        printf("Child done.\n");
        return 3;
    } else {
        sleep(1);
        kill(pid, SIGALRM);
        kill(pid, SIGALRM);
        kill(pid, SIGALRM);
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Exited with %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Killed by signal %d\n", WTERMSIG(status));
    }
    return 0;
}
```

---

## Τέλος Ασκήσεων

Αυτό το README περιλαμβάνει όλες τις ασκήσεις 1–16 με τις εκφωνήσεις και ενδεικτικό κώδικα για κάθε μία. Για περισσότερα, συμβουλευτείτε τις διαλέξεις του μαθήματος.
