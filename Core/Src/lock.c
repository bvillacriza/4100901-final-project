#include "lock.h"
#include "ring_buffer.h"
#include "keypad.h"
#include "main.h"
#include "gui.h"

#include <stdio.h>
#include <string.h>

// Maximum length of the password
#define MAX_PASSWORD 12

// Default password
uint8_t password[MAX_PASSWORD] = "1992";

// Buffer and ring buffer for keypad input
uint8_t keypad_buffer[MAX_PASSWORD];
ring_buffer_t keypad_rb;

// External variable for keypad events
extern volatile uint16_t keypad_event;

// Function to get a single key press from the keypad
static uint8_t lock_get_passkey(void)
{
    // Wait for a key press
    while (ring_buffer_size(&keypad_rb) == 0) {
        // Poll the keypad for events
        uint8_t key_pressed = keypad_run(&keypad_event);

        // If a key is pressed, add it to the ring buffer
        if (key_pressed != KEY_PRESSED_NONE) {
            ring_buffer_put(&keypad_rb, key_pressed);
        }
    }

    // Retrieve the key pressed from the ring buffer
    uint8_t key_pressed;
    ring_buffer_get(&keypad_rb, &key_pressed);

    // Check if the key pressed is '*' or '#' (special keys)
    if (key_pressed == '*' || key_pressed == '#') {
        return 0xFF;
    }

    return key_pressed;
}

// Function to get a new password from the user
static uint8_t lock_get_password(void)
{
    uint8_t idx = 0;
    uint8_t passkey = 0;
    uint8_t new_password[MAX_PASSWORD];
    memset(new_password, 0, MAX_PASSWORD);
    uint8_t password_shadow[MAX_PASSWORD + 1] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};

    // Loop to get a new password until a special key is pressed
    while (passkey != 0xFF) {
        // Update the GUI to show the entered password
        GUI_update_password(password_shadow);

        // Get a key press from the keypad
        passkey = lock_get_passkey();

        // Update the password display in the GUI
        password_shadow[idx] = '*';
        new_password[idx++] = passkey;
        GUI_update_password(new_password);

        // Delay to make the password entry visible
        HAL_Delay(200);
    }

    // If a valid password is entered, update the password and show success
    if (idx > 1) {
        memcpy(password, new_password, MAX_PASSWORD);
        GUI_update_password_success();
    } else {
        // If the entered password is too short, indicate failure
        GUI_locked();
        return 0;
    }

    return 1;
}

// Function to validate the entered password
static uint8_t lock_validate_password(void)
{
    uint8_t password_shadow[MAX_PASSWORD + 1] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
    uint8_t sequence[MAX_PASSWORD];
    uint8_t seq_len = ring_buffer_size(&keypad_rb);

    // Update the GUI to show the entered password
    GUI_update_password(password_shadow);

    // Retrieve the entire sequence from the ring buffer
    for (uint8_t idx = 0; idx < seq_len; idx++) {
        ring_buffer_get(&keypad_rb, &sequence[idx]);
    }

    // Compare the entered sequence with the stored password
    if (memcmp(sequence, password, 4) == 0) {
        return 1; // Password is valid
    }

    return 0; // Password is invalid
}

// Function to update the password by validating the existing one
static void lock_update_password(void)
{
    // If the entered password is valid, initiate the password update process
    if (lock_validate_password() != 0) {
        GUI_update_password_init();
        lock_get_password();
    } else {
        // If the entered password is invalid, indicate failure
        GUI_locked();
    }
}

// Function to open the lock by validating the entered password
static void lock_open_lock(void)
{
    // If the entered password is valid, unlock the GUI
    if (lock_validate_password() != 0) {
        GUI_unlocked();
    } else {
        // If the entered password is invalid, indicate failure
        GUI_locked();
    }
}

// Initialization function for the lock system
void lock_init(void)
{
    ring_buffer_init(&keypad_rb, keypad_buffer, 12); // Initialize keypad ring buffer
    GUI_init(); // Initialize the GUI
}

// Handler function for keypad input
void lock_sequence_handler(uint8_t key)
{
    // Start the password initialization screen in the GUI
    GUI_start_password_init();

    // Display variables for password entry
    uint8_t password_shadow[MAX_PASSWORD + 1] = {'-'};
    uint8_t new_password[MAX_PASSWORD];
    uint8_t idx = 0;

    // Update the GUI to show the entered password
    GUI_update_password(password_shadow);

    // Update the password display with the pressed key
    password_shadow[idx] = '*';
    new_password[idx++] = key;
    GUI_update_password(new_password);

    // Delay to make the key press visible
    HAL_Delay(100);

    // Update the GUI to hide the pressed key
    GUI_update_password(password_shadow);

    // Perform actions based on the pressed key
    if (key == '*') {
        lock_update_password(); // Update the password
    } else if (key == '#') {
        lock_open_lock(); // Open the lock
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // Set GPIO pin high (example action)
    } else {
        ring_buffer_put(&keypad_rb, key); // Put the pressed key in the ring buffer
    }
}
