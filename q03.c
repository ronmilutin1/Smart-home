#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // For sleep function

// Define a structure for the smart home state
typedef struct {
    bool lamp1;
    bool lamp2;
    bool lamp3;
    int dimmerALevel; // 0 to 4
    int dimmerBLevel; // 0 to 4
    int temperatureRoomLevel; // 0 to 9
} SmartHomeState;
// Function prototypes
void initializeSmartHome(SmartHomeState *state);
void updateLighting(SmartHomeState *state, bool lamp1, bool lamp2, bool lamp3, int dimmerA, int
dimmerB);
void updateTemperature(SmartHomeState *state, int temperature);
void printSmartHomeState(const SmartHomeState *state);
void drawRoom(const SmartHomeState *state);
bool isValidInput(char d);
void getSimCode(int arr[]);

int main() {
    SmartHomeState state;
    int i, simcode[5];
    getSimCode(simcode);//It convert from char digits into integer digits
    initializeSmartHome(&state);
    // Simulate different situations
    for (i = 0; i < 5; i++) {
        //update new home state base on the given code (e.g 24553)
        updateLighting(&state, i % simcode[0] == 0, i % simcode[1] == 0, i % simcode[2] == 0, i % simcode[3],
                       (4 - i) % simcode[4]);
        updateTemperature(&state, i);
        printSmartHomeState(&state);
        drawRoom(&state);
        sleep(1); // sleep for 1 second
    }
    return 0;
}


void initializeSmartHome(SmartHomeState *state) {
    // Set default values for the SmartHomeState members
    state->lamp1 = 0;
    state->lamp2 = 0;
    state->lamp3 = 0;
    state->dimmerALevel = 0;
    state->dimmerBLevel = 0;
    state->temperatureRoomLevel = 0;
}

void updateLighting(SmartHomeState *state, bool lamp1, bool lamp2, bool lamp3, int dimmerA, int dimmerB){
    state->lamp1 = lamp1;
    state->lamp2 = lamp2;
    state->lamp3 = lamp3;
    state->dimmerALevel = dimmerA;
    state->dimmerBLevel = dimmerB;
}

void updateTemperature(SmartHomeState *state, int temperature){
    state->temperatureRoomLevel = temperature;
}

void printSmartHomeState(const SmartHomeState *state){
    printf("Room State:\n");
    printf("Lamps: 1[%s] 2[%s] 3[%s]\n",
           state->lamp1 ? "ON" : "OFF",
           state->lamp2 ? "ON" : "OFF",
           state->lamp3 ? "ON" : "OFF");
    printf("Dimmer Levels: A[%d] B[%d]\n", state->dimmerALevel,state->dimmerBLevel);
    printf("Temperature: %d°C\n",state->temperatureRoomLevel);
}

void drawRoom(const SmartHomeState *state){
    printf("Lamp 1: ");
    if (state->lamp1){
        for (int i=0; i < state->dimmerALevel+1; i++){
            printf("*");
        }
        printf("\n");
    }
    else printf("-\n");


    printf("Lamp 2: ");
    if (state->lamp2){
        for (int i=0; i < state->dimmerALevel+1; i++){
            printf("*");
        }
        printf("\n");
    }
    else printf("-\n");


    printf("Lamp 3: ");
    if (state->lamp3){
        for (int i=0; i < state->dimmerBLevel+1; i++){
            printf("*");
        }
        printf("\n");
    }
    else printf("-\n");

    printf("Temperature: ");
    for (int i=0; i < state->temperatureRoomLevel+1; i++){
        printf("-");
    }
    printf("\n");
}

bool isValidInput(char d){
    return (d >= '1' && d <= '5');
}

void getSimCode(int arr[]) {
    char userInput[6]; // limit the input to 6 characters
    while (1) {
        printf("Simulation senario code: Enter Five digits without spaces (1-5): ");
        scanf("%5s[^\n]", userInput);

        //discard any remaining characters in the buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF){
        };

        // Check if the input has exactly 5 characters
        int l =0;
        while (userInput[l] != '\0' && l<6) {
            l++;
        }
        if (l != 5) {
            printf("Invalid input. Please enter digits from 1 to 5 only.\n");
            continue;
        }

        // Check if all characters are digits
        bool validInput = true;
        for (int i = 0; userInput[i] != '\0'; ++i) {
            if (!isValidInput(userInput[i])) {
                validInput = false;
                break;
            }
        }
        if (!validInput) {
            printf("Invalid input. Please enter digits from 1 to 5 only.\n");
        } else {
            // Convert the chars to ints
            for (int i = 0; i < 5; ++i) {
                arr[i] = userInput[i] - '0';
            }
            break; // Break out of the loop if input is valid
        }
    }

    // Print the valid array
    printf("You entered: %d, %d, %d, %d, %d\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
}