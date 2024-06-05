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
int billBike(parkingLot* head, char time_out[30], char plate[30]) {
	int bill = 0;
	if (findVehicle(head, plate) == -1) return -1;
	parkingLot* current = head;
	for (int i = 0; i < findVehicle(head, plate); i++) current = current->next;
	if (strcmp(current->time_in, "06:00:00") < 0) {
		if (strcmp(time_out, "06:00:00") < 0) bill = 2;
		else if (strcmp(time_out, "06:00:00") > 0 && strcmp(time_out, "18:00:00") < 0) bill = 3;
		else bill = 5;
	}
	else if (strcmp(current->time_in, "06:00:00") > 0 && strcmp(current->time_in, "18:00:00") < 0) {
		if (strcmp(time_out, "18:00:00") < 0) bill = 1;
		else bill = 3;
	}
	else bill = 2;
	return bill;
}
int billMoto(parkingLot* head, char time_out[30], char plate[30]) {
	int bill = 0;
	if (findVehicle(head, plate) == -1) return -1;
	parkingLot* current = head;
	for (int i = 0; i < findVehicle(head, plate); i++) current = current->next;
	if (strcmp(current->time_in, "06:00:00") < 0) {
		if (strcmp(time_out, "06:00:00") < 0) bill = 5;
		else if (strcmp(time_out, "06:00:00") > 0 && strcmp(time_out, "18:00:00") < 0) bill = 8;
		else bill = 13;
	}
	else if ((strcmp(current->time_in, "06:00:00") > 0 ) && (strcmp(current->time_in, "18:00:00") < 0)){
		if (strcmp(time_out, "18:00:00") < 0) bill = 3;
		else bill = 8;
	}
	else bill = 5;
	return bill;
}
void list(parkingLot* head) {
	while (head != NULL) {
		printf("%s %s\n", head->time_in, head->plate);
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