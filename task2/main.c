#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct subscriber {
    int id;
    int deleted;
    char *name;
    char *number;
} subscriber;

char *get_str(FILE *file);

char *normalize_number(char *number);

int check_name(char *a);

char *lower_case(char *);

void read_subscriber(FILE *file, char *file_name, int id);

size_t size;
int max_id;
subscriber *records;


void add(int id, char *name, char *number) {
    records = (subscriber *) realloc(records, (size + 1) * sizeof(subscriber));
    records[size].id = id;
    records[size].name = name;
    records[size].number = number;
    size++;
}

int load_from_file(char *file_name) {
    FILE *file;
    file = fopen(file_name, "r+");
    if (file == NULL) {
        return 1;
    }
    rewind(file);
    int cur_id = 0;
    while (fscanf(file, "%d", &cur_id) != EOF) {
        if (cur_id > max_id) {
            max_id = cur_id;
        }
        read_subscriber(file, file_name, cur_id);
    }

    fclose(file);
    return 0;
}

void rewrite(char *file_name) {
    FILE *file = fopen(file_name, "w");
    rewind(file);
    int i = 0;
    for (i = 0; i < size; i++)
        if (!records[i].deleted) {
            fprintf(file, "%d %s %s\n", records[i].id, records[i].name, records[i].number);
        }
    fclose(file);
}

void read_subscriber(FILE *file, char *file_name, int id) {
    char *name = get_str(file);
    char *number = get_str(file);

    if (name != NULL && check_name(name) && number != NULL && normalize_number(number) != "") {
        add(id, name, number);
        rewrite(file_name);
    } else {
        printf("ERROR! Can't load subscriber%d\n", id);
        free(name);
        free(number);
    }
}

void get_by_name(char *name) {
    name = lower_case(name);

    for (int i = 0; i < size; ++i) {
        if (records[i].deleted) {
            continue;
        }
        char *curName = records[i].name;
        curName = lower_case(curName);
        if (strstr(curName, name) != NULL) {
            printf("%d %s %s \n", records[i].id, records[i].name, records[i].number);
        }
    }
    return;
}

void get_by_number(char *number) {
    number = normalize_number(number);
    for (int i = 0; i < size; ++i) {
        if (records[i].deleted) {
            continue;
        }
        char *curNum = records[i].number;
        if (strcmp(curNum, number) == 0) {
            printf("%d %s %s \n", records[i].id, records[i].name, records[i].number);
        }
    }
}

int get_by_id(int id) {
    for (int i = 0; i < size; ++i) {
        if (records[i].id == id) {
            return i;
        }
    }
    return -1;
}
char *lower_case(char *str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; ++i) {
        str[i] = (char) tolower(str[i]);
    }
    return str;
}

char *normalize_number(char *number) {
    size_t len = strlen(number);
    int cur = 0;
    for (size_t i = 0; i < len; i++) {
        if (('0' <= number[i]) && (number[i] <= '9')) {
            if (cur != i) {
                number[cur] = number[i];
            }
            cur++;
        }
    }

    number[cur] = '\0';
    return number;
}

int check_name(char *name) {
    if (strcmp(name, "") == 0) {
        return 0;
    }

    int i = 0;
    while (name[i] != '\0') {
        if (!isalpha(name[i++])) {
            return 0;
        }
    }
    return 1;
}

int check_phone(char *phone) {
    if (strcmp(phone, "") == 0) {
        return 0;
    }

    int i = 0;
    while (phone[i] != '\0') {
        if (!isdigit(phone[i]) && phone[i] != '-' && phone[i] != '+'
            && phone[i] != '(' && phone[i] != ')') {
            return 0;
        }
        i++;
    }
    return 1;
}

char *get_str(FILE *file) {
    int cur_size = 300;
    char *str = (char *) malloc(cur_size * sizeof(char));

    int i = 0;
    char c = (char) fgetc(file);
    while (c == ' ') {
        c = (char) fgetc(file);
    }
    while (c != '\n' && c != ' ' && c != EOF) {
        if (i >= cur_size) {
            cur_size *= 2;
            str = (char *) realloc(str, cur_size * sizeof(char));
        }
        str[i++] = c;
        c = (char) fgetc(file);
    }
    str[i] = '\0';
    return str;
}

void find() {
    char *val = get_str(stdin);
    if (isalpha(val[0]) && check_name(val)) {
        get_by_name(val);
    } else if (check_phone(val)) {
        get_by_number(val);
    } else {
        printf("ERROR! Incorrect name or number \n");
    }
}

void create() {
    char *name = get_str(stdin);
    char *number = get_str(stdin);
    if (check_name(name) && check_phone(number)) {
        max_id++;
        add(max_id, name, normalize_number(number));
    } else {
        printf("ERROR! Incorrect name or number \n");
    }
}

void erase(int id) {
    id = get_by_id(id);
    if (id == -1) {
        printf("ERROR! No such id\n");
    } else {
        records[id].deleted = 1;
    }
}

void change(int id) {
    char *type = get_str(stdin);
    char *val = get_str(stdin);
    id = get_by_id(id);
    if (id == -1) {
        printf("ERROR! No such id\n");
    } else if (strcmp(type, "name") == 0) {
        if (check_name(val))
            records[id].name = val;
        else {
            printf("ERROR! Incorrect name\n");
        }
    } else {
        if (check_phone(val))
            records[id].number = normalize_number(val);
        else {
            printf("ERROR! Incorrect phone number\n");
        }
    }
}

int main(int argc, char *argv[]) {

    char *file_name = argv[1];
    if (file_name == NULL) {
        file_name = (char *) malloc(sizeof(char) * 10);
        strcpy(file_name, "tbook.txt");
    }
    size = 0;
    max_id = 0;
    records = (struct subscriber *) malloc(sizeof(struct subscriber) * 0);

    load_from_file(file_name);
    char *command;
    while (1) {
        command = get_str(stdin);
        if (!strcmp(command, "find")) {
            find();
        } else if (!strcmp(command, "create")) {
            create();
            rewrite(file_name);
        } else if (!strcmp(command, "delete")) {
            int id;
            id = atoi(get_str(stdin));
            erase(id);
            rewrite(file_name);
        } else if (!strcmp(command, "change")) {
            int id;
            id = atoi(get_str(stdin));
            change(id);
            rewrite(file_name);
        } else if (!strcmp(command, "exit")) {
            rewrite(file_name);
            free(records);
            return 0;
        } else {
            printf("Error: No such command %s\n", command);
        }
        fflush(stdout);
    }
}
