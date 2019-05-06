
/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 *
 * @defgroup ble_sdk_srv_sg Biopotential Measurement Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Biopotential Measurement Service module.
 *
 * @details This module implements the Biopotential Measurement Service with the Voltage characteristic.
 *          During initialization it adds the Biopotential Measurement Service and Voltage characteristic
 *          to the BLE stack dataBISe. Optionally it can also add a Report Reference descriptor
 *          to the Battery Level characteristic (used when including the Biopotential Measurement Service in
 *          the HID service).
 *
 *          If specified, the module will support notification of the Battery Level characteristic
 *          through the ble_sg_battery_level_update() function.
 *          If an event handler is supplied by the application, the Biopotential Measurement Service will
 *          generate Biopotential Measurement Service events to the application.
 *
 * @note The application must propagate BLE stack events to the Biopotential Measurement Service module by calling
 *       ble_sg_on_ble_evt() from the from the @ref ble_stack_handler callback.
 */

#ifndef BLE_SG_H__
#define BLE_SG_H__

#include "ble.h"
#include "ble_srv_common.h"
#include <stdint.h>

// Base UUID
#define BMS_UUID_BASE {0x57, 0x80, 0xD2, 0x94, 0xA3, 0xB2, 0xFE, 0x39, 0x5F, 0x87, 0xFD, 0x35, 0x00, 0x00, 0x8B, 0x22}

// Service UUID
#define BLE_UUID_SG_MEASUREMENT_SERVICE 0xA730

// Characteristic UUIDs
#define BLE_UUID_SG_CH1_CHAR 0xA731

#define SG_PACKET_LENGTH 40

/**@brief Biopotential Measurement Service init structure. This contains all options and data needed for
 *        initialization of the service. */
typedef struct
{
  uint8_t uuid_type;
  uint16_t conn_handle;    /**< Event handler to be called for handling events in the Biopotential Measurement Service. */
  uint16_t service_handle; /**< Handle of ble Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t sg_ch1_handles; /**< Handles related to the our body V measure characteristic. */
  uint8_t sg_ch1_buffer[SG_PACKET_LENGTH]; //246 or 4* = 
  uint16_t sg_ch1_count;
} ble_sg_t;

void ble_sg_service_init(ble_sg_t *p_sg);

/**@brief Biopotential Measurement Service BLE stack event handler.
 *
 * @details Handles all events from the BLE stack of interest to the Biopotential Measurement Service.
 *
 * @param[in]   p_sg      Biopotential Measurement Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_sg_on_ble_evt(ble_sg_t *p_sg, ble_evt_t *p_ble_evt);

/**@brief function for updating/notifying BLE of new value.
*
*/

void ble_sg_update_1ch(ble_sg_t *p_sg);

#endif // BLE_SG_H__
