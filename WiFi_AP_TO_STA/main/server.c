#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"
#include "driver/gpio.h"
#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "connect.h"
#include "esp_wifi.h"

#define LED 2
#define TAG "SERVER"

static esp_err_t on_url_hit(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    esp_vfs_spiffs_conf_t config = {
        .base_path = "/spiffs",  /*!< File path prefix associated with the filesystem. */
        .partition_label = NULL, /*!< Optional, label of SPIFFS partition to use. If set to NULL, first partition with subtype=spiffs will be used. */
        .max_files = 5,          /*!< Maximum files that could be open at the same time. */
        .format_if_mount_failed = false};
    esp_vfs_spiffs_register(&config);

    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char path[600];
    sprintf(path, "/spiffs%s", req->uri);
    if (strcmp(path, "/spiffs/") == 0)
    {
        sprintf(path, "/spiffs/%s", "index.html");
    }
    //style.css
    char *ptr = strrchr(path, '.');
    if (strcmp(ptr, ".css") == 0)
    {
        ESP_LOGI(TAG, "setting mime type to css");
        httpd_resp_set_type(req, "text/css");
    }
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        httpd_resp_send_404(req);
        return ESP_OK;
    }

    char lineRead[256];
    while (fgets(lineRead, sizeof(lineRead), file))
    {
        httpd_resp_sendstr_chunk(req, lineRead);
    }
    httpd_resp_sendstr_chunk(req, NULL);
    esp_vfs_spiffs_unregister(NULL);
    return ESP_OK;
}

static esp_err_t on_get_temp(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char *message = "{\"temp\": 24}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

void resetWifi(void *params)
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    esp_wifi_stop();
    xSemaphoreGive(initSemaphore);
    vTaskDelete(NULL);
}

static esp_err_t on_setwifi_set(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char buf[150];
    memset(&buf, 0, sizeof(buf));
    httpd_req_recv(req, buf, req->content_len);
    char *ssid = strtok(buf, "\r\n");
    char *pass = strtok(NULL, "\r\n");

    ssid = strchr(ssid, '=') + 1;
    pass = strchr(pass, '=') + 1;

    printf("ssid: %s pass: %s\n", ssid, pass);

    nvs_flash_init();
    nvs_handle_t nvs;
    nvs_open("wifiCreds", NVS_READWRITE, &nvs);
    nvs_set_str(nvs, "ssid", ssid);
    nvs_set_str(nvs, "pass", pass);
    nvs_close(nvs);

    httpd_resp_set_status(req, "303");
    httpd_resp_set_hdr(req, "Location", "/wifi-set.html");
    httpd_resp_send(req, NULL, 0);

    xTaskCreate(resetWifi, "Reset Wifi", 1024 * 2, NULL, 15, NULL);
    return ESP_OK;
}

static esp_err_t on_led_set(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char buf[150];
    memset(&buf, 0, sizeof(buf));
    httpd_req_recv(req, buf, req->content_len);
    cJSON *payload = cJSON_Parse(buf);
    cJSON *isLedOn = cJSON_GetObjectItem(payload, "isLedOn");
    gpio_set_level(LED, cJSON_IsTrue(isLedOn));
    cJSON_Delete(payload);
    ESP_LOGI(TAG, "%s", buf);
    httpd_resp_set_status(req, "204 NO CONTENT");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

void IntializedLed()
{
    gpio_pad_select_gpio(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);
}

void RegisterEndPoints(void)
{
    IntializedLed();
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;
    ESP_LOGI(TAG, "Starting Server");
    if (httpd_start(&server, &config) != ESP_OK)
    {
        ESP_LOGI(TAG, "Could not start the server");
    }

    httpd_uri_t temparature_end_point_config = {
        .uri = "/api/temp",
        .method = HTTP_GET,
        .handler = on_get_temp};
    httpd_register_uri_handler(server, &temparature_end_point_config);

    httpd_uri_t led_end_point_config = {
        .uri = "/api/led",
        .method = HTTP_POST,
        .handler = on_led_set};
    httpd_register_uri_handler(server, &led_end_point_config);

    httpd_uri_t setwifi_end_point_config = {
        .uri = "/api/setwifi",
        .method = HTTP_POST,
        .handler = on_setwifi_set};
    httpd_register_uri_handler(server, &setwifi_end_point_config);

    httpd_uri_t first_end_point_config = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = on_url_hit};
    httpd_register_uri_handler(server, &first_end_point_config);
}