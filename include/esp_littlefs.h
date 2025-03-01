#ifndef ESP_LITTLEFS_H__
#define ESP_LITTLEFS_H__

#include "esp_err.h"
#include <sys/types.h>
#include <sys/reent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/poll.h>
#include <string.h>
#include "sdkconfig.h"

#include "littlefs/lfs.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#include <dirent.h>
#endif

#define ESP_LITTLEFS_VERSION_NUMBER "1.5.1"
#define ESP_LITTLEFS_VERSION_MAJOR 1
#define ESP_LITTLEFS_VERSION_MINOR 5
#define ESP_LITTLEFS_VERSION_PATCH 1

/**
 *Configuration structure for esp_vfs_littlefs_register.
 */
typedef struct {
    const char *base_path;            /**< Mounting point. */
    const char *partition_label;      /**< Label of partition to use. */
    uint8_t format_if_mount_failed:1; /**< Format the file system if it fails to mount. */
    uint8_t dont_mount:1;             /**< Don't attempt to mount or format. Overrides format_if_mount_failed */
} esp_vfs_littlefs_conf_t;

/**
 * Register and mount littlefs to VFS with given path prefix.
 *
 * @param   conf                      Pointer to esp_vfs_littlefs_conf_t configuration structure
 *
 * @return  
 *          - ESP_OK                  if success
 *          - ESP_ERR_NO_MEM          if objects could not be allocated
 *          - ESP_ERR_INVALID_STATE   if already mounted or partition is encrypted
 *          - ESP_ERR_NOT_FOUND       if partition for littlefs was not found
 *          - ESP_FAIL                if mount or format fails
 */
esp_err_t esp_vfs_littlefs_register(const esp_vfs_littlefs_conf_t * conf);

/**
 * Unregister and unmount littlefs from VFS
 *
 * @param partition_label  Label of the partition to unregister.
 *
 * @return  
 *          - ESP_OK if successful
 *          - ESP_ERR_INVALID_STATE already unregistered
 */
esp_err_t esp_vfs_littlefs_unregister(const char* partition_label);

/**
 * Check if littlefs is mounted
 *
 * @param partition_label  Label of the partition to check.
 *
 * @return  
 *          - true    if mounted
 *          - false   if not mounted
 */
bool esp_littlefs_mounted(const char* partition_label);

/**
 * Format the littlefs partition
 *
 * @param partition_label  Label of the partition to format.
 * @return  
 *          - ESP_OK      if successful
 *          - ESP_FAIL    on error
 */
esp_err_t esp_littlefs_format(const char* partition_label);

/**
 * Get information for littlefs
 *
 * @param partition_label           Optional, label of the partition to get info for.
 * @param[out] total_bytes          Size of the file system
 * @param[out] used_bytes           Current used bytes in the file system
 *
 * @return  
 *          - ESP_OK                  if success
 *          - ESP_ERR_INVALID_STATE   if not mounted
 */
esp_err_t esp_littlefs_info(const char* partition_label, size_t *total_bytes, size_t *used_bytes);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
