#include "ring_buffer.h"

/**
 * @brief Initializes the control struct of the ring buffer.
 * @param ring_buffer: Pointer to the ring buffer structure to be initialized.
 * @param buffer: Pointer to the data buffer used for the ring buffer.
 * @param capacity: Capacity of the ring buffer.
 */
void ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *buffer, uint16_t capacity)
{
	ring_buffer->buffer = buffer;
	ring_buffer->capacity = capacity;

	ring_buffer->head = 0;
	ring_buffer->tail = 0;
	ring_buffer->is_full = 0;
}

/**
 * @brief Adds a data element to the ring buffer.
 * @param ring_buffer: Pointer to the ring buffer structure.
 * @param data: The value to be added.
 * @return 1 if the operation was successful, 0 if the buffer is full.
 */
uint8_t ring_buffer_put(ring_buffer_t *ring_buffer, uint8_t data)
{
	ring_buffer->buffer[ring_buffer->head] = data;
	ring_buffer->head = (ring_buffer->head + 1) % ring_buffer->capacity;

	if (ring_buffer->is_full != 0) {
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;
	}

	if (ring_buffer->head == ring_buffer->tail) {
		ring_buffer->is_full = 1;
		return 0; // Buffer is full
	}
	return 1; // Operation successful
}

/**
 * @brief Reads a data element from the ring buffer.
 * @param ring_buffer: Pointer to the ring buffer structure.
 * @param data: Pointer to the address where the read data will be stored.
 * @return 1 if the operation was successful, 0 if the buffer is empty.
 */
uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data)
{
	if (ring_buffer_is_empty(ring_buffer) == 0) {
		*data = ring_buffer->buffer[ring_buffer->tail];
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;
		ring_buffer->is_full = 0;
		return 1; // Operation successful
	}
	return 0; // Buffer is empty
}

/**
 * @brief Returns the size of the ring buffer.
 * @param ring_buffer: Pointer to the ring buffer structure.
 * @return The size of the ring buffer.
 */
uint16_t ring_buffer_size(ring_buffer_t *ring_buffer)
{
	uint16_t size = 0;

	if ((ring_buffer->is_full == 0) && (ring_buffer->tail <= ring_buffer->head)) {
		size = ring_buffer->head - ring_buffer->tail;
	} else {
		size = ring_buffer->head + (ring_buffer->capacity - ring_buffer->tail);
	}

	return size;
}

/**
 * @brief Checks if the buffer is empty.
 * @param ring_buffer: Pointer to the ring buffer structure.
 * @return 1 if the buffer is empty, 0 otherwise.
 */
uint8_t ring_buffer_is_empty(ring_buffer_t *ring_buffer)
{
	return ((ring_buffer->is_full == 0) && (ring_buffer->tail == ring_buffer->head));
}

/**
 * @brief Checks if the buffer is full.
 * @param ring_buffer: Pointer to the ring buffer structure.
 * @return 1 if the buffer is full, 0 otherwise.
 */
uint8_t ring_buffer_is_full(ring_buffer_t *ring_buffer)
{
	return (ring_buffer->is_full != 0);
}

/**
 * @brief Resets the buffer to be empty.
 * @param ring_buffer: Pointer to the ring buffer structure.
 */
void ring_buffer_reset(ring_buffer_t *ring_buffer)
{
	ring_buffer->tail = 0;
	ring_buffer->head = 0;
	ring_buffer->is_full = 0;
}

