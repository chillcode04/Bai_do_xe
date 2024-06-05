#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct parkingLot {
    char plate[30];
    char time_in[30];
    struct parkingLot* next;
};
typedef struct parkingLot parkingLot;

parkingLot* makeVehicle(char time_in[30], char plate[30]) {
    parkingLot* newVehicle = (parkingLot*)malloc(sizeof(parkingLot));

    strcpy(newVehicle->time_in, time_in);
    strcpy(newVehicle->plate, plate);
    newVehicle->next = NULL;

    return newVehicle;
}

void addVehicle(parkingLot** head, char time_in[30], char plate[30]) {
    parkingLot* newVehicle = makeVehicle(time_in, plate);

    if (*head == NULL) *head = newVehicle;
    else {
        parkingLot* tmp = *head;
        while (tmp->next != NULL) tmp = tmp->next;
        tmp->next = newVehicle;
    }
}

void deleteVehicle(parkingLot** head, char time_out[30], char plate[30]) {
    parkingLot* current = *head;
    parkingLot* prev = current;

    if (!strcmp((*head)->plate, plate)) {
        (*head) = (*head)->next;
        return;
    }
    
    while (current != NULL) {
        if (!strcmp(current->plate, plate)) {
            prev->next = current->next;
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

int findVehicle(parkingLot* head, char plate[30]) {
    int index = 0;
    parkingLot* current = head;

    while (current != NULL) {
        if (!strcmp(current->plate, plate)) return index;
        current = current->next;
        index++;
    }
    return -1;
}

int cnt_moto(parkingLot* head) {
    int cnt = 0;
    parkingLot* current = head;

    while (current != NULL) {
        if (strcmp(current->plate, "xxxx") < 0) cnt++;
        current = current->next;
    }
    return cnt;
}


#define day "06:00:00"
#define night "18:00:00"

int check_day(char time[30]) {
    if (strcmp(time, day) > 0 && strcmp(time, night) < 0) return 1;
    return 0;
}

int billBike(parkingLot* head, char time_out[30], char plate[30]) {
    if (findVehicle(head, plate) == -1) return -1;
    parkingLot* current = head;
    for (int i = 0; i < findVehicle(head, plate); i++) current = current->next;

    int in_day = check_day(current->time_in);
    int out_day = check_day(time_out);

    if (in_day && out_day) return 1; // ngay - ngay
    else if (!in_day && !out_day && (strcmp(current->time_in, day) > 0 || strcmp(time_out, night) < 0)) return 2; // dem - dem
    else if ((!in_day && out_day) || (in_day && !out_day)) return 3; // dem - ngay || ngay - dem
    else return 5;
}

int billMoto(parkingLot* head, char time_out[30], char plate[30]) {
    if (findVehicle(head, plate) == -1) return -1;
    parkingLot* current = head;
    for (int i = 0; i < findVehicle(head, plate); i++) current = current->next;

    int in_day = check_day(current->time_in);
    int out_day = check_day(time_out);

    if (in_day && out_day) return 3;
    else if (!in_day && !out_day && (strcmp(current->time_in, day) > 0 || strcmp(time_out, night) < 0)) return 5;
    else if ((!in_day && out_day) || (in_day && !out_day)) return 8;
    else return 13;
}

void list(parkingLot* head) {
    while (head != NULL) {
        printf("%s\n", head->plate);
        head = head->next;
    }
}

int main() {
    parkingLot* head = NULL;
    int billall = 0;

    while (1) {
        char input1[30];
        scanf("%s", input1);

        if (!strcmp(input1, "*")) break;
        char plate[30];
        scanf("%s", plate);
        addVehicle(&head, input1, plate);
    }

    while (1) {
        char input2[30];
        scanf("%s", input2);

        if (!strcmp(input2, "***")) break;

        else if (!strcmp(input2, "list")) {
            list(head);
        }

        else if (!strcmp(input2, "find")) {
            char plate[30];
            scanf("%s", plate);
            printf("%d\n", findVehicle(head, plate));
        }

        else if (!strcmp(input2, "in")) {
            char time_in[30], plate[30];
            scanf("%s %s", time_in, plate);

            if (findVehicle(head, plate) == -1) {
                //TH khong co xe trong bai
                addVehicle(&head, time_in, plate);
                printf("1\n");
            }
            else {
                printf("0\n");
            }
        }

        else if (!strcmp(input2, "out")) {
            char time_out[30], plate[30];
            scanf("%s %s", time_out, plate);

            if (findVehicle(head, plate) == -1) {
                printf("0\n");
            }
            else {
                if (strcmp(plate, "xxxx") < 0) billall += billMoto(head, time_out, plate);
                else billall += billBike(head, time_out, plate);
                deleteVehicle(&head, time_out, plate);
                printf("1\n");
            }
        }

        else if (!strcmp(input2, "cnt-moto")) {
            printf("%d\n", cnt_moto(head));
        }

        else if (!strcmp(input2, "bill")) {
            char time_out[30], plate[30];
            scanf("%s %s", time_out, plate);

            if (strcmp(plate, "xxxx") < 0) {
                printf("%d\n", billMoto(head, time_out, plate));
            }
            else {
                printf("%d\n", billBike(head, time_out, plate));
            }
        }

        else if (!strcmp(input2, "billall")) {
            printf("%d\n", billall);
        }
    }
}