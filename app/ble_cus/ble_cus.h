#ifndef BLE_CUS_H__
#define BLE_CUS_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ble.h"
#include "ble_srv_common.h"

/**@brief   Macro for defining a ble_hrs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_CUS_DEF(_name)                                                                          \
static ble_cus_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_cus_on_ble_evt, &_name)



// CUSTOM_SERVICE_UUID_BASE 9b81d05c-72b2-11ee-b962-0242ac120002

#define CUSTOM_SERVICE_UUID_BASE         {0x02, 0x00, 0x12, 0xAC, 0x42, 0x02, 0x62, 0xB9, \
                                          0xEE, 0x11, 0xB2, 0x72, 0x5C, 0xD0, 0x81, 0x9B}

#define CUSTOM_SERVICE_UUID               0x1400
#define CUSTOM_VALUE_CHAR_UUID            0x1401


#define MAXIMUM_PICTURE_SIZE 1024
#define MAX_JUNK_LENGTH 32
																					
/**@brief Custom Service event type. */
typedef enum
{
    BLE_CUS_EVT_NOTIFICATION_ENABLED,                             /**< Custom value notification enabled event. */
    BLE_CUS_EVT_NOTIFICATION_DISABLED,                             /**< Custom value notification disabled event. */
    BLE_CUS_EVT_DISCONNECTED,
    BLE_CUS_EVT_CONNECTED,
    BLE_CUS_EVT_EINK
} ble_cus_evt_type_t;

/**@brief Custom Service event. */
typedef struct
{
    ble_cus_evt_type_t evt_type;                                  /**< Type of event. */
    uint8_t* data;
} ble_cus_evt_t;

// Forward declaration of the ble_cus_t type.
typedef struct ble_junk ble_cus_t;

/**@brief Custom Service event handler type. */
typedef void (*ble_cus_evt_handler_t) (ble_cus_t * p_bas, ble_cus_evt_t * p_evt);

/**@brief Custom Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_cus_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Custom Service. */
    uint8_t                       initial_custom_value;           /**< Initial custom value */
    ble_srv_cccd_security_mode_t  custom_value_char_attr_md;     /**< Initial security level for Custom characteristics attribute */
} ble_cus_init_t;

/**@brief Custom Service structure. This contains various status information for the service. */
struct ble_junk
{
  ble_cus_evt_handler_t evt_handler; /**< To be called for handling events in the Service. */
  uint16_t service_handle; /**< Service Handle (as provided by the BLE stack). */
  ble_gatts_char_handles_t custom_value_handles; /**< Handle to the characteristic. */
  uint16_t conn_handle; /**< Handle of the current connection. */
  uint8_t uuid_type; /**< where the custom uuid reference lives */
  uint8_t junk[MAX_JUNK_LENGTH]; /**< Contains the actual payload of the package. */
  uint8_t max_junk_len; /**< Characteristic length, adjusted according to the ATT MTU. */
};

// Defines a structure to keep track of the received picture chunks
typedef struct picture_reassembler {
  uint8_t* data;            /** Pointer to the reassembled picture data */
  uint16_t total_length;    /** Total length of the picture */
  uint16_t received_length; /** Length of received data so far */
} picture_reassembler_t;

// Initialize the reassembler
inline void initialize_picture_reassembler(picture_reassembler_t* reassembler, uint16_t length) {
  reassembler->data = (uint8_t*)malloc(length);
  reassembler->total_length = length;
  reassembler->received_length = 0;
}

// Cleanup resources used by the reassembler
inline void cleanup_picture_reassembler(picture_reassembler_t* reassembler) {
  free(reassembler->data);
  reassembler->data = NULL;
}

// The Method called every time a new package with a new chunk of data arrives
//static void on_characteristic_value_write(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt);




/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_cus       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_cus_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Custom(eink) Service.
 *
 * @note 
 *
 * @param[in]   p_cus      Custom Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Function for updating the custom value.
 *
 * @details The application calls this function when the cutom value should be updated. If
 *          notification has been enabled, the custom value characteristic is sent to the client.
 *
 * @note 
 *       
 * @param[in]   p_bas          Custom Service structure.
 * @param[in]   Custom value 
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */

uint32_t ble_cus_custom_value_update(ble_cus_t * p_cus, uint8_t custom_value);

#endif // BLE_CUS_H__
