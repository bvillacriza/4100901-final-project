#include "gui.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"


extern const uint8_t locked[];


void GUI_init(void)
{
	ssd1306_Init();
	GUI_locked();
}

void GUI_invalid(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString("invalid", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_locked(void)
{
	ssd1306_Fill(Black);
    ssd1306_SetCursor(20, 5);
    ssd1306_WriteString("Locked", Font_16x26, White);
    ssd1306_SetCursor(7, 30);
    ssd1306_WriteString("1:Empezar a escribir", Font_6x8, White);
    ssd1306_SetCursor(18, 37);
    ssd1306_WriteString("contraseña", Font_6x8, White);
    ssd1306_SetCursor(7, 47);
    ssd1306_WriteString("2:Pantalla de bloqueo", Font_6x8, White);
    ssd1306_UpdateScreen();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

}

void GUI_unlocked(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString("Unlocked", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_update_password_init(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString("New PW:", Font_16x26, White);
	ssd1306_UpdateScreen();
}
void GUI_start_password_init(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(5, 5);
	ssd1306_WriteString("Star PW", Font_16x26, White);
	ssd1306_UpdateScreen();
}

void GUI_update_password(uint8_t *password)
{
	ssd1306_SetCursor(10, 35);
	ssd1306_WriteString((char *)password, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void GUI_update_password_success(void)
{
	ssd1306_SetCursor(5, 35);
	ssd1306_WriteString("Success!", Font_16x26, White);
	ssd1306_UpdateScreen();
}
