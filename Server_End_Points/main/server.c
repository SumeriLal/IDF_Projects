#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"

#define TAG "SERVER"

static esp_err_t on_url_hit(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char *message = "Hello World !";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_get_temp(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char *message = "{\"temp\": 24}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_led_set(httpd_req_t *req)
{
    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char buf[150];
    memset(&buf, 0, sizeof(buf));

    httpd_req_recv(req, buf, req->content_len);
    ESP_LOGI(TAG, "%s", buf);
    httpd_resp_set_status(req, "204 NO CONTENT");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

void RegisterEndPoints(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    ESP_LOGI(TAG, "Starting Server");
    if (httpd_start(&server, &config) != ESP_OK)
    {
        ESP_LOGI(TAG, "Could not start the server");
    }
    httpd_uri_t first_end_point_config = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = on_url_hit};
    httpd_register_uri_handler(server, &first_end_point_config);

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
}