#include "gui.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

// External declaration of the "locked" image
extern const uint8_t locked[];

/**
 * @brief Initializes the GUI by initializing the SSD1306 display.
 */
void GUI_init(void)
{
    ssd1306_Init();
    GUI_locked();
}

/**
 * @brief Displays an "invalid" message on the screen.
 */
void GUI_invalid(void)
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString("invalid", Font_16x26, White);
    ssd1306_UpdateScreen();
}

/**
 * @brief Displays a "Locked" message and instructions on the locked screen.
 */
void GUI_locked(void)
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(20, 5);
    ssd1306_WriteString("Locked", Font_16x26, White);
    ssd1306_SetCursor(7, 30);
    ssd1306_WriteString("1: Start typing", Font_6x8, White);
    ssd1306_SetCursor(18, 37);
    ssd1306_WriteString("password", Font_6x8, White);
    ssd1306_SetCursor(7, 47);
    ssd1306_WriteString("2: Lock screen", Font_6x8, White);
    ssd1306_UpdateScreen();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

/**
 * @brief Displays an "Unlocked" message on the screen.
 */
void GUI_unlocked(void)
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString("Unlocked", Font_16x26, White);
    ssd1306_UpdateScreen();
}

/**
 * @brief Displays a "New PW:" message on the screen for updating the password.
 */
void GUI_update_password_init(void)
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString("New PW:", Font_16x26, White);
    ssd1306_UpdateScreen();
}

/**
 * @brief Displays a "Start PW" message on the screen for initiating password input.
 */
void GUI_start_password_init(void)
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(5, 5);
    ssd1306_WriteString("Start PW", Font_16x26, White);
    ssd1306_UpdateScreen();
}

/**
 * @brief Displays the updated password on the screen.
 * @param password: Pointer to the password to be displayed.
 */
void GUI_update_password(uint8_t *password)
{
    ssd1306_SetCursor(10, 35);
    ssd1306_WriteString((char *)password, Font_7x10, White);
    ssd1306_UpdateScreen();
}

/**
 * @brief Displays a "Success!" message on the screen for a successful password update.
 */
void GUI_update_password_success(void)
{
    ssd1306_SetCursor(5, 35);
    ssd1306_WriteString("Success!", Font_16x26, White);
    ssd1306_UpdateScreen();
}
